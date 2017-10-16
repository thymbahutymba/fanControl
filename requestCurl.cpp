#include <iostream>
#include <curl/curl.h>
#include "config.h"

extern "C" void sendMessage(std::string msg){
	std::string url = "https://api.telegram.org/bot"+std::string(token)+"/sendMessage" ;
	std::string post_data = "chat_id="+std::string(chat_id)+"&text="+msg;

	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, (char*)(&url[0]));
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (char*)(&post_data[0]));

		res = curl_easy_perform(curl);

		if(res != CURLE_OK)
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return;
}
