#include "CrossCorrelationTest.h"
#include "CrossCorrelationComputer.h"


CPPUNIT_TEST_SUITE_REGISTRATION(CrossCorrelationTest);

CrossCorrelationTest::CrossCorrelationTest() {
}

CrossCorrelationTest::~CrossCorrelationTest() {
}

void CrossCorrelationTest::setUp() {
}

void CrossCorrelationTest::tearDown() {
}

void CrossCorrelationTest::testSimple() {
    ValueStream* streams[2];
    streams[0] = new ValueStream();
    streams[0]->push_back(1.0f);
    streams[0]->push_back(2.0f);
    streams[0]->push_back(3.0f);
    streams[0]->push_back(4.0f);
    streams[0]->push_back(5.0f);
    streams[1] = new ValueStream();
    streams[1]->push_back(2.0f);
    streams[1]->push_back(3.0f);
    streams[1]->push_back(4.0f);
    streams[1]->push_back(5.0f);
    streams[1]->push_back(6.0f);
    ValueContainer* vc = new ValueContainer(2, streams);
    
    CrossCorrelationComputer cc;
    cc.setData(vc);
    cc.setWindowSize(1);
    cc.setStepSize(1);
    cc.setTauMax(0);
    cc.init();
    
    ValueContainer* vcc = cc.computeAll();
    
    delete vc;
    
    int outStreams = 2*2;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid streams count.", outStreams, (int)vcc->getStreamsCount());
    for (int i = 0; i < outStreams; i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Inconsistent stream length.", (int)vcc->getStream(i)->size(), (int)vcc->getStreamsLength());
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid streams length.", (int)streams[0]->size(), (int)vcc->getStreamsLength());
}

void CrossCorrelationTest::testNormal() {
    ValueStream* streams[3];
    streams[0] = new ValueStream();
    streams[0]->push_back(1.0f);
    streams[0]->push_back(2.0f);
    streams[0]->push_back(3.0f);
    streams[0]->push_back(4.0f);
    streams[0]->push_back(5.0f);
    streams[0]->push_back(4.0f);
    streams[0]->push_back(3.0f);
    streams[0]->push_back(2.0f);
    streams[0]->push_back(1.0f);
    streams[1] = new ValueStream();
    streams[1]->push_back(2.0f);
    streams[1]->push_back(3.0f);
    streams[1]->push_back(4.0f);
    streams[1]->push_back(5.0f);
    streams[1]->push_back(6.0f);
    streams[1]->push_back(5.0f);
    streams[1]->push_back(4.0f);
    streams[1]->push_back(3.0f);
    streams[1]->push_back(2.0f);
    streams[2] = new ValueStream();
    streams[2]->push_back(2.5f);
    streams[2]->push_back(1.3f);
    streams[2]->push_back(8.7f);
    streams[2]->push_back(4.1f);
    streams[2]->push_back(-2.3f);
    streams[2]->push_back(1.0f);
    streams[2]->push_back(4.2f);
    streams[2]->push_back(2.9f);
    streams[2]->push_back(2.0f);
    ValueContainer* vc = new ValueContainer(3, streams);
    
    CrossCorrelationComputer cc;
    cc.setData(vc);
    cc.setWindowSize(3);
    cc.setStepSize(1);
    cc.setTauMax(2);
    cc.init();
    
    ValueContainer* vcc = cc.computeAll();
    
    delete vc;
    
    int outStreams = 3*3;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid streams count.", outStreams, (int)vcc->getStreamsCount());
    for (int i = 0; i < outStreams; i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Inconsistent stream length.", (int)vcc->getStream(i)->size(), (int)vcc->getStreamsLength());
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid streams length.", 5, (int)vcc->getStreamsLength());
}

