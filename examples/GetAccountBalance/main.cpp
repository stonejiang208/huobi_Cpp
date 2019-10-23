/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//#include "Huobi/HuobiClient.h"
//#include<iostream>

#include "client/AccountClient.h"
#include "../../src/options/HuobiOptions.h"
#include "../../src/Huobi/HuobiAccountService.h"
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    //    RequestClient* client = createRequestClient("xxx", "xxx");
    //    Account account = client->getAccountBalance(AccountType::otc);
    //    cout << "Type: " << account.type.getValue() << endl;
    //    cout << "State: " << account.state.getValue() << endl;
    //    cout << "---Balances:---" << endl;
    //    vector<Balance> balances = account.balances;
    //    for (Balance balance : balances) {
    //        cout << "Currency: " << balance.currency << endl;
    //        cout << "Balance: " << balance.balance << endl;
    //    }
    
   
    
    HuobiOptions op;
    op.apiKey = "xxx";
    op.secretKey = "xxx";
    AccountClient* client_account = new HuobiAccountService(op);
    AccountBalanceRequest request(6012157);
    AccountBalance accountBalance = client_account->getAccountBalance(request);

    cout << "id " << accountBalance.id << endl;
    cout << "type " << accountBalance.type.getValue() << endl;
    cout << "state " << accountBalance.state.getValue() << endl;

    for (Balance balance : accountBalance.list) {
        cout << "currency: " << balance.currency << endl;
        cout << "balance: " << balance.balance << endl;
        cout << "type: " << balance.type.getValue() << endl;

    }


}
