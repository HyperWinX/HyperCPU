HyperCPU internals
==================

Components of vCPU
------------------

| HyperCPU includes following components:

* Fetcher + decoder (all in one) - StdDecoder class
* CPU itself - CPU class
* Memory controller - IMemoryController, interface. MemoryControllerST and MemoryControllerMT implement it

| These are the most important components. However, due to a project structure, they can be replaced by different implementations.

Registers
---------

| Any CPU (including mine:D) has registers to keep and process data.

+---------------+---------------+----------------------------------------------------------+
| Register name | Register size | Explanation                                              |
+===============+===============+==========================================================+
| xbp           | 64 bit        | Stack base register                                      |
+---------------+---------------+----------------------------------------------------------+
| xsp           | 64 bit        | Stack pointer register                                   |
+---------------+---------------+----------------------------------------------------------+
| xip           | 64 bit        | Instruction pointer register                             |
+---------------+---------------+----------------------------------------------------------+
| xgdp          | 64 bit        | Inaccessible - holds pointer to GDT                      |
+---------------+---------------+----------------------------------------------------------+
| xivt          | 64 bit        | Inaccessible - holds pointer to IVT                      |
+---------------+---------------+----------------------------------------------------------+
| x0 - x7       | 64 bit        | Biggest GP registers                                     |
+---------------+---------------+----------------------------------------------------------+
| xh0 - xh7     | 32 bit        | High halfs of x regs                                     |
+---------------+---------------+----------------------------------------------------------+
| xl0 - xl7     | 32 bit        | Low halfs of x regs                                      |
+---------------+---------------+----------------------------------------------------------+
| xll0 - xll3   | 16 bit        | Low halfs of low halfs of xh subregisters                |
+---------------+---------------+----------------------------------------------------------+
| xllh0 - xllh3 | 8 bit         | High halfs of low halfs of low halfs of xll subregisters |
+---------------+---------------+----------------------------------------------------------+
| xlll0 - xlll3 | 8 bit         | Low halfs of low halfs of low halfs of xll subregisters  |
+---------------+---------------+----------------------------------------------------------+

| Thats how GP (general purpose) registers are "placed":

.. code-block:: none

  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
  ┃ x0                                                             ┃
  ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
  ┃ xh0                           ┃ xl0                            ┃
  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┫
                                                  ┃ xll0           ┃
                                                  ┣━━━━━━━━┳━━━━━━━┫
                                                  ┃ xllh0  ┃ xlll0 ┃
                                                  ┗━━━━━━━━┻━━━━━━━┛

Flags
-----

Flags have only two states - "set" or "not set".
List of flags with descriptions:

.. list-table:: Flags
  :widths: 5 30
  :header-rows: 1

  * - Flag name
    - Description
  
  * - CRF
    - Carry flag, can be used for mathematical operations.
  
  * - OVF
    - Overflow flag, shows if number has been overflown during math operation.
  
  * - UDF
    - Underflow flag, shows if number has been underflown during math operation.
  
  * - ZRF
    - Zero flag... yes. No one knows why it's here.

IVT
---

IVT stands for Interrupt Vector Table. As the name says, it stores interrupt vectors, which are called when the interrupt is raised.
IVT can store up to 256 vectors. Each vector is a pointer to the code.


Interrupts
----------

Interrupts are "signals", that stop CPU from executing user code. Every interrupt has its own index, and when CPU gets such signal, it fetches vector from IVT, and then starts executing it.

There are different kinds of interrupts. First 8 interrupts are reserved by CPU.

.. list-table:: Reserved interrupts
  :widths: 17 21 21
  :header-rows: 1

  * - Index
    - Interrupt name
    - Description
  * - 0
    - IA (Invalid Memory Access)
    - Code tried to access memory, inaccessible on the current execution level.
  * - 1
    - ZRDIV (Division by zero)
    - Code tried to divide value by zero.
  * - 2
    - IO (Invalid Opcode)
    - CPU encountered invalid opcode.
