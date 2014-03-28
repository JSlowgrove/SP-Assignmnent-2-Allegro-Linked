#include "fileLoader.h"
#include <allegro.h>
#include <string>
#include <vector>

FileLoader::FileLoader()
{	
}

void loadFile(std::string fileName)
{
}

void FileLoader::setArrays()
{
	girderPosition.resize(numberOfGirders);
	originalPusherPosition.resize(numberOfPushers);
	holePosition.resize(numberOfBombs);
	holePosition[0].x = 32;
	holePosition[0].y = 64;
	holePosition[1].x = 320;
	holePosition[1].y = 320;
	originalPusherPosition[0].x = 32;
	originalPusherPosition[0].y = 96;
	int a = 0;
	for (int i = 0;i < 20; i++)
	{
		girderPosition[i].x = (a*32);
		girderPosition[i].y = 0;
		a++;
	}
	a = 0;
	for (int i = 20;i < 40; i++)
	{
		girderPosition[i].x = (a*32);
		girderPosition[i].y = 448;
		a++;
	}
	a = 1;
	for (int i = 40; i < 53; i++)
	{
		girderPosition[i].x = 0;
		girderPosition[i].y = (a*32);
		a++;
	}
	a = 1;
	for (int i = 53;i < 66; i++)
	{
		girderPosition[i].x = 608;
		girderPosition[i].y = (a*32);
		a++;
	}
}

void FileLoader::setNumbers()
{
	numberOfBombs = 2;
	numberOfGirders = 66;
	pusherRange = 6;
	numberOfPushers = 1;
}

int FileLoader::getBombs()
{
	return numberOfBombs;
}

int FileLoader::getGirders()
{
	return numberOfGirders;
}

int FileLoader::getPusherRange()
{
	return pusherRange;
}

int FileLoader::getPushers()
{
	return numberOfPushers;
}

int FileLoader::getHolePositionX(int i)
{
	return holePosition[i].x;
}

int FileLoader::getGirderPositionX(int i)
{
	return girderPosition[i].x;
}

int FileLoader::getPusherPositionX(int i)
{
	return originalPusherPosition[i].x;
}

int FileLoader::getHolePositionY(int i)
{
	return holePosition[i].y;
}

int FileLoader::getGirderPositionY(int i)
{
	return girderPosition[i].y;
}

int FileLoader::getPusherPositionY(int i)
{
	return originalPusherPosition[i].y;
}