#include <iostream>
using namespace std;

int main(){
    uint32_t a, b;
    cin >> a >> b;
    if (b == 0){
        cout << "Impossible" << endl;
        return 1;
    }
    cout << a / b;
    return 0;
}