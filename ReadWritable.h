#ifndef RW
#define RW

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Menu.h"

using namespace std;

namespace sdds
{
    class ReadWritable
    {
    protected:
        bool isCommaSeperated;

    public:
        ReadWritable();
        bool isCsv() const;
        void setCsv(bool v);
        virtual istream &read(istream &istr = cin) = 0;
        virtual ostream &write(ostream &ostr = cout) const = 0;
        virtual ~ReadWritable();

        friend ostream &operator<<(ostream &ostr, const ReadWritable &rw);
        friend istream &operator>>(istream &istr, ReadWritable &rw);
    };
} // namespace sdds

#endif