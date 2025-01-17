#pragma once
#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class FileLoader
{
private:
	struct position //a structure for coordinates of an entity
	{
		int x;
		int y;
	};
	int numberOfBombs;
	int numberOfGirders;
	int pusherRange;
	int numberOfPushers;
	int numberOfLevels;
	position playerXY;
	std::vector<position> holePosition;
	std::vector<position> girderPosition;
	std::vector<int> firstPusherPosition;
	std::vector<position> pusherPosition;
	std::vector<position> bombPosition;
public:
	FileLoader();
	~FileLoader();
	void loadFile(std::string,int);
	int getNumberOfLevels(std::string);
	int getBombs();
	int getGirders();
	int getPusherRange();
	int getPushers();
	int getPlayerX();
	int getPlayerY();
	int getHolePositionX(int);
	int getHolePositionY(int);
	int getGirderPositionX(int);
	int getGirderPositionY(int);
	int getPusherPositionX(int);
	int getPusherPositionY(int);
	int getBombPositionX(int);
	int getBombPositionY(int);
	int getFirstPusherPositionX(int);
	void setPlayerX(int);
	void setPlayerY(int);
	void setBombPositionX(int, int);
	void setBombPositionY(int, int);
	void setPusherPositionX(int, int);
};

#endif