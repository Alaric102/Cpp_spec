#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(){
    map<vector<string>, unsigned int> buses;

    unsigned int Q;
    cin >> Q;

    for (unsigned int i = 0; i < Q; ++i){
        unsigned int count;
        cin >> count;

        vector<string> stops(count);
        for (auto& stop : stops)
            cin >> stop;

        if (!buses.count(stops)){
            const unsigned int new_number = buses.size() + 1;
            buses[stops] = new_number;
            cout << "New bus " << new_number << std::endl;
        } else {
            cout << "Already exists for " << buses[stops] << endl;
        }
    }        
    return 0;
}