#pragma once

class PEOptionalHeader : public DataBlockBase
{
public:
    PEOptionalHeader();

    static constexpr uint32_t NumberDataDirectories = 16;

    void SetContext(const BlockContext* context);

    void RegisterDirectory(int index, DataBlockBase* directory);
protected:
    void GenerateImpl(ByteStream& stream) const override;
private:
    struct DataDirectory
    {
    public:
        DataDirectory();

        DataBlockBase* directory = nullptr;

    protected:
        void GenerateImpl(ByteStream& stream);
    };

    std::vector<DataDirectory> directories;
    NTHeader ntHeader;
    const BlockContext* context;
};


