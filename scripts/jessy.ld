ENTRY(_start)

KERNEL_VMA = -2048M;
KERNEL_LMA = 1M;

SECTIONS
{
  /*
   * Bootstrap
   */
  . = KERNEL_LMA;

  _start_physical = .;
  _start_virtual = . + KERNEL_VMA;

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

  /*
   * Kernel
   */

  . = ALIGN(4K);
  . += KERNEL_VMA;

  .init ALIGN(4K) : AT(ADDR (.init) - KERNEL_VMA)
  {
    KEEP(*(.jessy_crti_init))
    KEEP(*(.init))
    KEEP(*(.jessy_crtn_init))
  }

  .fini ALIGN(4K) : AT(ADDR (.fini) - KERNEL_VMA)
  {
    KEEP(*(.jessy_crti_fini))
    KEEP(*(.fini))
    KEEP(*(.jessy_crtn_fini))
  }

  .text ALIGN(4K) : AT(ADDR (.text) - KERNEL_VMA)
  {
    *(.text*)
  }

  .rodata ALIGN(4K) : AT (ADDR (.rodata) - KERNEL_VMA)
  {
    *(.rodata)
    *(.rodata.*)
  }

  .ctors ALIGN(4K) : AT (ADDR (.ctors) - KERNEL_VMA)
  {
    KEEP(*crtbegin.o(.ctors))
    KEEP(*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP(*(SORT(.ctors.*)))
    KEEP(*crtend.o(.ctors))
  }

  .dtors ALIGN(4K) : AT (ADDR (.dtors) - KERNEL_VMA)
  {
    KEEP(*crtbegin.o(.dtors))
    KEEP(*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP(*(SORT(.dtors.*)))
    KEEP(*crtend.o(.dtors))
  }

  .data ALIGN(4K) : AT (ADDR (.data) - KERNEL_VMA)
  {
    *(.data)
  }

  .bss ALIGN(4K) : AT (ADDR (.bss) - KERNEL_VMA)
  {
    *(COMMON)
    *(.bss*)
  }

  _end_virtual = ADDR(.bss) + SIZEOF(.bss);
  _end_physical = _end_virtual - KERNEL_VMA;

  /DISCARD/ : { *(.comment) }
}
