/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "client/AccountClient.h"
#include "../../src/options/HuobiOptions.h"
#include "../../src/Huobi/HuobiAccountService.h"

#include<iostream>
#include<vector>
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    HuobiOptions op;
    op.apiKey = "xxx";
    op.secretKey = "xxx";
    AccountClient* client = new HuobiAccountService(op);
    vector<Account> accounts = client->getAccounts();
    for (Account account : accounts) {
        cout << account.id << endl;
        cout << account.type.getValue() << endl;
        cout << account.subtype << endl;
        cout << account.state.getValue() << endl;

    }


}