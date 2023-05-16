#pragma once

#include <GacUI.h>

vl::WString Appdata(const vl::WString& filename);
vl::WString Trim(const vl::WString& text);
vl::WString EscapeCDATA(const vl::WString& text);
vl::WString EscapeSQL(const vl::WString& text);
