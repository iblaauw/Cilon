#include "TextSection.h"

TextSection::TextSection(uint32_t virtualAddress, int index, uint32_t sectionVirtualAlignment)
    : Section(".text", virtualAddress, index, sectionVirtualAlignment), dllString("mscoree.dll")
{
    AddChild(&iat);
    AddChild(&cli);
    AddChild(&importTable);
    AddChild(&ilt);
    AddChild(&hintTable);
    AddChild(&dllString);
    AddChild(&padding);
    AddChild(&padding2);
    AddChild(&entryPoint);
}

void TextSection::SetContext(const BlockContext* context)
{
    Section::SetContext(context);

    iat.SetHintTable(&hintTable);
    importTable.SetTextContext(&iat, &ilt, &dllString);
    ilt.SetHintTable(&hintTable);
    hintTable.SetContext(context);
    entryPoint.SetContext(context);

    context->optHeader->RegisterDirectory(1, &importTable);
    context->optHeader->RegisterDirectory(12, &iat);
    context->optHeader->RegisterDirectory(14, &cliHeader);
}

