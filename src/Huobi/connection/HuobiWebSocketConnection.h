/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuobiWebSocketConnection.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午8:44
 */

#ifndef HUOBIWEBSOCKETCONNECTION_H
#define HUOBIWEBSOCKETCONNECTION_H
#include <mutex>
#include "../../Utils/WebSocketConnection.h"
#include"../../Utils/ApiSignature.h"
#include "constant/enums.h"
#include "constant/Logger.h"
#include "../../Utils/TimeService.h"
#include "../../exception/SDKException.h"
#include "../../Utils/JsonWriter.h"
#include "../../Utils/JsonWrapper.h"
#include "../../Utils/JsonDocument.h"

#include "../../Utils/WebSocketWatchDog.h"
#include "../../Utils/GetHost.h"
#include "../../Utils/gzip.h"
#include "../../options/HuobiOptions.h"
#include "../../Utils/ConnectionFactory.h"

namespace Huobi {

    template <typename T>
    class HuobiWebSocketConnection : public WebSocketConnection {

        class AutoLock {
        public:

            AutoLock(std::mutex& mutex) : mutex_(mutex) {
                mutex_.lock();
            }

            ~AutoLock() {
                mutex_.unlock();
            }
        private:
            std::mutex& mutex_;
        };

        //        int  connectionCounter = 0;
        //
        //         WebSocketConnection(
        //                const std::string& apiKey,
        //                const std::string& secretKey,
        //                WebSocketRequest* request,
        //                WebSocketWatchDog*dog,
        //                std::string host) : request(request) {
        //            this->apiKey = apiKey;
        //            this->secretKey = secretKey;
        //            this->client = nullptr;
        //            this->dog = dog;
        //            this->host = host;
        //            this->connectionId = connectionCounter++;
        //           
        //        };

        //        void  connect(lws_context* context) {
        //
        //            if (connectStatus == ConnectionStatus::CONNECTED) {
        //                Logger::WriteLog("[Sub][%d] Already connect", connectionId);
        //                lwsl_user("Already connect\n");
        //                return;
        //            }
        //            this->context = context;
        //            lwsl_user("connect_endpoint\n");
        //            struct lws_client_connect_info ccinfo = {0};
        //            ccinfo.context = context;
        //            ccinfo.address = host.c_str();
        //            ccinfo.port = 443;
        //            if (request->isNeedSignature == true) {
        //                ccinfo.path = "/ws/v1";
        //            } else {
        //                if (host.find("api") != -1) {
        //                    ccinfo.path = "/ws";
        //                } else {
        //                    ccinfo.path = "/api/ws";
        //                }
        //            }
        //            ccinfo.userdata = (void*) this;
        //            ccinfo.protocol = "ws";
        //            ccinfo.origin = "origin";
        //            ccinfo.host = ccinfo.address;
        //            ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
        //            struct lws* conn = lws_client_connect_via_info(&ccinfo);
        //            lineStatus = LineStatus::LINE_ACTIVE;
        //            lwsl_user("connect_endpoint end\n");
        //        }

        bool send(const char* message) {

            AutoLock lock(mutex);

            if (!strcmp("*", message)) {
                lwsl_user("Get close message\n");
                commandList.clear();
                return false;
            }

            uint8_t buf[LWS_PRE + 1024] = {0};
            int m;
            int n = lws_snprintf((char *) buf + LWS_PRE, 1024,
                    "%s", message);

            lwsl_user("Sending message %s\n", buf + LWS_PRE);
            //   Logger::WriteLog("[Sub][%d] Send: %s", connectionId, buf + LWS_PRE);
            m = lws_write(wsi, buf + LWS_PRE, n, LWS_WRITE_TEXT);
            if (m < n) {
                Logger::WriteLog("[Sub][%d] Sending failed", connectionId);
                lwsl_err("sending failed: %d\n", m);
                close();
                return false;
            }

            lws_callback_on_writable(wsi);
        }

