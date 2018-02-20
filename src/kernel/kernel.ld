ENTRY(_start)

SECTIONS
{
  /*
   * Bootstrap
   */
  . = 1M;
  _start_physical = .;

  .bs_mbh :
  {
    KEEP(*(.bs_mbh))
  }

  .bs_text :
  {
    *(.bs_text)
  }

  .bs_rodata :
  {
    *(.bs_rodata)
  }

  .bs_data :
  {
    *(.bs_data)
  }

  .bs_bss :
  {
    *(.bs_bss)
  }

  .bs_stack :
  {
    *(.bs_stack)
  }

  . = ALIGN(4096);
  _end_boot = .;

  /*
   * Kernel
   */

  . += 0xFFFFFFFF80000000;
  .init : AT(_end_boot)
  {
    KEEP(*(.init))
  }

  . = ALIGN(4096);
  .fini :
  {
    KEEP(*(.fini))
  }

  . = ALIGN(4096);
  .ctors :
  {
    KEEP(*crtbegin.o(.ctors))
    KEEP(*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP(*(SORT(.ctors.*)))
    KEEP(*crtend.o(.ctors))
  }

  . = ALIGN(4096);
  .dtors :
  {
    KEEP(*crtbegin.o(.dtors))
    KEEP(*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP(*(SORT(.dtors.*)))
    KEEP(*crtend.o(.dtors))
  }

  . = ALIGN(4096);
  .text :
  {
    *(.text*)
  }

  . = ALIGN(4096);
  .rodata :
  {
    *(.rodata)
    *(.rodata.*)
  }

  . = ALIGN(4096);
  .data :
  {
    *(.data)
  }

  . = ALIGN(4096);
  .bss :
  {
    *(COMMON)
    *(.bss*)
  }

  /DISCARD/ : { *(.comment) }

  _end_physical = (LOADADDR (.bss) + SIZEOF(.bss) + 0xFFF) & 0xFFFFFFFFFFFFF000;
}
