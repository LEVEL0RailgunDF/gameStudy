#include "Parent.h"
#include "Sequence/Title.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Game/Game_Parent.h"

namespace Sequence {

	Parent::Parent() :
		mTitle(0),
		mStageSelect(0),
		mGame(0),
		mNext(SEQ_NONE),
		mStageID(0)
	{
		mTitle = new Title();
	}

	Parent::~Parent()
	{
		SAFE_DELETE(mTitle);
		SAFE_DELETE(mStageSelect);
		SAFE_DELETE(mGame);
	}


	void Parent::update() {
		cout << endl;
		if (mTitle) {
			mTitle->update(this);
		}
		else if (mStageSelect) {
			mStageSelect->update(this);
		}
		else if (mGame) {
			mGame->update(this);
		}
		//else {
		//	HALT("bakana!"); //不可能的
		//}

		
		if (mNext == SEQ_STAGE_SELECT) {
			mStageSelect = new StageSelect();
			SAFE_DELETE(mTitle);
			SAFE_DELETE(mGame);
		}
		else if (mNext == SEQ_TITLE) {
			mTitle = new Title();
			SAFE_DELETE(mStageSelect);
			SAFE_DELETE(mGame);
		}
		else if (mNext == SEQ_GAME) {
			mGame = new Game::Game_Parent(mStageID);
			SAFE_DELETE(mStageSelect);
			SAFE_DELETE(mTitle);
		}

		mNext = SEQ_NONE;

	}

	void Parent::moveTo(SeqID next) {
		mNext = next;
	}

	void Parent::setStageID(int stageID)
	{
		mStageID = stageID;
	}
}