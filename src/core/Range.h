#pragma once

template <class TIter>
class Range
{
public:
    Range(TIter iterBegin, TIter iterEnd)
        : iterBegin(iterBegin), iterEnd(iterEnd)
    {}

    TIter begin() const { return iterBegin; }
    TIter end() const { return iterEnd; }

private:
    TIter iterBegin;
    TIter iterEnd;
};

