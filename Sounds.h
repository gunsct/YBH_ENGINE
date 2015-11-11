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
};