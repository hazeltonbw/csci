#include <iostream>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <cstdlib>

//Modified from: https://stackoverflow.com/a/45067593
//This function changes the standard input from "canonical" mode (which means it buffers until a newline is read)
// into raw mode, where it'll return one keystroke at a time
void set_raw_mode(bool flag) {
	static struct termios old_tio; //Save old settings
	static bool former_flag = false; //We default to canonical mode
	if (flag and !former_flag) { //Save original terminal settings
		tcgetattr(STDIN_FILENO,&old_tio);
		former_flag = true;
		termios tio = old_tio;
		tio.c_lflag &= ~(ICANON | ECHO); // Disable echo and canonical (cooked) mode
		tcsetattr(STDIN_FILENO, TCSANOW, &tio);
	} else if (!flag and former_flag) { //Restore original settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
		former_flag = false;
	}
	//else, do nothing since it's already set one way or the other
}

//Returns how many bytes are waiting in the input buffer
//Precondition: Requires set_raw_mode(true) to work
int kbhit() {
	int count = 0;
	ioctl(STDIN_FILENO, FIONREAD, &count);
	return count;
}

//Output values for quick_read() (in addition to ASCII codes)
//Some contants for making reading non-ASCII keys easy
//These might change, so be prepared to just deal with raw numbers from quick_read
const int ERR 			= -1;
const int ESC 			= 27; //ASCII code 27 is Escape
const int KEY_EOF 		= 4;
const int ARROW_UP 		= 156;
const int ARROW_DOWN 	= 157;
const int ARROW_RIGHT 	= 158;
const int ARROW_LEFT 	= 159;
const int UP_ARROW 		= ARROW_UP; //Alias
const int DOWN_ARROW 	= ARROW_DOWN; //Alias
const int RIGHT_ARROW	= ARROW_RIGHT; //Alias
const int LEFT_ARROW 	= ARROW_LEFT; //Alias
const int HOME			= 266;
const int INSERT		= 267;
const int DEL			= 268;
const int DELETE		= DEL; //Alias
const int END 			= 269;
const int PAGE_UP		= 270;
const int PAGE_DOWN 	= 271;
const int F1 			= 315;
const int F2 			= 316;
const int F3 			= 317;
const int F4 			= 318;
const int F5 			= 319;
const int F6 			= 321; //WTF
const int F7 			= 322;
const int F8 			= 323;
const int F9 			= 324;
const int F10 			= 325; 
const int F11 			= 327; //WTF
const int F12 			= 328;

//Does a non-blocking I/O read from standard input, returns one keystroke
//Lightweight Equivalent to NCURSES getch()
//Precondition: Requires set_raw_mode(true) to work
int quick_read() {
	int bytes_available = kbhit();
	if (bytes_available) {
		char c = getchar();
		if (c != 27) //The escape key is ASCII code 27
			return c;
		//Happy fun escape code parsing time
		int sum = 0;
		bytes_available--; //We've already pulled off the escape character
		if (!bytes_available) return c; //They just hit Escape in this case
		for (int i = 0; i < bytes_available; i++) {
			c = getchar();
			if (c == '2' and i == 1 and bytes_available == 4) { //We need to special case F9-12
				sum += 9;
			}
			sum += c;
		}
		return sum; //This should match ARROW_UP and so forth above
	}
	return ERR;
}

//Demo Main
/*
int main()
{
	set_raw_mode(true);
	while (true) {
		int c = quick_read();
		if (c == 'q') break;
		if (c == ERR) usleep(10'000);
		else std::cout << c << endl;
	}
	set_raw_mode(false);
}
*/
