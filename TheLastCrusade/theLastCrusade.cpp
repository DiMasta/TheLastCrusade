#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

const bool OUTPUT_GAME_DATA = 1;

const int INVALID_ID = -1;
const int INVALID_NODE_DEPTH = -1;
const int TREE_ROOT_NODE_DEPTH = 1;
const int ZERO_CHAR = '0';
const int INVALID_COORD = -1;
const int DIRECTIONS_COUNT = 4;

const string LEFT = "LEFT";
const string TOP = "TOP";
const string RIGHT = "RIGHT";

enum RoomType {
	RT_INVALID = -1,
	RT_0 = 0,
	RT_1,
	RT_2,
	RT_3,
	RT_4,
	RT_5,
	RT_6,
	RT_7,
	RT_8,
	RT_9,
	RT_10,
	RT_11,
	RT_12,
	RT_13,
};

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

class Coords {
public:
	Coords();
	Coords(int xCoord, int yCoord);

	int getXCoord() const {
		return xCoord;
	}

	int getYCoord() const {
		return yCoord;
	}

	void setXCoord(int xCoord) { this->xCoord = xCoord; }
	void setYCoord(int yCoord) { this->yCoord = yCoord; }

	Coords& operator=(const Coords& other);
	bool operator==(const Coords& other);
	Coords operator+(const Coords& other);
	Coords& operator+=(const Coords& other);

	bool isValid() const;
	void debug() const;
private:
	int xCoord;
	int yCoord;
};

//*************************************************************************************************************
//*************************************************************************************************************

Coords::Coords() :
	xCoord(INVALID_COORD),
	yCoord(INVALID_COORD)
{
}

//*************************************************************************************************************
//*************************************************************************************************************

Coords::Coords(
	int xCoord,
	int yCoord
) :
	xCoord(xCoord),
	yCoord(yCoord)
{
}

//*************************************************************************************************************
//*************************************************************************************************************

Coords& Coords::operator=(const Coords& other) {
	if (this != &other) {
		xCoord = other.xCoord;
		yCoord = other.yCoord;
	}

	return *this;
}

//*************************************************************************************************************
//*************************************************************************************************************

bool Coords::operator==(const Coords& other) {
	return (xCoord == other.xCoord) && (yCoord == other.yCoord);
}

//*************************************************************************************************************
//*************************************************************************************************************

Coords Coords::operator+(const Coords& other) {
	return Coords(xCoord + other.xCoord, yCoord + other.yCoord);
}

//*************************************************************************************************************
//*************************************************************************************************************

Coords& Coords::operator+=(const Coords& other) {
	xCoord += other.xCoord;
	yCoord += other.yCoord;

	return *this;
}

//*************************************************************************************************************
//*************************************************************************************************************

bool Coords::isValid() const {
	return INVALID_COORD != xCoord && INVALID_COORD != yCoord;
}

//*************************************************************************************************************
//*************************************************************************************************************

void Coords::debug() const {
	cerr << "Position: X=" << xCoord << ", Y=" << yCoord << endl;
}

//*************************************************************************************************************
//*************************************************************************************************************

enum Direction {
	DIR_INVALID = -1,
	DIR_N = 0,
	DIR_E,
	DIR_S,
	DIR_W,
};

//*************************************************************************************************************
//*************************************************************************************************************

Coords DIRECTIONS[DIRECTIONS_COUNT] = {
	Coords(0, -1), // N
	Coords(1,  0), // E
	Coords(0,  1), // S
	Coords(-1,  0), // W
};

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

class Room {
public:
	Room();
	virtual ~Room();

	RoomType getType() const {
		return type;
	}

	void setType(RoomType type) { this->type = type; }

	void addOpennedExit(Direction dir);

	virtual Direction getExitDirection(string entry) const = 0;
	virtual bool fillOpennedExit(Direction exitDirection, RoomType neighType) = 0;

private:
	RoomType type;
	vector<Direction> opennedExits;
};

//*************************************************************************************************************
//*************************************************************************************************************

