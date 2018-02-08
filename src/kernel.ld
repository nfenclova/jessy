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
    /*
    KEEP(*(.init*))
    KEEP(*(.fini*))
    KEEP(*(.ctors*))
    KEEP(*(.dtors*))
    */
    *(.text*)
  }

  .rodata :
  {
    *(.rodata*)
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
