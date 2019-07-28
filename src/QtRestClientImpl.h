#ifndef QTRESTCLIENTIMPL_H
#define QTRESTCLIENTIMPL_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <string>
#include "Huobi/QtRestClient.h"
#include <QList>
#include <QtCore/QJsonDocument>
#include "Utils/QtJsonTool.h"
#include "QtHttpClient.h"
#include "InputChecker.h"
#include <QUrlQuery>
#include <QtCore/QDebug>
#include <QtCore/QJsonObject>
#include <QtCore/QString>
#include "Utils/QtDecimalTool.h"
#include "Utils/TimeService.h"


using namespace std;
using namespace Huobi;


namespace Huobi {
    class QtRestClientImpl : public QObject, public RestClient {

    Q_OBJECT
    public:

        explicit QtRestClientImpl(QObject *parent = nullptr);

        explicit QtRestClientImpl(const char *accessKey, const char *secretKey, QObject *parent = nullptr);

        ~QtRestClientImpl();

    public:
        std::vector<Candlestick> getLatestCandlestick(const char *symbol,
                                                      CandlestickInterval interval,
                                                      int size,
                                                      long startTime,
                                                      long endTime) override;

        std::vector<Trade> getHistoricalTrade(const char *symbol,
                                              int size) override;

        PriceDepth getPriceDepth(const char *symbol, int size) override;

        TradeStatistics get24HTradeStatistics(const char *symbol) override;

    private:
        string m_accessKey;
        string m_secretKey;
        string m_url;
        string m_host = "api.huobi.pro";
        string m_port = "443";
        string m_tradeUrl = "https://" + m_host + ":" + m_port;
        string m_marketUrl = "https://" + m_host + ":" + m_port;

        QList<QtHttpClient *> m_pHttpClientList;
    };
}


#endif /* QTRESTCLIENTIMPL_H */

