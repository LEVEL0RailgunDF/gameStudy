#pragma once
#include "Game_Parent.h"
class Image;

namespace Sequence {
	namespace Game {


		class Clear
		{

		public:

		private:
			Image* mImage;
		public:
			Clear();
			~Clear();


			void update(Game_Parent* game_parent);

		};

	}
}

