.include "bootstrap/common_constants.s"

.extern _transition
.extern _end_physical

// Bootstrap BSS

.section .bs_bss, "aw", @nobits
.align 4096

.global page_map_level_4
page_map_level_4:             .skip 512 * 8

.global page_map_level_3_low_memory
page_map_level_3_low_memory:  .skip 512 * 8

.global page_map_level_3_high_memory
page_map_level_3_high_memory: .skip 512 * 8

.global page_map_level_2_low_memory
page_map_level_2_low_memory:  .skip 512 * 8

.global page_map_level_2_high_memory
page_map_level_2_high_memory: .skip 512 * 8

.global multiboot_information_pointer
multiboot_information_pointer: .skip 4

// Bootstrap Stack

.section .bs_stack, "aw", @nobits
.align 16

stack_bottom: .skip 1 << 16
stack_top:

// Bootstrap Constants

.section .bs_rodata, "a", @progbits

gdt: .quad 0
gdt_code = . - gdt
.quad (1<<43) | (1<<44) | (1<<47) | (1<<53)
gdt_ptr:
.word . - gdt - 1
.quad gdt

msg_panic: .string "PANIC: "
msg_multiboot: .string "NOT LOADED BY MULTIBOOT2 LOADER"
msg_cpuid: .string "CPUID INSTRUCTION NOT SUPPORTED"
msg_longmode: .string "LONG-MODE NOT SUPPORTED"

// Bootstrap Data

.section .bs_data, "aw", @progbits

vga_buffer: .long cVgaTextBufferAddress

// Bootstrap Code

.section .bs_text, "ax", @progbits
.align 16
.code32

_print:
  push %ebp
  mov %esp, %ebp
  push %ebx
  push %esi
  mov 8(%ebp), %eax
  mov 12(%ebp), %ebx
  mov $0, %ecx
  mov (vga_buffer), %esi

.loop:
  mov (%ebx, %ecx, 1), %dl
  test %dl, %dl
  je .store_new_buffer_address
  mov %dl, (%esi, %ecx, 2)
  mov %al, 1(%esi, %ecx, 2)
  inc %ecx
  jmp .loop

.store_new_buffer_address:
  shl $1, %ecx
  add %ecx, (vga_buffer)

.leave:
  pop %esi
  pop %ebx
  mov %ebp, %esp
  pop %ebp
  ret

_panic:
  push %ebp
  mov %esp, %ebp

  push msg_panic
  push $0x4f
  call _print
  add 8, %esp

  push 8(%ebp)
  push 0x4f
  call _print
  add $8, %esp

  hlt

.global _start
_start:
  mov $stack_top, %esp
  mov %esp, %ebp

  call check_loaded_by_multiboot
  mov %ebx, multiboot_information_pointer

  call check_cpuid_is_supported
  call check_long_mode_is_supported
  call initialize_page_table_structure
  call enable_paging
  call enable_sse

  lgdt (gdt_ptr)

  jmp $gdt_code,$_transition

  hlt

check_loaded_by_multiboot:
  cmp $0x36d76289, %eax
  jne .Lerror1
  ret
.Lerror1:
  push $msg_multiboot
  call _panic

check_cpuid_is_supported:
  pushfl
  pop %eax
  mov %eax, %ecx

  xor $(1 << 21), %eax
  push %eax
  popfl

  pushfl
  pop %eax

  push %ecx
  popfl

  cmp %ecx, %eax
  je .Lerror2
  ret
.Lerror2:
  push $msg_cpuid
  call _panic

check_long_mode_is_supported:
  push %ebx
  mov $0x80000000, %eax
  cpuid
  cmp $0x80000001, %eax
  jb .Lerror3

  mov $0x80000001, %eax
  cpuid
  test $(1 << 29), %edx
  jz .Lerror3
  pop %ebx
  ret
.Lerror3:
  push $msg_longmode
  call _panic

initialize_page_table_structure:
  mov $page_map_level_3_low_memory, %eax
  or $0x3, %eax
  mov %eax, (page_map_level_4 + ((0x0000000000100000 >> 39) & 0x1ff) * 8)

  mov $page_map_level_3_high_memory, %eax
  or $0x3, %eax
  mov %eax, (page_map_level_4 + ((0xffffffff80100000 >> 39) & 0x1ff) * 8)

  mov $page_map_level_2_low_memory, %eax
  or $0x3, %eax
  mov %eax, (page_map_level_3_low_memory + ((0x0000000000100000 >> 30) & 0x1ff) * 8)

  mov $page_map_level_2_high_memory, %eax
  or $0x3, %eax
  mov %eax, (page_map_level_3_high_memory + ((0xffffffff80100000 >> 30) & 0x1ff) * 8)

  xor %ecx, %ecx

  mov $_end_physical, %esi
  shr $21, %esi
  add $2, %esi

.map_pt_pages:
  mov $cTwoMegaBytes, %eax
  mul %ecx
  or  $(cPagePresentBit | cPageWritableBit | cPageHugePageBit), %eax
  mov %eax, page_map_level_2_low_memory(,%ecx,8)
  mov %eax, page_map_level_2_high_memory(,%ecx,8)

  inc %ecx
  cmp %esi, %ecx
  jne .map_pt_pages

  ret

enable_paging:
  mov $page_map_level_4, %eax
  mov %eax, %cr3

  mov %cr4, %eax
  or $(1 << 5), %eax
  mov %eax, %cr4

  mov $0xC0000080, %ecx
  rdmsr
  or $(1 << 8), %eax
  wrmsr

  mov %cr0, %eax
  or $(1 << 31), %eax
  mov %eax, %cr0

  ret

enable_sse:
    mov %cr0, %eax
    and $0xFFFFFFFB, %eax
    or $0x00000002, %eax
    mov %eax, %cr0

    mov %cr4, %eax
    or $(3 << 9), %eax
    mov %eax, %cr4

    ret
