#pragma once
#include "header.h"
#include "SDL_mixer.h"

#define PATH_LEN 1024
#define BGM_FADE_DURATION 800
#define AUDIO_BGM_SIZE (1<<4)
#define AUDIO_SOUND_SIZE (1<<8)
using namespace std;

class Audio
{
public: 
	static int randint(int l, int r) { return rand() % (r - l + 1) + l; }

	static void playBgm(int);
	//void playAudio(int);
	static void randomBgm();
	static void stopBgm();
	void pauseSound();
	void resumeSound();

private:
	static const int bgmNums = 4;
	const char* bgmsPath1 = "resources/main_title.ogg";
	const char* bgmsPath2 = "resources/bg1.ogg";
	const char* bgmsPath3 = "resources/bg2.ogg";
	const char* bgmsPath4 = "resources/bg3.ogg";


	const char soundsPath[PATH_LEN] = "res/audio/sounds";
	const char soundsPathPrefix[PATH_LEN] = "res/audio/";
};

