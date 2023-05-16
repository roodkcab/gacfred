//
// Created by css on 2/7/23.
//

#ifndef GACFRED_CHATGPTREQUEST_H
#define GACFRED_CHATGPTREQUEST_H

#include "UI/Source/Gacfred.h"
#include <cpprest/http_client.h>

namespace gacfred
{
    class ChatGPTRequest
    {
    private:
        vl::Ptr<web::http::client::http_client> client;
        ChatGPTRequest();

    public:
        static ChatGPTRequest& Instance()
        {
            static ChatGPTRequest instance;
            return instance;
        }
        vl::WString GetAnswer(const vl::WString& question);
    };
}



#endif //GACFRED_CHATGPTREQUEST_H
