#pragma once

class Image;

namespace Sequence {
	class Parent;

	class Title
	{

		public:
			Title();
			~Title();
			void update(Parent*);
		private:
			Image* mImage; //Ö÷Ìâ»­Ãæ

	};

}

