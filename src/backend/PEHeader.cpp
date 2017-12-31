#include "PEHeader.h"

PEHeader::PEHeader()
{
    optionalHeader = std::make_unique<PEOptionalHeader>();

    AddChild(optionalHeader.get());
}

void PEHeader::SetContext(const BlockContext* context)
{
    this->context = context;
    auto* file = context->file;

    sectionHeaders.reserve(file->GetSections().size());

    for (auto& sect : file->GetSections())
    {
        auto header = std::make_unique<SectionHeader>(sect);
        AddChild(header.get());
        sectionHeaders.emplace_back(std::move(header));
    }

    optionalHeader->SetContext(context);
}

int PEHeader::GetPaddedAligment() const
{
    return PEFile::SectionFileAlignment;
}

void PEHeader::GenerateImpl(ByteStream& stream) const
{
    // PE signature 'PE\0\0'
    stream.Write8('P');
    stream.Write8('E');
    stream.Write16(0x0);

    stream.Write16(0x014C); // machine
    stream.Write16(sectionHeaders.size()); // num sections
    stream.Write32(/** ??? **/0); // date/time TODO: implement
    stream.Write32(0); // symbol ptr
    stream.Write32(0); // num symbols
    stream.Write16(optionalHeader->GetSize()); // opt-header size

    // TODO: implement 32-bit only flag?
    uint16_t flags = parent->IsDll() ? 0x2002 : 0x0002;
    stream.Write16(flags);

    stream.AssertBlockSize(24);
}

