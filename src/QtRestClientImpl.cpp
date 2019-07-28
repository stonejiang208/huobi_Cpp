#include "QtRestClientImpl.h"


QT_USE_NAMESPACE

namespace Huobi {

    QtRestClientImpl::QtRestClientImpl(const char *accessKey, const char *secretKey, QObject *parent) :
            QObject(parent) {
        m_accessKey = accessKey;
        m_secretKey = secretKey;
    }


    QtRestClientImpl::QtRestClientImpl(QObject *parent) :
            QObject(parent) {
    }

    QtRestClientImpl::~QtRestClientImpl() {
        qDeleteAll(m_pHttpClientList);
        m_pHttpClientList.clear();
    }

    std::vector<Candlestick> QtRestClientImpl::getLatestCandlestick(const char *symbol,
                                                                    CandlestickInterval interval,
                                                                    int size,
                                                                    long startTime,
                                                                    long endTime) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->checkRange(size, 1, 2000, "size");

        m_url = m_marketUrl;
        QString path = "/market/history/kline";
        QUrl url(QString::fromStdString(m_url) + path);

        QUrlQuery query;
        query.addQueryItem("symbol", QString::fromStdString(symbol));
        query.addQueryItem("period", QString::fromStdString(interval.getValue()));
        query.addQueryItem("size", QString::number(size));
        query.addQueryItem("start", QString::number(startTime));
        query.addQueryItem("end", QString::number(endTime));
        url.setQuery(query);

        auto pHttpClient = new QtHttpClient();

        QJsonObject jsonObject = pHttpClient->get(url);

        QJsonDocument jsonDocument(jsonObject);
        QVariantMap result = jsonDocument.toVariant().toMap();

        vector<Candlestick> event;

                foreach (QVariant data, result["data"].toList()) {
                QVariantMap item = data.toMap();
                Candlestick candlestick;
                candlestick.timestamp = TimeService::convertCSTInSecondToUTC(item["id"].toULongLong());
                candlestick.amount = QtDecimalTool::toDecimal(item["amount"]);
                candlestick.close = QtDecimalTool::toDecimal(item["close"]);
                candlestick.high = QtDecimalTool::toDecimal(item["high"]);
                candlestick.low = QtDecimalTool::toDecimal(item["low"]);
                candlestick.open = QtDecimalTool::toDecimal(item["open"]);
                candlestick.volume = QtDecimalTool::toDecimal(item["vol"]);
                candlestick.count = item["count"].toULongLong();

                event.push_back(candlestick);
            }

        m_pHttpClientList.append(pHttpClient);

        return event;
    }

    std::vector<Trade> QtRestClientImpl::getHistoricalTrade(const char *symbol, int size) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->checkRange(size, 1, 2000, "size");

        m_url = m_marketUrl;
        QString path = "/market/history/trade";
        QUrl url(QString::fromStdString(m_url) + path);

        QUrlQuery query;
        query.addQueryItem("symbol", QString::fromStdString(symbol));
        query.addQueryItem("size", QString::number(size));
        url.setQuery(query);

        auto pHttpClient = new QtHttpClient();

        QJsonObject jsonObject = pHttpClient->get(url);

        QJsonDocument jsonDocument(jsonObject);
        QVariantMap result = jsonDocument.toVariant().toMap();

        vector<Trade> event;

                foreach (QVariant data, result["data"].toList()) {
                QVariantMap item = data.toMap();
                        foreach (QVariant dataIn, item["data"].toList()) {
                        QVariantMap itemIn = dataIn.toMap();
                        Trade trade;
                        trade.price = QtDecimalTool::toDecimal(itemIn["price"]);
                        trade.amount = QtDecimalTool::toDecimal(itemIn["amount"]);
                        trade.tradeId = itemIn["id"].toString().toStdString();
                        trade.timestamp = TimeService::convertCSTInSecondToUTC(itemIn["ts"].toULongLong());
                        trade.direction = TradeDirection::lookup(itemIn["direction"].toString().toStdString());

                        event.push_back(trade);
                    }
            }


        m_pHttpClientList.append(pHttpClient);

        return event;
    }

    PriceDepth QtRestClientImpl::getPriceDepth(const char *symbol, int size) {
        InputChecker::checker()->checkSymbol(symbol)->checkRange(size, 1, 150, "size");

        m_url = m_marketUrl;

        QString path = "/market/depth";
        QUrl url(QString::fromStdString(m_url) + path);

        QUrlQuery query;
        query.addQueryItem("symbol", QString::fromStdString(symbol));
        query.addQueryItem("type", "step0");

        url.setQuery(query);

        auto pHttpClient = new QtHttpClient();

        QJsonObject jsonObject = pHttpClient->get(url);

        QJsonDocument jsonDocument(jsonObject);
        QVariantMap result = jsonDocument.toVariant().toMap();

        PriceDepth event;
        std::vector<DepthEntry> bidsves;
        std::vector<DepthEntry> asksves;

        QVariantMap tick = result["tick"].toMap();
        event.timestamp = TimeService::convertCSTInMillisecondToUTC(tick["ts"].toULongLong());

                foreach (QVariant bid, tick["bids"].toList()) {
                DepthEntry de;
                de.price = QtDecimalTool::toDecimal(bid.toList().at(0));
                de.amount = QtDecimalTool::toDecimal(bid.toList().at(1));
                bidsves.push_back(de);
            }
                foreach (QVariant ask, tick["asks"].toList()) {
                DepthEntry de;
                de.price = QtDecimalTool::toDecimal(ask.toList().at(0));
                de.amount = QtDecimalTool::toDecimal(ask.toList().at(1));
                asksves.push_back(de);
            }

        event.bids = bidsves;
        event.asks = asksves;

        m_pHttpClientList.append(pHttpClient);

        return event;
    }


    TradeStatistics QtRestClientImpl::get24HTradeStatistics(const char *symbol) {

        InputChecker::checker()->checkSymbol(symbol);

        m_url = m_marketUrl;

        QString path = "/market/detail";
        QUrl url(QString::fromStdString(m_url) + path);

        QUrlQuery query;
        query.addQueryItem("symbol", QString::fromStdString(symbol));

        url.setQuery(query);

        auto pHttpClient = new QtHttpClient();

        QJsonObject jsonObject = pHttpClient->get(url);

        QJsonDocument jsonDocument(jsonObject);
        QVariantMap result = jsonDocument.toVariant().toMap();

        TradeStatistics event;

        long ts = TimeService::convertCSTInMillisecondToUTC(result["ts"].toULongLong());
        QVariantMap tick = result["tick"].toMap();

        event.amount = QtDecimalTool::toDecimal(tick["amount"]);
        event.open = QtDecimalTool::toDecimal(tick["open"]);
        event.close = QtDecimalTool::toDecimal(tick["close"]);
        event.high = QtDecimalTool::toDecimal(tick["high"]);
        event.timestamp = ts;
        event.count = tick["count"].toULongLong();
        event.low = QtDecimalTool::toDecimal(tick["low"]);
        event.volume = QtDecimalTool::toDecimal(tick["vol"]);

        m_pHttpClientList.append(pHttpClient);

        return event;
    }
}