Room::Room() :
	type(RT_INVALID),
	opennedExits()
{
}

//*************************************************************************************************************
//*************************************************************************************************************

Room::~Room() {

}

//*************************************************************************************************************
//*************************************************************************************************************

void Room::addOpennedExit(Direction dir) {
	opennedExits.push_back(dir);
}

//*************************************************************************************************************
//*************************************************************************************************************

class Type0 : public Room {
public:
	Type0() {}
	~Type0() {}

	Direction getExitDirection(string entry) const {
		return DIR_INVALID;
	}

	bool fillOpennedExit(Direction exitDirection, RoomType neighType) {
		return false;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type1 : public Room {
public:
	Type1() {}
	~Type1() {}

	Direction getExitDirection(string entry) const {
		return DIR_S;
	}

	bool fillOpennedExit(Direction exitDirection, RoomType neighType) {
		bool exitOpenned = false;

		if (DIR_S == exitDirection) {
			exitOpenned = checkIfExitIsOpenned(exitDirection, neighType);

		}

		if (DIR_E == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_2 == neighType ||
				RT_5 == neighType ||
				RT_6 == neighType ||
				RT_8 == neighType ||
				RT_9 == neighType ||
				RT_13 == neighType;
		}

		if (DIR_W == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_2 == neighType ||
				RT_4 == neighType ||
				RT_6 == neighType ||
				RT_7 == neighType ||
				RT_8 == neighType ||
				RT_12 == neighType;
		}

		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type2 : public Room {
public:
	Type2() {}
	~Type2() {}

	Direction getExitDirection(string entry) const {
		Direction dir = DIR_INVALID;

		if (LEFT == entry) {
			dir = DIR_E;
		}
		else if (RIGHT == entry) {
			dir = DIR_W;
		}

		return dir;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;

		if (DIR_E == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_2 == neighType ||
				RT_5 == neighType ||
				RT_6 == neighType ||
				RT_8 == neighType ||
				RT_9 == neighType ||
				RT_13 == neighType;
		}
		else if (DIR_W == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_2 == neighType ||
				RT_4 == neighType ||
				RT_6 == neighType ||
				RT_7 == neighType ||
				RT_8 == neighType ||
				RT_12 == neighType;
		}

		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type3 : public Room {
public:
	Type3() {}
	~Type3() {}

	Direction getExitDirection(string entry) const {
		return DIR_S;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;

		if (DIR_S == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_3 == neighType ||
				RT_4 == neighType ||
				RT_5 == neighType ||
				RT_7 == neighType ||
				RT_9 == neighType ||
				RT_10 == neighType ||
				RT_11 == neighType;
		}

		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type4 : public Room {
public:
	Type4() {}
	~Type4() {}

	Direction getExitDirection(string entry) const {
		Direction dir = DIR_INVALID;

		if (TOP == entry) {
			dir = DIR_W;
		}
		else if (RIGHT == entry) {
			dir = DIR_S;
		}

		return dir;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;

		if (DIR_W == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_2 == neighType ||
				RT_4 == neighType ||
				RT_6 == neighType ||
				RT_7 == neighType ||
				RT_8 == neighType ||
				RT_12 == neighType;
		}
		else if (DIR_S == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_3 == neighType ||
				RT_4 == neighType ||
				RT_5 == neighType ||
				RT_7 == neighType ||
				RT_9 == neighType ||
				RT_10 == neighType ||
				RT_11 == neighType;
		}

		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type5 : public Room {
public:
	Type5() {}
	~Type5() {}

	Direction getExitDirection(string entry) const {
		Direction dir = DIR_INVALID;

		if (TOP == entry) {
			dir = DIR_E;
		}
		else if (LEFT == entry) {
			dir = DIR_S;
		}

		return dir;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;

		if (DIR_E == direction) {
			exitOpenned =
				RT_1 == neighType ||
				RT_2 == neighType ||
				RT_5 == neighType ||
				RT_6 == neighType ||
				RT_8 == neighType ||
				RT_9 == neighType ||
				RT_13 == neighType;
		}

		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type6 : public Room {
public:
	Type6() {}
	~Type6() {}

	Direction getExitDirection(string entry) const {
		Direction dir = DIR_INVALID;

		if (LEFT == entry) {
			dir = DIR_E;
		}
		else if (RIGHT == entry) {
			dir = DIR_W;
		}

		return dir;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type7 : public Room {
public:
	Type7() {}
	~Type7() {}

	Direction getExitDirection(string entry) const {
		return DIR_S;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type8 : public Room {
public:
	Type8() {}
	~Type8() {}

	Direction getExitDirection(string entry) const {
		return DIR_S;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type9 : public Room {
public:
	Type9() {}
	~Type9() {}

	Direction getExitDirection(string entry) const {
		return DIR_S;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type10 : public Room {
public:
	Type10() {}
	~Type10() {}

	Direction getExitDirection(string entry) const {
		return DIR_W;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type11 : public Room {
public:
	Type11() {}
	~Type11() {}

	Direction getExitDirection(string entry) const {
		return DIR_E;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type12 : public Room {
public:
	Type12() {}
	~Type12() {}

	Direction getExitDirection(string entry) const {
		return DIR_S;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//*************************************************************************************************************
//*************************************************************************************************************

class Type13 : public Room {
public:
	Type13() {}
	~Type13() {}

	Direction getExitDirection(string entry) const {
		return DIR_S;
	}

	bool checkForOpennedExit(Direction direction, RoomType neighType) {
		bool exitOpenned = false;



		return exitOpenned;
	}

private:
};

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

typedef vector<Room*> Rooms;

class Dungeon {
public:
	Dungeon();
	~Dungeon();

	void init(int height, int width);
	void setRoomType(Coords coords, RoomType roomType);
	Room* getRoom(Coords coords) const;
	bool validCoords(Coords coords) const;
	void createRoom(Coords coords, RoomType roomType);
	void fillOpennedExits();
	bool checkIfExitIsOpenned(Direction exitDirection, RoomType roomType, RoomType neighType) const;

	void debug() const;
private:
	int width;
	int height;

	Room*** map;
};

//*************************************************************************************************************
//*************************************************************************************************************

Dungeon::Dungeon() {

}

//*************************************************************************************************************
//*************************************************************************************************************

Dungeon::~Dungeon() {
	if (map) {
		for (int rowIdx = 0; rowIdx < height; ++rowIdx) {
			if (map[rowIdx]) {
				for (int colIdx = 0; colIdx < width; ++colIdx) {
					if (map[rowIdx][colIdx]) {
						delete map[rowIdx][colIdx];
						map[rowIdx][colIdx] = NULL;
					}
				}

				delete[] map[rowIdx];
				map[rowIdx] = NULL;
			}
		}

		delete[] map;
		map = NULL;
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Dungeon::init(int height, int width) {
	this->height = height;
	this->width = width;

	map = new Room**[height];

	for (int rowIdx = 0; rowIdx < height; ++rowIdx) {
		map[rowIdx] = new Room*[width];

		for (int colIdx = 0; colIdx < width; ++colIdx) {
			map[rowIdx][colIdx] = NULL;
		}
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Dungeon::setRoomType(Coords coords, RoomType roomType) {
	map[coords.getYCoord()][coords.getXCoord()]->setType(roomType);
}

//*************************************************************************************************************
//*************************************************************************************************************

Room* Dungeon::getRoom(Coords coords) const {
	return map[coords.getYCoord()][coords.getXCoord()];
}

//*************************************************************************************************************
//*************************************************************************************************************

bool Dungeon::validCoords(Coords coords) const {
	int x = coords.getXCoord();
	int y = coords.getYCoord();
	return x >= 0 && x < width && y >= 0 && y < height;
}

//*************************************************************************************************************
//*************************************************************************************************************

void Dungeon::createRoom(Coords coords, RoomType roomType) {
	switch (roomType) {
		case RT_0: { map[coords.getYCoord()][coords.getXCoord()] = new Type0(); break; }
		case RT_1: { map[coords.getYCoord()][coords.getXCoord()] = new Type1(); break; }
		case RT_2: { map[coords.getYCoord()][coords.getXCoord()] = new Type2(); break; }
		case RT_3: { map[coords.getYCoord()][coords.getXCoord()] = new Type3(); break; }
		case RT_4: { map[coords.getYCoord()][coords.getXCoord()] = new Type4(); break; }
		case RT_5: { map[coords.getYCoord()][coords.getXCoord()] = new Type5(); break; }
		case RT_6: { map[coords.getYCoord()][coords.getXCoord()] = new Type6(); break; }
		case RT_7: { map[coords.getYCoord()][coords.getXCoord()] = new Type7(); break; }
		case RT_8: { map[coords.getYCoord()][coords.getXCoord()] = new Type8(); break; }
		case RT_9: { map[coords.getYCoord()][coords.getXCoord()] = new Type9(); break; }
		case RT_10: { map[coords.getYCoord()][coords.getXCoord()] = new Type10(); break; }
		case RT_11: { map[coords.getYCoord()][coords.getXCoord()] = new Type11(); break; }
		case RT_12: { map[coords.getYCoord()][coords.getXCoord()] = new Type12(); break; }
		case RT_13: { map[coords.getYCoord()][coords.getXCoord()] = new Type13(); break; }
		default: { break; }
	}
	
	map[coords.getYCoord()][coords.getXCoord()]->setType(roomType);
}

//*************************************************************************************************************
//*************************************************************************************************************

void Dungeon::fillOpennedExits() {
	for (int rowIdx = 0; rowIdx < height; ++rowIdx) {
		for (int colIdx = 0; colIdx < width; ++colIdx) {
			Room* room = map[rowIdx][colIdx];

			Coords roomCoords(colIdx, rowIdx);
			// Start from 1, because Nort cannot be an exit
			for (int dirIdx = 1; dirIdx < DIRECTIONS_COUNT; ++dirIdx) {
				Coords neighCoords = roomCoords + DIRECTIONS[dirIdx];

				if (validCoords(neighCoords)) {
					Direction exitDir = (Direction)dirIdx;
					RoomType neighType = getRoom(neighCoords)->getType();

					bool opennedExit = checkIfExitIsOpenned(exitDir, room->getType(), neighType);

					if (opennedExit) {
						room->addOpennedExit(exitDir);
					}
				}
			}
		}
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Dungeon::debug() const {
	for (int rowIdx = 0; rowIdx < height; ++rowIdx) {
		for (int colIdx = 0; colIdx < width; ++colIdx) {
			cerr << map[rowIdx][colIdx]->getType();
		}

		cerr << endl;
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

bool Dungeon::checkIfExitIsOpenned(Direction exitDirection, RoomType roomType, RoomType neighType) const {
	bool exitOpenned = false;

	bool hasSouthExit = roomType;
	bool hasEastExit;
	bool hasWestExit;

	if (hasSouthExit && DIR_S == exitDirection) {
		exitOpenned =
			RT_1 == neighType ||
			RT_3 == neighType ||
			RT_4 == neighType ||
			RT_5 == neighType ||
			RT_7 == neighType ||
			RT_9 == neighType ||
			RT_10 == neighType ||
			RT_11 == neighType;
	}
	else if (hasEastExit && DIR_E == exitDirection) {
		exitOpenned =
			RT_1 == neighType ||
			RT_2 == neighType ||
			RT_5 == neighType ||
			RT_6 == neighType ||
			RT_8 == neighType ||
			RT_9 == neighType ||
			RT_13 == neighType;
	}
	else if (hasWestExit && DIR_W == exitDirection) {
		exitOpenned =
			RT_1 == neighType ||
			RT_2 == neighType ||
			RT_4 == neighType ||
			RT_6 == neighType ||
			RT_7 == neighType ||
			RT_8 == neighType ||
			RT_12 == neighType;
	}

	return exitOpenned;
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

class Indy {
public:
	Indy();
	~Indy();

	Coords getPosition() const {
		return position;
	}

	string getEntry() const {
		return entry;
	}

	void setPosition(Coords coords) { this->position = coords; }
	void setEntry(string entry) { this->entry = entry; }

private:
	Coords position;
	string entry;
};

//*************************************************************************************************************
//*************************************************************************************************************

Indy::Indy() :
	position()
{

}

//*************************************************************************************************************
//*************************************************************************************************************

Indy::~Indy() {

}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

class Game {
public:
	Game();
	~Game();

	void initGame();
	void gameBegin();
	void gameLoop();
	void getGameInput();
	void getTurnInput();
	void turnBegin();
	void makeTurn();
	void turnEnd();
	void play();

	void debug() const;

	Direction nextRoomDirection() const;

private:
	int turnsCount;

	Dungeon* dungeon;
	Indy* indy;
};

//*************************************************************************************************************
//*************************************************************************************************************

Game::Game() :
	turnsCount(0),
	dungeon(NULL),
	indy(NULL)
{
}

//*************************************************************************************************************
//*************************************************************************************************************

Game::~Game() {
	if (dungeon) {
		delete dungeon;
		dungeon = NULL;
	}

	if (indy) {
		delete indy;
		indy = NULL;
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::initGame() {
	indy = new Indy();
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::gameBegin() {
	dungeon->fillOpennedExits();
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::gameLoop() {
	while (true) {
		getTurnInput();
		turnBegin();
		makeTurn();
		turnEnd();
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::getGameInput() {
	int W; // number of columns.
	int H; // number of rows.
	cin >> W >> H; cin.ignore();
	if (OUTPUT_GAME_DATA) {
		cerr << W << " " << H << endl;
	}

	dungeon = new Dungeon();
	dungeon->init(H, W);

	for (int rowIdx = 0; rowIdx < H; ++rowIdx) {
		for (int colIdx = 0; colIdx < W; ++colIdx) {
			char roomTypeChar;
			cin >> roomTypeChar;
			if (OUTPUT_GAME_DATA) {
				cerr << roomTypeChar;
			}

			int roomTypeInt = roomTypeChar - ZERO_CHAR;

			Coords coords(colIdx, rowIdx);
			dungeon->createRoom(coords, (RoomType)roomTypeInt);
		}

		cin.ignore();
		if (OUTPUT_GAME_DATA) {
			cerr << endl;
		}
	}

	int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
	cin >> EX; cin.ignore();
	if (OUTPUT_GAME_DATA) {
		cerr << EX << endl;
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::getTurnInput() {
	int XI;
	int YI;
	string POS;
	cin >> XI >> YI >> POS; cin.ignore();
	if (OUTPUT_GAME_DATA) {
		//cerr << XI << " " << YI << " " << POS << endl;
	}

	indy->setPosition(Coords(XI, YI));
	indy->setEntry(POS);
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::turnBegin() {
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::makeTurn() {
	Direction dir = nextRoomDirection();
	Coords indyPositon = indy->getPosition();
	Coords res = indyPositon + DIRECTIONS[dir];

	cout << res.getXCoord() << " " << res.getYCoord() << endl;
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::turnEnd() {
	++turnsCount;
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::play() {
	initGame();
	getGameInput();
	gameBegin();
	gameLoop();
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::debug() const {
	dungeon->debug();
}

//*************************************************************************************************************
//*************************************************************************************************************

Direction Game::nextRoomDirection() const {
	Coords indyPosition = indy->getPosition();
	string indyEntry = indy->getEntry();
	return dungeon->getRoom(indyPosition)->getExitDirection(indyEntry);
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

#ifdef TESTS
#include "debug.h"
#endif // TESTS

int main(int argc, char** argv) {
#ifdef TESTS
	doctest::Context context;
	int res = context.run();
#else
	Game game;
	game.play();
#endif // TESTS

	return 0;
}