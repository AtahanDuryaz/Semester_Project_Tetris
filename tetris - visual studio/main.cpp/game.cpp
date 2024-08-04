#include "game.h"
#include <iostream>
#include <random>

using namespace std;
Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	if (blockHoldedVal && IsKeyPressed(KEY_E))
	{
		nextBlock = holdedBlock;
	}
	else
	{
		nextBlock = GetRandomBlock();
	}
	holdedBlock;
	NullBlock;
	tempBlock;
	gameOver = false;
	score = 0;
	HoldLimit = 2;
	shrinkingScore = 2000;
	InitAudioDevice();
	music = LoadMusicStream("Sound/tetris.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Sound/Sounds_rotate.mp3");
	clearSound = LoadSound("Sound/Sounds_clear.mp3");
}
Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}
Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock() };
}
void Game::Draw()
{

	grid.Draw();

	currentBlock.Draw(11, 11);
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(315, 260);
		break;
	case 4:
		nextBlock.Draw(315, 230);
		break;
	default:
		nextBlock.Draw(330, 220);
		break;
	}
	switch (holdedBlock.id)
	{
	case 3:
		holdedBlock.Draw(315, 360);
		break;
	case 4:
		holdedBlock.Draw(315, 360);
		break;

	default:
		holdedBlock.Draw(315, 370);
		break;
	}

}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();

	}
	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;

	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		UpdateScore(0, 1);
		break;
	case KEY_UP:
		RotateBlock();
		break;
	case KEY_LEFT_SHIFT:
		HoldBlock();
		break;
	case KEY_E:
		UseHoldedBlock();
		break;
	case KEY_SPACE:

		InstantDown(15);
		UpdateScore(0, 100);
		break;
	}
}


void Game::MoveBlockLeft()
{
	if (!gameOver) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, 1);
		}
	}
}
void Game::MoveBlockRight()
{
	if (!gameOver) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, -1);
		}
		else if (Portal())
		{
			InstantDown(10);

		}
	}
}
void Game::CheckScore()
{
	if (score >= shrinkingScore)
	{
		grid.ShrinkingRows();
		shrinkingScore *= 2;
	}
}
void Game::MoveBlockDown()
{
	if (!gameOver) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
		else if (Portal())
		{
			InstantDown(10);

		}


	}
}
void Game::InstantDown(int value) {
	for (int i = 0; i < value; i++) {
		if (!gameOver) {
			currentBlock.Move(1, 0);
			if (IsBlockOutside() || BlockFits() == false)
			{
				currentBlock.Move(-1, 0);
				LockBlock();
				break;
			}
			/*else if (Portal() && (IsBlockOutside() || BlockFits() == false))
			{
				currentBlock.Move(5, 0);
			}
			*/

		}
	}
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

bool Game::Portal()
{


	std::vector<Position> tiles = currentBlock.GetCellPositions();
	std::cout << "new" << std::endl;
	std::cout << tiles[0].row << tiles[0].column << std::endl;
	std::cout << tiles[1].row << tiles[1].column << std::endl;
	std::cout << tiles[2].row << tiles[2].column << std::endl;
	std::cout << tiles[3].row << tiles[3].column << std::endl;
	for (Position item : tiles)
	{


		if (grid.IsCellPortal(item.row, item.column))
		{

			return true;
		}

	}
	return false;
}

void Game::RotateBlock()
{
	if (!gameOver) {
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.UndoRotation();
		}
		else
		{
			PlaySound(rotateSound);
		}
	}
}
void Game::HoldBlock()
{
	if (IsKeyPressed(KEY_LEFT_SHIFT) && blockHoldedVal != true && HoldLimit != 0)
	{

		holdedBlock = currentBlock;
		blockHoldedVal = true;
		currentBlock = nextBlock;
		nextBlock = GetRandomBlock();
		HoldLimit--;



	}
}
void Game::UseHoldedBlock()
{
	if (blockHoldedVal == true)
	{
		currentBlock = holdedBlock;
		holdedBlock = NullBlock;
		blockHoldedVal = false;




	}
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	int rowsCleared;
	rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0)
	{
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
	UpdateScore(rowsCleared, 0);
}
bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row, item.column) == false)
		{
			return  false;
		}
	}
	return true;
}
void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	holdedBlock = {};
	score = 0;
}

void Game::UpdateScore(int LinesCleared, int moveDownPoints)
{
	switch (LinesCleared)
	{
	case 1:
		score += 100;

		break;
	case 2:
		score += 300;

		break;
	case 3:
		score += 500;

		break;
	case 4:
		score += 1000;

		break;

	default:
		break;
	}
	score += moveDownPoints;
	CheckScore();
}


