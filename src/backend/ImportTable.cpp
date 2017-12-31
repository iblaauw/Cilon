#include "ImportTable.h"

void ImportTable::SetTextContext(DataBlockBase* iat, DataBlockBase* ilt, DataBlockBase* dllString)
{
    this->iat = iat;
    this->ilt = ilt;
    this->dllString = dllString;
}

void ImportTable::GenerateImpl(ByteStream& stream) const
{
    stream.Write32(ilt->GetVirtualAddress());
    stream.Write32(0); // datetime
    stream.Write32(0); // forwarder chain
    stream.Write32(dllString->GetVirtualAddress());
    stream.Write32(iat->GetVirtualAddress());
}

void ImportAddressTable::GenerateImpl(ByteStream& stream) const
{
    uint32_t rva = hintTable->GetVirtualAddress();
    if ((rva & (1 << 31)) == 1)
        throw ArgumentException("Error: hint table virtual address is too large");

    stream.Write32(rva);
    stream.Write32(0); // end of table
}

