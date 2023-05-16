#include "Chat.h"
#include "Lib/util.h"

using namespace vl;
using namespace vl::presentation;

namespace gacfred {

    Chat::Chat(const WString& _content)
    {
        content = _content;
    }

    WString Chat::GetContent() const
    {
        return content;
    }

    void Chat::SetContent(const WString& _content)
    {
        content = _content;
    }

    bool Chat::GetSeparatorVisible()
    {
        return false;
    }

    void Chat::SetSeparatorVisible(bool _visible)
    {

    }

    vl::Ptr<::vl::presentation::DocumentModel> Chat::GetRichContent(bool full)
    {
        auto tempResource = Ptr(new GuiResource);
        auto tempResourceItem = Ptr(new GuiResourceItem);
        tempResource->AddItem(L"Document", tempResourceItem);
        auto tempResolver = Ptr(new GuiResourcePathResolver(tempResource, L""));

        auto parser = GetParserManager()->GetParser<vl::glr::xml::XmlDocument>(L"XML");
        vl::collections::List<GuiResourceError> errors;

        auto xml = parser->Parse({}, L"<Doc><Content><p><![CDATA[" + EscapeCDATA(Trim(content)) + L"]]></p></Content><Styles><Style name=\"Search\"><bkcolor>#F04A3E</bkcolor></Style></Styles></Doc>", errors);
        return DocumentModel::LoadFromXml(tempResourceItem, xml, tempResolver, errors);
    }
} // gacfred