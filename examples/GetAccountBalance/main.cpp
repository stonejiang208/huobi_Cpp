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
    Account account = client->getAccountBalance(AccountType::otc);
    cout << "Type: " << account.type.getValue() << endl;
    cout << "State: " << account.state.getValue() << endl;
    cout << "---Balances:---" << endl;
    vector<Balance> balances = account.balances;
    for (Balance balance : balances) {
        cout << "Currency: " << balance.currency << endl;
        cout << "Balance: " << balance.balance << endl;
    }
}
