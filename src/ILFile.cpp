#include "ILFile.h"

#include "Utils.h"

ILFile::ILFile(std::string filename, Name assemblyName)
    : name(filename)
{
    currentAssembly = std::make_unique<Assembly>(assemblyName, false);
}

Assembly* ILFile::CreateReference(Name assemblyName)
{
    std::unique_ptr<Assembly> assemblyRef = std::make_unique<Assembly>(assemblyName, true);

    Assembly* weakRef = assemblyRef.get();

    assemblyReferences.emplace_back(std::move(assemblyRef));
    return weakRef;
}

MethodDefinition* ILFile::CreateMethod(Name methodName, std::shared_ptr<FunctionSignature> signature)
{
    std::unique_ptr<MethodDefinition> newMethod = std::make_unique<MethodDefinition>(methodName, signature);
    MethodDefinition* methodWeak = newMethod.get();
    methods.emplace_back(std::move(newMethod));
    return methodWeak;
}

void ILFile::Generate(std::ostream& out) const
{
    out << "//*****************************//" << std::endl;
    out << "// Begin file " << name << std::endl;
    out << "//*****************************//" << std::endl;

    // Assemblies / assembly refs
    currentAssembly->Generate(out);
    for (const auto& ref : assemblyReferences)
    {
        ref->Generate(out);
    }

    out << std::endl;

    // Methods
    for (const auto& method : methods)
    {
        method->Generate(out);
    }

    out << "//*****************************//" << std::endl;
    out << "// End file " << name << std::endl;
    out << "//*****************************//" << std::endl;
}

