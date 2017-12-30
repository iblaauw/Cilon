#include "ByteStream.h"

/**** ByteStream ****/

void ByteStream::Write8(uint8_t data) { WriteRaw(1, &data); }
void ByteStream::Write16(uint16_t data) { WriteRaw(2, &data); }
void ByteStream::Write32(uint32_t data) { WriteRaw(4, &data); }
void ByteStream::Write64(uint64_t data) { WriteRaw(8, &data); }

/**** DataBlockStream ****/

void DataBlockStream::AssertBlockSize(int size) const
{
    if (IsSizeMode())
    {
        if (size != GetBlockSize())
        {
            throw AssertionException("Block is the incorrect size...");
        }
    }
}

void DataBlockSizeStream::SetVirtualAddressBase(uint32_t address)
{
    BlockData& data = blockData.back();
    data.vAddress = address;
}

void DataBlockSizeStream::BeginBlock()
{
    if (blockData.size() == 0)
    {
        BlockData first = { 0, 0 };
        blockData.push_back(first);
    }
    else
    {
        const BlockData& prev = blockData.back();
        BlockData next;
        next.address = position;
        next.vAddress = (position - prev.address) + prev.vAddress;
        blockData.push_back(next);
    }
}

void DataBlockSizeStream::EndBlock()
{
    blockData.pop_back();
}

uint32_t DataBlockSizeStream::GetBlockSize() const
{
    return position - blockData.front().address;
}

uint32_t DataBlockSizeStream::GetBlockPaddedSize() const
{
    return paddedPosition - blockData.front().address;
}

uint32_t DataBlockSizeStream::GetBlockAddress() const
{
    return blockData.front().address;
}

uint32_t DataBlockSizeStream::GetBlockVirtualAddress() const
{
    return blockData.front().vAddress;
}

void DataBlockSizeStream::PadToMultiple(int size)
{
    position = paddedPosition;

    uint32_t currentSize = GetBlockPaddedSize();

    if (currentSize % size == 0)
        return;

    int multiple = currentSize / size;
    int newSize = size * (multiple + 1);

    paddedPosition = newSize;
}

void DataBlockSizeStream::WriteRaw(int size, void* data)
{
    position += size;
    paddedPosition = position;
}




