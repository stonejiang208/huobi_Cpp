/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include<iostream>

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    RequestClient* client = createRequestClient("xxx", "xxx");

    Order order = client->getOrder("htusdt", 51213051224);
    cout << "Symbol: " << order.symbol << endl;
    cout << "OrderId: " << order.orderId << endl;
    cout << "FilledAmount: " << order.filledAmount << endl;
    cout << "CreatedTimestamp: " << order.createdTimestamp << endl;
    cout << "Price: " << order.price << endl;
    cout << "FilledCashAmount: " << order.filledCashAmount << endl;
    cout << "FilledFees: " << order.filledFees << endl;
    cout << "OrderType: " << order.type.getValue() << endl;

}
