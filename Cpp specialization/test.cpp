#include <iostream>
#include <list>
 
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
 
int main ()
{
    std::list<int> list = { 1, 2, 3, 4, 5 };
    std::cout << "list before: " << list << "\n";
 
    auto it1 = list.begin();
    // std::advance(it1, 1);

    auto it2 = list.begin();
    std::advance(it2, list.size() - 1);
    
    std::cout << "it1: " << *it1 << "\n";
    std::cout << "it2: " << *it2 << "\n";
    
    list.splice(it1, list, it2);
    std::cout << "list before: " << list << "\n";

    list.splice(list.end(), list, it1);
    std::cout << "list before: " << list << "\n";
    
    // std::cout << "list2: " << list2 << "\n";
 
    // list2.splice(list2.begin(), list1, it, list1.end());
 
    // std::cout << "list1: " << list1 << "\n";
    // std::cout << "list2: " << list2 << "\n";
}