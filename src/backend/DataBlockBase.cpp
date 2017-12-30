#include "DataBlockBase.h"

void DataBlockBase::AddChild(DataBlockBase* child)
{
    childBlocks.push_back(child);
}

void DataBlockBase::Generate(DataBlockStream& stream) const
{
    stream.BeginBlock();

    GenerateImpl(stream);
    for (auto* child : childBlocks)
    {
        Generate(child);
    }

    int alignment = GetPaddedAlignment();
    if (alignment > 0)
    {
        stream.PadToMultiple(aligment);
    }

    if (stream.IsSizeMode)
    {
        SetSize(stream.GetBlockSize());
        SetPaddedSize(stream.GetBlockPaddedSize());
        SetAddress(stream.GetBlockAddress());
        SetVirtualAddress(stream.GetBlockVirtualAddress());
    }

    stream.EndBlock();
}


