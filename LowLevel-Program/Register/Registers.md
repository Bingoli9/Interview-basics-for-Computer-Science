## Registers

### General Register

| Name      | Alias | Description                                                  |
| --------- | ----- | ------------------------------------------------------------ |
| r0        | rax   | Kind of an "accumulator", used in arithmetic instructions.   |
| r3        | rbx   | Base Register. Was used for base addressing in early processor models |
| r1        | rcx   | Used for cycles                                              |
| r2        | rdx   | Stores data during input/output operations                   |
| r4        | rsp   | Stores the address of the topmost element in the hardware stack. |
| r5        | rdp   | Stack frame's base                                           |
| r6        | rsi   | Source index in string manipulation commands (such as movsd) |
| r7        | rdi   | Destination index in string manipulation commands (such as movsd) |
| r8        |       |                                                              |
| r9... r15 | no    | Used mostly to store temporal variables (but sometimes used implicitly, like r10, which saves the CPU flags when syscall instruction in executed. ) |

```C++
Note

Unlike the hardware stack, which is implemented on top of the main memory, registers are a completely different kind of memory. Thus they do not have addressed, as the main memory's cells do.

```

Addressing a part of a register is possible. For each register, you can address its lowest 32 bits, lowest 16 bits, or lowest 8 bits. When using the names r0, .., r15 it is done by adding an appropriate suffix to a register's name:

- d for double word --- lower 32 bits
- w for word -- lower 16 bits
- b for byte -- lower 8 bits

For example,

- r7b is the lowrst byte of register r7

### Other Register

| Name   | Alias | Description                                                  |
| ------ | ----- | ------------------------------------------------------------ |
| rip    |       | Stores the address of the next instruction to be executed    |
| rflags |       | It stores flags, which reflect the current program state; For example, what was the result of the last arithmetic instruction: was it negative. |

### Protection Rings

Protection rings are one of the mechanisms designed to limit the applications' capabilities for security and robustness reasons. Each ring corresponds to a certain privilege level. Each instruction type is linked with one or more priviledge levels and is not executable on others. 

## Hardware Stack

 There's a hardware support for such data structure. It does not mean there is also a separate stack memoty. It is implemented with two mechine instructions and a register. The rsp register holds an address stack. The instructions perform as follows:

- Push argument

   	1. Depending on argument size(2, 4, and 8 bytes are allowed), the rsp value is decreased by 2, 4 or 8.
   	2. An argument is stored in memory starting at the address, taken from the modified rsp.

- pop argument

  1. The topmost stack elemnet is copied into the register/memory
  2. rsp is increased by the size of its argument. 


