#pragma once
#include "UI/Source/Gacfred.h"

namespace gacfred
{
	class MainWindowViewModel : public vl::Object, public virtual IMainWindowViewModel
	{
	private:
        bool hasSearch;
		vl::WString search;
        vl::WString program;
        Ptr<IProgramViewModel> programViewModel;
        Ptr<GuiCustomControl> view;

	public:
		MainWindowViewModel();
        ~MainWindowViewModel();

        WString GetProgram() override;
        void SetProgram(const WString& _program) override;
        WString GetSearch() override;
        void SetSearch(const WString& _search) override;
        void ResetSearch() override;

        Ptr<::gacfred::IProgramViewModel> GetProgramViewModel() override;
        void SetProgramViewModel(::vl::Ptr<::gacfred::IProgramViewModel> _programViewModel) override;
        void HandleKeyDown(::vl::presentation::compositions::GuiKeyEventArgs *arguments) override;
		void Copy() override;
	};
}