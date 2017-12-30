#include "PEFile.h"

PEFile::PEFile(uint32_t imageBase, uint32_t virtualAlign)
    : sectionFileAlignment(0x200), sectionVirtualAlignment(virtualAlign)
{
    AddChild(&header);
}

Section* PEFile::CreateNewSection(std::string name, uint32_t virtualAddress)
{
    int index = sections.size();
    std::unique_ptr<Section> newSection = std::make_unique<Section>(name, virtualAddress, index, this);
    Section* result = newSection.get();
    sections.emplace_back(std::move(newSection));
    AddChild(result);
    return result;
}

void PEFile::InitStandardSections()
{
    Section* text = CreateNewSection(".text", 0x2000);
    Section* reloc = CreateNewSection(".reloc", 0x4000);
}

void PEFile::GenerateImpl(ByteStream& stream) const
{
    // noop
}

CompiledProgram::CompiledProgram()
    // These constants are arbitrary, change as needed...
    : pe(0x40000, 0x2000)
{
}

void CompiledProgram::Compile(std::ostream& out)
{
    pe.InitStandardSections();

    DataBlockSizeStream sizingStream;
    pe.Generate(sizingStream);

    DataBlockOutputStream outputStream { out };
    pe.Generate(outputStream);
}

