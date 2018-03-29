#ifndef JESSY_BOOTSTRAP_ADDRESSES_HPP
#define JESSY_BOOTSTRAP_ADDRESSES_HPP

#include "iso/cstddef.hpp"

namespace os::bootstrap
  {

  extern "C" iso::byte_t const _start_physical;
  extern "C" iso::byte_t const _end_physical;
  extern "C" iso::byte_t const _start_virtual;
  extern "C" iso::byte_t const _end_virtual;

  /**
   * The physical address the kernel has been loaded at
   *
   * @author Natalia Fenclová
   * @since 0.1.0
   */
  auto const cPhysicalMemoryStartAddress = &_start_physical;

  /**
   * The physical end address of the kernel image
   *
   * @author Natalia Fenclová
   * @since 0.1.0
   */
  auto const cPhysicalMemoryEndAddress = &_end_physical;

  /**
   * The virtual address the kernel has been loaded at
   *
   * @author Natalia Fenclová
   * @since 0.1.0
   */
  auto const cVirtualMemoryStartAddress = &_start_virtual;

  /**
   * The virtual end address of the kernel image
   *
   * @author Natalia Fenclová
   * @since 0.1.0
   */
  auto const cVirtualMemoryEndAddress = &_end_virtual;

  }

#endif
