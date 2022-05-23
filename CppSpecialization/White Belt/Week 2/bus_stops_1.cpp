#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(){
    map<string, vector<string>> buses;
    map<string, vector<string>> stops;
    
    unsigned int Q;
    cin >> Q;

    string cmd;
    for (unsigned int i = 0; i < Q; ++i){
        cin >> cmd;
        if (cmd == "NEW_BUS"){
            string bus;
            cin >> bus;

            unsigned int stop_count;
            cin >> stop_count;

            buses[bus].resize(stop_count);
            for (auto& stop : buses[bus]){
                cin >> stop;
                stops[stop].push_back(bus);
            }
        }
        
        if (cmd == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;

            if (!stops.count(stop))
                cout << "No stop" << endl;
            else {
                for (auto bus : stops[stop])
                    cout << bus << " ";
                cout << endl;
            }
        }
        
        if (cmd == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;

            if (!buses.count(bus))
                cout << "No bus" << endl;
            else 
                for (auto stop : buses[bus]){
                    cout << "Stop " << stop << ":";
                    if (stops[stop].size() == 1){
                        cout << " no interchange";
                    } else
                        for (auto bus_another : stops[stop])
                            if (bus_another != bus)
                                cout << " " << bus_another;  
                    cout << endl;
                }
        }
        
        if (cmd == "ALL_BUSES") {
            if (!buses.size())
                cout << "No buses" << endl;
            else
                for (auto bus : buses){
                    cout << "Bus " << bus.first << ":";
                    for (auto stop : bus.second)
                        cout << " " << stop;
                    cout << endl;
                }
        }
    }
    
    return 0;
}