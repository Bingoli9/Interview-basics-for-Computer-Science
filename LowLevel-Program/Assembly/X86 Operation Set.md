## Assembly Language

Hello World.asm

```C++
global _start

section .data
message: db 'hello, world', 10

section .text
_start:
	mov rax, 1 ;system call number should be stored in rax
	mov rdi, 1 ; argument #1 in rdi: where to write (descriptor)?
	mov rsi, message ;argument #2 in rsi: where does the string start
	mov rdx,14 ;argument #3 in rdx: how many bytes to write
	syscall ; this instruction invokes a system call
```

### Basic Instruction

#### mov

- mov cannot copy data from memory to memory
- the source and the destination operands must be of the same size

#### syscall

The syscall instruction is used to perform system calls in unix systems. The input/output operations depend on hardware used by multiple programs at the same time, so programmers are not allowed to control them directily, bypassing the operating system.

Each system call has a unique number. To perform it

- The rax register has to hold system call's number;

- The following registers should hold its arguments: rdi, rsi, rdx, r10, r8 and r9

  system call cannot accept more than six arguments;

- Execute syscall instruction.

#### Local Labels

Variables name started with a dot.

#### Relative Addressing

Square brackets demote indirect addressing; The address is wiritten inside them.

```C++
mov rsi,rax  ;copies rax into rsi
mov rsi, [rax] ;copies memory contents starting at address, stored in rax, into rsi.
```

#### Order of Execution

- unconditional jump

  ```C++
  jmp addr
  ```

- conditional jump

  Conditional jumps rely on contents of rflags register. For example, jz address jumps to address only if zero flag is set.

  ```C++
  	cmp rax, 42
  	jl yes
  	mov rbx, 0
  	jmp ex
  yes: 
   	mov rbx, 1
  ex:
  ```

#### Function Calls

Instruction call \<address\> is used to perform calls. It does exactly the following:

```C++
push rip

jmp \<address\>
```
The address now stored in the stack is called return address.

The first six arguments are passed in rdi, rsi, rdx, rcx, r8 and r9, respectively.

```C++
section .data

newline_char: db 10
codes: db '0123'

section .text
global \ _start
print_newline:
	mov rax, 1
	mov rdi, 1
	mov rsi, newline_char
	mov rdx, 1
	syscall
ret

```

