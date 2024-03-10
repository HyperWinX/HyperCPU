# Official HyperCPU architecture manual

### Chapters
- [Registers](#registers)
- [Stack](#stack)
- [Instruction reference](#instruction-reference)
    - [ADC - Add With Carry](#adc)
    - [AND - and bitwise operation](#and)
    - [HLT - Halt cpu](#hlt)
    - [JE - Jump If Equals](#je)

### Registers
32-bit general purpose registers: x0-x31
16-bit general purpose high halfs subregisters: xh0-xh31
16-bit general purpose low halfs subregisters: xl0-xl31
8-bit general purpose high halfs subregisters: xlh0-xlh31
8 bit general purpose low halfs subregisters: xll0-xll31
Stack registers: stp, bstp
    - stp register: current stack pointer
    - bstp register: stack base pointer
Instruction pointer register: insp
Vector math registers: vecr0-vecr7

### Stack
Used stack type: LIFO

r/m
r/imm
r/r
m/imm
m/r

### Opcode structure
ADC
Byte 0 - opcode (0x01)
Byte 1 [  0  |  0  |  0  |  0  |  0  |  0  |  0  |  0  ]
                                  ^     ^     ^     ^
                                  |     |     |     |
                                  |     |     |     |
                                  |     |     |     |
                                  |     |     |     |
                                  |     |     |     |
                                  |     |     |     |     
                                  -------------------
                                          | Specifies types of target/source
                                          | 0000 - r(m)/r
                                          | 0001 - r/r(m)
                                          | 0010 - r(m)/imm
                                          | 0011 - r/imm
                                          | 0100 - r(m)/m
                                          | 0101 - r/m
                                          | 0110 - m/r
                                          | 0111 - m/r(m)
                                          | 1000 - r
                                          | 1001 - imm
If one register is used, byte 2 is register code
If two registers are used, byte 2-3 are register codes

Maximum opcode size: 10 bytes
Opcode can store one immediate value, one address, or address with immediate value
## Instruction reference

### ADC
Signature:
```
adc r8/m8    imm8
adc r16/m16  imm16
adc r32/m32  imm32
adc r8       m8
adc r16      m16
adc r32      m32
```
Adds values with carry. If overflown, overflow flag is set.

Flags affected:
None

### AND
Signature:
```
and reg32/reg16/reg8/mem32/mem16/mem8 reg32/reg16/reg8/mem32/mem16/mem8
```
Applies bitwise and to register or memory block.

Flags affected:  
None

### HLT
Signature:
```
hlt
```
Halts cpu.

Flags affected:  
None

### JE
Signature:
```
je <label>
```
Jumps to specified label if CMPR flag is set.

Flags affected:  
None