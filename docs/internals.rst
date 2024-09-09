HyperCPU internals
==================

Components of vCPU
------------------

| HyperCPU includes following components:

* Fetcher + decoder (all in one)
* Main execution block
* Memory controller
* Set of registers

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
| xidp          | 64 bit        | Inaccessible - holds pointer to IDT                      |
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
