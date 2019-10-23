/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include "client/AccountClient.h"
#include "../../src/options/HuobiOptions.h"
#include "../../src/Huobi/HuobiAccountService.h"
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {


    HuobiOptions op;
    op.apiKey = "xxx";
    op.secretKey = "xxx";
    AccountClient* client_account = new HuobiAccountService(op);
    vector<SubuserAggregateBalance> subuserAggregateBalances = client_account->getSubuserAggregateBalance();
    for (SubuserAggregateBalance subuserAggregateBalance : subuserAggregateBalances) {

        cout << "currency: " << subuserAggregateBalance.currency << endl;
        cout << "balance: " << subuserAggregateBalance.balance << endl;
        cout << "type: " << subuserAggregateBalance.type.getValue() << endl;

    }



}