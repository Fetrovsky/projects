// Copyright (C) 2011, Daniel Valencia (Fetrovsky)
// 
// Usage:
//   Define a test by using the TEST macro.
//   Check for conditions using the CHECK* macros.
//
//   TEST(max) {
//        CHECK_EQ(max(3, 4), 4);
//        CHECK_EQ(max(3, 3), 3);
//        CHECK_EQ(max(-100, 0, 100), 100);
//   }

#ifndef TESTING_BASE_H_INCLUDED
#define TESTING_BASE_H_INCLUDED

#include <algorithm>
#include <list>

#include "../base/debugging.h"

class TestCase {
     public:
          typedef void (*Test)();
          typedef std::pair<std::string, Test> TestSpec;

          TestCase(std::string const& name, Test test) {
               _tests.push_back(std::make_pair(name, test));
          }

          static void RunAll() {
               std::cout << "Running " << _tests.size() << " test(s).\n";
               for_each(_tests.begin(), _tests.end(), Invoke);
          }

          static void Invoke(TestSpec const& test_spec) {
               _current_test = &test_spec;
               OUT << "Running " << _current_test->first << std::endl;
               _current_test->second();
          }

          static TestSpec const& current_test() { return *_current_test; }

     private:
          typedef std::list<TestSpec> TestList;
          typedef TestList::const_iterator TestIterator;

          static TestList _tests;
          static TestSpec const* _current_test;
};

TestCase::TestList TestCase::_tests;
TestCase::TestSpec const* TestCase::_current_test;

#define TEST(test_name) \
void test_name(); \
TestCase o_##test_name(#test_name, &test_name); \
void test_name()

#define TEST_ERROR PREFIX_ERROR(TestCase::current_test().first)

#define CHECK_T CHECK
#define CHECK_F(x) CHECK(!x)

#define CHECK(x) \
     if (!x) TEST_ERROR << "Test failed: " << #x << std::endl

#define CHECK_EQ(a, b) \
     if ((a) != (b)) TEST_ERROR << "No match." << std::endl \
                                << "Expected: " << std::endl \
                                << PrepareValue(#b, b) \
                                << "Encountered: " << std::endl \
                                << PrepareValue(#a, a)

#define CHECK_NEQ(a, b) \
     if ((a) == (b)) TEST_ERROR << "Unexpected match for " << #b << ":\n" \
                                << PrepareValue(#a, a)

int main() {
     TestCase::RunAll();
     return 0;
}

#endif  // TESTING_BASE_H_INCLUDED

