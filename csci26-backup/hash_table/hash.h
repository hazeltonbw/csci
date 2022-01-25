#include <vector>

const int LINEAR = 0, QUADRATIC = 1, DOUBLE = 2;

template <class T, int SIZE>
class Hash {
	private:
		int mode = 0;
		std::vector<T> data;
	public:
		Hash(int mode = 0) {
			data.resize(SIZE);
			if (mode < LINEAR or mode > DOUBLE) mode = LINEAR;
			this->mode = mode;
		}
		void insert(T new_data) {
			int address = new_data % SIZE;
			if (data.at(address) == 0) {
				data.at(address) = new_data;
				return;
			}
			//OTHERWISE... yeah. Handle collisions
		}
		void remove(T old_data) {
		}
		bool search(T test_data) {
			return false;
		}
		void change(T old_data, T new_data) {
			//Remember, only change it if it actually is in the hash table
		}
};
