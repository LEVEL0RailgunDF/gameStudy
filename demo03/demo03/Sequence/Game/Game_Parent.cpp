#include "Game_Parent.h"
#include "Sequence/Parent.h"
#include "Loading.h"
#include "Play.h"
#include "Clear.h"

using namespace Sequence;


namespace Sequence {
	namespace Game {


		Game_Parent::Game_Parent(int mStageID) :
			mNext(SEQ_LOAD),
			mStageID(mStageID)
		{
			setStageID(mStageID);
		}

		Game_Parent::~Game_Parent()
		{
			SAFE_DELETE(mLoading);
			SAFE_DELETE(mPlay);
		}

		void Game_Parent::update(Parent* parent) {

			if (mLoading) {
				mLoading->update(this);
			}
			else if (mPlay) {
				mPlay->update(this);
			}
			else if (mClear) {
				mClear->update(this);
			}

			if (mNext == SEQ_LOAD) {
				mLoading = new Loading();
				SAFE_DELETE(mPlay);
				SAFE_DELETE(mClear);
			}
			else if (mNext == SEQ_GAME) {
				mPlay = new Play(mStageID);
				SAFE_DELETE(mLoading);
				SAFE_DELETE(mClear);
			}		
			else if (mNext == SEQ_CLEAR) {
				mClear = new Clear();
				SAFE_DELETE(mPlay);
				SAFE_DELETE(mLoading);
			}


			if (mNext == SEQ_TITLE) {
				parent->moveTo(Parent::SEQ_TITLE);
			}
			mNext = SEQ_NONE;
		}

		void Game_Parent::moveTo(SeqID seqID){
			mNext = seqID;
		}
		
		void Game_Parent::setStageID(int stageID){
			mStageID = stageID;
		}

	}
}