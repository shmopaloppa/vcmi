#pragma once
#include "fl/Headers.h"
#include "Goals.h"

/*
 * Fuzzy.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
*/

class VCAI;
class CArmedInstance;
class CBank;

class engineBase
{
public:
	fl::Engine engine;
	fl::RuleBlock rules;

	engineBase();
	void configure();
	void addRule(const std::string &txt);
};

class FuzzyHelper
{
	friend class VCAI;

	class TacticalAdvantage : public engineBase
	{
	public:
		fl::InputVariable * ourWalkers, * ourShooters, * ourFlyers, * enemyWalkers, * enemyShooters, * enemyFlyers;
		fl::InputVariable * ourSpeed, * enemySpeed;
		fl::InputVariable * bankPresent;
		fl::InputVariable * castleWalls;
		fl::OutputVariable * threat;
		~TacticalAdvantage();
	} ta;

	class EvalVisitTile : public engineBase
	{
	public:
		fl::InputVariable * strengthRatio;
		fl::InputVariable * heroStrength;
		fl::InputVariable * turnDistance;
		fl::InputVariable * missionImportance;
		fl::OutputVariable * value;
		fl::RuleBlock rules;
		~EvalVisitTile();
	} vt;

public:
	enum RuleBlocks {BANK_DANGER, TACTICAL_ADVANTAGE, VISIT_TILE};
	//blocks should be initialized in this order, which may be confusing :/

	FuzzyHelper();
	void initTacticalAdvantage();
	void initVisitTile();

	float evaluate (Goals::Explore & g);
	float evaluate (Goals::RecruitHero & g);
	float evaluate (Goals::VisitTile & g);
	float evaluate (Goals::VisitHero & g);
	float evaluate (Goals::BuildThis & g);
	float evaluate (Goals::DigAtTile & g);
	float evaluate (Goals::CollectRes & g);
	float evaluate (Goals::Build & g);
	float evaluate (Goals::GatherArmy & g);
	float evaluate (Goals::ClearWayTo & g);
	float evaluate (Goals::Invalid & g);
	float evaluate (Goals::AbstractGoal & g);
	void setPriority (Goals::TSubgoal & g);

	ui64 estimateBankDanger (const CBank * bank);
	float getTacticalAdvantage (const CArmedInstance *we, const CArmedInstance *enemy); //returns factor how many times enemy is stronger than us

	Goals::TSubgoal chooseSolution (Goals::TGoalVec vec);
	//shared_ptr<AbstractGoal> chooseSolution (std::vector<shared_ptr<AbstractGoal>> & vec);
};
