#pragma once

#include "Method.h"
#include "BasicBlock.h"

class MethodBuilder
{
public:
    MethodBuilder(Method* method);
private:
    Method* method;
    BasicBlock* currentBlock;
    std::vector<std::unique_ptr<BasicBlock>> basicBlocks;
};

