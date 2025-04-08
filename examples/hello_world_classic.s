/*
 * This is a simple "Hello World" program written in HyperCPU assembly (hASM).
 * It writes a string to console char by char, then writes a newline byte (0x10) and halts CPU.
 *
 * Since 0.4.5 version it is available to use string literals — see hello_world.s for example.
 *
 * Contributed by Ivan Movchan <ivan.movchan.07@gmail.com>, 2025.
 */

main:
	write xlll0, 'H';
	write xlll0, 'e';
	write xlll0, 'l';
	write xlll0, 'l';
	write xlll0, 'o';
	write xlll0, ',';
	write xlll0, ' ';
	write xlll0, 'w';
	write xlll0, 'o';
	write xlll0, 'r';
	write xlll0, 'l';
	write xlll0, 'd';
	write xlll0, '!';
	write xlll0, 0u10; // 0x10 — newline character.
	halt;
