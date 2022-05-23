#include <iostream>
#include <vector>
using namespace std;

int main(){
    unsigned int a;
    cin >> a;

    vector<int> reversed_bits;
    while (a > 1){
        reversed_bits.push_back(a % 2);
        a /= 2;
    }
    reversed_bits.push_back(a);
    
    bool first_one = false;
    for (uint8_t i = reversed_bits.size(); i > 0; i--){
        if (!first_one && reversed_bits[i - 1] == 1)
            first_one = true;
        if (first_one)
            cout << reversed_bits.at(i - 1);
    }
    return 0;
}