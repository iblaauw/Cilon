#include "NTHeader.h"

void NTHeader::GenerateImpl(ByteStream& stream) const
{
    stream.Write32(context->file->GetImageBase());
    stream.Write32(context->file->GetSectionVirtualAlignment());
    stream.Write32(PEFile::SectionFileAlignment);
    stream.Write16(5); // OS Major
    stream.Write16(0); // OS Minor
    stream.Write16(0); // User Major
    stream.Write16(0); // User Minor
    stream.Write16(5); // Subsys Major
    stream.Write16(0); // Subsys Minor
    stream.Write32(0); // Reserved

    int numSections = context->file->GetSections().size();
    uint32_t imageSize = (numSections + 1) * context->file->GetSectionVirtualAlignment();
    stream.Write32(imageSize);

    stream.Write32(context->header->GetSize());
    stream.Write32(0); // Checksum

    bool isGui = false; //TODO: route this from the top
    uint16_t subsystem = isGui ? 0x2 : 0x3;
    stream.Write16(subsystem);

    stream.Write16(0x8540); // DLL flags // TODO: figure out what these mean

    stream.Write32(0x100000); // stack reserve size
    stream.Write32(0x1000); // stack commit size
    stream.Write32(0x100000); // heap reserve size
    stream.Write32(0x1000); // heap commit size
    stream.Write32(0); // loader flags
    stream.Write32(PEOptionalHeader::NumberDataDirectories);

    stream.AssertBlockSize(68);
}

