#include <string>
using namespace std;

struct Specialization
{
    explicit Specialization(const string& val){
        value = val;
    }
    string value;
};

struct Course
{
    explicit Course(const string& val){
        value = val;
    }
    string value;
};

struct Week
{
    explicit Week(const string& val){
        value = val;
    }
    string value;
};

struct LectureTitle {
  explicit LectureTitle(const Specialization& sp,const Course& co, const Week& we){
      specialization = sp.value;
      course = co.value;
      week = we.value;
  }
  string specialization;
  string course;
  string week;
};
