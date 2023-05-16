#pragma once
#include "GacUI.h"
#include <cpprest/http_client.h>

namespace gacfred
{
	class ClipboardRequest
	{
    private:
        vl::Ptr<web::http::client::http_client> client;
        ClipboardRequest();

	public:
		static ClipboardRequest& Instance()
		{
			static ClipboardRequest instance;
			return instance;
		}
		void SendCopy();
		web::json::object& GetCopy();
		void DownloadImages(const web::json::object& images);
	};
}