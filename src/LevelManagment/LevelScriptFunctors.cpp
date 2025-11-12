#include "LevelManagment/LevelScriptFunctors.h"
#include <cctype>
#include <iterator>
#include <ranges>
#include <sstream>
#include <unordered_set>
#include "LevelManagment/LevelScripter.h"
#include "Managers/LevelLogicManager.h"
#include "UI/UIManager.h"
#include "Config/ZombieData.h"

void handle_stream_error(const std::string& cmd)
{
	throw std::runtime_error("Invalid arguments for command: " + cmd);
}

int parseRow(const std::string& row, int maxRows)
{
	if (row == "random") return -1;
	bool numeric = !row.empty() && std::ranges::all_of(row, [](unsigned char c) { return std::isdigit(c); });
	if (numeric)
	{
		int idx = std::stoi(row);
		if (0 <= idx && idx < maxRows)
		{
			return idx;
		}
	}
	return -1;
}

std::string validateZombieType(const std::string& type)
{
	static const std::unordered_set<std::string> valid =
	{
		ZombieID::regularZombie,ZombieID::bucketheadZombie,
		ZombieID::coneheadZombie,ZombieID::flagZombie,
		ZombieID::zomboni,ZombieID::peashooterZombie,
		ZombieID::gatlingPeaZombie
	};
	return valid.contains(type) ? type : ZombieID::regularZombie;
}

void WaitCmd::operator()(float& tl, std::istream& is) const
{
	float s;
	if (!(is >> s))
	{
		handle_stream_error("WAIT");
	}
	tl += s;
}

void ConfigCmd::operator()(float tl, std::istream& is) const
{
	std::string k, v;
	if (!(is >> k >> v))
	{
		handle_stream_error("CONFIG");
	}
	push({ tl, [=] { logic.configure(k, v); } });
}

void SpawnCmd::operator()(float tl, std::istream& is) const
{
	std::string typeStr, rowStr;
	if (!(is >> typeStr >> rowStr))
	{
		handle_stream_error("SPAWN");
	}
	++(*zombieTotal);

	std::string type = validateZombieType(typeStr);

	push({ tl, [=]
		{
		int lane = parseRow(rowStr, laneCnt());
		if (lane == -1)
		{
			lane = (rng)() % laneCnt();
		}
		logic.spawnZombie(type, std::to_string(lane));
	} });
}

void SpawnGroupCmd::operator()(float& tl, std::istream& is) const
{
	std::string rowStr; int cnt; float inter;
	if (!(is >> rowStr >> cnt >> inter))
	{
		handle_stream_error("SPAWN_GROUP");
	}

	std::string line; std::getline(is, line);
	std::istringstream ls(line);
	std::vector<std::string> raw{ std::istream_iterator<std::string>(ls), {} };
	if (raw.empty())
	{
		handle_stream_error("SPAWN_GROUP (empty list)");
	}

	std::vector<std::string> types; types.reserve(raw.size());
	for (auto&& id : raw) types.push_back(validateZombieType(id));

	(*zombieTotal) += cnt;

	push({ tl, [=] {
		std::uniform_int_distribution<std::size_t> pick(0, types.size() - 1);
		for (int i = 0; i < cnt; ++i)
		{
			float tFire = elapsed() + i * inter;
			std::string ty = types[pick(rng)];
			push({ tFire, [=] {
				int lane = parseRow(rowStr, laneCnt());
				if (lane == -1)
				{
					lane = std::uniform_int_distribution<int>(0, laneCnt() - 1)(rng);
				}
				logic.spawnZombie(ty, std::to_string(lane));
			}});
		}
	} });

	if (cnt > 1)
	{
		tl += (cnt - 1) * inter;
	}
}

void AnnounceCmd::operator()(float tl, std::istream& is) const
{
	std::string msg;
	if (!std::getline(is >> std::ws, msg))
	{
		handle_stream_error("ANNOUNCE");
	}
	push({ tl, [=] { ui.showAnnouncement(msg); } });
}

void FlagCmd::operator()(float tl, std::istream&) const
{
	flags.emplace_back(tl);
}