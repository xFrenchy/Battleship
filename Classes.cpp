#include "Classes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>	//https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

ostream &operator << (ostream &out, WaterVehicle _object)
{
	int horiOrVert = _object.getHorzOrVert();
	bool sunk = _object.getSunk();

	out << "Name of ship:" << _object.getNameOfShip() << "\tLength of ship:"
		<< _object.getLengthOfShip() << "\tStarting location:" << _object.getLocationX()
		<< _object.getLocationY();
	if (horiOrVert == 'H')
	{
		out << "\tShip is horizontal";
	}
	else
	{
		out << "\tShip is vertical";
	}
/*	if (sunk == true)
	{
		out << "\tShip has been sunk";
	}
	else
	{
		out << "\tShip has not been sunk";
	}
*/
	return out;
}

Grid::Grid()
{
	Carrier.setNameOfShip("Carrier");
	Carrier.setLengthOfShip(5);
	Carrier.setDamageTaken(0);

	Battleship.setNameOfShip("Battleship");
	Battleship.setLengthOfShip(4);
	Battleship.setDamageTaken(0);

	Cruiser.setNameOfShip("Cruiser");
	Cruiser.setLengthOfShip(3);
	Cruiser.setDamageTaken(0);

	Submarine.setNameOfShip("Submarine");
	Submarine.setLengthOfShip(3);
	Submarine.setDamageTaken(0);

	Destroyer.setNameOfShip("Destroyer");
	Destroyer.setLengthOfShip(2);
	Destroyer.setDamageTaken(0);

	grid.resize(10, vector<char>(10, '0'));
}

Bot::Bot()
{
	botGrid.resize(10, vector<char>(10, '0'));
}

void Grid::printGrid()
{
	//this doesn't have to be complex but I wanted to make it all align and have it look pretty
	char x = 'A';
	int y = 1;
	cout << "  ";
	for (int i = 0; i < 10; i++)
	{
		cout << "|" << x++;
	}
	cout << "|\n";

	for (int i = 0; i < 9; i++)
	{
		cout << y++ << " |";
		for (int j = 0; j < 10; j++)
		{
			cout << grid[j][i] << " ";
		}
		cout << endl;
	}
	for (int i = 9; i < 10; i++)
	{
		cout << y++ << "|";
		for (int j = 0; j < 10; j++)
		{
			cout << grid[j][i] << " ";
		}
		cout << endl;
	}
}

void Grid::printBoats()
{
	//this is using the overloaded cout operator with wateverhicle objects
	cout << "Here are you boats and coordinates!\n";
	cout << Carrier << endl;
	cout << Battleship << endl;
	cout << Cruiser << endl;
	cout << Submarine << endl;
	cout << Destroyer << endl;
}

void Grid::setGrid(int locationX, int locationY, char value)
{
	grid[locationX][locationY] = value;
}

void Grid::initializeShip(string nameOfShip, char xCordTemp, int yCordTemp, char HoriOrVertTemp)
{
	if (nameOfShip == Carrier.getNameOfShip())
	{
		setShip(Carrier, xCordTemp, yCordTemp, HoriOrVertTemp);
	}
	else if (nameOfShip == Battleship.getNameOfShip())
	{
		setShip(Battleship, xCordTemp, yCordTemp, HoriOrVertTemp);
	}
	else if (nameOfShip == Cruiser.getNameOfShip())
	{
		setShip(Cruiser, xCordTemp, yCordTemp, HoriOrVertTemp);
	}
	else if (nameOfShip == Submarine.getNameOfShip())
	{
		setShip(Submarine, xCordTemp, yCordTemp, HoriOrVertTemp);
	}
	else if (nameOfShip == Destroyer.getNameOfShip())
	{
		setShip(Destroyer, xCordTemp, yCordTemp, HoriOrVertTemp);
	}
	else
	{
		cout << "Sorry! " << nameOfShip << " doesn't exist as a ship!\n";
	}
}

