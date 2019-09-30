; vim: ft=nasm et ts=2 sw=2

%include "/common_constants.asm"

extern _transition
extern _end_physical

section .bs_bss nobits alloc noexec write align=4096

page_map_level_4:              ; pml4
  resq 512
page_map_level_3_low_memory:   ; pdpt (for low memory mappings)
  resq 512
page_map_level_3_high_memory:  ; pdpt (for high memory mappings)
  resq 512
page_map_level_2_low_memory:   ; pdt (for low memory mappings)
  resq 512
page_map_level_2_high_memory:  ; pdt (for high memory mappings)
  resq 512

global multiboot_information_pointer:data
multiboot_information_pointer:
  resd 1

section .bs_stack nobits alloc noexec write align=16

stack_bottom:
  resb 1 << 16
stack_top:

section .bs_rodata progbits alloc noexec nowrite

gdt:
  dq 0
.code: equ $ - gdt
  dq (1<<43) | (1<<44) | (1<<47) | (1<<53)
.ptr:
  dw $ - gdt - 1
  dq gdt

msg_panic:
  db "PANIC: ",0
msg_multiboot:
  db "NOT LOADED BY MULTIBOOT2 LOADER",0
msg_cpuid:
  db "CPUID INSTRUCTION NOT SUPPORTED",0
msg_longmode:
  db "LONG-MODE NOT SUPPORTED",0

section .bs_data progbits alloc noexec write

vga_buffer:
  dd cVgaTextBufferAddress
 
section .bs_text progbits alloc exec nowrite align=16
bits 32

_print:
  push ebp
  mov ebp, esp

  push ebx
  push esi

  mov eax, [ebp + 8]
  mov ebx, [ebp + 12]
  mov ecx, 0
  mov esi, [vga_buffer]

.loop:
  mov byte dl, [ebx + ecx]
  test dl, dl
  je .store_new_buffer_address
  mov byte [esi + ecx * 2], dl
  mov byte [esi + ecx * 2 + 1], al
  inc ecx
  jmp .loop

.store_new_buffer_address:
  shl ecx, 1
  add [vga_buffer], ecx

.leave:
  pop esi
  pop ebx
  mov esp, ebp
  pop ebp
  ret

_panic:
  push ebp
  mov ebp, esp

  push msg_panic
  push 0x4f
  call _print
  add esp, 8

  push dword [ebp + 8]
  push 0x4f
  call _print
  add esp, 8

  hlt

global _start:function
_start:
  mov esp, stack_top
  mov ebp, esp
  ; mov edi, ebx

  call check_loaded_by_multiboot
  mov [multiboot_information_pointer], ebx

  call check_cpuid_is_supported
  call check_long_mode_is_supported
  call initialize_page_table_structure
  call enable_paging

  lgdt [gdt.ptr]

  jmp gdt.code:_transition

  hlt

check_loaded_by_multiboot:
  cmp eax, 0x36d76289
  jne .error
  ret
.error:
  push msg_multiboot
  call _panic

check_cpuid_is_supported:
  pushfd
  pop eax
  mov ecx, eax

  xor eax, 1 << 21
  push eax
  popfd

  pushfd
  pop eax

  push ecx
  popfd

  cmp eax,ecx
  je .error
  ret
.error:
  push msg_cpuid
  call _panic

check_long_mode_is_supported:
  push ebx
  mov eax, 0x80000000
  cpuid
  cmp eax, 0x80000001
  jb .error

  mov eax, 0x80000001
  cpuid
  test edx, 1 << 29
  jz .error
  pop ebx
  ret
.error:
  push msg_longmode
  call _panic

initialize_page_table_structure:
  mov eax, page_map_level_3_low_memory
  or eax, 0x3
  mov [page_map_level_4 + ((0x0000000000100000 >> 39) & 0x1ff) * 8], eax

  mov eax, page_map_level_3_high_memory
  or eax, 0x3
  mov [page_map_level_4 + ((0xffffffff80100000 >> 39) & 0x1ff) * 8], eax

  mov eax, page_map_level_2_low_memory
  or eax, 0x3
  mov [page_map_level_3_low_memory + ((0x0000000000100000 >> 30) & 0x1ff) * 8], eax

  mov eax, page_map_level_2_high_memory
  or eax, 0x3
  mov [page_map_level_3_high_memory + ((0xffffffff80100000 >> 30) & 0x1ff) * 8], eax

  xor ecx, ecx

  mov esi, _end_physical
  shr esi, 21
  add esi, 2

.map_pt_pages:
  mov eax, cTwoMegaBytes
  mul ecx
  or  eax, cPagePresentBit | cPageWritableBit | cPageHugePageBit
  mov [page_map_level_2_low_memory + ecx * 8], eax
  mov [page_map_level_2_high_memory + ecx * 8], eax

  inc ecx
  cmp ecx, esi
  jne .map_pt_pages

  ret

enable_paging:
  mov eax, page_map_level_4
  mov cr3, eax

  mov eax, cr4
  or eax, 1 << 5
  mov cr4, eax

  mov ecx, 0xC0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  mov eax, cr0
  or eax, 1 << 31
  mov cr0, eax

  ret
