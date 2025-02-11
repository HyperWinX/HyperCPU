Extended vCPU functionality
===========================

-----------
Console I/O
-----------

Using simple console API is pretty simple. To read one character from stdin, you should read from port 0.
That operation places read character in xlll0 register.

.. code-block::

  read 0u;

To write one character, write it to the port 0.

.. code-block::

  write 55h, 0u;


-----------------------------
Advanced console I/O features
-----------------------------

| You are allowed to configure printing functionality.
| To change any setting, you should write FFh to the port 0, and then write your command.
| Example:

.. code-block::

  write FFh, 0u;
  write 11h, 0u;

| In that example we disabled I/O controller from printing characters, pressed by user.

.. list-table:: I/O controller commands
  :widths: 15 5 45
  :header-rows: 1

  * - Command
    - Hex code
    - Description
  * - ENABLE_PRINTING
    - 10h
    - Enable printing character, pressed by user
  * - DISABLE_PRINTING
    - 11h
    - Disable printing character, pressed by user
  * - ENABLE_BUFFERING
    - 20h
    - Enable waiting for "Enter" keypress
  * - DISABLE_BUFFERING
    - 21h
    - Disable waiting for "Enter" keypress