/*

This is a simple "Hello World" program written in HyperCPU assembly (hASM).
It writes a string to console char by char, then writes an newline byte (0x10) and halts CPU.

Copyrignt (c) 2025 Ivan Movchan <ivan.movchan.07@gmail.com>

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
	write xlll0, 0u10;
	halt;
