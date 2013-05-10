#include "SimpleComputationFramework.h"

SimpleComputationFramework::SimpleComputationFramework(std::string* fileIn, std::vector<std::string*> filesOut, CorrelationComputer* cc) : ComputationFramework(fileIn, filesOut, cc) {
}

SimpleComputationFramework::~SimpleComputationFramework() {
}

