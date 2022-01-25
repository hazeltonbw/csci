//colors.h - A lightweight replacement for NCURSES that does 24 bit color, cursor movement, and nonblocking I/O
//It uses standard ANSI escape codes to set the foreground and background text colors for a terminal
//Author: ShakaUVM, using code sequences found online
//#pragma once
#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <utility>

//Usage:
//Echo RED as part of a cout to turn the following text red
//Echo RESET after you are done and it will go back to normal
//For example: cout << RED << "Hello World" << RESET << endl;
const std::string RESET   = "\033[0m";
const std::string BLACK   = "\033[30m";      /* Black */
const std::string RED     = "\033[31m";      /* Red */
const std::string GREEN   = "\033[32m";      /* Green */
const std::string YELLOW  = "\033[33m";      /* Yellow */
const std::string BLUE    = "\033[34m";      /* Blue */
const std::string MAGENTA = "\033[35m";      /* Magenta */
const std::string CYAN    = "\033[36m";      /* Cyan */
const std::string WHITE   = "\033[37m";      /* White */
const std::string BOLDBLACK   = "\033[1m\033[30m";      /* Bold Black */
const std::string BOLDRED     = "\033[1m\033[31m";      /* Bold Red */
const std::string BOLDGREEN   = "\033[1m\033[32m";      /* Bold Green */
const std::string BOLDYELLOW  = "\033[1m\033[33m";      /* Bold Yellow */
const std::string BOLDBLUE    = "\033[1m\033[34m";      /* Bold Blue */
const std::string BOLDMAGENTA = "\033[1m\033[35m";      /* Bold Magenta */
const std::string BOLDCYAN    = "\033[1m\033[36m";      /* Bold Cyan */
const std::string BOLDWHITE   = "\033[1m\033[37m";      /* Bold White */

//Sets the background color for all text printed from this point on
//Values range from 0 to 255 in each color channel
void setbgcolor(uint8_t R, uint8_t G, uint8_t B) {
	std::cerr << "\x1b[48;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}

//Sets the foreground color for all text printed from this point on
void setcolor(uint8_t R, uint8_t G, uint8_t B) {
	std::cerr << "\x1b[38;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}

//Sets the foreground and background colors back to the default
void resetcolor() {
	std::cerr << "\x1b[0m";
}

//These functions are like a mini NCURSES library

//Returns the ROWS and COLS of the current terminal
std::pair<int,int> get_terminal_size() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return {w.ws_row-1, w.ws_col}; //Subtract 1 to give room for the UNIX prompt at the bottom of the screen
}

//Moves the cursor to the indicated row and column
void movecursor(uint32_t row, uint32_t col) {
	std::cerr << "\033[" << row << ";" << col << "H";
}

//Clears the screen
void clearscreen() {
	std::cerr << "\033[2J";
}

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
const int F6 			= 321; //Hmm
const int F7 			= 322;
const int F8 			= 323;
const int F9 			= 324;
const int F10 			= 325;
const int F11 			= 327; //Hmm
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
int main()
{
	set_raw_mode(true);
	while (true) {
		int c = quick_read();
		if (c == 'q') break;
		if (c == ERR) usleep(10'000);
		else std::cout << c << std::endl;
	}
	set_raw_mode(false);
}
