//
// Created by css on 23-2-6.
//

#include "ClipboardViewModel.h"
#include "Model/Copy.h"
#include "Model/DB.h"
//#include "Lib/ClipboardRequest.h"

using namespace vl;
using namespace vl::reflection::description;

namespace gacfred
{

    ClipboardViewModel::ClipboardViewModel()
			:search(L"")
    {
        /*try {
			auto content = ClipboardRequest::Instance().GetCopy();
			auto idx = content["idx"].as_string();
			int synced = DB.count(&Copy::GetIdx, where(c(&Copy::GetIdx) == WString(idx.c_str()))) >= 1;
			if (!synced) {
				auto doc = content["doc"].as_string();
				DB.replace<Copy>(Copy(doc.c_str(), idx.c_str()));
				auto images = content["images"].as_object();
				ClipboardRequest::Instance().DownloadImages(images);
			}
		}
		catch (std::exception& e) {
		}*/
		SetShowType(CopyType::None);
		itemChangedEventHandler = GetCopies()->ItemChanged.Add([this](long start, long oldCount, long newCount) {
			if (newCount > 0)
			{
				vl::presentation::controls::GetApplication()->DelayExecuteInMainThread([this](){
					static_cast<vl::presentation::controls::GuiBindableListView*>(ListView)->SetSelected(0, true);
				}, 0);
			}
		});
    }

    ClipboardViewModel::~ClipboardViewModel()
    {
		GetCopies()->ItemChanged.Remove(itemChangedEventHandler);
    }

    WString ClipboardViewModel::GetSearch()
    {
        return search;
    }

    void ClipboardViewModel::SetSearch(const WString& value)
    {
		search = Trim(value);
		std::vector<Copy> _copies;
		if (search.Length() > 0)
		{
			_copies = std::move(DB.get_all<Copy>(where(
					c(&Copy::GetType) == CopyType::Text
					and
					like(&Copy::GetContent, L"%" + EscapeSQL(search) + L"%").escape("\\")
			), order_by(&Copy::GetCtime).desc()));
		}
		else
		{
			_copies = std::move(DB.get_all<Copy>(order_by(&Copy::GetCtime).desc()));
		}

		copies.Clear();
		for (auto& copy : _copies)
		{
			copies.Add(Ptr(new Copy(copy, search)));
		}
    }

    bool ClipboardViewModel::HandleKeyDown(::vl::presentation::compositions::GuiKeyEventArgs *arguments)
    {
        switch (arguments->code)
        {
            case vl::presentation::VKEY::KEY_UP:
            case vl::presentation::VKEY::KEY_DOWN:
			{
                ListView->GetFocusableComposition()->GetEventReceiver()->keyDown.Execute(*arguments);
                return true;
			}
            case vl::presentation::VKEY::KEY_LEFT:
			{
				if (search.Length() == 0)
				{
					SetShowType((CopyType) (((int) type + 2) % 3));
				}
				return true;
			}
            case vl::presentation::VKEY::KEY_RIGHT:
			{
				if (search.Length() == 0)
				{
					SetShowType((CopyType) (((int) type + 1) % 3));
				}
				return true;
			}
            case vl::presentation::VKEY::KEY_RETURN:
			{
				if (static_cast<vl::presentation::controls::GuiBindableListView*>(ListView)->GetSelectedItemIndex() != -1)
				{
					auto item = UnboxValue<vl::Ptr<ICopy>>(static_cast<vl::presentation::controls::GuiBindableListView*>(ListView)->GetSelectedItem());
					auto clipboard = vl::presentation::GetCurrentController()->ClipboardService()->WriteClipboard();
					clipboard->SetDocument(item->GetRichContent(true));
					clipboard->Submit();
					DB.update_all(set(c(&Copy::GetCtime) = std::time(0)), where(c(&Copy::GetIdx) == item->GetIdx()));
				}
                static_cast<vl::presentation::controls::GuiBindableListView*>(ListView)->SetSelected(0, true);
				return true;
			}
        }
        return false;
    }

    vl::Ptr<IValueObservableList> ClipboardViewModel::GetCopies()
    {
        return UnboxValue<vl::Ptr<IValueObservableList>>(BoxParameter(copies));
    }

    void ClipboardViewModel::AddCopy(vl::Ptr<ICopy> _copy)
    {
        copies.Insert(0, _copy);
    }

    Ptr<ICopy> ClipboardViewModel::GetCopy(vl::vint64_t idx)
    {
        idx = (0 >= idx ? 0 : idx);
        return copies[idx];
    }

    CopyType ClipboardViewModel::GetShowType()
    {
        return type;
    }

    void ClipboardViewModel::SetShowType(CopyType _type)
    {
		type = _type;
		ShowTypeChanged();

		std::vector<Copy> _copies;
		if (type != CopyType::None)
		{
			_copies = std::move(DB.get_all<Copy>(where(c(&Copy::GetType) == type), order_by(&Copy::GetCtime).desc()));
		}
		else
		{
			_copies = std::move(DB.get_all<Copy>(order_by(&Copy::GetCtime).desc()));
		}

		copies.Clear();
		for (auto &copy: _copies)
		{
			copies.Add(Ptr(new Copy(copy, search)));
		}
    }
} // gacfred