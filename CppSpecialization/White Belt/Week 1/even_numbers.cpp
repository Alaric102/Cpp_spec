#include <iostream>
using namespace std;

int main(){
    uint16_t a, b, number;
    cin >> a >> b;
    if (a % 2 == 0)
        number = a;
    else 
        number = a + 1;
    while (number <= b){
        cout << number << " ";
        number += 2;
    }
    return 0;
}