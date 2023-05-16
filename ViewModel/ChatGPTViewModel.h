//
// Created by css on 2/7/23.
//

#ifndef GACFRED_CHATGPTVIEWMODEL_H
#define GACFRED_CHATGPTVIEWMODEL_H

#include "UI/Source/Gacfred.h"

namespace gacfred {

    class ChatGPTViewModel : public IChatGPTViewModel
    {
    private:
        vl::WString search;
        vl::collections::ObservableList<vl::Ptr<IChat>> chats;

    public:
        vl::WString GetSearch() override;
        void SetSearch(const vl::WString& _search) override;
        bool HandleKeyDown(::vl::presentation::compositions::GuiKeyEventArgs *arguments) override;
		vl::Ptr<::vl::reflection::description::IValueObservableList> GetChats() override;
        void AddChat(::vl::Ptr<::gacfred::IChat> chat) override;
        vl::Ptr<::gacfred::IChat> GetChat(::vl::vint64_t idx) override;
	};

} // gacfred

#endif //GACFRED_CHATGPTVIEWMODEL_H
