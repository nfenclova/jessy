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
    *(.text)
  }

  .rodata :
  {
    *(.rodata)
  }

  .data :
  {
    *(.data)
  }

  .bass :
  {
    *(COMMON)
    *(.bss)
  }

  /DISCARD/ :
  {
    *(.comment)
  }

}
