#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Gacfred.h"
#include "ViewModel/MainWindowViewModel.h"
#include "Model/DB.h"
#include "Lib/util.h"

using namespace vl::collections;
using namespace vl::stream;
using namespace gacfred;

/*void initWebkit()
{
	wkeSetWkeDllPath(L"C:\\Users\\buaac\\Projects\\gacfred\\Debug\\node.dll");
	if (!wkeInitialize()) {
		return;
	}
}*/

void initDir()
{
	auto folder = vl::filesystem::Folder(vl::filesystem::FilePath(Appdata(L"/Images")));
	if (!folder.Exists())
	{
		folder.Create(true);
	}
}

void GuiMain()
{
	//initWebkit();
	initDir();
	DB.sync_schema(true);

	FileStream fileStream(L"./Gacfred.bin", FileStream::ReadOnly);
	GetResourceManager()->LoadResourceOrPending(fileStream);
	auto viewModel = Ptr(new MainWindowViewModel());
	MainWindow window(viewModel);
	window.MoveToScreenCenter();
	viewModel->SetProgram(L"clipboard");
	GetApplication()->Run(&window);
}

