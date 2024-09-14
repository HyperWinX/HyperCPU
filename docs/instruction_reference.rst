Instruction reference
=====================

----------
Main terms
----------

* r8 - 8 bit register
* r16 - 16 bit register
* r32 - 32 bit register
* r64 - 64 bit register
* rm - interpret register value as address
* m - immediate memory address
* m8 - 8 bits from immediate memory address
* m16 - 16 bits from immediate memory address
* m32 - 32 bits from immediate memory address
* m64 - 64 bits from immediate memory address
* imm8 - immediate 8 bit value
* imm16 - immediate 16 bit value
* imm32 - immediate 32 bit value
* imm64 - immediate 64 bit value

----------------------
'Opcode' field meaning
----------------------
* <m> - memory address. Size - 64 bit
* <r> - encoded register. Size - 8 bit
* <imm> - immediate value. Size - (8 - 64) bit


========================
ADC - Add With Carry
========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 010000<r><r>
    - add <r8>, <r8>
    - R_R
  * - 010040<r><r>
    - add <r16>, <r16>
    - R_R
  * - 010080<r><r>
    - add <r32>, <r32>
    - R_R
  * - 0100C0<r><r>
    - add <r64>, <r64>
    - R_R
  * - 010001<r><r>
    - add <r8>, <rm>
    - R_RM
  * - 010041<r><r>
    - add <r16>, <rm>
    - R_RM
  * - 010081<r><r>
    - add <r32>, <rm>
    - R_RM
  * - 0100C1<r><r>
    - add <r64>, <rm>
    - R_RM
  * - 010002<r><m>
    - add <r8>, <m8>
    - R_M
  * - 010042<r><m>
    - add <r16>, <m16>
    - R_M
  * - 010082<r><m>
    - add <r32>, <m32>
    - R_M
  * - 0100C2<r><m>
    - add <r64>, <m64>
    - R_M
  * - 010003<r><imm>
    - add <r8>, <imm8>
    - R_IMM
  * - 010043<r><imm>
    - add <r16>, <imm16>
    - R_IMM
  * - 010083<r><imm>
    - add <r32>, <imm32>
    - R_IMM
  * - 0100C3<r><imm>
    - add <r64>, <imm64>
    - R_IMM


| **Description**:
| Adds the source operand (second operand) and the carry flag to destination operand (first operand).
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| Overflow flag set if result is overflown.


========================
ADD - Add With Carry
========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 020000<r><r>
    - add <r8>, <r8>
    - R_R
  * - 020040<r><r>
    - add <r16>, <r16>
    - R_R
  * - 020080<r><r>
    - add <r32>, <r32>
    - R_R
  * - 0200C0<r><r>
    - add <r64>, <r64>
    - R_R
  * - 020001<r><r>
    - add <r8>, <rm>
    - R_RM
  * - 020041<r><r>
    - add <r16>, <rm>
    - R_RM
  * - 020081<r><r>
    - add <r32>, <rm>
    - R_RM
  * - 0200C1<r><r>
    - add <r64>, <rm>
    - R_RM
  * - 020002<r><m>
    - add <r8>, <m8>
    - R_M
  * - 020042<r><m>
    - add <r16>, <m16>
    - R_M
  * - 020082<r><m>
    - add <r32>, <m32>
    - R_M
  * - 0200C2<r><m>
    - add <r64>, <m64>
    - R_M
  * - 020003<r><imm>
    - add <r8>, <imm8>
    - R_IMM
  * - 020043<r><imm>
    - add <r16>, <imm16>
    - R_IMM
  * - 020083<r><imm>
    - add <r32>, <imm32>
    - R_IMM
  * - 0200C3<r><imm>
    - add <r64>, <imm64>
    - R_IMM

| **Description**:
| Adds the source operand (second operand) and the carry flag to destination operand (first operand).
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| Overflow flag set if result is overflown.

========================
MOV - Move
========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type

  * - 7F0000<r><r>
    - mov <r8>, <r8>
    - R_R
  * - 7F0040<r><r>
    - mov <r16>, <r16>
    - R_R
  * - 7F0080<r><r>
    - mov <r32>, <r32>
    - R_R
  * - 7F00C0<r><r>
    - mov <r64>, <r64>
    - R_R

  * - 7F0001<r><r>
    - mov <r8>, <rm>
    - R_RM
  * - 7F0041<r><r>
    - mov <r16>, <rm>
    - R_RM
  * - 7F0081<r><r>
    - mov <r32>, <rm>
    - R_RM
  * - 7F00C1<r><r>
    - mov <r64>, <rm>
    - R_RM

  * - 7F0002<r><m>
    - mov <r8>, <m8>
    - R_M
  * - 7F0042<r><m>
    - mov <r16>, <m16>
    - R_M
  * - 7F0082<r><m>
    - mov <r32>, <m32>
    - R_M
  * - 7F00C2<r><m>
    - mov <r64>, <m64>
    - R_M

  * - 7F0003<r><imm>
    - mov <r8>, <imm8>
    - R_IMM
  * - 7F0043<r><imm>
    - mov <r16>, <imm16>
    - R_IMM
  * - 7F0083<r><imm>
    - mov <r32>, <imm32>
    - R_IMM
  * - 7F00C3<r><imm>
    - mov <r64>, <imm64>
    - R_IMM

  * - 7F0004<r><r>
    - mov <rm>, <r8>
    - RM_R
  * - 7F0044<r><r>
    - mov <rm>, <r16>
    - RM_R
  * - 7F0084<r><r>
    - mov <rm>, <r32>
    - RM_R
  * - 7F00C4<r><r>
    - mov <rm>, <r64>
    - RM_R

  * - 7F0005<r><m>
    - mov <rm>, <m8>
    - RM_M
  * - 7F0045<r><m>
    - mov <rm>, <m16>
    - RM_M
  * - 7F0085<r><m>
    - mov <rm>, <m32>
    - RM_M
  * - 7F00C5<r><m>
    - mov <rm>, <m64>
    - RM_M

  * - 7F0006<r><imm>
    - mov <rm>, <imm8>
    - RM_IMM
  * - 7F0046<r><imm>
    - mov <rm>, <imm16>
    - RM_IMM
  * - 7F0086<r><imm>
    - mov <rm>, <imm32>
    - RM_IMM
  * - 7F00C6<r><imm>
    - mov <rm>, <imm64>
    - RM_IMM

  * - 7F0007<m><r>
    - mov <m8>, <r8>
    - M_R
  * - 7F0047<m><r>
    - mov <m16>, <r16>
    - M_R
  * - 7F0087<m><r>
    - mov <m32>, <r32>
    - M_R
  * - 7F00C7<m><r>
    - mov <m64>, <r64>
    - M_R

| **Description**:
| Copies the value of the second operand to the first operand.
| The source can be either a register, a memory location, or an immediate value.
| The destination can be either a register or a memory location.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| None.
