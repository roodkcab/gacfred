﻿/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

GacGen.exe Resource.xml

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#ifndef VCZH_WORKFLOW_COMPILER_GENERATED_CLIPBOARD
#define VCZH_WORKFLOW_COMPILER_GENERATED_CLIPBOARD

#include "GacfredPartialClasses.h"

#if defined( _MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#endif

namespace gacfred
{
	class Clipboard : public ::vl::presentation::controls::GuiCustomControl, public ::gacfred::ClipboardConstructor, public ::vl::reflection::Description<Clipboard>
	{
		friend class ::vl_workflow_global::__vwsnc12_Gacfred_gacfred_Clipboard_PerformChangeAnimation___vl_reflection_description_ICoroutine;
		friend struct ::vl_workflow_global::__vwsnf37_Gacfred_gacfred_Clipboard_PerformChangeAnimation_;
		friend struct ::vl_workflow_global::__vwsnf38_Gacfred_gacfred_Clipboard_PerformChangeAnimation_;
		friend struct ::vl_workflow_global::__vwsnf39_Gacfred_gacfred_Clipboard_PerformChangeAnimation__;
		friend struct ::vl_workflow_global::__vwsnf40_Gacfred_gacfred_Clipboard_PerformChangeAnimation__Resume_;
		friend class ::gacfred::ClipboardConstructor;
		friend struct ::vl_workflow_global::__vwsnf27_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf28_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf29_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf30_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf31_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf32_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf33_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf34_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf35_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf36_Gacfred_gacfred_ClipboardConstructor___vwsn_gacfred_Clipboard_Initialize_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<Clipboard>;
#endif
	public:
		::vl::vint64_t selected;
		void InstallClipboard();
		void Paste();
		::vl::vint64_t lastPosX;
		::vl::Func<double(double)> bezier;
		::vl::Ptr<::vl::presentation::controls::IGuiAnimation> anim;
	private:
		::vl::Ptr<::vl::presentation::controls::IGuiAnimation> PerformChangeAnimation(::vl::presentation::compositions::GuiBoundsComposition* backgroundBar, ::vl::vint64_t posX);
	public:
		::vl::Ptr<::gacfred::IClipboardViewModel> __vwsn_parameter_ViewModel;
		::vl::Ptr<::gacfred::IClipboardViewModel> GetViewModel();
		Clipboard(::vl::Ptr<::gacfred::IClipboardViewModel> __vwsn_ctor_parameter_ViewModel);
		void __vwsn_instance_ctor_();
		~Clipboard();

	/* USER_CONTENT_BEGIN(custom members of ::gacfred::Clipboard) */
	/* USER_CONTENT_END() */
	};

}
#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif