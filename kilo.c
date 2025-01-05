/* includes */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* data */
struct termios orig_termious;

/* terminal */
void die(const char *s) {
	perror(s);
	exit(1);
}

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termious) == -1) {
		die("tcsetattr");
	}
}

void enableRawMode() {
	if (tcgetattr(STDIN_FILENO, &orig_termious) == -1) die("tcsetattr");
	
	

	atexit(disableRawMode);
	
	struct termios raw = orig_termious;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	
	raw.c_oflag &= ~(OPOST);
	
	raw.c_cflag |= (CS8);

	raw.c_iflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	
	raw.c_cc[VMIN] = 0;
	
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1 && errno != EAGAIN) die("tcsetattr");
}




/* init */

int main() {

	enableRawMode();

//	char c;
//	while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {

	while(1) {
		char c = '\0';

		read(STDIN_FILENO, &c, 1);
		if(iscntrl(c)) {
			printf("%d\r\n", c);
		}

		else {
			printf("%d ('%c')\r\n", c, c);
		}

		if(c == 'q') break;
	}
	return 0;
}
