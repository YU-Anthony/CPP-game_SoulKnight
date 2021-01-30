#include "header.h"
#include "SDL_mixer.h"
#include "Audio.h"


//const int bgmNums;
Mix_Music *bgms[AUDIO_BGM_SIZE];
Mix_Chunk *sounds[AUDIO_SOUND_SIZE];

int nowBgmId = -1;



void Audio::playBgm(int id) {

	const char bgmsPath[AUDIO_BGM_SIZE][PATH_LEN] = {
	  "resources/main_title.ogg",
	  "resources/bg1.ogg",
	  "resources/bg2.ogg",
	  "resources/bg3.ogg"
	};

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *sound = Mix_LoadMUS(bgmsPath[id]);

	if (nowBgmId == id) return;
	if (nowBgmId == -1) Mix_PlayMusic(sound, 1);
	else Mix_FadeInMusic(sound, -1, BGM_FADE_DURATION);
	nowBgmId = id;
}
void Audio::stopBgm() {
	/*Mix_FadeOutMusic(BGM_FADE_DURATION);
	nowBgmId = -1;*/
	Mix_CloseAudio();
	Mix_Quit();
}

void Audio::randomBgm() {
	int i = randint(1, bgmNums - 1);
	playBgm(i);
}

//void Audio::playAudio(int id) {
//	if (id >= 0)
//		Mix_PlayChannel(-1, sounds[id], 0);
//}

void Audio::pauseSound() {
	Mix_Pause(-1);
	Mix_PauseMusic();
}
void Audio::resumeSound() {
	Mix_Resume(-1);
	Mix_ResumeMusic();
}