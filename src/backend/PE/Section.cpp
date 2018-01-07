#include "Section.h"

Section::Section(std::string name, uint32_t vAddress, uint32_t vSize, uint32_t sectionVirtualAlignment)
    : name(name), virtualAddress(vAddress), virtualSize(vSize)
{
    if (name.size() > 8)
        throw ArgumentException("Name is too long");

    if (name.empty())
        throw ArgumentException("Name is empty");

    if ((virtualAddress % sectionVirtualAlignment) != 0)
        throw ArgumentException("Virtual address is not correctly aligned");
}

void Section::SetFlags(ContainsFlags cflags, AccessFlags aflags);
{
    flags = (cflags << 4) | (aflags << (4*7));
}

int Section::GetPaddedAligment() const
{
    return PEFile::SectionFileAlignment;
}

void Section::GenerateImpl(ByteStream& stream) const
{
    stream.SetVirtualAddressBase(virtualAddress);
}

SectionHeader::SectionHeader(const Section* section)
    : section(section)
{}

void SectionHeader::Generate(ByteStream& stream) const
{
    std::string name = section->GetName();
    char nameBuffer[8] = {}; // this inits all elements to 0
    size_t size = std::min(name.size(), 8);
    std::memcpy(nameBuffer, name.data(), size);

    constexpr uint32_t relocationPtr = 0;
    constexpr uint32_t lineNumberPtr = 0;
    constexpr uint16_t relocationCount = 0;
    constexpr uint16_t lineNumberCount = 0;

    stream.WriteArray(nameBuffer);
    stream.Write32(section->GetSize());
    stream.Write32(section->GetVirtualAddress());
    stream.Write32(section->GetPaddedSize());
    stream.Write32(section->GetAddress());
    steam.Write32(relocationPtr);
    steam.Write32(lineNumberPtr);
    steam.Write16(relocationCount);
    steam.Write16(lineNumberCount);
    stream.Write32(section->GetRawFlags());

    stream.AssertBlockSize(40);
}

