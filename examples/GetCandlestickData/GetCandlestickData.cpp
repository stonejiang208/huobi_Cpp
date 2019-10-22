/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//#include "Huobi/HuobiClient.h"
#include "client/MarketClient.h"
#include "../../src/options/HuobiOptions.h"
#include "../../src/Huobi/HuobiMarketService.h"

#include<iostream>
#include<vector>
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {
    //  RequestClient* client = createRequestClient();
    //    vector<Candlestick>candelves = client->getLatestCandlestick("btcusdt", CandlestickInterval::min1);
    //    cout << "---- 1 min candlestick for btcusdt ----" << endl;
    //
    //    for (Candlestick candlestick : candelves) {
    //        cout << "Timestamp: " << candlestick.timestamp << endl;
    //        cout << "High: " << candlestick.high << endl;
    //        cout << "Low: " << candlestick.low << endl;
    //        cout << "Open: " << candlestick.open << endl;
    //        cout << "Close: " << candlestick.close << endl;
    //        cout << "Volume: " << candlestick.volume << endl;
    //    }
    HuobiOptions op;
    CandlestickRequest req("btcusdt",CandlestickInterval::day1);
    MarketClient* client = new HuobiMarketService(op);
    vector<Candlestick>cans = client->getCandlestick(req);
    
    for (Candlestick candlestick : cans) {
        cout << "Id: " << candlestick.id << endl;
        cout << "High: " << candlestick.high << endl;
        cout << "Low: " << candlestick.low << endl;
        cout << "Open: " << candlestick.open << endl;
        cout << "Close: " << candlestick.close << endl;
        cout << "Volume: " << candlestick.volume << endl;
    }
    //    SubCandlestickRequest req("btcusdt,eosusdt", CandlestickInterval::min1);
    //
    //
    //    client->subCandlestick(req, [](CandlestickEvent candlestickEvent) {
    //
    //        cout << "Timestamp: " << candlestickEvent.ts << endl;
    //        cout << "High: " << candlestickEvent.candlestick.high << endl;
    //        cout << "Low: " << candlestickEvent.candlestick.low << endl;
    //        cout << "Open: " << candlestickEvent.candlestick.open << endl;
    //        cout << "Close: " << candlestickEvent.candlestick.close << endl;
    //        cout << "Volume: " << candlestickEvent.candlestick.volume << endl;
    //    });


}