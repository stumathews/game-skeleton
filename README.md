# Game Skeleton

This project demonstrates how to use the CppGameLib library to create a minimalist game environment that runs at 60FPS.
This is a CMake project that will automatically download the CppGameLib library and its dependencies, links and builds the game.

Folder structure:

    main.cpp                      <== Main game
    gamedata/conf/settings.xml    <-- game settings
    gamedata/config/Resources.xml <-- game resources
    vcpkg-configuration.json      <-- package repositories
    vcpkg.json                    <-- required packeges from repositories
    cmakepresets.json             <-- cmake presets
    cmakelists.txt                <-- cmake build configuration 

main.cpp:

```cpp
#include <SDL.h>
#include <file/SettingsManager.h>
#include <structure/GameStructure.h>
#include <structure/FixedStepGameLoop.h>
#include <objects/GameWorldData.h>
#include <Logging/ErrorLogManager.h>

#include <iostream>
using namespace gamelib;

int main(int, char* [])
{
	// 1. Setup loop control data
	static GameWorldData gameWorldData;
		
	// 2. Initialise the settings manager and read the required game settings
	SettingsManager::Get()->ReadSettingsFile("conf\\settings.xml");

	// 3. Create the underlying game infrastructure with a fixed-step game loop running at 60FPS, providing update, render, and input handling functions
	GameStructure infrastructure(std::make_shared<FixedStepGameLoop>(16, [](const unsigned long deltaMs)
	{
			// Update game world here...
	}, []()
	{
			// Render game world here...
	}, [](const unsigned long deltaMs)
	{
			// Handle input events here
        }}));

	infrastructure.Initialize(500, 400, "Skeleton", "conf\\Resources.xml","conf\\");

	infrastructure.DoGameLoop(&gameWorldData);

	GameStructure::Unload();

	return 0;
}

```

Settings.xml
```xml
<!-- Required settings for the game engine -->
<settings>
	<global>
		<setting name="verbose" type="bool">false</setting>
		<setting name="isNetworkGame" type="bool">true</setting>
	</global>

	<gameStructure>
		<setting name="sampleInput" type="bool" description="sampleInput">true</setting>
		<setting name="sampleNetwork" type="bool" description="sampleNetwork">true</setting>
	</gameStructure>

	<eventManager>
		<setting name="logEvents" type="bool">true</setting>
	</eventManager>

	<!-- networking ignored if global.isNetworkGame is false -->
	<networking>
		<setting name="isGameServer" type="bool">false</setting>
		<setting name="gameServerAddress" type="string">192.168.1.171</setting>
		<setting name="gameServerPort" type="string">9090</setting>
		<setting name="maxPlayers" type="int">4</setting>
		<setting name="nickname" type="string">Surface4</setting>	
		<setting name="isTcp" type="bool">false</setting>
		<setting name="useReliableUdp" type="bool">true</setting>
		<setting name="useEncryption" type="bool">true</setting>
		<setting name="encoding" type="int">3</setting><!-- 1=Json, 2=Xml, 3=BitPacked -->
		<setting name="sendClientEventsToServer" type="bool">false</setting>
	</networking>	
</settings>

```

## Build

    cmake --preset=windows
    cmake --build build

## Run

    cd .\build\Debug\
    .\game.exe

