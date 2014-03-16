#include "Button.h"
#include "Helper.h"
#include <vector>

class Menu{
	public:
		std::vector<Button*> buttons;
		unsigned int backgroundTexID;

		Menu();

		Menu(const char* filename);

		Menu(unsigned int backgroundID);

		void addButton(Button* button);
	

};