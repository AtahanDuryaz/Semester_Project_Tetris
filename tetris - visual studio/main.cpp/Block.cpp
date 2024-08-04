#include "Block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	rotationCount = 0;
	colors = GetCellColors();
	rowOffset = 0;
	columnOffset = 0;

}
void Block::Draw(int X, int Y)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles) {
		DrawRectangle(item.column * cellSize + X, item.row * cellSize + Y, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}
std::vector <Position> Block::GetCellPositions()

{
	std::vector<Position>tiles = cells[rotationState];
	std::vector<Position>movedTiles;
	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

void Block::Rotate()
{
	rotationState++;
	if (rotationState == (int)cells.size())
	{
		rotationState = 0;
	}

}

void Block::UndoRotation()
{
	rotationState--;
	if (rotationState == -1)
	{
		rotationState = cells.size() - 1;
	}
}