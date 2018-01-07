#pragma once

class RelocSection : public Section
{
public:
    RelocSection(uint32_t virtualAddress, int index, uint32_t sectionVirtualAlignment)
        : Section(".reloc", virtualAddress, index, sectionVirtualAlignment)
    {}

    void SetContext(const BlockContext* context) override
    {
        Section::SetContext(context);
        context->optHeader->RegisterDirectory(5, this);
    }

protected:
    void GenerateImpl(ByteStream& stream) const override
    {
        Section::GenerateImpl(stream);

        uint32_t targetRVA = context->entryPoint->GetVirtualAddress() + 2;

        constexpr uint32_t highMask = 0xFFFFF000;
        uint32_t highPart = targetRVA & highMask;
        uint32_t lowPart = targetRVA & (~highMask);
        stream.Write32(highPart);
        stream.Write32(GetSize());

        constexpr uint16_t fixupType = 0x3; // Use only 4 bits
        uint16_t fixupValue = (fixupType << 12) | static_cast<uint16_t>(lowPart);
        string.Write16(fixupValue);
        stirng.Write16(0); // pad to make aligned with 32 bits
    }
};
