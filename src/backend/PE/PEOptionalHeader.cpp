#include "PEOptionalHeader.h"

PEOptionalHeader::PEOptionalHeader()
{
    directories.resize(NumberDataDirectories);

    AddChild(&ntHeader);

    for (auto& dir : directories)
    {
        AddChild(&dir);
    }
}

void PEOptionalHeader::SetContext(const BlockContext* context)
{
    this->context = context;
    ntHeader.SetContext(context);
}

void PEOptionalHeader::RegisterDirectory(int index, DataBlockBase* directory)
{
    directories.at(index).directory = directory;
}

void PEOptionalHeader::GenerateImpl(ByteStream& stream) const
{
    stream.Write16(0x010B); // magic
    stream.Write8(0x6); // linker major
    stream.Write8(0x0); // linker minor
    stream.Write32(context->codeSection->GetPaddedSize());
    stream.Write32(context->relocSection->GetPaddedSize());
    stream.Write32(0); // uninit data size
    stream.Write32(context->entryPointBlock->GetVirtualAddress());
    stream.Write32(context->codeSection->GetVirtualAddress());
    stream.Write32(context->relocSection->GetVirtualAddress());

    stream.AssertBlockSize(28);
}


void PEOptionalHeader::DataDirectory::GenerateImpl(ByteStream& stream)
{
    stream.Write32(directory->GetVirtualAddress());
    stream.Write32(directory->GetSize());

    stream.AssertBlockSize(8);
}

