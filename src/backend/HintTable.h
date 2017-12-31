#pragma once

class HintTable : public DataBlockBase
{
public:
    void SetContext(const BlockContext* context);
protected:
    void GenerateImpl(ByteStream& stream) const override;
private:
    std::unique_ptr<RawString> importString;
};
