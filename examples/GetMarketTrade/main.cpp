/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MarketClient.h"
#include "../../src/options/HuobiOptions.h"
#include "../../src/Huobi/HuobiMarketService.h"

#include<iostream>
#include<vector>
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    HuobiOptions op;
    MarketTradeRequest req("btcusdt");
    MarketClient* client = new HuobiMarketService(op);
    MarketTrade marketTrade = client->getMarketTrade(req);
    cout << "Id: " << marketTrade.id << endl;
    cout << "price: " << marketTrade.price << endl;
    cout << "amount: " << marketTrade.amount << endl;
    cout << "direction: " << marketTrade.direction.getValue() << endl;
    cout << "tradeId: " << marketTrade.tradeId << endl;
    cout << "ts: " << marketTrade.ts << endl;
    

}