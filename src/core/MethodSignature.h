#pragma once

class MethodParameter
{
public:
    ILType* type;
    Identifier name;
};

class MethodSignature
{
public:
    MethodSignature(ILType* returnType);

    const ILType* GetReturnType() const { return returnType; }

    int NumParams() const { return parameters.size(); }

    void AddParameter(ILType* type, Identifier name);

    MethodParameter& GetParameter(int index);
    const MethodParameter& GetParameter(int index) const;

private:
    ILType* returnType;
    std::vector<MethodParameter> parameters;
};

