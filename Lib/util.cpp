#include "util.h"

vl::WString Appdata(const vl::WString& filename)
{
#ifdef WIN32
    wchar_t* appdata = nullptr;
	size_t appdata_len;
	if (_wdupenv_s(&appdata, &appdata_len, L"APPDATA") == 0 && appdata != nullptr)
	{
		vl::WString path(appdata);
		free(appdata);
		path += L"\\GacFred";
		if (filename.Length() > 0)
		{
			path += filename;
		}
		return path;
	}
#endif
	return L"/tmp" + filename;
}

vl::WString EscapeCDATA(const vl::WString& text)
{
    //escape ]]>
    vl::WString escaped = L"";
    vl::vint j = 0;
    for (vl::vint i = 0; i <= text.Length() - 3; i++)
    {
        if (text.Sub(i, 3) == L"]]>")
        {
            escaped += text.Sub(j, i);
            escaped += L"]]]]><![CDATA[>";
            j = i + 3;
        }
    }
    escaped += text.Sub(j, text.Length() - j);
    return escaped;
}

vl::WString Trim(const vl::WString& text)
{
	int pre = 0, post = 0;
	for (int i = 0; i < text.Length(); i++)
	{
		auto c = text.Sub(i, 1);
		if (c != L"\n" && c != L"\r" && c != L" " && c != L"\t")
		{
			break;
		}
		pre = i + 1;
	}
	for (int i = 1; i <= text.Length(); i++)
	{
		auto c = text.Sub(text.Length() - i, 1);
		if (c != L"\n" && c != L"\r" && c != L" " && c != L"\t")
		{
			break;
		}
		post = i;
	}
	return text.Sub(pre, text.Length() - post - pre);
}

vl::WString EscapeSQL(const vl::WString& text)
{
	vl::WString ret = text;
	int len = text.Length();
	for (int i = 1; i <= len; i++)
	{
		auto c = text.Sub(len - i, 1);
		if (c == L"_" || c == L"%")
		{
			ret = ret.Insert(len - i, L"\\");
		}
	}
	return ret;
}