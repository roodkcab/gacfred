#define GAC_HEADER_USE_NAMESPACE

#include "ClipboardRequest.h"
#include "Lib/util.h"

#include <cpprest/filestream.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

namespace gacfred
{
	ClipboardRequest::ClipboardRequest()
	{
		http_client_config config;
		config.set_validate_certificates(false);
		client = vl::Ptr(new http_client("http://gaclip.com", config));
	}

	void ClipboardRequest::SendCopy()
	{
	}

	json::object& ClipboardRequest::GetCopy()
	{
		http_response resp = client->request(methods::GET, uri_builder("/api/clipboard").to_string()).get();
		return resp.extract_json(true).get().as_object();
	}

	void ClipboardRequest::DownloadImages(const json::object& images)
	{
		auto kv = images;
		for (auto& [filename, url] : kv) {
			http_client dl(url["host"].as_string());
			http_response image = dl.request(methods::GET, uri_builder(url["path"].as_string()).to_string()).get();
			//ostream store = fstream::open_ostream(Appdata(L"\\Images\\" + atow(filename.c_str())).Buffer()).get();
			//image.body().read_to_end(store.streambuf()).get();
			//store.close();
		}
	}
}