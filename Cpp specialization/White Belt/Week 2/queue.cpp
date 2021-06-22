#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int Q;
    cin >> Q;
    vector<bool> queue = {};

    for (int i = 0; i < Q; ++i ){
        string cmd;
        cin >> cmd;
        if (cmd == "WORRY_COUNT"){
            cout << count(begin(queue), end(queue), true) << endl;
        } else {
            int cmd_param; 
            cin >> cmd_param;

            if (cmd == "WORRY" || cmd == "QUIET")
                queue[cmd_param] = (cmd == "WORRY");
            else if (cmd == "COME")
                queue.resize(queue.size() + cmd_param, false);
        } 
    }
    return 0;
}