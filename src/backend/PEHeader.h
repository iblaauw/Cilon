#pragma once

class PEFile;

class PEHeader : public DataBlockBase
{
public:
    PEHeader();
    void SetContext(const BlockContext* context);
    void AddSectionHeaders(const std::vector<Section*>& sections);

    int GetPaddedAligment() const override;

    inline PEOptionalHeader* GetOptHeader() const { return optionalHeader.get(); }
protected:
    void GenerateImpl(ByteStream& stream) const override;
private:
    std::vector<std::unique_ptr<SectionHeader>> sectionHeaders;
    std::unique_ptr<PEOptionalHeader> optionalHeader;
    const BlockContext* context;
};

