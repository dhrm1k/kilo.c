#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termious;

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termious);
}

void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termious);
	
	atexit(disableRawMode);
	
	struct termios raw = orig_termious;

	raw.c_iflag &= ~(ECHO | ICANON);
	
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {

	enableRawMode();

	char c;
	while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if(iscntrl(c)) {
			printf("%d\n", c);
		}

		else {
			printf("%d ('%c')\n", c, c);
		}
	}
	return 0;
}
