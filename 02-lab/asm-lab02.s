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
  movl $0, %ecx
  movl $array, %ebx
  movzbl (%ebx), %eax

  jmp is_last_element

# start loop until the end of the array
start_loop:
  and $34, %eax
  cmpl $34, %eax
  jne to_next_element

  movzbl (%ebx), %edx # need to convert from byte to long
  addl %edx, %ecx

# jump to the next element
to_next_element:
  addl $1, %ebx 
  movzbl (%ebx), %eax

# compare with the last array element
is_last_element:
  cmpl $size, %ebx
  jne start_loop

  pushl %ecx
  pushl $print
  call printf
  addl $8, %esp
  xor %ecx, %ecx
  xor %ebx, %ebx
  xor %eax, %eax

  ret
