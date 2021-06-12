#include "Utils.h"
#include <iostream>
#include <cstdio>

namespace sdds
{
    void clearBuffer()
    {
        while (getchar() != '\n')
            ;
    }

    void printIndentation(int level)
    {
        if (!(level <= 0))
        {
            for (int i = 0; i < level; i++)
            {
                std::cout << "    ";
            }
        }
    }
} // namespace sdds
