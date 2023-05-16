#define GAC_HEADER_USE_NAMESPACE

#include "MainWindowViewModel.h"
#include "ClipboardViewModel.h"
#include "ChatGPTViewModel.h"
#include "Lib/util.h"
#include "Lib/MD5.h"
#define UUID_SYSTEM_GENERATOR
#include "Lib/uuid.h"
#include "Model/DB.h"

using namespace vl;
using namespace vl::reflection::description;

namespace gacfred
{
	MainWindowViewModel::MainWindowViewModel()
            :hasSearch(false),
             search(L"")
	{
	}

    MainWindowViewModel::~MainWindowViewModel()
    {
    }

    WString MainWindowViewModel::GetProgram()
    {
        return program;
    }

    void MainWindowViewModel::SetProgram(const WString& _program)
    {
        if (program != _program)
        {
            program = _program;
            if (program == L"clipboard")
            {
                auto vm = vl::Ptr(new ClipboardViewModel());
                SetProgramViewModel(vm);
                view = vl::Ptr(new Clipboard(vm));
                ProgramControl->AddChild(view->GetBoundsComposition());
            }
            else if (program == L"chatgpt")
            {
                auto vm = vl::Ptr(new ChatGPTViewModel());
                SetProgramViewModel(vm);
                view = vl::Ptr(new ChatGPT(vm));
                ProgramControl->AddChild(view->GetBoundsComposition());
            }
            else
            {
                program = L"";
                if (view != nullptr)
                {
                    ProgramControl->RemoveChild(view->GetBoundsComposition());
                    view = NULL;
                    SetProgramViewModel(NULL);
                }
            }
            ProgramChanged();
        }
    }

    WString MainWindowViewModel::GetSearch()
    {
        return search;
    }

    void MainWindowViewModel::SetSearch(const WString& _search)
    {
		if (_search == L"" || search != Trim(_search))
		{
			search = Trim(_search);
			if (static_cast<bool>(programViewModel))
			{
				programViewModel->SetSearch(search);
			}
			SearchChanged();
		}
    }

    void MainWindowViewModel::ResetSearch()
    {
        SetSearch(L"");
        hasSearch = false;
    }

    Ptr<::gacfred::IProgramViewModel> MainWindowViewModel::GetProgramViewModel()
    {
        return programViewModel;
    }

    void MainWindowViewModel::SetProgramViewModel(::vl::Ptr<::gacfred::IProgramViewModel> _programViewModel)
    {
        programViewModel = _programViewModel;
        if (programViewModel != nullptr)
        {
            programViewModel->mainWindowViewModel = this;
        }
    }

    void MainWindowViewModel::HandleKeyDown(::vl::presentation::compositions::GuiKeyEventArgs *arguments)
    {
		if (arguments->code == vl::presentation::VKEY::KEY_ESCAPE)
		{
			GetCurrentController()->WindowService()->GetMainWindow()->Hide(false);
		}
		else
		{
			if (static_cast<bool>(programViewModel))
			{
				arguments->handled = programViewModel->HandleKeyDown(arguments);
				if (arguments->code == vl::presentation::VKEY::KEY_RETURN)
				{
					ResetSearch();
					vl::presentation::GetCurrentController()->WindowService()->GetMainWindow()->Hide(false);
				}
				else if (arguments->code == vl::presentation::VKEY::KEY_BACK && !hasSearch)
				{
					SetProgram(L"");
				}
				hasSearch = (search.Length() > 0);
			}
			else
			{
				if (arguments->code == vl::presentation::VKEY::KEY_RETURN)
				{
					SetProgram(search);
					ResetSearch();
				}
			}
		}
    }

	void MainWindowViewModel::Copy()
	{
		auto clipboard = vl::presentation::GetCurrentController()->ClipboardService()->ReadClipboard();
		if (clipboard->ContainsDocument())
		{
			auto doc = clipboard->GetDocument();
		}
		else
		{
			bool store = false;
			MD5 md5;
			auto id = uuids::to_string(uuids::uuid_system_generator{}());
			auto idx = atow(md5(id).c_str());
			CopyType type = CopyType::Text;
			WString doc = L"";
			if (clipboard->ContainsText())
			{
				store = true;
				doc = clipboard->GetText();
				idx = atow(md5(wtoa(doc).Buffer()).c_str());
			}
			if (clipboard->ContainsImage())
			{
				store = true;
				type = CopyType::Image;
				vint i = 0;
				auto image = clipboard->GetImage();
				auto size = image->GetFrame(0)->GetSize();
				if (size.y > 100.0) {
					size.x *= 100.0 / size.y;
					size.y = 100.0;
				}
				if (size.x > 640.0) {
					size.y *= 640.0 / size.x;
					size.x = 640;
				}
				doc += L"<img width=\"" + itow(size.x) + L"\" height=\"" + itow(size.y) + L"\" source=\"res://" + idx + L"_0\"/>";
				vl::stream::FileStream fileStream(Appdata(L"/Images/" + idx + L"_0"), vl::stream::FileStream::ReadWrite);
				console::Console::WriteLine(itow(image->GetFrame(0)->GetSize().x) + L" " + itow(image->GetFrame(0)->GetSize().y));
				image->SaveToStream(fileStream);
				fileStream.Close();
				//upload file to server
			}
			if (store)
			{
				auto copy = Ptr(new gacfred::Copy(idx, type, doc));
				DB.replace<gacfred::Copy>(*copy.Obj());
				DB.remove_all<gacfred::Copy>(where(c(&gacfred::Copy::GetIdx) == select(columns(&gacfred::Copy::GetIdx), order_by(&gacfred::Copy::GetCtime).desc(), limit(80, 1))));
				ResetSearch();
			}
		}
	}
}
