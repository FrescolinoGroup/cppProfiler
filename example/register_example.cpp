/** ****************************************************************************
 * \file
 * \brief
 * \author
 * Year      | Name
 * --------: | :------------
 * 2016      | Mario S. Koenz
 * \copyright  todo
 ******************************************************************************/

#include <iostream>
#include <type_traits>
#include <vector>

// defining all tags here allows to turn of tags in MIB_TEST
#define MIB_TAGS a, b, main
// dont measure b
#define MIB_TEST a, main

#include <fsc/profiler.hpp>
#include <fsc/stdSupport.hpp>

int main() {
    MIB_START(main)
    for(uint32_t i = 0; i < 1000; ++i) {
        MIB_START(a)
        std::vector<double> a(100);

        MIB_NEXT(a, b)
        std::cout << a << std::endl;
        MIB_STOP(b)
    }
    MIB_STOP(main)

    // this will only print the data, since we are already in register mode
    MIB_PRINT(cycle)

    return 0;
}
