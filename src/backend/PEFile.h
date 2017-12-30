#pragma once

class PEFile : public DataBlockBase
{
public:
    PEFile(uint32_t imageBase, uint32_t virtualAlign);

    static constexpr uint32_t SectionFileAlignment = 0x200;

    Section* CreateNewSection(std::string name, uint32_t virtualAddress);

    void InitStandardSections();

    inline uint32_t GetSectionVirtualAlignment() const { return sectionVirtualAlignment; }

protected:
    void GenerateImpl(ByteStream& stream) const override;
private:
    PEHeader header;
    std::vector<std::unique_ptr<Section>> sections;
    uint32_t sectionVirtualAlignment;
    bool isDll;
};

class CompiledProgram
{
public:
    CompiledProgram();
    void Compile(std::ostream& out);
private:
    PEFile pe;
};

