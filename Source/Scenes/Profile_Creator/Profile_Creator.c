#include "Profile_Creator.h"


bool once = false;

Music profile_creator_music_start;
Music profile_creator_music_loop;

void profile_creator()
{
	if (once == false) {
		profile_creator_music_start = LoadMusicStream(TextFormat("%s/Game/Background Music/Whoami (Profile Creator and Selector) [Start].ogg",GetResourcePath()));
		profile_creator_music_loop = LoadMusicStream(TextFormat("%s/Game/Background Music/Whoami (Profile Creator and Selector) [Loop].ogg",GetResourcePath()));
		SetMusicVolume(profile_creator_music_start, 1.f);
		SetMusicPitch(profile_creator_music_start, 1.f);
		PlayMusicStream(profile_creator_music_start);
		once = true;
	}

	UpdateMusicStream(profile_creator_music_start);
	DrawRectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, BLACK);
	name_creator();
}
