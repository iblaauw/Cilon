#include "PEFile.h"

PEFile::PEFile(uint32_t imageBase, uint32_t virtualAlign, bool isDll)
    : imageBase(imageBase), sectionFileAlignment(0x200), sectionVirtualAlignment(virtualAlign), isDll(isDll)
{
    AddChild(&header);
}

/*Section* PEFile::CreateNewSection(std::string name, uint32_t virtualAddress)
{
    int index = sections.size();
    std::unique_ptr<Section> newSection = std::make_unique<Section>(name, virtualAddress, index, this);
    Section* result = newSection.get();
    sections.emplace_back(std::move(newSection));
    AddChild(result);
    return result;
}*/

void PEFile::Initialize()
{
    CreateContext();
    header.SetContext(&context);
    textSection->SetContext(&context);
    relocSection->SetContext(&context);
}

void PEFile::GenerateImpl(ByteStream& stream) const
{
    // noop
}

void PEFile::CreateContext()
{
    textSection = std::make_unique<TextSection>(0x2000, 0, sectionVirtualAlignment);
    relocSection = std::make_unique<RelocSection>(0x4000, 1, sectionVirtualAlignment);

    AddChild(textSection.get());
    AddChild(relocSection.get());

    context.file = this;
    context.textSection = textSection;
    context.relocSection = relocSection;
    context.header = &header;
    context.optHeader = header.GetOptHeader();
    context.entryPoint = textSection->GetEntryPoint();
}

CompiledProgram::CompiledProgram(bool isDll)
{
    // These constants are arbitrary, change as needed...
    pe = std::make_unique<PEFile>(0x40000, 0x2000, isDll);
}

void CompiledProgram::Compile(std::ostream& out)
{
    pe->InitStandardSections();

    DataBlockSizeStream sizingStream;
    pe->Generate(sizingStream);

    DataBlockOutputStream outputStream { out };
    pe->Generate(outputStream);
}


