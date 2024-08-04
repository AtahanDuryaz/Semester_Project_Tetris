#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include "colors.h"

class Block
{
public:
	Block();
	void Draw(int X, int Y);
	void Move(int rows, int columns);
	std::vector<Position> GetCellPositions();
	int id;
	void Rotate();
	void UndoRotation();
	std::map<int, std::vector<Position>> cells;
	int rowOffset;
	int columnOffset;

private:
	int cellSize;
	int rotationState;
	int rotationCount;
	std::vector<Color> colors;

};

