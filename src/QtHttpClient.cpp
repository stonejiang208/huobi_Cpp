#include "QtHttpClient.h"
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

QT_USE_NAMESPACE

namespace Huobi {
    QtHttpClient::QtHttpClient(QObject *parent) :
            QObject(parent) {
    }


    QtHttpClient::~QtHttpClient() {

    }

    QJsonObject QtHttpClient::get(QUrl url) {
        QNetworkAccessManager manager;
        QNetworkRequest request;
        request.setUrl(url);
        QNetworkReply *reply = manager.get(request);
        QEventLoop loop;
        connect(&manager, SIGNAL(finished(QNetworkReply * )), &loop, SLOT(quit()));
        loop.exec();
        QJsonObject jsonObject = QtJsonTool::getJsonObjectFromByteArray(reply->readAll());
        reply->deleteLater();
        return jsonObject;
    }
}

