#pragma once

struct BlockContext
{
    PEFile* file;
    PEHeader* header;
    PEOptionalHeader* optHeader;
    Section* textSection;
    Section* relocSection;
    DataBlockBase* entryPoint;
};
