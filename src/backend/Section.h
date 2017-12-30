#pragma once

#include "DataBlockBase.h"

class SectionHeader;
class PEFile;

class Section : public DataBlockBase
{
public:
    Section(std::string name, uint32_t vAddress, int index, PEFile* owner);

    enum class ContainsFlags
    {
        HasCode = 0x2,
        HasInitData = 0x4,
        HasUninitData = 0x8,
    };

    enum class AccessFlags
    {
        CanExecute = 0x2,
        CanRead = 0x4,
        CanWrite = 0x8
    };

    void SetFlags(ContainsFlags cflags, AccessFlags aflags);
    uint32_t GetRawFlags() const { return flags; }

    std::string GetName() const { return name; }

    int GetPaddedAligment() const override;

protected:
    void GenerateImpl(ByteStream& stream) const override;
private:
    std::string name;
    PEFile* owningFile;
    uint32_t virtualAddress;
    uint32_t virtualSize;
    uint32_t flags;
    int selfIndex;
};

class SectionHeader : public DataBlockBase
{
public:
    SectionHeader(const Section* section);

    void GenerateImpl(ByteStream& stream) const;

private:
    const Section* section;
};

