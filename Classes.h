#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>

using namespace std;

class WaterVehicle
{
private:
	string name;
	int lengthOfShip;
	char xCord;
	int yCord;
	char horiOrVert;
	bool sunk;
	bool ready = false; //default is false and will be changed when succefully added to true
	int damageTaken;
public:
	WaterVehicle() { ; }
	void setNameOfShip(string _name) { name = _name; }
	string getNameOfShip() { return name; }
	void setLengthOfShip(int _lengthOfShip) { lengthOfShip = _lengthOfShip; }
	int getLengthOfShip() { return lengthOfShip; }
	void setLocationX(char _location) { xCord = _location; }
	char getLocationX() { return xCord; }
	void setLocationY(int _location) { yCord = _location; }
	int getLocationY() { return yCord; }
	void setHorzOrVert(char _horiOrVert) { horiOrVert = _horiOrVert; }
	char getHorzOrVert() { return horiOrVert; }
	void setSunk(bool _sunk) { sunk = _sunk; }
	bool getSunk() { return sunk; }
	void setReady(bool _ready) { ready = _ready; }
	bool getReady() { return ready; }
	void setDamageTaken(int _damageTaken) { damageTaken = _damageTaken; }
	int getDamageTaken() { return damageTaken; }
	void increaseDamageTaken() { damageTaken++; }
	friend ostream &operator << (ostream &out, WaterVehicle _object);
};

class Grid
{
private:
	WaterVehicle Carrier;
	WaterVehicle Battleship;
	WaterVehicle Cruiser;
	WaterVehicle Submarine;
	WaterVehicle Destroyer;
	vector<vector<char> > grid;
public:
	Grid();
	void initializeShip(string nameOfShip, char xCordTemp, int yCordTemp, char HoriOrVertTemp);
	void setShip(WaterVehicle &object, char xCordTemp, int yCordTemp, char HoriOrVertTemp);
	void printGrid();
	void printBoats();
	void setGrid(int locationX, int locationY, char value);
	bool getReadyStatus();
	int getGridPosition(int xCord, int yCord);
	bool isGameOver();
	bool isHit(int xCord, int yCord);
};
//each player has a grid
//each grid has a watervehicle
//a user is a player
//a bot is a player
//a game has players who have grids

class Player
{
protected:
//	char xTorp;
//	int yTorp;
//	char xStart;
//	int yStart;
	Grid playerGrid;
public:
	Player() { ; }
	void createCordShips() { ; }
	void isReady() { ; }
	void showGrid() { ; }
	void updateGrid() { ; }
	int getGridPosition(int xCord, int yCord) { ; }
	int createTorpX() { ; }
	int createTorpY() { ; }
	void setSinkStatus(int xCord, int yCord) { ; }
	bool isGameOver() { ; }
};

class User : public Player 
{
public:
	User() { ; }
	void createCordShips();
	void isReady(User player1);
	void showGrid();
	bool updateGrid(int xCord, int yCord);
	int getGridPosition(int xCord, int yCord);
	int createTorpX();
	int createTorpY();
	void setSinkStatus(int xCord, int yCord);
	bool isGameOver();
};

class Bot : public Player
{
private:
	vector<vector<char> > botGrid; //FAKE GRID
public:
	Bot();
	void createCordShips();
	void isReady(Bot player2);
	void showGrid();
	void showGridCheat();
	bool updateGrid(int xCord, int yCord);
	int getGridPosition(int xCord, int yCord);
	int createTorpX();
	int createTorpY();
	void setSinkStatus(int xCord, int yCord);
	bool isGameOver();
};

class Game
{
private:
	User player1;
	Bot player2;
public:
	Game();
	void playGame();
};
#endif
