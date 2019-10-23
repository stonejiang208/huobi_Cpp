/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <iostream>
//#include "Huobi/HuobiClient.h"


#include "client/AccountClient.h"
#include "../../src/options/HuobiOptions.h"
#include "../../src/Huobi/HuobiAccountService.h"
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    
     HuobiOptions op;
    //CandlestickRequest req("btcusdt",CandlestickInterval::day1);
     op.apiKey="xxx";
     op.secretKey="xxx";
    AccountClient* client = new HuobiAccountService(op);   
    SubAccountChangeRequest req;
    client->subAccounts(req, [](AccountChangeEvent event) {

        cout << "event: " << event.event << endl;
       //  cout << "event: " << event.list << endl;
//        cout << "High: " << event.candlestick.high << endl;
//        cout << "Low: " << event.candlestick.low << endl;
//        cout << "Open: " << event.candlestick.open << endl;
//        cout << "Close: " << event.candlestick.close << endl;
//        cout << "Volume: " << event.candlestick.volume << endl;
    });
    

}
