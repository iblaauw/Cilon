#pragma once

class NTHeader : public DataBlockBase
{
public:
    void SetContext(const BlockContext* context) { this->context = context; }
protected:
    void GenerateImpl(ByteStream& stream) const override;
private:
    const BlockContext* context;
};

