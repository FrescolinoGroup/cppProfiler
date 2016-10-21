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
//~ #define MIB_TAGS a, b, main
// dont measure b
//~ #define MIB_TEST a, b, main

#include <fsc/profiler.hpp>
#include <fsc/stdSupport.hpp>

int main() {
    for(uint32_t i = 0; i < 10000; ++i) {
        MIB_START(main)
        MIB_START(a)
        MIB_START(b)
        MIB_START(c)
        std::vector<double> a(100);
        (void)a;
        MIB_STOP(c)
        MIB_STOP(b)
        MIB_STOP(a)
        MIB_STOP(main)
    }

    MIB_PRINT(
        cycle)  // can handle the a, b, c structure with such a small load well
    MIB_PRINT(
        nsec)  // will have some missing % for each a, b, c, since load to light

    return 0;
}