        bool send() {
            AutoLock lock(mutex);
            std::list<std::string>::iterator it = commandList.begin();
            for (; it != commandList.end(); ++it) {

                uint8_t buf[LWS_PRE + 1024] = {0};
                int m;
                int n = lws_snprintf((char *) buf + LWS_PRE, 1024,
                        "%s", it->c_str());
                lwsl_user("Sending message %s\n", buf + LWS_PRE);
                //   Logger::WriteLog("[Sub][%d] Send: %s", connectionId, buf + LWS_PRE);
                m = lws_write(wsi, buf + LWS_PRE, n, LWS_WRITE_TEXT);
                lws_callback_on_writable(wsi);
                if (m < n) {
                    Logger::WriteLog("[Sub][%d] Sending failed", connectionId);
                    lwsl_err("sending failed: %d\n", m);
                    commandList.clear();
                    close();
                    return false;
                }
            }
            commandList.clear();
            return true;
        }

        void onOpen(lws* wsi) {
            lwsl_user("onOpen \n");
            //            Logger::WriteLog("[Sub][%d] Connected", connectionId);
            state = ConnectionStateEnum::CONNECTED;
            //            lineStatus = LineStatus::LINE_ACTIVE;
            lastReceivedTime = TimeService::getCurrentTimeStamp();

            WebSocketWatchDog::onConnectionCreated(this);
            this->wsi = wsi;
            if (op.apiKey != "") {
                send(createSignature(op).c_str());
            } else {

                send();
            }
        }

        void onMessage(const char* message, size_t len) {


            char buf[4096 * 100] = {0};
            unsigned int l = 4096 * 100;
            l = gzDecompress((char*) message, len, buf, l);
            //lwsl_user("RX %d: %s\n", l, (const char *) buf);

            lwsl_user("RX: %s \n", buf);
            lastReceivedTime = TimeService::getCurrentTimeStamp();

            JsonDocument doc;
            JsonWrapper json = doc.parseFromString(buf);

            if ((json.containKey("status") && strcmp(json.getString("status"), "ok") != 0) ||
                    (json.containKey("err-code") && json.getInt("err-code") != 0)) {
                std::string errorCode = json.getStringOrDefault("err-code", "Unknown error code");
                std::string errorMsg = json.getStringOrDefault("err-msg", "Unknown error message");
                SDKException ex;
                ex.errorCode = errorCode;
                ex.errorMsg = errorMsg;
                Logger::WriteLog("[Sub][%d] Error: %s", errorMsg.c_str());
                close();
            } else if (json.containKey("op")) {
                std::string op = json.getString("op");
                if (op == "notify") {
                    onReceive(json);
                } else if (op == "ping") {
                    processPingOnTradingLine(json);
                } else if (op == "auth") {
                    send();
                } else if (op == "req") {
                    onReceive(json);
                }
            } else if (json.containKey("ch")) {
                onReceive(json);
            } else if (json.containKey("ping")) {
                processPingOnMarketLine(json);
            } else if (json.containKey("subbed")) {

            } else if (json.containKey("rep")) {
                onReceive(json);
            } else {
                std::cout << "parse failed" << std::endl;
                Logger::WriteLog("parse failed！：%s", message);
            }
        }

        void onReceive(JsonWrapper& json) {
            T value = JsonParser(json);
            callback(value);
        }

        void processPingOnTradingLine(JsonWrapper& json) {
            lwsl_user("processPingOnTradingLine \n");
            long ts = json.getLong("ts");
            char buf[1024] = {0};
            sprintf(buf, "{\"op\":\"pong\",\"ts\":%ld}", ts);
            std::string message = buf;
            send(message.c_str());
        }

        void processPingOnMarketLine(JsonWrapper& json) {
            long ts = json.getLong("ping");
            char buf[1024] = {0};
            sprintf(buf, "{\"pong\":%ld}", ts);
            std::string message = buf;
            lwsl_user("processPingOnMarketLine %s\n", message.c_str());
            send(message.c_str());
        }

