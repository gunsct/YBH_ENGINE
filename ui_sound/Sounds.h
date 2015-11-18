#include "../resource.h"
#include <irrKlang.h>//sound
#include <conio.h>
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

class Sound{
	private:
		ISoundEngine* engine;// start the sound engine with default parameters

	public:
		Sound();
		~Sound();

		void set_sound();
		void backgroud(float _vol);
		void effect(enum soundtype _type, float _vol);//효과음으로 쓸려고 만듬
};