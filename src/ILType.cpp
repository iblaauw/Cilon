#include "ILType.h"

#include "Assembly.h"
#include "MethodReference.h"
#include "Utils.h"

ILType::ILType(Name name, const Assembly* owningAssembly)
    : name(name), assembly(owningAssembly)
{
}

/*static*/ ILType* ILType::GetVoid()
{
    static ILType* voidType = new ILType("void", nullptr);
    return voidType;
}

/*static*/ ILType* ILType::GetString()
{
    static ILType* stringType = new ILType("string", nullptr);
    return stringType;
}

/*static*/ ILType* ILType::GetInt()
{
    static ILType* intType = new ILType("int32", nullptr);
    return intType;
}

MethodReference* ILType::GetMethod(Name name, std::shared_ptr<FunctionSignature> signature)
{
    std::string key = name.GetString();

    auto iter = ownedMethods.find(key);
    if (iter != ownedMethods.end())
    {
        // Method has been created already
        return iter->second.get();
    }

    // Need to create the method
    std::unique_ptr<MethodReference> method = std::make_unique<MethodReference>(name, signature, this);
    MethodReference* methodWeak = method.get();

    ownedMethods.emplace(key, std::move(method));

    return methodWeak;
}

void ILType::Generate(std::ostream& out) const
{
    if (assembly != nullptr && assembly->IsExternal())
    {
        out << '[' << assembly->GetName() << ']';
    }
    out << name;
}

std::ostream& operator<<(std::ostream& out, const ILType& type)
{
    type.Generate(out);
}

std::ostream& operator<<(std::ostream& out, const ILType* type)
{
    type->Generate(out);
}

