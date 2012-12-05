#include "DistributedComputationFramework.h"

DistributedComputationFramework::DistributedComputationFramework(std::string* fileIn, CorrelationComputer* cc) : ComputationFramework(fileIn, NULL, cc) {
}

DistributedComputationFramework::~DistributedComputationFramework() {
}

