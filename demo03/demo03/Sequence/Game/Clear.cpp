#include "Clear.h"
#include "Image.h"


namespace Sequence {
	namespace Game {

		Clear::Clear() {
			mImage = new Image("data/imgData/Clear.dds");
		}
		Clear::~Clear() {

		}


		void Clear::update(Game_Parent* game_parent) {

			if (Framework::instance().isKeyTriggered(' ')) {
				game_parent->moveTo(Game_Parent::SEQ_TITLE);
			}
			else {
				mImage->draw();
			}
		}


	}
}