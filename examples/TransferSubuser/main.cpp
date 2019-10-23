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
    TransferSubuserRequest request(12345,"eos",Decimal("0.00002"),TransferMasterType::master_transfer_out);
    long id = client_account->transferSubuser(request);

    cout << "id " << id << endl;
    


}