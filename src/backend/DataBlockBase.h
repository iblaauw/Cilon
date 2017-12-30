#pragma once

#include <memory>

#include "Address.h"
#include "BlockSize.h"

class DataBlockBase
{
public:
    void AddChild(DataBlockBase* child);

    inline uint32_t GetAddress() const { return address; }
    inline uint32_t GetVirtualAddress() const { return virtualAddress; }
    inline uint32_t GetSize() const { return size; }
    inline uint32_t GetPaddedSize() const { return paddedSize; }

    void Generate(DataBlockStream& stream) const;

    virtual int GetPaddedAligment() const { return 0; }

protected:
    virtual void GenerateImpl(ByteStream& stream) const = 0;

private:
    inline void SetAddress(uint32_t address) { this->address = address; }
    inline void SetVirtualAddress(uint32_t address) { virtualAddress = address; }
    inline void SetSize(uint32_t size) { this->size = size; }
    inline void SetPaddedSize(uint32_t size) { paddedSize = size; }

    std::vector<DataBlockBase*> childBlocks;
    uint32_t address;
    uint32_t virtualAddress;
    uint32_t size;
    uint32_t paddedSize;
};

