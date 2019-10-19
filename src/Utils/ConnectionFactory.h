/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectionFactory.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午3:57
 */

#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <curl/curl.h>
#include <string>
#include "Request.h"
#include "../exception/SDKException.h"
#include "WebSocketConnection.h"
#include "GetHost.h"
namespace Huobi {

    class ConnectionFactory {
    public:

        /*
         * restful connect
         */

        static size_t writeFun(void *input, size_t uSize, size_t uCount, void *avg) {
            size_t uLen = uSize*uCount;
            std::string &sBuffer = *reinterpret_cast<std::string *> (avg);
            sBuffer.append(reinterpret_cast<const char *> (input), uLen);
            return uLen;
        }

        static std::string execute(Request* request) {
            std::unique_ptr<Request > ptr(request);
            CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
            if (code != CURLE_OK) {
                std::cout << "curl_global_init() Err" << std::endl;
                throw SDKException("", "curl_global_init() Err");
            }
            CURL* pCurl = curl_easy_init();
            if (pCurl == NULL) {
                std::cout << "curl_easy_init() Err" << std::endl;
                throw SDKException("", "curl_easy_init() Err");
            }
            std::string sBuffer;
            printf("\n");
            printf("------request------\n");
            printf(ptr->getUrl().c_str());
            printf("\n");
            curl_easy_setopt(pCurl, CURLOPT_SSLKEYTYPE, "PEM");
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 1L);
            curl_easy_setopt(pCurl, CURLOPT_URL, request->getUrl().c_str()); // 访问的URL
            curl_easy_setopt(pCurl, CURLOPT_CAINFO, "/etc/huobi_cert/cert.pem");
            if (ptr->method == "POST") {
                curl_easy_setopt(pCurl, CURLOPT_POST, 1);
                curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8");
                curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
            } else {
                curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/x-www-form-urlencoded");
                curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
            }
            curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 20); // 超时(单位S)
            curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &writeFun); // !数据回调函数
            curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &sBuffer); // !数据回调函数的参，一般为Buffer或文件fd
            if (request->method == "POST") {
                curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, request->getPostBody().c_str());
            }
            curl_easy_perform(pCurl);
            if (code != CURLE_OK) {
                std::cout << "curl_easy_perform() Err" << std::endl;
                throw SDKException("", "curl_easy_perform() Err");
            }
            printf("------response------\n");
            printf(sBuffer.c_str());
            printf("\n");

            curl_easy_cleanup(pCurl);
            curl_global_cleanup();

            return sBuffer;
        }

        /*
         * websocket connect 
         *
         */

        static int event_cb(
                struct lws* wsi,
                enum lws_callback_reasons reason,
                void* user,
                void* in,
                size_t len) {
            static int i = 10;
            WebSocketConnection* connection = reinterpret_cast<WebSocketConnection*> (user);

            switch (reason) {

                case LWS_CALLBACK_CLIENT_ESTABLISHED:
                    connection->onOpen(wsi);
                    break;
                case LWS_CALLBACK_CLIENT_WRITEABLE:
                {
                    bool flag = connection->send();
                    if (!flag) {
                        //lws_cancel_service_pt(wsi);
                        return 1;
                    }
                    break;
                }
                case LWS_CALLBACK_CLIENT_RECEIVE:
                {
                    // lwsl_user("receive");
                    //                    char buf[4096 * 100] = {0};
                    //                    unsigned int l = 4096 * 100;
                    //                    l = gzDecompress((char*) in, len, buf, l);
                    //lwsl_user("RX %d: %s\n", l, (const char *) buf);
                    connection->onMessage((char*)in,len);

                    break;
                }
                case LWS_CALLBACK_CLIENT_CLOSED:

                    //connection->close();
                    lwsl_user("afer canceled.....\n");
                    connection->disconnect();

                    return 1;
                    //case LWS_CALLBACK_WSI_DESTROY:
                case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
                    connection->disconnect();
                    lwsl_user("closed... \n");
                    return 1;
                default:
                    lwsl_notice("notice %d\n", reason);
                    break;
            }

            return 0;
        }
        static  struct lws_protocols protocols[] ;
        static struct lws_context* context;

        static void init_context() {
            if (context == nullptr) {
                int logs = LLL_ERR | LLL_WARN | LLL_USER;
                lws_set_log_level(logs, NULL);
                struct lws_context_creation_info info;
                memset(&info, 0, sizeof (info));
                info.port = CONTEXT_PORT_NO_LISTEN;
                info.protocols = protocols;
                info.gid = -1;
                info.uid = -1;
                info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
                info.client_ssl_ca_filepath = "/etc/huobi_cert/cert.pem";
                context = lws_create_context(&info);
            }
        }
            // void WebSocketConnection::connect(WebsocketConnection* connection, const char* websocketHost, const char* path) {

            //            if (connectStatus == ConnectionStatus::CONNECTED) {
            //                Logger::WriteLog("[Sub][%d] Already connect", connectionId);
            //                lwsl_user("Already connect\n");
            //                return;
            //            }
            //            this->context = context;
            // lwsl_user("connect_endpoint\n");
            //                struct lws_client_connect_info ccinfo = {0};
            //                ccinfo.context = context;
            //                ccinfo.address = GetHost(std::to_string(websocketHost));
            //                ccinfo.port = 443;
            //                ccinfo.path = path;
            //                ccinfo.userdata = (void*) connection;
            //                ccinfo.protocol = "ws";
            //                ccinfo.origin = "origin";
            //                ccinfo.host = ccinfo.address;
            //                ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
            //                struct lws* conn = lws_client_connect_via_info(&ccinfo);
            //                //   lineStatus = LineStatus::LINE_ACTIVE;
            //                lwsl_user("connect_endpoint end\n");
            //            }

            static void createWebSocket(WebSocketConnection* connection, const char* websocketHost, const char* path) {
                init_context();
               
                struct lws_client_connect_info ccinfo = {0};
                ccinfo.context = context;
                ccinfo.address = GetHost(std::string(websocketHost)).c_str();
                ccinfo.port = 443;
                ccinfo.path = path;
                ccinfo.userdata = (void*) connection;
                ccinfo.protocol = "ws";
                ccinfo.origin = "origin";
                ccinfo.host = ccinfo.address;
                ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
                struct lws* conn = lws_client_connect_via_info(&ccinfo);

                lwsl_user("enter_event_loop\n");
                while (1) {
                    try {
                        lws_service(context, 100);
                    } catch (...) {
                        break;
                    }
                }
                lwsl_user("enter_event_loop END\n");
                lws_context_destroy(context);
            }

        };
    }

#endif /* CONNECTIONFACTORY_H */

