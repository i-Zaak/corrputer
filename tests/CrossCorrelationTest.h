/*
 * File:   CrossCorrelationTest.h
 * Author: dejvino
 *
 * Created on 29.11.2012, 20:08:15
 */

#ifndef CROSSCORRELATIONTEST_H
#define	CROSSCORRELATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CrossCorrelationTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CrossCorrelationTest);

    CPPUNIT_TEST(testSimple);
    CPPUNIT_TEST(testNormal);

    CPPUNIT_TEST_SUITE_END();

public:
    CrossCorrelationTest();
    virtual ~CrossCorrelationTest();
    void setUp();
    void tearDown();

private:
    void testSimple();
    void testNormal();
};

#endif	/* CROSSCORRELATIONTEST_H */

