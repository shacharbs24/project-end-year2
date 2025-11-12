#pragma once
#include <istream>
#include <string>
#include <vector>
#include <functional>
#include <random>
#include "LevelManagment/LevelScripter.h"
#include "Board.h"

class LevelScripter;
class LevelLogicManager;
class UIManager;

using PushEventFn = std::function<void(const LevelScripter::Event&)>;
using LaneCountFn = std::function<int()>;
using ElapsedFn = std::function<float()>;
using RngPtr = std::mt19937&;

void handle_stream_error(const std::string& cmd);
int parseRow(const std::string& row, int maxRows = Board::ROWS - 1);
std::string validateZombieType(const std::string& id);

struct WaitCmd
{
	void operator()(float& tl, std::istream& is) const;
};

struct ConfigCmd
{
	PushEventFn push;
	LevelLogicManager& logic;
	void operator()(float tl, std::istream& is) const;
};

struct SpawnCmd
{
	PushEventFn push;
	LevelLogicManager& logic;
	RngPtr rng;
	LaneCountFn laneCnt;
	int* zombieTotal;
	void operator()(float tl, std::istream& is) const;
};

struct SpawnGroupCmd
{
	PushEventFn push;
	LevelLogicManager& logic;
	RngPtr rng;
	LaneCountFn laneCnt;
	ElapsedFn elapsed;
	int* zombieTotal;
	void operator()(float& tl, std::istream& is) const;
};

struct AnnounceCmd
{
	PushEventFn push;
	UIManager& ui;
	void operator()(float tl, std::istream& is) const;
};

struct FlagCmd
{
	std::vector<float>& flags;
	void operator()(float tl, std::istream& is) const;
};
