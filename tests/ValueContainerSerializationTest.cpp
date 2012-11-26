/*
 * File:   ValueContainerSerializationTest.cpp
 * Author: dejvino
 *
 * Created on 20.11.2012, 19:27:47
 */

#include "ValueContainerSerializationTest.h"

#include "../common.h"
#include "../ValueContainer.h"
#include "../ValueStream.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ValueContainerSerializationTest);

ValueContainerSerializationTest::ValueContainerSerializationTest() {
}

ValueContainerSerializationTest::~ValueContainerSerializationTest() {
}

void ValueContainerSerializationTest::setUp() {
}

void ValueContainerSerializationTest::tearDown() {
}

void ValueContainerSerializationTest::testSaveAndLoad() {
    ValueStream vs;
    vs.push_back(1.0f);
    vs.push_back(2.5f);
    vs.push_back(-1.3f);
    
    ValueContainer vc;
    vc.setStreamsCount(1);
    vc.setStreamsLength(3);
    vc.setStream(0, &vs);
    
    char* filename = "test_saveAndLoad.vc";
    
    // save
    {
        std::ofstream file(filename, std::ios::binary);
    
        vc.saveHeader(file);
        vc.saveStream(0, file);
        
        file.close();
    }
 
    {
        std::ifstream file(filename);
        CPPUNIT_ASSERT(file);
    }
    
    // load
    {
        ValueContainer vcl;
        
        std::ifstream file(filename, std::ios::binary);
    
        vcl.loadHeader(file);
        
        CPPUNIT_ASSERT_EQUAL(vc.getStreamsCount(), vcl.getStreamsCount());
        CPPUNIT_ASSERT_EQUAL(vc.getStreamsLength(), vcl.getStreamsLength());
        
        vcl.loadStream(0, file);
        ValueStream* vsl = vcl.getStream(0);
        for (int i = 0; i < vcl.getStreamsLength(); i++) {
            CPPUNIT_ASSERT_EQUAL(vs.at(i), vsl->at(i));
        }
    }
}
