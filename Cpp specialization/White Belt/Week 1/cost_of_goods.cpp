#include <iostream>
using namespace std;

int main(){
    float n, a, b;
    float x, y;
    cin >> n >> a >> b >> x >> y;
    if (n > b)
        cout << n - n * y / 100.0f << endl;
    else if (n > a)
        cout << n - n * x / 100.0f << endl;
    else
        cout << n << endl;
    return 0;
}