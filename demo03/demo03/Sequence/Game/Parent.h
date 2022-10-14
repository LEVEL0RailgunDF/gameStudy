#pragma once
namespace Sequence {

	class Title;
	class Game;
	class Stage;


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

		void moveTo(SeqID);
		void setStageID(int stageID);

	private:
		Title* mTitle;
		StageSelect* mStageSelect;
		Game::Paren* mGame;

		int mStageID;
		SeqID mNext;


	private:

	};



};


