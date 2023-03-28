#pragma once
#include "GameLib/Framework.h"

namespace Sequence {

	class Title;
	class StageSelect;
	namespace Game {
		class Game_Parent;
	}

	class Parent
	{
	public:
		enum SeqID {
			SEQ_STAGE_SELECT,
			SEQ_TITLE,
			SEQ_GAME,

			SEQ_NONE,
		};
		
		
		Parent();
		~Parent();

		void update();

		void moveTo(SeqID next);
		void setStageID(int stageID);

	private:
		Title* mTitle;
		StageSelect* mStageSelect;
		Game::Game_Parent* mGame;

		int mStageID;
		SeqID mNext;


	private:

	};



};


