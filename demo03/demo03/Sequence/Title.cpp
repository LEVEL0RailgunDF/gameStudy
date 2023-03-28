#include "Title.h"

#include "Image.h"
#include "Sequence/Parent.h"

Sequence::Title::Title()
{
	mImage = new Image("data/imgData/Title.dds");
}

Sequence::Title::~Title()
{
	SAFE_DELETE(mImage);
}

void Sequence::Title::update(Parent *parent)
{
	if (Framework::instance().isKeyTriggered(' ')) {
		parent->moveTo(Parent::SEQ_STAGE_SELECT);
	}
	else {
		mImage->draw();
	}


}
