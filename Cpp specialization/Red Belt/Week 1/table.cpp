#include "test_runner.h"
#include <utility>
#include <vector>
using namespace std;

template<typename T>
class Table{
    public:
    Table(size_t n, size_t m){
        Resize(n, m);
    };

    pair<size_t, size_t> Size() const{ 
        if(table.empty() || table[0].empty()){
            return {0, 0};
        }
        return {table.size(), table[0].size()}; 
    };

    void Resize(size_t n, size_t m){
        table.resize(n);
        for (auto& item : table){
            item.resize(m);
        }
    }

    vector<T>& operator[](size_t val){
        return table.at(val);
    };

    const vector<T>& operator[](size_t val) const{
        return table[val];
    };

    private:
    vector<vector<T>> table;
};

// void TestTable() {
//   Table<int> t(1, 1);
//   ASSERT_EQUAL(t.Size().first, 1u);
//   ASSERT_EQUAL(t.Size().second, 1u);
//   t[0][0] = 42;
//   ASSERT_EQUAL(t[0][0], 42);
//   t.Resize(3, 4);
//   ASSERT_EQUAL(t.Size().first, 3u);
//   ASSERT_EQUAL(t.Size().second, 4u);
//   cout << t[0][0] << endl;
//   t.Resize(0, 4);
//   ASSERT_EQUAL(t.Size().first, 0u);
//   ASSERT_EQUAL(t.Size().second, 0u);
// }

int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestTable);
  return 0;
}

// 'is_convertible_v<belts::nonesuch, std::pair<unsigned long, unsigned long> >\' "Member function pair<size_t, size_t> Size() const not found in Table<T>"