void Grid::setShip(WaterVehicle &object, char xCordTemp, int yCordTemp, char HoriOrVertTemp)
{
	int valueInGrid = 0;
	int xCordGrid = (xCordTemp - 65);
	int yCordGrid = yCordTemp - 1; //I need to reduce it by 1 or else it will always be 1-10 and never equal 0

	if (grid[xCordGrid][yCordGrid] == '0') //if starting location is not taken
	{
		if (HoriOrVertTemp == 'V')	//if Vertical
		{
			if (yCordGrid + object.getLengthOfShip() <= 9) //if it doesn't go out of bounds vertically, 0-9 for grid 1-10 for player
			{
				for (int j = yCordGrid; j < (object.getLengthOfShip() + yCordGrid); j++)
				{
					valueInGrid += grid[xCordGrid][j];	//adding the value inside the grid that the ship would have taken up
				}
				if (valueInGrid == ('0' * object.getLengthOfShip())) //if the value is equal to 0 for every spot is takes up
				{
					for (int j = 0; j < object.getLengthOfShip(); j++)
					{
						grid[xCordGrid][yCordGrid++] = '1'; //placing the boat on the grid
					}
					object.setLocationX(xCordTemp);
					object.setLocationY(yCordTemp);
					object.setHorzOrVert(HoriOrVertTemp);
					object.setReady(true);	//ship has been added succefully
				}
				else	//It was able to be on the grid BUT a boat was already there
				{
					cout << "Some coordinates of the ship are already taken!\n";
				}
			}	
			else	//out of bounds
			{
				cout << "Your ship is out of bounds with these coordinates!\n";
				cout << xCordTemp << yCordTemp << " " << "going: " << HoriOrVertTemp << endl;
			}
		}	//end of if vertical
		else if(HoriOrVertTemp == 'H')	//horizontal
		{
			if (xCordGrid + object.getLengthOfShip() <= 9)	//Making sure it doesn't go out of bounds horizontally
			{
				for (int j = xCordGrid; j < (object.getLengthOfShip() + xCordGrid); j++)
				{
					valueInGrid += grid[j][yCordGrid];
				}
				if (valueInGrid == ('0' * object.getLengthOfShip()))
				{
					for (int j = 0; j < object.getLengthOfShip(); j++)
					{
						grid[xCordGrid++][yCordGrid] = '1';
					}
					object.setLocationX(xCordTemp);
					object.setLocationY(yCordTemp);
					object.setHorzOrVert(HoriOrVertTemp);
					object.setReady(true);
				}
				else
				{
					cout << "Some coordinates of the ship are already taken!\n";
				}
			}
			else
			{
				cout << "Your ship is out of bounds with these coordinates!\n";
				cout << xCordTemp << yCordTemp << " " << "going: " << HoriOrVertTemp << endl;
			}
		}
		else
		{
			cout << "Something went wrong with the vertical or horizontal variable!\n";
		}

	}
	else
	{
		cout << xCordTemp << yCordTemp << " is already taken by another ship! Choose again for this ship\n";
	}
}

/*
				   ______________________________________________________
	              | Beep Boop                                            |
             /    |          I'm distracted                              |
            /---, |                        There goes my thinking process|
       -----# ==| |                                                      |
       | :) # ==| |               oh well...                             |
  -----'----#   | |______________________________________________________|
  |)___()  '#   |______====____   \___________________________________|
 [_/,-,\"--"------ //,-,  ,-,\\\   |/             //,-,  ,-,  ,-,\\ __#
   ( 0 )|===******||( 0 )( 0 )||-  o              '( 0 )( 0 )( 0 )||
----'-'--------------'-'--'-'-----------------------'-'--'-'--'-'--------------	
*/

