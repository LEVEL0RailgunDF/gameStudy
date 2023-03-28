#include "Loading.h"
#include "Image.h"


namespace Sequence {
	namespace Game {

		Loading::Loading() {
			mImage = new Image("data/imgData/Loading.dds");
		}
		Loading::~Loading() {

		}


		void Loading::update(Game_Parent* game_parent) {
			loadingTimes += 1;
			if (loadingTimes >= 60) {
				game_parent->moveTo(Game_Parent::SEQ_GAME);
			}
			else {
				mImage->draw();
			}
		}


	}
}