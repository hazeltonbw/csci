#include <iostream>
#include <vector>
#include <assert.h>
#include "Player.cc"
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
const int PADDING = PADDING_FOR_BOTTOM_MENU / 2;

class GameWindow
{
	private:
		vector<vector<char>> game_map;
		int MAX_Y, MAX_X;
		int HEIGHT_FOR_MAP;
		int LENGTH_FOR_MAP;
		int TOTAL_PADDING_FOR_MAP_LENGTH;
		int PADDING;
		int curs_y, curs_x;

	public:
		GameWindow() {
			pair<int,int> windowSize = get_terminal_size();
			MAX_Y = windowSize.first;
			MAX_X = windowSize.second;
			TOTAL_PADDING_FOR_MAP_LENGTH = 20;
			srand(time(NULL));
			set_raw_mode(true);
			clearscreen();
			createWindow();
			handleInput();
		}

		~GameWindow() {
			clean_up();
		}

		void clean_up() {
			set_raw_mode(false);
			clearscreen();
			cout << "";
			show_cursor(true);
		}

		void monsterCombat() {
			sleep(2);
			clearMenu();
			drawMap();
		}

		void demonCombat() {
			sleep(2);
			clearMenu();
			drawMap();
		}
		void check_is_on_npc(int &curs_y, int &curs_x, vector<vector<char>> &game_map) {
			// Fix one off error for screen position
			int spot_on_screen_y = curs_y-1;
			int spot_on_screen_x = curs_x-1;
			assert(game_map.size() != 0);
			assert(spot_on_screen_x >= 0 && spot_on_screen_x < (int)game_map.at(0).size());
			assert(spot_on_screen_y >= 0 && spot_on_screen_y < (int)game_map.size());
			if (game_map[spot_on_screen_y][spot_on_screen_x] == MONSTER) {
				movecursor(HEIGHT_FOR_MAP + 4,0);
				system("figlet MONSTER! | lolcat");
				//TODO: MONSTER COMBAT
				game_map[spot_on_screen_y][spot_on_screen_x] = EMPTY;
				monsterCombat();
				movecursor(curs_y, curs_x);
				cout << "X";

			}
			else if (game_map[spot_on_screen_y][spot_on_screen_x] == DEMON) {
				movecursor(HEIGHT_FOR_MAP + 4,0);
				system("figlet DEMON! | lolcat");
				//TODO: DEMON COMBAT
				game_map[spot_on_screen_y][spot_on_screen_x] = EMPTY;
				demonCombat();
				movecursor(curs_y, curs_x);
				cout << "X";
			}
			if (map_is_empty()){
				clearscreen();
				cout << "";
				movecursor(0,0);
				cout << "Map is empty! Game over.\n";
				sleep(5);
				clean_up();
				exit(0);
			}
		}

		void clearMenu() {
			movecursor(HEIGHT_FOR_MAP+4,0);
			const int COLS_USED_BY_LOLCAT = 5;
			for (int i = 0; i < COLS_USED_BY_LOLCAT; i++) {
				for (int j = 0; j < MAX_X; j++) {
					cout << " ";
				}
				cout << endl;
			}
		}

		void drawMap() {
			movecursor(0,0);
			for (size_t i = 0; i < game_map.size(); i++) {
				for (size_t j = 0; j < game_map.at(i).size(); j++) {
					cout << game_map[i][j];
				}
				cout << endl;
			}
		}

		bool map_is_empty() {
			for (vector<char> &vec : game_map)
				for (char &c : vec)
					if (c != EMPTY) return false;
			return true;
		}
		void createWindow(){
			movecursor(0,0);
			//	cout << max_x << ", " << max_y << endl;
			HEIGHT_FOR_MAP = MAX_Y - TOTAL_PADDING_FOR_MAP_LENGTH;
			if (HEIGHT_FOR_MAP < 10) {
				cout << "You're screen is too small for this game, sucks to be a pleb!\n";
				sleep(5);
				clean_up();
				exit(1);
			}
			LENGTH_FOR_MAP = MAX_X;
			curs_x = LENGTH_FOR_MAP / 2;
			curs_y = HEIGHT_FOR_MAP / 2;
			int MENU_Y_START = HEIGHT_FOR_MAP+2;
			int random_number = 0;
			// Create how high or map will be and store in map vector
			for (int i = 0; i < HEIGHT_FOR_MAP; i++) {
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
					if (i == 0 or i == MAX_Y - MENU_Y_START - 1) cout << "-";
//					else if (j == PADDING or j == MAX_X - PADDING) cout << "|";
					else if (j < PADDING or j > MAX_X - PADDING) {
						cout << " ";
					}
					else cout << " ";
				}
				cout << endl;
			}
			movecursor(curs_y, curs_x); // move to center of terminal
			cout << "X";
		}

		void handleInput() {
			while (1) {
				int c = quick_read();
				show_cursor(false); // have to turn cursor off for characters to be updated to screen correctly, otherwise you have a 1 off error
				if (c == 'q') {
//					clean_up();
//					clearscreen();
//					show_cursor(true);
//					cout << "";
					break;
				}
				else if (c == ERR) usleep(1'000'000 / 60); // 60 FPS
				else mv(curs_y, curs_x, HEIGHT_FOR_MAP, LENGTH_FOR_MAP, c);
			}
		}

		void mv(int &curs_y, int &curs_x, const int &MAX_Y, const int &MAX_X, const int &c) {
#ifndef DEBUG
			assert(curs_y >= 1 && curs_y <= MAX_Y);
			assert(curs_x >= 1 && curs_x <= MAX_X);
#endif
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
// To find positions on screen.
#ifndef DEBUG
				if (curs_y > MAX_Y) curs_y = MAX_Y;
#endif
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
#ifndef DEBUG
			check_is_on_npc(curs_y, curs_x, game_map);
#endif
		}

};

