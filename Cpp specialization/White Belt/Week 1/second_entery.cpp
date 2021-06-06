#include <iostream>
#include <string>
using namespace std;

int main(){
    string line;
    int position = 0, counter = -2;
    cin >> line;
    for (auto ch : line){
        if (ch == 'f')
            counter++;
        if (counter == 0){
            cout << position << endl;
            return 0;
        }
        position++;
    }
    cout << counter << endl;    
    return 0;
}