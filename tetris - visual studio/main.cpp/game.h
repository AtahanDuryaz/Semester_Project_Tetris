#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	Music music;
	std::vector<Block> GetAllBlocks();
	Block GetRandomBlock();
	void Draw();
	void HandleInput();

	bool gameOver;
	bool blockHoldedVal = false;
	int HoldLimit = 6;
	int difficult = 1;
	void MoveBlockDown();

	void InstantDown(int value);

	int score;


private:
	Grid grid;
	void MoveBlockLeft();
	void MoveBlockRight();
	void CheckScore();
	bool IsBlockOutside();
	int shrinkingScore;
	bool Portal();
	void RotateBlock();
	void HoldBlock();
	void UseHoldedBlock();
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int LinesCleared, int moveDownPoints);
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Block holdedBlock;
	Block tempBlock;
	Block NullBlock;
	Sound rotateSound;
	Sound clearSound;



};

