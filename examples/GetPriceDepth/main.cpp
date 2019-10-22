/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "MarketClient.h"
#include "../../src/options/HuobiOptions.h"
#include "../../src/Huobi/HuobiMarketService.h"
#include<iostream>
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    //    RequestClient* client = createRequestClient();
    //    PriceDepth depth = client->getPriceDepth("btcusdt", 5);
    //
    //    int i = 0;
    //    cout<<"---- Top 5 bids ----"<<endl;
    //    for (DepthEntry entry : depth.bids) {
    //        cout << i++<< ": price: " << entry.price << ", amount: " << entry.amount << endl;
    //    }
    //    i = 0;
    //    cout<<"---- Top 5 asks ----"<<endl;
    //    for (DepthEntry entry : depth.asks){
    //            cout << i++<< ": price: " << entry.price << ", amount: " << entry.amount << endl;
    //        }

    HuobiOptions op;
    MarketDepthRequest req("btcusdt", DepthStep::step0);
    MarketClient* client = new HuobiMarketService(op);
    MarketDepth depth = client->getMarketDepth(req);
    cout << "ts: " << depth.ts << endl;
    cout << "version: " << depth.version << endl;
    cout << "ask price: " << depth.asks[0].price << endl;
    cout << "ask amount: " << depth.asks[0].amount << endl;
    cout << "bid price: " << depth.bids[0].price << endl;
    cout << "bid amount: " << depth.bids[0].amount << endl;


}