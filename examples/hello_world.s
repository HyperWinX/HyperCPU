/*
 * This is a simple "Hello World" program written in HyperCPU assembly (hASM).
 * It writes a [null-terminated] string to console using string literals and a little loop, then halts CPU.
 *
 * Before 0.4.5 version you could have to write a string char by char — see hello_world_classic.s for example.
 *
 * Contributed by Ivan Movchan <ivan.movchan.07@gmail.com>, 2025.
 */

data:
	.b8 "Hello, world!\n";
	.b8 0u0;

.attr(entry) main:          // Set program start point.
	mov x1, data;

loop:
	mov xlll2, [x1];
	cmp xlll2, 0u0;     // Is NULL (0u0)?
	jme end;            // Yes — go to finish.
	write xlll0, xlll2; // No — write data to console.
	inc x1;
	jmp loop;

end:
	halt;
