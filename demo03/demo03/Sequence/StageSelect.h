#pragma once

class Image;

namespace Sequence {
	class Parent;

	class StageSelect
	{
	public:
		StageSelect();
		~StageSelect();
		void update(Parent*);
	private:
		Image* mImage; //
	};

}

