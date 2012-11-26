/*
 * File:   ValueContainerSerializationTest.h
 * Author: dejvino
 *
 * Created on 20.11.2012, 19:27:46
 */

#ifndef VALUECONTAINERSERIALIZATIONTEST_H
#define	VALUECONTAINERSERIALIZATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ValueContainerSerializationTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ValueContainerSerializationTest);

    CPPUNIT_TEST(testSaveAndLoad);

    CPPUNIT_TEST_SUITE_END();

public:
    ValueContainerSerializationTest();
    virtual ~ValueContainerSerializationTest();
    void setUp();
    void tearDown();

private:
    void testSaveAndLoad();
};

#endif	/* VALUECONTAINERSERIALIZATIONTEST_H */

