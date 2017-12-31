#pragma once

template <int Size>
class Padding : public DataBlockBase
{
public:
    int GetPaddedAligment() const override { return Size; }
protected:
    void GenerateImpl(ByteStream& stream) const override { /*noop*/ }
};

template <int Size>
class Zeros : public DataBlockBase
{
protected:
    void GenerateImpl(ByteStream& stream) const override
    {
        for (int i = 0; i < Size; i++)
        {
            stream.Write8(0);
        }
    }
};

class RawString : public DataBlockBase
{
public:
    RawString(std::string str)
        : str(str)
    {}

protected:
    void GenerateImpl(ByteStream& stream) const override
    {
        stream.WriteString(str);
    }

private:
    std::string str;
};
