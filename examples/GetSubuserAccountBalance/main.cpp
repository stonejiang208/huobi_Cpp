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
    vector<AccountBalance> accountsBalance = client_account->getSubuserAccountBalance(123145390);
    for (AccountBalance accountBalance : accountsBalance) {
        
        cout << "id: " << accountBalance.id << endl;
        cout << "state: " << accountBalance.state.getValue() << endl;
        cout << "type: " << accountBalance.type.getValue() << endl;

        for (Balance balance : accountBalance.list) {
            cout << "currency: " << balance.currency << endl;
            cout << "balance: " << balance.balance << endl;
            cout << "type: " << balance.type.getValue() << endl;

        }


    }



}