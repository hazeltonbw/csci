#include "/public/colors.h"
using namespace std;

int main()
{
	clearscreen(); //Erase the screen
	set_raw_mode(true); //Turn on nonblocking I/O
	while (true) {
		int c = quick_read();
		if (c == 'q') break;
		if (c == -1) {
			usleep(1000);
			continue;
		}
		std::cout << c << endl;
	}
	set_raw_mode(false);
}
