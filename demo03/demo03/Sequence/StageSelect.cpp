#include "StageSelect.h"

#include "Image.h"
#include "Sequence/Parent.h"

namespace Sequence {
	Sequence::StageSelect::StageSelect()
	{
		mImage = new Image("data/imgData/StageSelect.dds");
	}

	Sequence::StageSelect::~StageSelect()
	{
	}

	void Sequence::StageSelect::update(Parent *parent)
	{	
		int stage = 0;
		//如果下标移动了，那就麻烦了，所以放0
		char numberChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		for (int i = 0; i < 10; ++i) {
			if (Framework::instance().isKeyTriggered(numberChars[i])) {
				stage = i;
			}
		}
		if (stage != 0) { //到下一个
			parent->setStageID(stage);
			parent->moveTo(Parent::SEQ_GAME);
		}


		mImage->draw();

	}

}
