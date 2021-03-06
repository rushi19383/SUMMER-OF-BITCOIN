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

void readinput(string input,unordered_map<string,TransactionInfo*>& ump){
    ifstream fin(input);
    vector<string> row;
    string temp,line,word;
    getline(fin,line);
    while (getline(fin,line)){
        row.clear();
        stringstream s(line);
        while (getline(s,word,','))
        {
            row.push_back(word);

        }
        pair<string, TransactionInfo*>p=initiateTransaction(row);
        ump[p.first]=p.second;
        
    }
    fin.close();
    cout<<"num of transactions read :"<<ump.size()<<endl;
    
    
}
//This only works when if it contains parents
bool isValidTx(TransactionInfo* tx,set<string>& included_tx_set){
    for(auto parent : tx->parents){
        if(included_tx_set.find(parent)== included_tx_set.end())
            return false;


    }
    return true;
}

void writeOutput(vector<string>& included_tx_vector, string fn){
    ofstream myfile(fn);
    for(auto s:included_tx_vector)
    myfile<<s<<endl;
    myfile.close();
}

int main(){
    unordered_map<string, TransactionInfo*>ump;
    readinput(input,ump);
    set<pair<float,TransactionInfo*>,greater<pair<float,TransactionInfo*>>> tx_set;
    set<string>included_tx_set;
    vector<string>included_tx_vector;
    for(auto p:ump){
        tx_set.insert({(float)p.second->fee/(float)p.second->weight,p.second});
    }
    int currBlockWeight = 0;
    int totalFee = 0;
    while(!tx_set.empty() && currBlockWeight<totalBlockWeight){
        bool found = false;
        for(auto itr = tx_set.begin();itr != tx_set.end();itr++){
            TransactionInfo* curr_tx = (*itr).second;
            int currFee = curr_tx->fee;
            int currWeight = curr_tx->weight;
            if(isValidTx(curr_tx,included_tx_set) && currBlockWeight + currWeight <= totalBlockWeight){
                currBlockWeight += currWeight;
                included_tx_set.insert(curr_tx->tx_id);
                included_tx_vector.push_back(curr_tx->tx_id);
                totalFee += currFee;
                tx_set.erase(itr);
                found = true;
                break;
            }
        }
        // No valid tx  ans found
        if(!found)
            break; 
    }
    cout<<"num of tx in final block "<<included_tx_set.size()<<endl;
    cout<<"total fee in curr block : "<<totalFee<<" total weight : "<<currBlockWeight<<endl;
    writeOutput(included_tx_vector,"block.txt");

}