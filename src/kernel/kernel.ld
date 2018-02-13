ENTRY(_start)

SECTIONS
{
  . = 1M;

  .boot :
  {
    KEEP(*(.multiboot_header))
  }

  .text :
  {
    KEEP(*(.init))
    KEEP(*(.fini))
    *(.text*)
  }

  .rodata :
  {
    KEEP(*crtbegin.o(.ctors))
    KEEP(*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP(*(SORT(.ctors.*)))
    KEEP(*crtend.o(.ctors))
    KEEP(*crtbegin.o(.dtors))
    KEEP(*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP(*(SORT(.dtors.*)))
    KEEP(*crtend.o(.dtors))
    *(.rodata)
    *(.rodata.*)
  }

  .data :
  {
    *(.data)
  }

  .bss :
  {
    *(COMMON)
    *(.bss*)
  }

  /DISCARD/ :
  {
    *(.comment)
  }

}
