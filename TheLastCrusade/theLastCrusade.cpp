#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int W; // number of columns.
	int H; // number of rows.
	cin >> W >> H; cin.ignore();
	for (int i = 0; i < H; i++) {
		string LINE; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
		getline(cin, LINE);
	}
	int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
	cin >> EX; cin.ignore();

	// game loop
	while (1) {
		int XI;
		int YI;
		string POS;
		cin >> XI >> YI >> POS; cin.ignore();

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;


		// One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
		cout << XI << " " << YI + 1 << endl;
	}
}