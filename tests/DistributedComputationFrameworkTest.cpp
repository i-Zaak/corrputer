/*
 * File:   DistributedComputationFrameworkTest.cpp
 * Author: dejvino
 *
 * Created on 11.12.2012, 23:32:26
 */

#include "DistributedComputationFrameworkTest.h"
#include "mpi/common.h"

#include "../CrossCorrelationComputer.h"
#include "../DistributedComputationFramework.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DistributedComputationFrameworkTest);

DistributedComputationFrameworkTest::DistributedComputationFrameworkTest() {
}

DistributedComputationFrameworkTest::~DistributedComputationFrameworkTest() {
}

void DistributedComputationFrameworkTest::setUp() {
}

void DistributedComputationFrameworkTest::tearDown() {
}

void DistributedComputationFrameworkTest::testSerialization() {
    std::string fileIn("montazr11.vc");
    
    // corel init
    CrossCorrelationComputer* corelComp = new CrossCorrelationComputer();
    corelComp->setTauMax(10);
    corelComp->setWindowSize(10);
    corelComp->setStepSize(10);
    corelComp->setSubpartLength(100);
    
    CrossCorrelationComputer* corelSave = new CrossCorrelationComputer();
    corelSave->setTauMax(10);
    corelSave->setWindowSize(10);
    corelSave->setStepSize(10);
    corelSave->setSubpartLength(100);
    
    // framework init
    DistributedComputationFramework* frameworkComp = new DistributedComputationFramework(&fileIn, corelComp);
    frameworkComp->open();
    
    DistributedComputationFramework* frameworkSave = new DistributedComputationFramework(&fileIn, corelSave);
    frameworkSave->open();
    
    int blocksCount = frameworkComp->getBlocksCount();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Inconsistent framework configurations.",
            blocksCount, frameworkSave->getBlocksCount());
    
    // temp mem
    char* buffer = NULL;
    int size = 0;
    
    // computations
    frameworkComp->setActiveBlock(0);
    
    int block = 0;
    do {
        printf("Computing block %3d/%3d...", block, blocksCount-1);
        frameworkComp->compute();
        
        printf("exporting...");
        frameworkComp->exportBlockData(&buffer, &size);
        
        printf("importing...");
        frameworkSave->importBlockData(buffer, size);
        
        delete[] buffer;
        
        printf("done.\n");
        block++;
    } while (frameworkComp->nextBlock());
    
    // verification
    int index = 0;
    ValueContainer* vcComp = frameworkComp->getOutputValues();
    ValueContainer* vcSave = frameworkSave->getOutputValues();
    CPPUNIT_ASSERT_MESSAGE("Computed values cannot be NULL.", vcComp != NULL);
    CPPUNIT_ASSERT_MESSAGE("Saved values cannot be NULL.", vcSave != NULL);
    for (index = 0; index < vcComp->getStreamsCount(); index++) {
        printf("Comparing stream %4d/%4d...", index, vcComp->getStreamsCount() - 1);
        
        ValueStream* vsComp = vcComp->getStream(index);
        ValueStream* vsSave = vcSave->getStream(index);
        CPPUNIT_ASSERT_MESSAGE("Computed stream cannot be NULL.", vsComp != NULL);
        CPPUNIT_ASSERT_MESSAGE("Saved stream cannot be NULL.", vsSave != NULL);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Inconsistent output sizes.",
                vsComp->size(), vsSave->size());
        for (int p = 0; p < vsComp->size(); p++) {
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Inconsistent output values.",
                vsComp->at(p), vsSave->at(p));
        }
        
        printf("done.\n");
    }   
}


