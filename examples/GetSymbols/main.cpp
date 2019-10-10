/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include<iostream>
#include<vector>
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {
    RequestClient* client = createRequestClient();
    vector<Symbols>symbolsList = client->getSymbols();
    cout << "---- all the symbols detail info ----" << endl;

    for (Symbols symbolInfo : symbolsList) {
        cout << "baseCurrency: " << symbolInfo.baseCurrency << endl;
        cout << "quoteCurrency: " << symbolInfo.quoteCurrency << endl;
        cout << "pricePrecision: " << symbolInfo.pricePrecision << endl;
        cout << "amountPrecision: " << symbolInfo.amountPrecision << endl;
        cout << "symbolPartition: " << symbolInfo.symbolPartition << endl;
        cout << "symbol: " << symbolInfo.symbol << endl;
    }

}