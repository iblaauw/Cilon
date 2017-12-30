#pragma once

class ByteStream
{
public:
    void Write8(uint8_t data);
    void Write16(uint16_t data);
    void Write32(uint32_t data);
    void Write64(uint64_t data);

    template <size_t Size>
    void WriteArray(uint8_t data[Size]) { WriteRaw(Size, data); }

    virtual void SetVirtualAddressBase(uint32_t address) = 0;
    virtual void AssertBlockSize(int size) const = 0;

protected:
    virtual void WriteRaw(int size, void* data) = 0;
};

class DataBlockStream : public ByteStream
{
public:
    virtual void BeginBlock() = 0;
    virtual void EndBlock() = 0;

    virtual bool IsSizeMode() const = 0;

    virtual uint32_t GetBlockSize() const = 0;
    virtual uint32_t GetBlockPaddedSize() const = 0;
    virtual uint32_t GetBlockAddress() const = 0;
    virtual uint32_t GetBlockVirtualAddress() const = 0;

    virtual void PadToMultiple(int size) = 0;

    void AssertBlockSize(int size) const override;
};

// This stream does sizing calculation only
class DataBlockSizeStream : public DataBlockStream
{
public:
    // ByteStream impl
    void SetVirtualAddressBase(uint32_t address) override;

    // DataBlockStream impl
    void BeginBlock();
    void EndBlock();

    bool IsSizeMode() const override { return true; }

    uint32_t GetBlockSize() const override;
    uint32_t GetBlockPaddedSize() const override;
    uint32_t GetBlockAddress() const override;
    uint32_t GetBlockVirtualAddress() const override;

    void PadToMultiple(int size) override;

protected:
    void WriteRaw(int size, void* data) override;

private:
    struct BlockData
    {
        uint32_t address;
        uint32_t vAddress;
    };

    std::vector<BlockData> blockData;
    uint32_t position;
    uint32_t paddedPosition;
};

// This stream doesn't bother with calculating sizing or address, it just outputs data
class DataBlockOutputStream : public DataBlockStream
{
public:
    // ByteStream impl
    virtual void PadToMultiple(int size) = 0;
    virtual void AssertBlockSize(int size) const = 0;

    // DataBlockStream impl
    virtual void BeginBlock() = 0;
    virtual void EndBlock() = 0;

    bool IsSizeMode() const override { return false; }

    virtual uint32_t GetBlockSize() const = 0;
    virtual uint32_t GetBlockPaddedSize() const = 0;
    virtual uint32_t GetBlockAddress() const = 0;
    virtual uint32_t GetBlockVirtualAddress() const = 0;
protected:
    virtual void WriteRaw(int size, void* data) = 0;
};



