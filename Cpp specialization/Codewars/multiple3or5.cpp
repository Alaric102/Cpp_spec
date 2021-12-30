#include <set>
#include <iostream>
using namespace std;

int solution(int number) 
{
    set<int> nums;
    int num_by_val = 3;
    while (num_by_val < number){
    nums.insert(num_by_val);
    num_by_val += 3;
    }

    num_by_val = 5;
    while (num_by_val < number){
    nums.insert(num_by_val);
    num_by_val += 5;
    }

    int res = 0;
    for (auto item : nums){
        res += item;
    }
    return res;
}

int main(){
    int num = 0;
    cin >> num;

    solution(num);
}