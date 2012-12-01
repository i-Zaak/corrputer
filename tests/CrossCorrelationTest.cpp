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
    ValueContainer vc(2, streams);
    
    CrossCorrelationComputer cc();
    cc.setData(vc);
    ValueContainer* vcc = cc.computeAll();
    
    CPPUNIT_ASSERT(vcc->getStreamsCount() == 2*2);
    CPPUNIT_ASSERT(vcc->getStreamsLength() == streams[0]->size());
}

