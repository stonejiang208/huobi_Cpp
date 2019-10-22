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
    MarketDetailMergedRequest req("btcusdt");
    MarketClient* client = new HuobiMarketService(op);
    MarketDetailMerged marketDetailMerged = client->getMarketDetailMerged(req);
    cout << "Id: " << marketDetailMerged.id << endl;
    cout << "High: " << marketDetailMerged.high << endl;
    cout << "Low: " << marketDetailMerged.low << endl;
    cout << "Open: " << marketDetailMerged.open << endl;
    cout << "Close: " << marketDetailMerged.close << endl;
    cout << "Volume: " << marketDetailMerged.vol << endl;
    cout << "ask amount: " << marketDetailMerged.ask.amount << endl;
    cout << "ask price: " << marketDetailMerged.ask.price << endl;
    cout << "bid amount: " << marketDetailMerged.bid.amount << endl;
    cout << "bid price: " << marketDetailMerged.bid.price << endl;


}