        std::string createSignature(HuobiOptions& op) {

            time_t t = time(NULL);
            struct tm *local = gmtime(&t);
            char timeBuf[100] = {0};

            sprintf(timeBuf, "%04d-%02d-%02dT%02d%%3A%02d%%3A%02d",
                    local->tm_year + 1900,
                    local->tm_mon + 1,
                    local->tm_mday,
                    local->tm_hour,
                    local->tm_min,
                    local->tm_sec);
            char buf[100] = {0};
            sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d",
                    local->tm_year + 1900,
                    local->tm_mon + 1,
                    local->tm_mday,
                    local->tm_hour,
                    local->tm_min,
                    local->tm_sec);
            std::string signa = ApiSignature::CreateSignature(GetHost(std::string(op.websocketHost)),
                    op.apiKey,
                    op.secretKey,
                    "/ws/v1", "GET", timeBuf, "");

            JsonWriter writer;
            writer.put("SignatureVersion", "2");
            writer.put("op", "auth");
            writer.put("AccessKeyId", op.apiKey);
            writer.put("Signature", signa.c_str());
            writer.put("SignatureMethod", "HmacSHA256");
            writer.put("Timestamp", buf);
            return writer.toJsonString();
        }

        void reConnect() {
            if (delayInSecond != 0) {
                delayInSecond--;
            } else {
                lwsl_user("reConnecting...\n");
                // this->connect(context);
                createMarketConnection(commandList, callback, op, JsonParser);
                lws_set_timeout(wsi, PENDING_TIMEOUT_KILLED_BY_PARENT, LWS_TO_KILL_ASYNC);
                WebSocketWatchDog::onClosedNormally(this);

            }
        }

        void reConnect(int delayInSecond) {
            Logger::WriteLog("[Sub][%d] Reconnecting after %d seconds later", connectionId, delayInSecond);
            lwsl_user("Reconnecting after %d seconds later\n", delayInSecond);
            if (wsi != nullptr) {
                lwsl_user("closing client\n");
                //  send("*");
            } else {
                lwsl_user("wsi is null\n");
            }
            wsi = nullptr;
            this->delayInSecond = delayInSecond;
            state = ConnectionStateEnum::DELAY_CONNECT;
        }

        void disconnect() {
            Logger::WriteLog("[Sub][%d] Disconnected", connectionId);
            state = ConnectionStateEnum::CLOSED_ON_ERROR;
            wsi = nullptr;
            WebSocketWatchDog::onClosedNormally(this);

        }

        void close() {
            Logger::WriteLog("[Sub][%d] Closing normally", connectionId);
            lwsl_user("Closing normally \n");
            lws_set_timeout(wsi, PENDING_TIMEOUT_KILLED_BY_PARENT, LWS_TO_KILL_ASYNC);
            //  lineStatus = LineStatus::LINE_IDEL;
            wsi = nullptr;
            WebSocketWatchDog::onClosedNormally(this);
        }


    private:
        std::list<std::string> commandList;
        std::function<void(const T&) > callback;
        HuobiOptions op;
        std::function < T(JsonWrapper&) > JsonParser;
        int delayInSecond = 0;
        lws*wsi;
        ConnectionStateEnum state;
        long lastReceivedTime;
        int connectionId;
        static int connectionCounter;
        std::mutex mutex;

        HuobiWebSocketConnection(
                std::list<std::string>& commandList,
                std::function<void( const T&) > callback,
                HuobiOptions& op,
                std::function < T(JsonWrapper&) > JsonParser) {
            this->commandList = commandList;
            this->callback = callback;
            this->op = op;
            this->JsonParser = JsonParser;
            this->connectionId = connectionCounter++;
        }


    public:

        ConnectionStateEnum getConnectState() {
            return state;
        }

        long getLastReceivedTime() {

            return lastReceivedTime;
        }

        static void createMarketConnection(
                std::list<std::string>& commandList,
                std::function<void(const T&) > callback,
                HuobiOptions& op,
                std::function < T(JsonWrapper&) > JsonParser) {

            HuobiWebSocketConnection* huobiWebSocketConnection = new HuobiWebSocketConnection<T>(commandList, callback, op, JsonParser);
            ConnectionFactory::createWebSocket(huobiWebSocketConnection, op.websocketHost, "/ws");
        }


    };
    template <typename T>
    int HuobiWebSocketConnection<T>::connectionCounter = 0;

}

#endif /* HUOBIWEBSOCKETCONNECTION_H */