bool Grid::getReadyStatus()
{
	//if any are not set up properly, get the name, xcord, ycord, and H/V to pass into initialization
	//I've changed some of the couts and removed some because they got spammy
	bool notReady = true;
	string nameOfShip;
	char xCordTemp, HoriOrVertTemp;
	int yCordTemp, random;
	while (notReady == true)
	{
		while (Carrier.getReady() == false)
		{
			if (Carrier.getReady() == false)
			{
				cout << "Changing Carrier...\n";
				nameOfShip = Carrier.getNameOfShip();
				xCordTemp = (rand() % 9 + 65);
				yCordTemp = (rand() % 10 + 1);
				random = rand() % 1;
				if (random == 0)
				{
					HoriOrVertTemp = 'H';
				}
				if (random == 1)
				{
					HoriOrVertTemp = 'V';
				}
				initializeShip(nameOfShip, xCordTemp, yCordTemp, HoriOrVertTemp);
				if (Carrier.getReady() == false)
				{
//					cout << "Whoops I gave it values that just don't work.. Let me try again!\n";
				}
				else
				{
					cout << "Carrier has been set up corrently!\n";
				}
			}
		}
		while (Battleship.getReady() == false)
		{
			if (Battleship.getReady() == false)
			{
				cout << "Changing Battleship...\n";
				nameOfShip = Battleship.getNameOfShip();
				xCordTemp = (rand() % 9 + 65);
				yCordTemp = (rand() % 10 + 1);
				random = rand() % 1;
				if (random == 0)
				{
					HoriOrVertTemp = 'H';
				}
				if (random == 1)
				{
					HoriOrVertTemp = 'V';
				}
				initializeShip(nameOfShip, xCordTemp, yCordTemp, HoriOrVertTemp);
				if (Battleship.getReady() == false)
				{
//					cout << "Whoops I gave it values that just don't work.. Let me try again!\n";
				}
				else
				{
					cout << "Battleship has been set up corrently!\n";
				}
			}
		}
		while (Cruiser.getReady() == false)
		{
			if (Cruiser.getReady() == false)
			{
				cout << "Changing Cruiser...\n";
				nameOfShip = Cruiser.getNameOfShip();
				xCordTemp = (rand() % 9 + 65);
				yCordTemp = (rand() % 10 + 1);
				random = rand() % 1;
				if (random == 0)
				{
					HoriOrVertTemp = 'H';
				}
				if (random == 1)
				{
					HoriOrVertTemp = 'V';
				}
				initializeShip(nameOfShip, xCordTemp, yCordTemp, HoriOrVertTemp);
				if (Cruiser.getReady() == false)
				{
//					cout << "Whoops I gave it values that just don't work.. Let me try again!\n";
				}
				else
				{
					cout << "Cruiser has been set up corrently!\n";
				}
			}
		}
		while (Submarine.getReady() == false)
		{
			if (Submarine.getReady() == false)
			{
				cout << "Changing Submarine...\n";
				nameOfShip = Submarine.getNameOfShip();
				xCordTemp = (rand() % 9 + 65);
				yCordTemp = (rand() % 10 + 1);
				random = rand() % 1;
				if (random == 0)
				{
					HoriOrVertTemp = 'H';
				}
				if (random == 1)
				{
					HoriOrVertTemp = 'V';
				}
				initializeShip(nameOfShip, xCordTemp, yCordTemp, HoriOrVertTemp);
				if (Submarine.getReady() == false)
				{
//					cout << "Whoops I gave it values that just don't work.. Let me try again!\n";
				}
				else
				{
					cout << "Submarine has been set up corrently!\n";
				}
			}
		}
		while (Destroyer.getReady() == false)
		{
			if (Destroyer.getReady() == false)
			{
				cout << "Changing Destroyer...\n";
				nameOfShip = Destroyer.getNameOfShip();
				xCordTemp = (rand() % 9 + 65);
				yCordTemp = (rand() % 10 + 1);
				random = rand() % 1;
				if (random == 0)
				{
					HoriOrVertTemp = 'H';
				}
				if (random == 1)
				{
					HoriOrVertTemp = 'V';
				}
				initializeShip(nameOfShip, xCordTemp, yCordTemp, HoriOrVertTemp);
				if (Destroyer.getReady() == false)
				{
//					cout << "Whoops I gave it values that just don't work.. Let me try again!\n";
				}
				else
				{
					cout << "Destroyer has been set up corrently!\n";
				}
			}
		}
		if ((Carrier.getReady() && Battleship.getReady() && Cruiser.getReady() && Submarine.getReady() && Destroyer.getReady()) == true)
		{
//			cout << "Player 1 is ready to play the game! Here is your grid:\n";
//			printGrid();
//			cout << "Here are you boats and coordinates!\n";
//			cout << Carrier << endl;
//			cout << Battleship << endl;
//			cout << Cruiser << endl;
//			cout << Submarine << endl;
//			cout << Destroyer << endl;

			notReady = false;
		}
	}
	return true;
}

