#include "airline_ticket.h"
#include "test_runner.h"
#include <iostream>
using namespace std;

bool operator < (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator < (const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator == (const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& os, const Date& d) {
  return os << d.year << '-' << d.month << '-' << d.day;
}

ostream& operator<<(ostream& os, const Time& t) {
  return os << t.hours << ':' << t.minutes;
}

istream& operator>> (istream& ss, Date& d){
  ss >> d.year;
  ss.ignore(1);
  ss >> d.month;
  ss.ignore(1);
  ss >> d.day;
  return ss;
}

istream& operator>> (istream& ss, Time& t){
  ss >> t.hours;
  ss.ignore(1);
  ss >> t.minutes;
  return ss;
}

#define UPDATE_FIELD(ticket, field, values) { \
    if (values.count(#field)){                \
      istringstream is(values.at(#field));    \
      is >> ticket.field;                     \
    }                                         \
  }

// void TestUpdate() {
//   AirlineTicket t;
//   t.price = 0;

//   const map<string, string> updates1 = {
//     {"departure_date", "2018-2-28"},
//     {"departure_time", "17:40"},
//   };
//   UPDATE_FIELD(t, departure_date, updates1);
//   UPDATE_FIELD(t, departure_time, updates1);
//   UPDATE_FIELD(t, price, updates1);

//   ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//   ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//   ASSERT_EQUAL(t.price, 0);

//   const map<string, string> updates2 = {
//     {"price", "12550"},
//     {"arrival_time", "20:33"},
//   };
//   UPDATE_FIELD(t, departure_date, updates2);
//   UPDATE_FIELD(t, departure_time, updates2);
//   UPDATE_FIELD(t, arrival_time, updates2);
//   UPDATE_FIELD(t, price, updates2);

//   ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//   ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//   ASSERT_EQUAL(t.price, 12550);
//   ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
// }

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestUpdate);
// }