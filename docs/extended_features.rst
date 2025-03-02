Extended vCPU functionality
===========================

-----------
Console I/O
-----------

Using simple console API is pretty simple. To read one character from stdin, you should read from port 0.
That operation places read character in xlll0 register.

.. code-block::

  read 0u0;

To write one character, write it to the port 0.

.. code-block::

  write 0x55, 0u0;


-----------------------------
Advanced console I/O features
-----------------------------

| You are allowed to configure printing functionality.
| To change any setting, you should write FFh to the port 0, and then write your command.
| Example:

.. code-block::

  write 0xFF, 0u0;
  write 0x11, 0u0;

| In that example we disabled I/O controller from printing characters, pressed by user.

.. list-table:: I/O controller commands
  :widths: 15 5 45
  :header-rows: 1

  * - Command
    - Hex code
    - Description
  * - ENABLE_PRINTING
    - 0x10
    - Enable printing character, pressed by user
  * - DISABLE_PRINTING
    - 0x11
    - Disable printing character, pressed by user

-------------------------
Custom interrupts handler
-------------------------
| You also can set custom handlers for already existing interrupts. See example below:

.. code-block::
  ivt:
  .b64 0x0;
  .b64 io;

  io: // IO means Invalid Opcode, not I/O.
    mov xlll0, 0x0;
    write xlll0, 'I';
    write xlll0, 'O';
    write xlll0, '!';
    halt;

  .attr(entry) main:
    loivt ivt;
    .b8 0x88; // Invalid opcode!

| In this example we created handler for the IO interrupt, loaded it, and then triggered the interrupt.
| 