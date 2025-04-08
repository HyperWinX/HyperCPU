/*
 * This program demonstrates how HyperCPU can handle ANSI escape sequences [1].
 * They can be used for displaying a colorful text or moving a cursor.
 * String literals are used — see hello_world.s for details.
 *
 * ASCII text has been generated using FIGlet [2].
 *
 * Contributed by Ivan Movchan <ivan.movchan.07@gmail.com>, 2025.
 *
 * [1] https://en.wikipedia.org/wiki/ANSI_escape_code
 * [2] http://www.figlet.org/
 */

data:
    .b8 "\n";
    .b8 "ooooo   ooooo                                           \e[7m   .oooooo.   ooooooooo.   ooooo     ooo \e[0m\n";
    .b8 "`888'   `888'                                           \e[7m  d8P'  `Y8b  `888   `Y88. `888'     `8' \e[0m\n";
    .b8 " 888     888  oooo    ooo oo.ooooo.   .ooooo.  oooo d8b \e[7m 888           888   .d88'  888       8  \e[0m\n";
    .b8 " 888ooooo888   `88.  .8'   888' `88b d88' `88b `888\"\"8P \e[7m 888           888ooo88P'   888       8  \e[0m\n";
    .b8 " 888     888    `88..8'    888   888 888ooo888  888     \e[7m 888           888          888       8  \e[0m\n";
    .b8 " 888     888     `888'     888   888 888    .o  888     \e[7m `88b    ooo   888          `88.    .8'  \e[0m\n";
    .b8 "o888o   o888o     .8'      888bod8P' `Y8bod8P' d888b    \e[7m  `Y8bood8P'  o888o           `YbodP'    \e[0m\n";
    .b8 "              .o..P'       888\n";
    .b8 "              `Y8P'       o888o\n";
    .b8 "\n";
    .b8 "\e[1;37m                       HyperCPU — the \e[1;33mhyper\e[1;37m toolkit for \e[1;33mhyper\e[1;37m custom ISA.\n";
    .b8 "\e[1;32m                             https://github.com/HyperWinX/HyperCPU/\e[0m\n\n";
    .b8 0u0;

.attr(entry) main:
    mov x1, data;

loop:
    mov xlll2, [x1];
    cmp xlll2, 0u0;
    jme end;
    write xlll0, xlll2;
    inc x1;
    jmp loop;

end:
    halt;
