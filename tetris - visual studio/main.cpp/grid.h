#pragma once
#include <vector>
#include <raylib.h>
#include <xkeycheck.h>

class Grid
{
public:
	Grid();
	void Initialize();
	void Print();
	void Draw();
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);
	bool IsCellPortal(int row, int column);
	int grid[20][10];
	int ClearFullRows();
	void ShrinkingRows();
private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int ShrinkingRate;
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;
};
