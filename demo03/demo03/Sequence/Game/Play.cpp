#include "Play.h"
#include "File.h"
#include "Stage.h"

namespace Sequence {
	namespace Game {


		Play::Play(int stageID) {
			File stageFile("stage.txt");
			char* stageData = stageFile.data();
			mStage = new Stage(stageData, stageFile.size(), "box.dds");
		}
		Play::~Play() {
			SAFE_DELETE(mStage);
		}


		void Play::update(Game_Parent* game_parent) {
			

			if (mStage->checkClear()) {
				game_parent->moveTo(Game_Parent::SEQ_CLEAR);
				return;
			}

			mStage->update();
			mStage->draw();
		}


	}
}