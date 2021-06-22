#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(){
    int Q;
    cin >> Q;
    map<string, string> country_capital;

    for (int i = 0; i < Q; ++i ){
        string cmd;
        cin >> cmd;
        if (cmd == "DUMP"){
            if (country_capital.size() == 0)
                cout << "There are no countries in the world" << endl;
            else
                for (auto item : country_capital)
                    cout << item.first << ' ' << item.second << endl;
        } else {
            if (cmd == "RENAME"){
                string old_capital, new_capital;
                cin >> old_capital >> new_capital;

            } else {
                string country;
                cin >> country;
                if (cmd == "ABOUT"){
                    if (country_capital.count(country))
                        cout << "Country " << country << " has capital " << country_capital[country] << endl;
                    else
                        cout << "Country " << country << " doesn't exist" << endl;
                } else if (cmd == "CHANGE_CAPITAL"){
                    string new_capital;
                    cin >> new_capital;
                    if (country_capital.count(country) == 0)
                        cout << "Introduce new country " << country << " with capital " << new_capital << endl;
                    else if (country_capital[country] == new_capital)
                        cout << "Country " << country << " hasn't changed its capital" << endl;
                    else
                        cout << "Country " << country << " has changed its capital from " 
                        << country_capital[country] << " to " << new_capital << endl;
                    country_capital[country] = new_capital;
                }
            }
        }
    }
    return 0;
}