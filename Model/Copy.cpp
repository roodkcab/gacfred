#include "Copy.h"
#include "Lib/util.h"
#include <ctime>
#include "DB.h"

using namespace vl;
using namespace vl::presentation;

namespace gacfred
{
	Copy::Copy()
	{
	}

	Copy::Copy(const vl::WString& _idx, const CopyType _type, const vl::WString& _content)
	{
		Content = _content;
        Type = _type;
		Idx = _idx;
		Ctime = std::time(0);
        SeparatorVisible = true;
	}

	Copy::Copy(const Copy& copy)
	{
        Idx = copy.Idx;
        Type = copy.Type;
		Content = copy.Content;
		Ctime = copy.Ctime;
        SeparatorVisible = true;
	}

    Copy::Copy(const Copy& copy, const vl::WString& search)
    {
        WString content = copy.Content;
        switch (copy.Type)
        {
            case CopyType::Text:
            {
                if (search.Length() > 0)
                {
                    for (vint i = 0; i < copy.Content.Length() - search.Length() + 1; i++)
                    {

                        if (Locale().ToLower(copy.Content.Sub(i, search.Length())) == Locale().ToLower(search))
                        {
                            //b i a
                            auto before = copy.Content.Sub(0, i);
                            auto after = copy.Content.Sub(i + search.Length(), copy.Content.Length() - search.Length() - i);
                            if (before.Length() > 100)
                            {
                                before = L"..." + before.Sub(before.Length() - 100, 100);
                            }
                            if (after.Length() > 100)
                            {
                                after = after.Sub(0, 100) + L"...";
                            }
                            content = EscapeCDATA(before) + L"]]><div style=\"Search\"><![CDATA[" + EscapeCDATA(content.Sub(i, search.Length())) + L"]]></div><![CDATA[" + EscapeCDATA(after);
                            break;
                        }
                    }
                    Content = content;
                }
                else
                {
                    if (content.Length() > 200)
                    {
                        Content = EscapeCDATA(content.Sub(0, 200) + L"...");
                    }
                    else
                    {
                        Content = EscapeCDATA(content);
                    }
                }
            }
            break;

            case CopyType::Image:
                Content = copy.Content;
                break;
        }

        Idx = copy.Idx;
        Type = copy.Type;
        Ctime = copy.Ctime;
        SeparatorVisible = true;
    }

    vl::WString Copy::GetIdx()const
    {
        return Idx;
    }

    void Copy::SetIdx(const vl::WString& _idx)
    {
        Idx = _idx;
    }

    CopyType Copy::GetType()const
    {
        return Type;
    }

    void Copy::SetType(CopyType _type)
    {
        Type = _type;
    }

    vl::WString Copy::GetContent()const
	{
		return Content;
	}

	void Copy::SetContent(const vl::WString& _content)
	{
		Content = _content;
	}

	Ptr<presentation::DocumentModel> Copy::GetRichContent(bool full)
	{
		auto tempResource = Ptr(new GuiResource);
		auto tempResourceItem = Ptr(new GuiResourceItem);
		tempResource->AddItem(L"Document", tempResourceItem);
		auto tempResolver = Ptr(new GuiResourcePathResolver(tempResource, L""));

		auto parser = GetParserManager()->GetParser<vl::glr::xml::XmlDocument>(L"XML");
		vl::collections::List<GuiResourceError> errors;

		auto imagePath = vl::filesystem::FilePath(Appdata(L"/Images/" + Idx + L"_0"));
		vl::WString doc = L"";
		if (imagePath.IsFile())
		{
			if (auto image = GetCurrentController()->ImageService()->CreateImageFromFile(imagePath.GetFullPath()))
			{
				auto imageItem = Ptr(new GuiResourceItem);
				imageItem->SetContent(L"Image", Ptr(new GuiImageData(image, 0)));
				tempResource->AddItem(Idx + L"_0", imageItem);
				doc = this->Content;
			}
		}
		else
		{
            if (full)
            {
                auto copy = DB.get<Copy>(Idx);
                doc = copy.Content;
            }
            else
            {
                doc = Trim(this->Content);
            }
            doc = L"<![CDATA[" + doc + L"]]>";
        }

        auto xml = parser->Parse({}, L"<Doc><Content><p>" + doc + L"</p></Content><Styles><Style name=\"Search\"><bkcolor>#F04A3E</bkcolor></Style></Styles></Doc>", errors);
        return DocumentModel::LoadFromXml(tempResourceItem, xml, tempResolver, errors);
	}


	vl::vint64_t Copy::GetCtime()const
	{
		return Ctime;
	}

	void Copy::SetCtime(const vl::vint64_t _ctime)
	{
		Ctime = _ctime;
	}

	vl::WString Copy::GetShowtime()
	{
		time_t t = std::time(0);
		if (t - Ctime < 60)
		{
			return L"moment ago";
		}
		else if (t - Ctime < 3600)
		{
            vint min = floor((t - Ctime) / 60);
            return itow(min) + (min == 1 ? L" minute" : L" minutes") + L" ago";
		}
		else if (t - Ctime < 86400)
		{
            vint hours = floor((t - Ctime) / 3600);
            return itow(hours) + (hours == 1 ? L" hour" : L" hours") + L" ago";
		}
		else
		{
            vint days = floor((t - Ctime) / 86400);
			return itow(days) + (days == 1 ? L" day" : L" days") + L" ago";
		}
	}

    bool Copy::GetSeparatorVisible()
    {
        return SeparatorVisible;
    }

    void Copy::SetSeparatorVisible(bool visible)
    {
        SeparatorVisible = visible;
        SeparatorVisibleChanged();
    }
}
