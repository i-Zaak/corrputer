/*
 * File:   DistributedComputationFrameworkTest.h
 * Author: dejvino
 *
 * Created on 11.12.2012, 23:32:26
 */

#ifndef DISTRIBUTEDCOMPUTATIONFRAMEWORKTEST_H
#define	DISTRIBUTEDCOMPUTATIONFRAMEWORKTEST_H

#include <cppunit/extensions/HelperMacros.h>

class DistributedComputationFrameworkTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(DistributedComputationFrameworkTest);

    CPPUNIT_TEST(testSerialization);
    
    CPPUNIT_TEST_SUITE_END();

public:
    DistributedComputationFrameworkTest();
    virtual ~DistributedComputationFrameworkTest();
    void setUp();
    void tearDown();

private:
    void testSerialization();
};

#endif	/* DISTRIBUTEDCOMPUTATIONFRAMEWORKTEST_H */

