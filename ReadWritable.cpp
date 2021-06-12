#include <iostream>
#include "ReadWritable.h"

using namespace std;

namespace sdds
{
    ReadWritable::ReadWritable()
    {
        isCommaSeperated = false;
    }

    bool ReadWritable::isCsv() const
    {
        return isCommaSeperated;
    }

    void ReadWritable::setCsv(bool v)
    {
        isCommaSeperated = v;
    }

    ostream &operator<<(ostream &ostr, const ReadWritable &rw)
    {
        rw.write(ostr);
        return ostr;
    }

    istream &operator>>(istream &istr, ReadWritable &rw)
    {
        rw.read(istr);
        return istr;
    }

    ReadWritable::~ReadWritable()
    {
    }
} // namespace sdds