// #include "test_runner.h"

#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2){
        return;
    } else {
        vector<typename RandomIt::value_type> range(
            std::make_move_iterator(range_begin),
            std::make_move_iterator(range_end)
        );
        vector<typename RandomIt::value_type> temp;

        MergeSort(begin(range), begin(range) + range.size()/3 );
        MergeSort(begin(range) + range.size()/3 , begin(range) + 2*range.size()/3 );
        MergeSort(begin(range) + 2*range.size()/3 , end(range));

        merge(
            std::make_move_iterator(range.begin()),
            std::make_move_iterator(range.begin() + range.size() * 1/3),
            std::make_move_iterator(range.begin() + range.size() * 1/3),
            std::make_move_iterator(range.begin() + range.size() * 2/3),
            back_inserter(temp)
        );
        merge(
            std::make_move_iterator(temp.begin()), 
            std::make_move_iterator(temp.end()),
            std::make_move_iterator(range.begin() + range.size() * 2/3), 
            std::make_move_iterator(range.end()),
            range_begin
        );
    }
}

// void TestIntVector() {
//   vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
//   MergeSort(begin(numbers), end(numbers));
//   ASSERT(is_sorted(begin(numbers), end(numbers)));
// }

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestIntVector);
//   return 0;
// }