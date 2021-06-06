#include <iostream>
using namespace std;

unsigned int factorial(unsigned int a){
    if (a == 1)
        return 1;
    return a * factorial(a-1);
}

int main(){
    unsigned int a;
    cin >> a;
    cout << factorial(a);
}