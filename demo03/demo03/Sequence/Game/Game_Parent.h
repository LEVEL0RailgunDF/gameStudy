#pragma once
#include "GameLib/Framework.h"
#include <iostream>
#include <fstream>
using namespace std;


namespace Sequence {
	class Parent;

	namespace Game {

		class Clear;
		class Loading;
		class Menu;
		class Play;
	

		class Game_Parent
		{
		public:
			enum SeqID {
				SEQ_TITLE,
				SEQ_LOAD,
				SEQ_CLEAR,
				SEQ_GAME,
				SEQ_MENU,

				SEQ_NONE,
			};

			Game_Parent(int mStageID);
			~Game_Parent();

			void update(Parent* parent);

			void moveTo(SeqID seqID);
			void setStageID(int stageID);

		private:

			Clear* mClear;
			Loading *mLoading;
			Play *mPlay;


			int mStageID;
			SeqID mNext;


		private:

		};
	}
};


