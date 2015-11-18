#include "Sounds.h"

Sound::Sound()
{

	engine = createIrrKlangDevice();
}

Sound::~Sound()
{
	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().

	engine->drop(); // delete engine
}
void Sound::backgroud(float _vol){
	engine->play2D("..\\resource\\doctorwho.mp3", true);
	engine->setSoundVolume(_vol);
}
void Sound::effect(soundtype _type, float _vol){
	switch (_type){
		case CRASH:
			engine->play2D("..\\resource\\Crash.mp3", false);
			engine->setSoundVolume(_vol);
			break;
		case DEAD:
			engine->play2D("..\\resource\\Death.mp3", false);
			engine->setSoundVolume(_vol);
			break;
		case ALARM:
			engine->play2D("..\\resource\\Alarm.mp3", false);
			engine->setSoundVolume(_vol);
			break;
	}
}
void Sound::set_sound()
{
	//if (!engine)
	//{
	//	printf("Could not startup engine\n");
	//	return 0; // error starting up the engine
	//}

	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.

	// play some sound stream, looped
	

	// In a loop, wait until user presses 'q' to exit or another key to
	// play another sound.
	//do
	//{
	//	// play a single sound
	//	engine->play2D("/resource/bell.wav");
	//} while (getch() != 'q');
}
