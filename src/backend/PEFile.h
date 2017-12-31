#pragma once

class PEFile : public DataBlockBase
{
public:
    PEFile(uint32_t imageBase, uint32_t virtualAlign, bool isDll);

    static constexpr uint32_t SectionFileAlignment = 0x200;

    //Section* CreateNewSection(std::string name, uint32_t virtualAddress);

    void Initialize();

    inline uint32_t GetSectionVirtualAlignment() const { return sectionVirtualAlignment; }
    inline uint32_t GetImageBase() const { return imageBase; }

    inline const std::vector<std::unique_ptr<Section>>& GetSections() const { return sections; }

    inline bool IsDll() const { return isDll; }
protected:
    void GenerateImpl(ByteStream& stream) const override;
private:

    void CreateContext();

    PEHeader header;
    BlockContext context;
    //std::vector<std::unique_ptr<Section>> sections;
    std::unique_ptr<TextSection> textSection;
    std::unique_ptr<RelocSection> relocSection;
    uint32_t imageBase;
    uint32_t sectionVirtualAlignment;
    bool isDll;
};

class CompiledProgram
{
public:
    CompiledProgram(bool isDll);
    void Compile(std::ostream& out);
private:
    std::unique_ptr<PEFile> pe;
};

