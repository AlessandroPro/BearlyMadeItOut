# 'Bearly' Made It Out!
## Text-Based Adventure Game

There are two projects included in this repo: <br>
A C++ text-based adventure game, and a small C# winform application for visualizing in-game stats recorded while playing the game.

All relevant C++ code for the game is included in BearlyMadeItOut_TextAdventureGame/TextAdventureGame/TextAdventureGame/. <br>
All relevant C# code for the data visualizer is included in GameDataAnalysisTool/GameDataAnalysisTool/.

### Game Overview 
This is a command-line, text-based adventure game (in the style of the classic game, Zork), written in C++ using Visual Studio. You play as a bear trying to escape a zoo, and as the player, you type out various commands to interact with items, guards, animals, and traverse various locations. See the game's map at the end of this README.

The data for this game is not hard-coded; it is loaded from a JSON file containing all of the locations, connections, items, dialogue, descriptions, etc. This JSON file is exported from an external data editor tool that I wrote, designed specifically for writing all of the information for this game.
That project can be viewed here: <br>
https://github.com/AlessandroPro/TextAdventureGameDataEditor.git

You can save or load your game at any point during a playthrough, or even start a new game. <br>
Game save data is stored in a JSON file.

Sample screenshot of the game:
![Screenshot1](https://user-images.githubusercontent.com/15040875/72189952-3bedb300-33cc-11ea-88a3-cbf404371805.PNG)


### Gameplay
You’re a bear trying to escape the Turonno Zoo.
As a bear sneaking around a zoo at night, you traverse different animal enclosures and the pathways between them. You start off in the bear enclosure and then go off to search for 5 pieces of clothing to create a disguise.
Once all items are found, go back to the bear enclosure, type ‘GO TO SLEEP’. The bear will go to sleep, wake up in the morning, put on all of the clothes, and walk out of the zoo unnoticed. You win!
You can search, attack, travel (north south, east, west), pickup and drop items. If there is a guard in your location, they will tranquilize you if you perform any actions before attacking them. This is like “dying’ in the game, and you respawn back in your enclosure but your items are dropped. Once a guard is attacked, they go unconscious, and must be hidden. If you don’t hide the body, the next time you visit the location, you’ll get tranquilized by other guards who found the body.

![DressedBear](https://user-images.githubusercontent.com/15040875/72189950-3bedb300-33cc-11ea-8e48-965d89a64990.PNG)

### Item Checks
There are some items and directions that are locked unless the player and/or player’s location have specific items. For example, one of the items are unlocked if a banana is in that location.

### Saving and Loading
You can new/save/load at anytime.
There are two files to care about here, both in /TextAdventureGame/Build/Assets/SaveData/ .
Backups of the these files are included with the submission in the Backup folder, in case the they are overwritten and you want them back.
* NEW -> Loads a new game from newGameData.game.json
* SAVE -> Saves data to gameSaveData.json (NOTE: This file is overwritten every time, so there is only one save file.)
* LOAD-> Loads the default game data from newGameData.game.json and then loads the save data from gameSaveData.json

So, newGameData.game.json and gameSaveData.json are used for loading and saving. A third file, newGameData.editor.json, is for loading into the data tool editor.


### List of commands:
Go [Direction] Pickup/Take [x] Attack [x] <br>
Drop [x] Search [x] Hide [x]<br>
Look <br>
Inventory <br>
Help <br>
New -> new game <br>
Save -> saves game <br>
Load -> loads game save file <br>
Q -> quits game <br>

### Game Map:
![GameMap](https://user-images.githubusercontent.com/15040875/72189951-3bedb300-33cc-11ea-8399-5bbfc13491ae.PNG)

More screenshots of the game:

![Screenshot2](https://user-images.githubusercontent.com/15040875/72189953-3bedb300-33cc-11ea-96d5-09272b642214.PNG)

![Screenshot3](https://user-images.githubusercontent.com/15040875/72189954-3c864980-33cc-11ea-8d74-5fef9f93628a.PNG)

![Screenshot4](https://user-images.githubusercontent.com/15040875/72189955-3c864980-33cc-11ea-8c97-3aae078d3e8c.PNG)

### Data Analysis Tool

While the game is running, there are statistics being recorded based on the user's inputs and actions. This data is stored in an SQLite database, which can then be loaded and visualized in this Analysis Tool. The data is pushed to the database once the user quits, with each game session stored as new record in the TextBasedGameAnalytics database in /TextAdventureGame/Build/Assets/Database/.

The following are recorded.

The number of times the player: <br>
* changes location
* picks up an item
* drops an item
* attacks a guard
* searches a guard
* hides a guard
* gets tranquilized

![Screenshot](https://user-images.githubusercontent.com/15040875/72189967-4445ee00-33cc-11ea-8b7e-dbf974d87e5c.PNG)
