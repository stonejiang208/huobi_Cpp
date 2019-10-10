/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include <iostream>

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {
    RequestClient* client = createRequestClient();
    BestQuote bestQuote = client->getBestQuote("btcusdt");
    cout << "---- BestQuote ----" << endl;
    cout << "Timestamp: " << bestQuote.timestamp << endl;
    cout << "AskPrice: " << bestQuote.askPrice << endl;
    cout << "AskAmount: " << bestQuote.askAmount << endl;
    cout << "BidPrice: " << bestQuote.bidPrice << endl;
    cout << "BidAmount: " << bestQuote.bidAmount << endl;
}
