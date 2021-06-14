#include<bits/stdc++.h>
using namespace std;


string input = "mempool.csv"; 
set<string> included_trx_ids; // Will store all tx_ids
int totalBlockWeight = 4000000; // The total weight of transactions in a block must not exceed 4,000,000 weight

class TransactionInfo{
    public:
    string tx_id;
    int fee;
    int weight;
    vector<string> parents;
};

pair<string,TransactionInfo*> initiateTransaction(vector<string>& row){
    auto ans = new TransactionInfo();
    ans->tx_id=row[0];
    ans->fee=stoi(row[1]);
    ans->weight= stoi(row[2]);
    vector<string> p;
    for (int i = 3; i < row.size(); i++)
    {       
        p.push_back(row[i]);
    }
    ans->parents=p;
    return {row[0],ans};
    
}

void readinput(string fileName,unordered_map<string,TransactionInfo*>& ump){
    ifstream fin(fileName);
}
