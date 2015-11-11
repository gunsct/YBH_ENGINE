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
	engine->play2D("C:/Users/gunsct/Desktop/project/graphics/YBH_Engine/YBH_Engine/resource/doctorwho.mp3", true);
	engine->setSoundVolume(1.0f);

	// In a loop, wait until user presses 'q' to exit or another key to
	// play another sound.
	//do
	//{
	//	// play a single sound
	//	engine->play2D("/resource/bell.wav");
	//} while (getch() != 'q');
}
