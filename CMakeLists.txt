cmake_minimum_required(VERSION 3.24)
project(gacfred)

set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(VCZH_DEBUG_NO_REFLECTION)

find_package(PkgConfig REQUIRED)
find_package(SqliteOrm REQUIRED)
find_package(cpprestsdk REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtkmm-3.0 sigc++-2.0)
#pkg_check_modules(gGac REQUIRED gGac GacUI)
#include_directories(./ ${gGac_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})

add_library(GacUI
        ../gGac/GacUI/Import/GacUI.cpp
        ../gGac/GacUI/Import/Vlpp.cpp
        ../gGac/GacUI/Import/Vlpp.Linux.cpp
        ../gGac/GacUI/Import/VlppOS.cpp
        ../gGac/GacUI/Import/VlppOS.Linux.cpp
        ../gGac/GacUI/Import/VlppRegex.cpp
        ../gGac/GacUI/Import/VlppReflection.cpp
        ../gGac/GacUI/Import/VlppParser.cpp
        ../gGac/GacUI/Import/VlppGlrParser.cpp
        ../gGac/GacUI/Import/VlppWorkflowLibrary.cpp
        ../gGac/GacUI/Import/Skins/DarkSkin/DarkSkin.cpp
        )

add_library(gGac
        ../gGac/Source/Services/GGacCallbackService.cpp
        ../gGac/Source/Services/GGacInputService.cpp
        ../gGac/Source/Services/GGacAsyncService.cpp
        ../gGac/Source/Services/GGacImageService.cpp
        ../gGac/Source/Services/GGacDialogService.cpp
        ../gGac/Source/Services/GGacResourceService.cpp
        ../gGac/Source/Services/GGacScreenService.cpp
        ../gGac/Source/Services/GGacClipboardService.cpp
        ../gGac/Source/Renderers/GuiSolidBorderElementRenderer.cpp
        ../gGac/Source/Renderers/GGacRenderer.cpp
        ../gGac/Source/Renderers/Gui3DBorderElementRenderer.cpp
        ../gGac/Source/Renderers/GuiSolidBackgroundElementRenderer.cpp
        ../gGac/Source/Renderers/GuiSolidLabelElementRenderer.cpp
        ../gGac/Source/Renderers/Gui3DSplitterElementRenderer.cpp
        ../gGac/Source/Renderers/GuiGradientBackgroundElementRenderer.cpp
        ../gGac/Source/Renderers/GuiImageFrameElementRenderer.cpp
        ../gGac/Source/Renderers/GuiPolygonElementRenderer.cpp
        ../gGac/Source/Renderers/GuiFocusRectangleElementRenderer.cpp
        ../gGac/Source/Renderers/GuiColorizedTextElementRenderer.cpp
        ../gGac/Source/Renderers/GuiInnerShadowElementRenderer.cpp
        ../gGac/Source/Renderers/GGacLayoutProvider.cpp
        ../gGac/Source/Renderers/GuiGGacElementRenderer.cpp
        ../gGac/Source/GGacController.cpp
        ../gGac/Source/GGacWindow.cpp
        ../gGac/Source/GGacWindowListener.cpp
        ../gGac/Source/GGacHelper.cpp
        ../gGac/Source/GGacControllerListener.cpp
        ../gGac/Source/GGacView.cpp
        ../gGac/Source/GGacCursor.cpp
        ../gGac/Source/Lib/Keybinder.c
        )
target_link_libraries(gGac GacUI ${GTK3_LIBRARIES})
include_directories(./ ../gGac/GacUI/Import ../gGac/Source ../gGac/Source/Renderers ../gGac/Source/Services ${GTK3_INCLUDE_DIRS})

add_executable(gacfred
        App.cpp
        Main.cpp
        Lib/MD5.cpp
        Lib/util.cpp
        Model/Chat.cpp
        Model/Copy.cpp
        ViewModel/MainWindowViewModel.cpp
        UI/Source/GacfredPartialClasses.cpp
        UI/Source/MainWindow.cpp
        UI/Source/ChatGPT.cpp
        UI/Source/Clipboard.cpp
        ViewModel/ClipboardViewModel.cpp
        ViewModel/ChatGPTViewModel.cpp
        Lib/Request/ChatGPTRequest.cpp)

target_link_libraries (gacfred gGac GacUI ${GTK3_LIBRARIES} X11 sqlite_orm::sqlite_orm uuid cpprestsdk::cpprest)