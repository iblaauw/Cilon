#pragma once

class EntryPoint : public DataBlockBase
{
public:
    void SetContext(const BlockContext* context) { this->context = context; }
protected:
    void GenerateImpl(ByteStream& stream) const override
    {
        stream.Write8(0xFF);
        stream.Write8(0x25);
        uint32_t entryPoint = context->textSection->GetVirtualAddress() + context->file->GetImageBase();
        stream.Write32(entryPoint);
    }
private:
    const BlockContext* context;
};
