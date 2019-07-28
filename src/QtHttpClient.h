#ifndef QTHTTPCLIENT_H
#define QTHTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include "Utils/QtJsonTool.h"

using namespace std;

QT_FORWARD_DECLARE_CLASS(QNetworkAccessManager)

namespace Huobi {
    class QtHttpClient : public QObject {
    Q_OBJECT
    public:
        explicit QtHttpClient(QObject *parent = nullptr);

        ~QtHttpClient();

    public:
        QJsonObject get(QUrl url);
    };
}

#endif // QTHTTPCLIENT_H
