//
// Created by css on 2/7/23.
//

#pragma once
#include "UI/Source/Gacfred.h"

namespace gacfred {

    class Chat : public IChat
    {
    private:
        vl::WString content;

    public:
        Chat(const vl::WString& _content);
        vl::WString GetContent() const override;
        void SetContent(const vl::WString &__vwsn_value_) override;
        vl::Ptr<::vl::presentation::DocumentModel> GetRichContent(bool full) override;
        bool GetSeparatorVisible() override;
        void SetSeparatorVisible(bool __vwsn_value_) override;
    };

} // gacfred