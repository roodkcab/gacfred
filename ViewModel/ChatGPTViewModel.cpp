//
// Created by css on 2/7/23.
//

#include "ChatGPTViewModel.h"
#include "Model/Chat.h"
#include "Lib/util.h"
#include "Lib/Request/ChatGPTRequest.h"

using namespace vl;
using namespace vl::reflection::description;

namespace gacfred {

    WString ChatGPTViewModel::GetSearch()
    {
        return search;
    }

    void ChatGPTViewModel::SetSearch(const WString &_search)
    {
        search = Trim(_search);
    }

    bool ChatGPTViewModel::HandleKeyDown(::vl::presentation::compositions::GuiKeyEventArgs *arguments)
    {
        switch (arguments->code)
        {
            case vl::presentation::VKEY::KEY_UP:
            case vl::presentation::VKEY::KEY_DOWN:
                ListView->GetFocusableComposition()->GetEventReceiver()->keyDown.Execute(*arguments);
                return true;
            case vl::presentation::VKEY::KEY_RETURN:
				if (arguments->ctrl)
				{
					auto item = static_cast<vl::presentation::controls::GuiBindableListView*>(ListView)->GetSelectedItem();
					auto clipboard = vl::presentation::GetCurrentController()->ClipboardService()->WriteClipboard();
					clipboard->SetDocument(UnboxValue<vl::Ptr<IChat>>(item)->GetRichContent(true));
					clipboard->Submit();
				}
				else
				{
					auto question = search;
					if (question.Length() > 0)
					{
						chats.Insert(0, Ptr(new Chat(search)));
						mainWindowViewModel->ResetSearch();
						vl::presentation::controls::GetApplication()->InvokeAsync([=]() {
							auto answer = ChatGPTRequest::Instance().GetAnswer(question);
							vl::presentation::controls::GetApplication()->DelayExecuteInMainThread([=](){
								chats.Insert(0, Ptr(new Chat(answer)));
								static_cast<vl::presentation::controls::GuiBindableListView*>(ListView)->SetSelected(0, true);
							}, 0);
						});
					}
				}
                return true;
        }
        return false;
    }

    Ptr<IValueObservableList> ChatGPTViewModel::GetChats()
    {
        return UnboxValue<vl::Ptr<IValueObservableList>>(BoxParameter(chats));
    }

    void ChatGPTViewModel::AddChat(::vl::Ptr<::gacfred::IChat> chat)
    {
    }

    Ptr<::gacfred::IChat> ChatGPTViewModel::GetChat(::vl::vint64_t idx)
    {
    }
} // gacfred