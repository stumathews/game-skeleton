// We need to include SDL.h before any other CPPGameLib headers because some of the CPPGameLib headers include SDL.h themselves, 
// and we want to ensure that the correct version of SDL.h is included first.
#include <SDL.h>

// CPPGameLib includes
#include <file/SettingsManager.h>
#include <structure/GameStructure.h>
#include <structure/FixedStepGameLoop.h>
#include <objects/GameWorldData.h>
#include <Logging/ErrorLogManager.h>

#include <iostream>

/*
 * This is a simple game template that demonstrates how to set up a basic game loop using the CPPGameLib framework.
*/

using namespace gamelib;

int main(int, char* [])
{
	// 1. Setup loop control data
	static GameWorldData gameWorldData;
		
	// 2. Initialize the settings manager and read the required game settings
	SettingsManager::Get()->ReadSettingsFile("conf\\settings.xml");

	// 3. Create the underlying game infrastructure with a fixed step game loop, providing update, render, and input handling functions
	GameStructure infrastructure(std::make_shared<FixedStepGameLoop>(16, [](const unsigned long deltaMs)
	{
			// Update game world here...
	}, []()
	{
			// Render game world here...
	}, [](const unsigned long deltaMs)
	{
			// Handle input events here
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				// Handle closed window event
				if (e.type == SDL_QUIT)
				{
					gameWorldData.IsGameDone = true;
					return;
				}

				if (e.key.repeat == 0) // we ignore key repeats
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_q: 
					case SDLK_ESCAPE:
						std::cout << "Quit key pressed" << std::endl;
						gameWorldData.IsGameDone = true;
						break;
					case SDLK_w: case SDLK_UP: case SDLK_s: case SDLK_DOWN:
					case SDLK_a: case SDLK_LEFT: case SDLK_d: case SDLK_RIGHT:
						std::cout << "Movement key pressed" << std::endl;
						break;
					default: 
						break;
					}
				}
			}
	}));

	// 4. Initialize the game infrastructure, providing window dimensions, title, and resource configuration
	infrastructure.Initialize(500, 400, "Skeleton", "conf\\Resources.xml","conf\\");

	// 5. Start game loop - the game loop will run until gameWorldData.IsGameDone is set to true
	infrastructure.DoGameLoop(&gameWorldData);

	// 6. Game loop has exited, clean up and exit
	GameStructure::Unload();

	return 0;
}
