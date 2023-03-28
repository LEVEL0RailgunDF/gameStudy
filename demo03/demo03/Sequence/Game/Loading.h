#pragma once
#include "Game_Parent.h"

class Image;

namespace Sequence {
	namespace Game {
		

		class Loading
		{

		public:

		private:
			int loadingTimes=0;
			Image *mImage;
		public:
			Loading();
			~Loading();


			void update(Game_Parent* game_parent);

		};

	}
}