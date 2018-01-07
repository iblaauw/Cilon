#pragma once

class TextSection : public Section
{
public:
    TextSection(uint32_t virtualAddress, int index, uint32_t sectionVirtualAlignment);
    void SetContext(const BlockContext* context) override;

    DataBlockBase* GetEntryPoint() { return &entryPoint; }
private:
    ImportAddressTable iat; // used by: import table
    CLIDataBlock cli;
    ImportTable importTable;
    ImportAddressTable ilt; // used by: import table
    HintTable hintTable; // used by: IAT, ILT
    RawString dllString; // used by: import table
    Padding<4> padding;
    Zeros<2> padding2;
    EntryPointBlock entryPoint;
};
