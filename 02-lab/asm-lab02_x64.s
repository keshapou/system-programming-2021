.data

# format print 
print:
  .string "%d\n"

# array
array:
  .byte 127, 255, 2, 3, 4, 5, 6, 7, 8, 9
size:

.text
.global main
.type main, @function

# main function
main:
  movq $0, %rcx
  movq $array, %rbx
  movzbq (%rbx), %rax

  jmp is_last_element

# start loop until the end of the array
start_loop:
  and $34, %rax
  cmpq $34, %rax
  jne to_next_element

  movzbq (%rbx), %rdx # need to convert from byte to long
  addq %rdx, %rcx

# jump to the next element
to_next_element:
  addq $1, %rbx 
  movzbq (%rbx), %rax

# compare with the last array element
is_last_element:
  cmpq $size, %rbx
  jne start_loop

  movq $print, %rdi
  movq %rcx, %rsi
  movq $0, %rax
  callq printf
  xor %rcx, %rcx
  xor %rbx, %rbx
  xor %rax, %rax

  ret
