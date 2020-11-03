#ifndef JESSY_BOOTSTRAP_PAGE_TABLES_HPP
#define JESSY_BOOTSTRAP_PAGE_TABLES_HPP

#include <cstdint>

namespace os::bootstrap
{

  struct page_table
  {
    void * entries[512];
  };

  extern "C" page_table page_map_level_4;
  extern "C" page_table page_map_level_3_low_memory;
  extern "C" page_table page_map_level_3_high_memory;
  extern "C" page_table page_map_level_2_low_memory;
  extern "C" page_table page_map_level_2_high_memory;

}  // namespace os::bootstrap

#endif
