//
// Created by css on 2/7/23.
//

#include "ChatGPTRequest.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

namespace gacfred
{
    ChatGPTRequest::ChatGPTRequest()
    {
        http_client_config config;
        config.set_validate_certificates(false);
        client = vl::Ptr(new http_client("", config));
    }

    vl::WString ChatGPTRequest::GetAnswer(const vl::WString& question)
    {
        json::value content;
        content["content"] = json::value::string(wtoa(question).Buffer());
        http_response resp = client->request(methods::POST,
                                             uri_builder("/api/chat").to_string(),
                                             content).get();
        auto obj = resp.extract_json(true);
        return vl::atow(obj.then([](json::value obj){
            return obj[U("choices")];
        }).then([](json::value obj) {
            return obj[0];
        }).then([](json::value obj) {
            return obj[U("text")];
        }).get().as_string().c_str());
    }
}
