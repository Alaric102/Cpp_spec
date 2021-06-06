#include <iostream>
using namespace std;

void UpdateIfGreater(const int& first, int& second){
    if (first > second)
        second = first;
}

int main(){
    int x = 5, y = 2;
    UpdateIfGreater(x, y);
    cout << x << " " << y << endl;
    UpdateIfGreater(7, x);
    cout << x << " " << y << endl;
    return 0;
}