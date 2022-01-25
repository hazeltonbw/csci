#include <iostream>
#include <vector>
#include <assert.h>
#include "/public/colors.h"
using namespace std;
const int KEY_W = 119;
const int KEY_A = 97;
const int KEY_S = 115;
const int KEY_D = 100;
const char EMPTY = '.';
const char DEMON = 'D';
const char MONSTER = 'M';
const int PADDING_FOR_BOTTOM_MENU = 20;
const int PADDING = 10;

void check_is_on_npc(int &curs_y, int &curs_x, vector<vector<char>> &game_map) {
	// Fix one off error for screen position
	int spot_on_screen_y = curs_y-1;
	int spot_on_screen_x = curs_x-1;
	assert(game_map.size() != 0);
	assert(spot_on_screen_x >= 0 && spot_on_screen_x < (int)game_map.at(0).size());
	assert(spot_on_screen_y >= 0 && spot_on_screen_y < (int)game_map.size());;

	if (game_map[spot_on_screen_y][spot_on_screen_x] == MONSTER) {
		movecursor(3,0);
		cout << "MONSTER!";
	}
	if (game_map[spot_on_screen_y][spot_on_screen_x] == DEMON) {
		movecursor(4,0);
		cout << "DEMON!";
	}
}

void mv(int &curs_y, int &curs_x, const int &MAX_Y, const int &MAX_X, const int &c) {
	assert(curs_y >= 1 && curs_y <= MAX_Y);
	assert(curs_x >= 1 && curs_x <= MAX_X);
	movecursor(curs_y,curs_x);  // still dont know why we need this, but if it's not there we get duplicate X's
	cout << ".";
	if (c == KEY_W) {
		curs_y--;
		if (curs_y < 1) curs_y = 1;
	}
	if (c == KEY_A) {
		curs_x--;
		if (curs_x < 1) curs_x = 1;
	}
	if (c == KEY_S) {
		curs_y++;
		if (curs_y > MAX_Y) curs_y = MAX_Y;
	}
	if (c == KEY_D) {
		curs_x++;
		if (curs_x > MAX_X) curs_x = MAX_X;
	}
	movecursor(0,0);
	cout << "(y,x): (" << curs_y << "," << curs_x << ")\n";
	cout << "Size: (" << MAX_Y << "," << MAX_X << ")";
	movecursor(curs_y, curs_x);
	cout << "X";
}

int main() {
	srand(time(NULL));
	set_raw_mode(true);
	pair<int,int> max_coords = get_terminal_size();
	vector<vector<char>> game_map;
	const int MAX_X = max_coords.second, MAX_Y = max_coords.first;
//	cout << max_x << ", " << max_y << endl;
	int HEIGHT_FOR_MAP = MAX_Y - PADDING_FOR_BOTTOM_MENU;
	int LENGTH_FOR_MAP = MAX_X;
	int curs_x = LENGTH_FOR_MAP / 2;
	int curs_y = HEIGHT_FOR_MAP / 2;
	int MENU_Y_START = HEIGHT_FOR_MAP+2;

	clearscreen();
	movecursor(0,0);
	int random_number = 0;
	// Create how high or map will be and store in map vector
	for (int i = 0; i < MAX_Y; i++) {
		game_map.push_back(vector<char>{});
	}
	// Store our chars in map
	for (int i = 0; i < HEIGHT_FOR_MAP; i++) {
		for (int j = 0; j < LENGTH_FOR_MAP; j++) {
			random_number = rand() % 500;
			if (random_number == 420){
				game_map.at(i).push_back(MONSTER);
				cout << MONSTER;
			}
			else if (random_number == 69){
				game_map.at(i).push_back(DEMON);
				cout << DEMON;
			}
			else {
			   	game_map.at(i).push_back(EMPTY);
				cout << EMPTY;
			}
		}
		cout << endl;
	}

	// Display the menu
	movecursor(MENU_Y_START, 0);
	for (int i = 0; i < MAX_Y - MENU_Y_START; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (i == 0 or i == MAX_Y-MENU_Y_START-1) cout << "-";
			else if (j == PADDING or j == MAX_X-PADDING) cout << "|";
			else if (j < PADDING or j > MAX_X - PADDING) {
				cout << " ";
			}
			else cout << " ";
		}
		cout << endl;
	}
	movecursor(curs_y, curs_x); // move to center of terminal
	cout << "X";

	while (1) {
		int c = quick_read();
		show_cursor(false); // have to turn cursor off for characters to be updated to screen correctly, otherwise you have a 1 off error
		if (c == 'q') {
			clearscreen();
			show_cursor(true);
			cout << "";
			break;
		}
		else if (c == ERR) usleep(1'000'000 / 60); // 60 FPS
		else mv(curs_y, curs_x, HEIGHT_FOR_MAP, LENGTH_FOR_MAP, c);
		check_is_on_npc(curs_y, curs_x, game_map);
		/*
		else if (c == KEY_W) cout << "W";
		else if (c == KEY_A) cout << "A";
		else if (c == KEY_S) cout << "S";
		else if (c == KEY_D) cout << "D";
		*/
	}
	set_raw_mode(false);
}
