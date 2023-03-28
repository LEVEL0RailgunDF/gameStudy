#pragma once
#include "Game_Parent.h"

class Stage;
namespace Sequence {
	namespace Game {

		class Play
		{

		public:

		private:
			Stage *mStage ;

		public:
			Play(int stageID);
			~Play();


			void update(Game_Parent* game_parent);



		};
	}
}