#include "deque_vector.h"
#include <iostream>
#include "test_runner.h"

void TestDeque() {
    Deque<int> t;
    ASSERT_EQUAL(t.Empty(), true);
    ASSERT_EQUAL(t.Size(), 0u);
    {
        ostringstream ss;
        try {
            t.At(0);
        }
        catch(const std::exception& e) {
            ss << e.what();
        }
        ASSERT_EQUAL(ss.str(), "");
    }

    {
        t.PushFront(-1);
        ASSERT_EQUAL(t.Empty(), false);
        ASSERT_EQUAL(t.Size(), 1u);
        t.PushBack(1);
        ASSERT_EQUAL(t.Empty(), false);
        ASSERT_EQUAL(t.Size(), 2u);
    }

    {
        t.PushFront(-2);
        ostringstream ss;
        ss << t[0] << ", " << t[t.Size() - 1];
        ASSERT_EQUAL(ss.str(), "-2, 1");
        
        ss.str("");
        t.PushBack(2);
        ss << t[1] << ", " << t[t.Size() - 2];
        ASSERT_EQUAL(ss.str(), "-1, 1");
    }

    {
        ostringstream ss;
        ss << t.At(1) << ", " << t.At(3);
        ASSERT_EQUAL(ss.str(), "-1, 2");

        ss.str("");
        try {
            t.At(4);
        }
        catch(const std::exception& e) {
            ss << e.what();
        }
        ASSERT_EQUAL(ss.str(), "out of range");
    }

    {
        ostringstream ss;
        ss << t.Front() << ", " << t.Back();
        ASSERT_EQUAL(ss.str(), "-2, 2");
    }

    {
        stringstream ss;
        t.PushBack(3);
        t.PushFront(-3);
        ss << t.Front();
        ASSERT_EQUAL(ss.str(), "-3");
    }
    
}

void foo(Deque<int> const& d) {
	for (int i = 0; i < d.Size(); ++i) {
		cout << d.At(i) << ", ";
	}
    cout << endl;
}

#define PRINT(x) std::cout << x << std::endl

int main(){
    TestRunner tr;
    RUN_TEST(tr, TestDeque);

	Deque<int> deque;
	deque.PushFront(1);
	deque.PushBack(2);
	foo(deque);

    Deque<int> d;
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);
    PRINT("--");
    PRINT(d.Front());
    PRINT(d.Back());
    d.PushFront(4);
    d.PushFront(5);
    PRINT(d.Front());
    PRINT(d.Back());
    PRINT("--");
    PRINT(d[0]);
    PRINT(d[1]);
    PRINT(d[2]);
    PRINT(d[3]);
    PRINT(d[4]);

    return 0;
}

/*
Compile error: b'/tmp/submissionc917mz9n/tmpbygub4hx.cpp:64:20: fatal error: binding reference of type \'int\' to value of type \
'const __gnu_cxx::__alloc_traits<std::allocator<int>, int>::value_type\' (aka \'const int\') drops \'const\' qualifier\n            
return direct.front();\n                   ^~~~~~~~~~~~~~\n/tmp/submissionc917mz9n/tmpbygub4hx.cpp:179:19: note: 
in instantiation of member function \'Deque<int>::Front\' requested here\n  belts::Assert(c.Front() == 3,
 "Wrong result of const Front after PushFront/PushBack");\n                  ^\n1 error generated.\n'

*/