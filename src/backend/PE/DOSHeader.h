#pragma once

#include "DataBlockBase.h"

class DOSHeader : public DataBlockBase
{
public:
    DOSHeader(DataBlockBase& peBlock);
protected:
    void GenerateImpl(ByteStream& stream) override;
private:
    const DataBlockBase& peBlock;
};

