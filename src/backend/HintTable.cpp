#include "HintTable.h"

void HintTable::SetContext(const BlockContext* context)
{
    if (context->file->IsDll())
    {
        importString = std::make_unique<RawString>("_CorDllMain");
    }
    else
    {
        importString = std::make_unique<RawString>("_CorExeMain");
    }

    AddChild(importString.get());
}

void HintTable::GenerateImpl(ByteStream& stream) const
{
    stream.Write16(0); // hint

    // next, write the import string (which is already a child at this point)
}

void HintTable::
