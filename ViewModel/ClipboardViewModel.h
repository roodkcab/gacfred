//
// Created by css on 23-2-6.
//

#ifndef GACFRED_CLIPBOARDVIEWMODEL_H
#define GACFRED_CLIPBOARDVIEWMODEL_H

#include "UI/Source/Gacfred.h"

namespace gacfred {

    class ClipboardViewModel : public IClipboardViewModel
    {
    private:
        vl::collections::ObservableList<vl::Ptr<ICopy>> copies;
        vl::WString search;
        CopyType type;
        vl::vint64_t selected;
		vl::Ptr<vl::EventHandler> itemChangedEventHandler;

    public:
        ClipboardViewModel();
        ~ClipboardViewModel();
        vl::WString GetSearch()override;
        void SetSearch(const vl::WString& _search)override;
        bool HandleKeyDown(::vl::presentation::compositions::GuiKeyEventArgs *arguments) override;
		vl::Ptr<vl::reflection::description::IValueObservableList> GetCopies()override;
        void AddCopy(vl::Ptr<ICopy> _copy)override;
        vl::Ptr<ICopy> GetCopy(vl::vint64_t idx)override;
        CopyType GetShowType()override;
        void SetShowType(CopyType _type)override;
    };

} // gacfred

#endif //GACFRED_CLIPBOARDVIEWMODEL_H