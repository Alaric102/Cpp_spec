#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

  void Read(int user_id, int page_count) {        // O(N)
    if (user_page_counts_[user_id] == 0) {        // O(c)
      AddUser(user_id);                           // O(c)
    }
    user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {   // O(N) * O(c)
      SwapUsers(position, position - 1);          // O(c)
    }
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];

    // O(N^2)
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }
    
    return (user_count - position) * 1.0 / (user_count - 1);
  }

private:

  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;
  vector<int> user_positions_;

  int GetUserCount() const {                              // O(c)
    return sorted_users_.size();
  }

  void AddUser(int user_id) {                             // O(c)
    sorted_users_.push_back(user_id);                     // O(c)
    user_positions_[user_id] = sorted_users_.size() - 1;  // O(c)
  }

  void SwapUsers(int lhs_position, int rhs_position) {    // O(c)
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
};

class PageManager {
public:
  PageManager(): 
  user_to_page_(MAX_USER_COUNT_ + 1, 0), 
  pages(MAX_PAGE_COUNT_ + 1, {0, 0}) {}

  void Read(int user_id, int page_count){
    int old_page_count = user_to_page_[user_id];
    user_to_page_[user_id] = page_count;
    if (old_page_count == 0){
      user_count++;
    }
    
    pages[old_page_count].users_current--;
    for (old_page_count; old_page_count < page_count; ++old_page_count)
      pages[old_page_count].users_after++;
    pages[page_count].users_current++;
  }

  double Cheer(int user_id) const {
    int page_num = user_to_page_[user_id];
    if (page_num == 0)
      return 0.0;
    
    if (user_count == 1){
      return 1.0;
    }

    double res =  (user_count - (pages[page_num].users_after + pages[page_num].users_current) * 1.0) / (user_count - 1);
    return res;
  }

  void PrintUser2Pages(){
    for (int i = 0; i < 10; ++i){
      if (user_to_page_[i])
        cout << "user " << i << " : " << user_to_page_[i] << endl;
    }
    cout << "User count: " << user_count << endl;
  };

private:
  struct Page
  {
    int users_after = 0;
    int users_current = 0;
  };
  
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;

  vector<int> user_to_page_;
  vector<Page> pages;
  int user_count = 0;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  PageManager manager;
  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);                            // O(N)
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";    // O(N)
    }
  }

  return 0;
}