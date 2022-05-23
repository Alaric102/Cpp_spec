#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main(){
    map<set<string>, unsigned int> buses;

    unsigned int Q;
    cin >> Q;

    for (unsigned int i = 0; i < Q; ++i){
        unsigned int count;
        cin >> count;

        set<string> stops;
        for (unsigned int i = 0; i < count; ++i){
            string stop_s;
            cin >> stop_s;
            stops.insert(stop_s);
        }

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