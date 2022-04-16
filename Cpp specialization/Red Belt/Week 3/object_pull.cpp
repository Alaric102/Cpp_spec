// #include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate(){
        if (liberated.empty()){
            T* newPtr = new T;
            dedicated.insert(newPtr);
            return newPtr;
        }
        T* ptr = liberated.front();
        liberated.pop();
        dedicated.insert(ptr);
        return ptr;
    };
    
    T* TryAllocate(){
        if (liberated.empty()){
            return nullptr;
        }
        T* ptr = liberated.front();
        liberated.pop();
        dedicated.insert(ptr);
        return ptr;
    };

    void Deallocate(T* object){
        auto itObject = dedicated.find(object);
        if (itObject == dedicated.end()){
            throw invalid_argument("");
        }
        
        liberated.push(*itObject);
        dedicated.erase(itObject);
    };

    ~ObjectPool(){
        for (auto it : dedicated) {
            delete it;
        }
        while (!liberated.empty()){
            T* ptr = liberated.front();
            liberated.pop();
            delete ptr;
        }
    };

private:
    queue<T*> liberated;
    set<T*> dedicated;
};

// void TestObjectPool() {
//   ObjectPool<string> pool;

//   auto p1 = pool.Allocate();
//   auto p2 = pool.Allocate();
//   auto p3 = pool.Allocate();

//   *p1 = "first";
//   *p2 = "second";
//   *p3 = "third";

//   pool.Deallocate(p2);
//   ASSERT_EQUAL(*pool.Allocate(), "second");

//   pool.Deallocate(p3);
//   pool.Deallocate(p1);
//   ASSERT_EQUAL(*pool.Allocate(), "third");
//   ASSERT_EQUAL(*pool.Allocate(), "first");

//   pool.Deallocate(p1);
// }

// void Test1(){
//     string* p1;
//     {
//         ObjectPool<string> pool;
//         p1 = pool.Allocate();
//         *p1 = "first";  
//         pool.Deallocate(p1);
//         try
//         {
//             pool.Deallocate(p1);
//         }
//         catch(const std::invalid_argument& e)
//         {
//             std::cerr << e.what() << '\n';
//         }
//     }

// }

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestObjectPool);
//   RUN_TEST(tr, Test1);
  
//   return 0;
// }