#include "../common.h"
#include "TestedDistributedComputationFramework.h"

TestedDistributedComputationFramework::TestedDistributedComputationFramework(std::string* fileIn, std::string* fileOut, CorrelationComputer* cc) : DistributedComputationFramework(fileIn, fileOut, cc) {
}

TestedDistributedComputationFramework::~TestedDistributedComputationFramework() {
}

void TestedDistributedComputationFramework::onResultComputed(int index, ValueStream* vs)
{
    // save for later
    this->results[index] = new ValueStream(*vs);
    
    // carry on...
    DistributedComputationFramework::onResultComputed(index, vs);
}