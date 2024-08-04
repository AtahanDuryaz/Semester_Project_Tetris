#include "grid.h"
#include <iostream>
#include <vector>
#include "colors.h"
#include "game.h"
using namespace std;

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialize();
	colors = GetCellColors();
	ShrinkingRate = 2;

}

void Grid::Initialize()
{
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			grid[row][column] = 0;
		}
	}

}

void Grid::Print()
{
	for (int row = 0; row < numRows; row++) {
		for (int columns = 0; columns < numCols; columns++) {
			cout << grid[row][columns] << " ";
		}
		cout << endl;
	}
}

void Grid::Draw()
{
	//if (score%1000==0 && Flag) {
		//numRows-=2;
		// Flag = false;

	//}
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			int cellValue = grid[row][column];
			DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
		}

	}
	DrawRectangle(9 * cellSize + 11, 7 * cellSize + 11, cellSize - 1, cellSize - 1, colors[8]);
	DrawRectangle(8 * cellSize + 11, 7 * cellSize + 11, cellSize - 1, cellSize - 1, colors[8]);

}

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numCols)
	{
		return false;
	}
	return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}
	return false;
}

bool Grid::IsCellPortal(int row, int column)
{
	if ((row == 7 && column == 8) || (row == 7 && column == 9))
	{
		return true;
	}
	return false;
}

int Grid::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

void Grid::ShrinkingRows()
{
	numRows -= 2;
}

bool Grid::IsRowFull(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		if (grid[row][column] == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::ClearRow(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row][column] = 0;
	}
}

void Grid::MoveRowDown(int row, int numRows)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}







