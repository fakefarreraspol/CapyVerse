#include "App.h"
#include "Audio.h"

#include "Defs.h"
#include "Log.h"
#include "Player.h"
#include "Entity.h"
#include "EntityManager.h"
// NOTE: Recommended using: Additional Include Directories,
// instead of 'hardcoding' library location path in code logic
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL_mixer/libx86/SDL2_mixer.lib")

Audio::Audio(bool startEnabled) : Module(startEnabled)
{
	music = NULL;
	name.Create("audio");
}

// Destructor
Audio::~Audio()
{}

// Called before render is available
bool Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// Load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	// Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}
	volMusic = Mix_VolumeMusic(config.child("music").attribute("value").as_int());
	volFX = Mix_Volume(-1, config.child("fx").attribute("value").as_int());
	return ret;
}

// Called before quitting
bool Audio::CleanUp()
{
	if(!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	ListItem<Mix_Chunk*>* item;
	for(item = fx.start; item != NULL; item = item->next)
		Mix_FreeChunk(item->data);

	fx.Clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

bool Audio::Update(float dt)
{
	bool ret = true;
	Mix_VolumeMusic(volMusic);
	Mix_Volume(-1, volFX);
	return ret;
}

// Play a music file
bool Audio::PlayMusic(const char* path, float fadeInTime, float fadeOutTime)
{
	bool ret = true;

	if(!active)
		return false;

	if(music != NULL)
	{
		if(fadeOutTime > 0.0f)
		{
			Mix_FadeOutMusic(int(fadeOutTime * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fadeInTime > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fadeInTime * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if(!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if(chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.Add(chunk);
		ret = fx.Count();
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if(!active)
		return false;

	if(id > 0 && id <= fx.Count())
	{
		Mix_PlayChannel(-1, fx[id - 1], repeat);
	}

	return ret;
}
bool Audio::ChangeMusic(int Id, float fadeInTime, float fadeOutTime)
{
	// Todo 1 (done): Complete the music switcher (an enumerator on Audio.h is given with all the playlist)
	switch (Id)
	{
	case 0:
	{
		Mix_HaltMusic();
	}break;
	case 1:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/intro.wav", fadeInTime, fadeOutTime);

	}break;
	case 2:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/backgroundForest.ogg", fadeInTime, fadeOutTime);

	}break;
	case 3:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/battleMusic1.ogg", fadeInTime, fadeOutTime);
	}break;
	case 4:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/bossFight1.ogg", fadeInTime, fadeOutTime);
	}break;
	case 5:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/houseMusic.wav", fadeInTime, fadeOutTime);
	}break;
	}
	Mix_ResumeMusic();

	


	
	return true;
}
bool Audio::PlayMusicSpatially(iPoint musicGeneratorPosition)
{
	// Todo 2 (done): Complete the function to be able to play music tracks spatially
	
	int setMusicVolume = MUSIC_VOLUME - (sqrt(pow(app->entMan->entities.At(1)->data->GetPosition().x-musicGeneratorPosition.x, 2) + pow(app->entMan->entities.At(1)->data->GetPosition().y - musicGeneratorPosition.y, 2)) / 6);

	if (setMusicVolume <= 0) setMusicVolume = 0;

	Mix_VolumeMusic(setMusicVolume);

	return true;
}