int Grid::getGridPosition(int xCord, int yCord)
{
	return grid[xCord][yCord];
}

bool Grid::isGameOver()
{
	if ((Carrier.getSunk() && Battleship.getSunk() && Cruiser.getSunk() && Submarine.getSunk() && Destroyer.getSunk()) == true)
		return true;
	else
		return false;
}

bool Grid::isHit(int xCord, int yCord)
{
	//Before you judge me for the copy and pasta of this function, I know..I know..It's bad.
	//But I can't think of a way to figure out which object I'm working with without using the
	//coordinates to check if they match. I can figure out the object based on the coordinates
	//But if I do that and then throw it into a function that does the rest, it's still really copy/pasty
	char horz, temp;
	int boatX, boatY;
	horz = Carrier.getHorzOrVert();
	temp = Carrier.getLocationX();
	boatX = temp - 65;
	boatY = (Carrier.getLocationY() - 1);
	if (horz == 'V')
	{
		for (int i = 0; i < Carrier.getLengthOfShip(); i++)
		{
			if (yCord == (Carrier.getLocationY() - 1)+ i)
			{
				if (xCord == Carrier.getLocationX())
				{
					Carrier.increaseDamageTaken();
					if (Carrier.getDamageTaken() == Carrier.getLengthOfShip())
					{
						Carrier.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}//end of if vertical
	else
	{
		for (int i = 0; i < Carrier.getLengthOfShip(); i++)
		{
			if (xCord == (Carrier.getLocationX() - 65) + i)
			{
				if (yCord == (Carrier.getLocationY() - 1))
				{
					Carrier.increaseDamageTaken();
					if (Carrier.getDamageTaken() == Carrier.getLengthOfShip())
					{
						Carrier.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}
	horz = Battleship.getHorzOrVert();
	temp = Battleship.getLocationX();
	boatX = temp - 65;
	boatY = Battleship.getLocationY() - 1;
	if (horz == 'V') 
	{
		for (int i = 0; i < Battleship.getLengthOfShip(); i++)
		{
			if (yCord == (Battleship.getLocationY() - 1) + i)
			{
				if (xCord == Battleship.getLocationX())
				{
					Battleship.increaseDamageTaken();
					if (Battleship.getDamageTaken() == Battleship.getLengthOfShip())
					{
						Battleship.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}//end of if vertical
	else
	{
		for (int i = 0; i < Battleship.getLengthOfShip(); i++)
		{
			if (xCord == (Battleship.getLocationX() - 65) + i)
			{
				if (yCord == (Battleship.getLocationY() - 1))
				{
					Battleship.increaseDamageTaken();
					if (Battleship.getDamageTaken() == Battleship.getLengthOfShip())
					{
						Battleship.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}
	horz = Cruiser.getHorzOrVert();
	temp = Cruiser.getLocationX();
	boatX = temp - 65;
	boatY = Cruiser.getLocationY() - 1;
	if (horz == 'V')
	{
		for (int i = 0; i < Cruiser.getLengthOfShip(); i++)
		{
			if (yCord == (Cruiser.getLocationY() - 1) + i)
			{
				if (xCord == Cruiser.getLocationX())
				{
					Cruiser.increaseDamageTaken();
					if (Cruiser.getDamageTaken() == Cruiser.getLengthOfShip())
					{
						Cruiser.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}//end of if vertical
	else
	{
		for (int i = 0; i < Cruiser.getLengthOfShip(); i++)
		{
			if (xCord == (Cruiser.getLocationX() - 65) + i)
			{
				if (yCord == (Cruiser.getLocationY() - 1))
				{
					Cruiser.increaseDamageTaken();
					if (Cruiser.getDamageTaken() == Cruiser.getLengthOfShip())
					{
						Cruiser.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}
	horz = Submarine.getHorzOrVert();
	temp = Submarine.getLocationX();
	boatX = temp - 65;
	boatY = Submarine.getLocationY() - 1;
	if (horz == 'V') 
	{
		for (int i = 0; i < Submarine.getLengthOfShip(); i++)
		{
			if (yCord == (Submarine.getLocationY() - 1) + i)
			{
				if (xCord == Submarine.getLocationX())
				{
					Submarine.increaseDamageTaken();
					if (Submarine.getDamageTaken() == Submarine.getLengthOfShip())
					{
						Submarine.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}//end of if vertical
	else
	{
		for (int i = 0; i < Submarine.getLengthOfShip(); i++)
		{
			if (xCord == (Submarine.getLocationX() - 65) + i)
			{
				if (yCord == (Submarine.getLocationY() - 1))
				{
					Submarine.increaseDamageTaken();
					if (Submarine.getDamageTaken() == Submarine.getLengthOfShip())
					{
						Submarine.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}
	horz = Destroyer.getHorzOrVert();
	temp = Destroyer.getLocationX();
	boatX = temp - 65;
	boatY = Destroyer.getLocationY() - 1;
	if (horz == 'V')
	{
		for (int i = 0; i < Destroyer.getLengthOfShip(); i++)
		{
			if (yCord == (Destroyer.getLocationY() - 1) + i)
			{
				if (xCord == Destroyer.getLocationX())
				{
					Destroyer.increaseDamageTaken();
					if (Destroyer.getDamageTaken() == Destroyer.getLengthOfShip())
					{
						Destroyer.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}//end of if vertical
	else
	{
		for (int i = 0; i < Destroyer.getLengthOfShip(); i++)
		{
			if (xCord == (Destroyer.getLocationX() - 65) + i)
			{
				if (yCord == (Destroyer.getLocationY() - 1))
				{
					Destroyer.increaseDamageTaken();
					if (Destroyer.getDamageTaken() == Destroyer.getLengthOfShip())
					{
						Destroyer.setSunk(true);
						return true;
					}
					return true;
				}
			}
		}
	}
}

void User::showGrid()
{
	playerGrid.printGrid();
}

bool User::updateGrid(int xCord, int yCord)
{
	int hit = getGridPosition(xCord, yCord); //this returns the value that's inside the grid
	if (hit == '0') //if a boat was not hit
	{
		playerGrid.setGrid(xCord, yCord, '.');
		return 0;
	}
	if (hit == '1') //if a boat was hit
	{
		//in here I have to set that boat's sink status to true
		//or I could return a number to send it to another function to do this for me
		playerGrid.setGrid(xCord, yCord, 'x');
		return 1;
	}
	if (hit == 'x' || hit == '.') //this means that this spot has already been hit
		cout << "Whoops I hit a spot that I previously hit, gonna re-roll on that one..I DIDN'T MEAN TO I SWEAR\n";
		return 2;
}

int User::getGridPosition(int xCord, int yCord)
{
	return playerGrid.getGridPosition(xCord, yCord);
}

bool User::isGameOver()
{
	if (playerGrid.isGameOver() == true)
		return true;
	else
		return false;
}

void User::createCordShips()
{
	//use exception handling if the file isn't there
	string line, line2, nameOfShip, cord, temp;
	char xCordTemp, HoriOrVertTemp,letterOfName;
	int yCordTemp, yCordTemp2, random;
	cout << "I will read the .csv file you've prodivded me for your coordinates\n";
	ifstream playerFile;
	playerFile.open("ship_placement.csv");
	try
	{
		if (playerFile.is_open())
		{
			//line 1 of the file should be skipped, always.
			//This is assuming that line 1 will always have no meaning, I should double check this
			getline(playerFile, line);
			while (!playerFile.eof())
			{
				//the logic under this should be setting the watervehicles private variables.
				getline(playerFile, line);
				stringstream lineRead(line);
				//this is reading the name of the boat
				getline(lineRead, line2, ',');
				nameOfShip = line2;
				//Here I will convert the name to be capital first lower and lowercase for the rest Ex: Carrier
				nameOfShip[0] = toupper(nameOfShip[0]);
				for (int i = 1; i < nameOfShip.length(); i++)
				{
					nameOfShip[i] = tolower(nameOfShip[i]);
				}
				//this is reading the full cord of the boat
				getline(lineRead, line2, ',');
				cord = line2;
				xCordTemp = cord[0];
				xCordTemp = toupper(xCordTemp);
				yCordTemp = cord[1] - 48;	//seems like converting the number from string to int, '1' starts at 49?
											//so i took away 48 and it works with all numbers converted
				yCordTemp2 = cord[2] - 48; // if nothing exists, it will be equal to -48 but if something does, we +10
				if (yCordTemp2 >= 0)
				{
					yCordTemp += 9 + yCordTemp2; //this only works at getting the number up to 19 coorectly, does the job.. :(
				}
				if (xCordTemp < 65 || xCordTemp > 74)
				{
					cout << nameOfShip << " X coordinates are invalid!\n"
						"Generating new ones...\n";
					xCordTemp = (rand() % 9 + 65);
				}
				if (yCordTemp < 1 || yCordTemp > 10)
				{
					cout << nameOfShip << " X coordinates are invalid!\n"
						"Generating new ones...\n";
					yCordTemp = (rand() % 10 + 1);
				}

				//this is reading the direction of the boat
				getline(lineRead, line2, ',');
				temp = line2;
				HoriOrVertTemp = temp[0];
				HoriOrVertTemp = toupper(HoriOrVertTemp);
				if (HoriOrVertTemp != 'H' && HoriOrVertTemp != 'V') //72 is 'H' 86 is 'V' using 'H' wasn't working
				{
					cout << HoriOrVertTemp << " is not a valid input for Vertical or Horizontal!\n"
						"Generating a new one...\n";
					random = rand() % 1;
					if (random == 0)
					{
						HoriOrVertTemp = 'H';
					}
					if (random == 1)
					{
						HoriOrVertTemp = 'V';
					}
				}

				//At this point, I should have checked if what I read are valid, and now I would want to
				//initialize the boat.

				//Now I will check if an item with this name exists. To do this I will need to be inside of grid to
				//use the .getName function that is inside of WaterVehicle.

				playerGrid.initializeShip(nameOfShip, xCordTemp, yCordTemp, HoriOrVertTemp);
				//This will loop and now everything for the player should be set

			}
		}
		else
		{
			throw line;
		}
	}
	catch (string e)
	{
		cout << "There was an error opening the file!\n";
		cout << "I'll initalize all your ships randomly!\n";
	}

	catch (...)
	{
		cout << "There was an error opening the file!\n";
		cout << "I'll initalize all your ships randomly!\n";
	}
	
	
	playerFile.close();
}

/*bool Player::isReady()
{
	//This function will be used for both players to check if the game is ready to start by looking at the ready variable
	//This means that I need to pass the player's grid to check the variable
	//I might want to make this a virtual function
	return false;
}
*/
void User::isReady(User player1)
{
	//currently redefinning since I'm not comfortable with virtual yet.
	playerGrid.getReadyStatus();
	cout << "If some coordinates do not match what you typed," 
		<< "it is because they were invalid and I changed them to be valid :)\n";
	cout << "Player 1 is ready to play the game! Here is your grid:\n";
	playerGrid.printGrid();
	playerGrid.printBoats();
}

int User::createTorpX()
{
	//maybe set it to a bool and if it returns true it's a hit?
	char temp;
	int xCord;
	bool loop = false;
	while (loop == false)
	{
		cout << "Please input the X-coordinate of the torpedo you want to send!(A-J)\nOr 'Q' to quit!\n";
		cin >> temp;
		temp = toupper(temp);
		xCord = temp - 65; //cord is stored as char and converted into an int for the grid
		if (xCord >= 0 && xCord <= 9)
			loop = true;
		else if (xCord == 16) //81 - 65
			loop = true;
		else
			cout << "Wrong input for X-coordinates, try again\n";
	}
	return xCord;
}

int User::createTorpY()
{
	char temp;
	int yCord;
	bool loop = false;
	while (loop == false)
	{
		cout << "Please input the Y-coordinate of the torpedo you want to send!(1-10)\n";
		cin >> yCord;
		yCord = (yCord - 1);
		if (yCord >= 0 && yCord <= 9)
			loop = true;
		else
			cout << "Wrong input for Y-coordinates, try again\n";
		cin.clear();
		cin.ignore(5, '\n');
	}
	return yCord;
}

void User::setSinkStatus(int xCord, int yCord)
{
	playerGrid.isHit(xCord, yCord);
}

void Bot::showGrid()
{
	char x = 'A';
	int y = 1;
	cout << "  ";
	for (int i = 0; i < 10; i++)
	{
		cout << "|" << x++;
	}
	cout << "|\n";

	for (int i = 0; i < 9; i++)
	{
		cout << y++ << " |";
		for (int j = 0; j < 10; j++)
		{
			cout << botGrid[j][i] << " ";
		}
		cout << endl;
	}
	for (int i = 9; i < 10; i++)
	{
		cout << y++ << "|";
		for (int j = 0; j < 10; j++)
		{
			cout << botGrid[j][i] << " ";
		}
		cout << endl;
	}
}

void Bot::showGridCheat()
{
	playerGrid.printGrid();
}

bool Bot::updateGrid(int xCord, int yCord)
{
	int hit = getGridPosition(xCord, yCord);
	if (hit == '0') //if a boat was not hit
	{
		botGrid[xCord][yCord] = '.';
		return 0;	//i understand that I am returning a 0 when it's a bool. pretty sure 0 is false
	}
	if (hit == '1') //if a boat was hit
	{
		//in here I have to set that boat's sink status to true
		//or I could return a number to send it to another function to do this for me
		botGrid[xCord][yCord] = 'x';
		return 1;
	}
}

int Bot::getGridPosition(int xCord, int yCord)
{
	return playerGrid.getGridPosition(xCord,yCord);
}

bool Bot::isGameOver()
{
	if (playerGrid.isGameOver() == true)
		return true;
	else
		return false;
}

void Bot::createCordShips()
{
	//I will need nameOfShip, xCordTemp, yCordTemp, HoriOrVertTemp to pass into the initialization function
	//Turns out I can just use the getReadyStatus function and skip all of this...is that bad? ha, idk but it's nice.
	string nameOfShip[5] = { "Carrier""BattleShip""Cruiser""Submarine""Destroyer"};
	char xCordTemp, HoriOrVertTemp;
	int yCordTemp;

}

void Bot::isReady(Bot player2)
{
	playerGrid.getReadyStatus();
	cout << "\nOkay I'm ready!\n";
}

int Bot::createTorpX()
{
	int xCord = rand() % 10;
	return xCord;
}

int Bot::createTorpY()
{
	int yCord = rand() % 10;
	return yCord;
}

void Bot::setSinkStatus(int xCord, int yCord)
{
	//In here I need to retrieve the coordinates of each boats and see which boat my coordinates belong to
	//once the boat is found, set the sink status to true;
	playerGrid.isHit(xCord, yCord);
}

Game::Game()
{
	;
}

void Game::playGame()
{
	string temp;
	char tempChar;
	int xCord, yCord;

	player1.createCordShips();	//this function has now read all the ships and coordinates and will store the valid answers
	sleep_for(seconds(1));	//Reason for these is because I feel like everything pops up too quick

	player1.isReady(player1);	//At this point, the ships of the user may not be correctly finished. We need to check if everything is valid
	sleep_for(seconds(1));
	cout << "\nI will now be creating my boats! Bare with me as I might make mistakes here and there\nchoosing my coordinates "
		<< "since my creator didn't give me any intelligence :)\n\n";
	sleep_for(seconds(1));

	player2.isReady(player2);	//this function creates all the coordinates for the ship randomly
	sleep_for(seconds(1));
//since I used the isReady function, I know that player2 is ready for sure, now the real game begins!

	cout << "BOTH PLAYERS ARE READY! FIGHT TO THE DEATH(unless you quit)\nMAY THE BEST GUESSER WIN!\n";
//Now from here all the way down will be the core of the game which will be ran in a while loop until the game is over
	bool gameOver = false;
	bool check, hit;
	
	while (gameOver == false)
	{
		cout << "####	Your turn player!	####\n";
		cout << "	ENEMY'S GRID:	\n";
//		player2.showGridCheat();	//DO NOT uncomment this unless you want to cheat in battlship like me :).
		player2.showGrid(); //Showing grid filled with 0's or updated from previous round
		cout << "	YOUR GRID:	\n";
		player1.showGrid();	//Showing player's grid with the boats. Will be updated as the game goes on
		xCord = player1.createTorpX();	//Asking user for his X torpedo shot
		if (xCord == 16)	//if the user decided to quit
		{
			gameOver = true;
			cout << "\n\n\n\n\n####	GAME OVER!	####\n\n\n\n\n";
			exit(0);
		}
		cin.clear();
		cin.ignore(5, '\n');	//I need this here because if the user puts a1 into the x-coordinates
		//it will carry the number into the y-coordinate. THIS IS GREAT, except that this bug only works when people
		//put in valid numbers. Put a11 and then things just...dont go right. So sadly I had to fix the bug :(

		yCord = player1.createTorpY();	//asking user for his Y torpedo shot
		hit = player2.updateGrid(xCord, yCord);	//Update the bot grid and determine whether something was hit
		if (hit == 1)
		{
			cout << "@@	A boat was hit!	@@\n";
			player2.setSinkStatus(xCord, yCord);	//In here is a messy alrgorithm to determine which boat was hit
			//IMPORTANT I don't specify what boat it is(I could) because it would give an unfair advantage to the user
			//knowing the size of the boat by the name
		}
		check = player2.isGameOver();	//checking if the game is over
		if (check == true)
		{
			gameOver = true;
			cout << "	ENEMY'S FINAL GRID:	\n";
			player2.showGrid();	//I decided to show the final grids before ending the game because having it end right
			//after typing in the last hit felt a bit weird since you wouldn't see the updated grid.
			cout << "	PLAYER FINAL GRID:	\n";
			player1.showGrid();
			cout << "\n\n\n\n\n##	GAME OVER! USER WINS!	##\n\n\n\n\n";
			exit(0);
		}
		//####	END OF TURN FOR PLAYER 1	####

		cout << "####	IT'S THE BOT'S TURN, HIDE YO BOATS!	####\n";
		//Loop of creating unique coordinates starts here
		bool botLoop = true;
		while (botLoop == true)
		{
			//Now this is not logical in my numbers but:
			//0) = boat not hit, end loop
			//1) = boat hit, end loop
			//2) = hit a cell that has already been hit, continue loop
			xCord = player2.createTorpX();
			yCord = player2.createTorpY();
			hit = player1.updateGrid(xCord, yCord);
			if (hit == 0)
			{
				botLoop = false;
			}
			if (hit == 1)
			{
				cout << "@@	Your boat was hit!	@@\n";
				player1.setSinkStatus(xCord, yCord);
				botLoop = false;
			}
			if (hit == 2)
			{
				botLoop = true;
			}
		}
		check = player1.isGameOver();	//checking if the game is over
		if (check == true)
		{
			gameOver = true;
			cout << "	ENEMY'S FINAL GRID:	\n";
			player2.showGrid();
			cout << "	PLAYER FINAL GRID:	\n";
			player1.showGrid();
			cout << "\n\n\n\n\n##	GAME OVER! BOT WINS!	##\n\n\n\n\n";
			exit(0);
		}
	}
}
