#ifndef TESTTESTING_H
#define TESTTESTING_H
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestTesting : public CppUnit::TestFixture
{

CPPUNIT_TEST_SUITE( TestTesting );
CPPUNIT_TEST( test1 );
CPPUNIT_TEST_SUITE_END();

private:

public:
TestTesting();

void setUp()
{
}

void tearDown()
{
}

void test1() {
  CPPUNIT_ASSERT ( 3 == 5 );
}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestTesting );
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestTesting, "TestTesting"  );

#endif // TESTTESTING_H
