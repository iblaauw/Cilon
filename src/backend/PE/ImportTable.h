#pragma once

class ImportTable : public DataBlockBase
{
public:
    void SetTextContext(DataBlockBase* iat, DataBlockBase* ilt, DataBlockBase* dllString, const BlockContext* context);
protected:
    virtual void GenerateImpl(ByteStream& stream) const override; 
private:
    DataBlockBase* iat;
    DataBlockBase* ilt;
    DataBlockBase* dllString;
};

class ImportAddressTable : public DataBlockBase
{
public:
    void SetHintTable(DataBlockBase* hintTable) { this->hintTable = hintTable; }
protected:
    virtual void GenerateImpl(ByteStream& stream) const override;
private:
    DataBlockBase* hintTable;
};


