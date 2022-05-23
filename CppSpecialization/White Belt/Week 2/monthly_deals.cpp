#include <iostream>
#include <string>
#include <vector>
using namespace std;

int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(){
    int Q;
    cin >> Q;

    int month_now = 0;
    vector<vector<string>> deals(days_in_month[month_now]);
    for (int i = 0; i < Q; ++i){
        string cmd;
        cin >> cmd;
        if (cmd == "ADD"){
            string deal;
            int day;
            cin >> day >> deal;
            --day;
            deals[day].push_back(deal);
        } else if (cmd == "DUMP") {
            int day;
            cin >> day;
            --day;
            cout << deals[day].size();
            for (auto deal : deals[day])
                cout << ' ' << deal;
            cout << endl;
        } else if (cmd == "NEXT") {
            //Check days count in next month
            int days_now = days_in_month[month_now];
            month_now = (month_now + 1) % 12;
            int days_next = days_in_month[month_now];
            //if next days number less than now, book days on last day of next month
            if (days_next < days_now)
                for (int i = days_next; i < days_now; ++i)
                    for (auto deal : deals[i])
                        deals[days_next - 1].push_back(deal);
            deals.resize(days_next);
        }
    }
    return 0;
}