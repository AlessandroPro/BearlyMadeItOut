# 'Bearly' Made It Out!
## Text-Based Adventure Game

### Overview
You’re a bear trying to escape a zoo. See the map included in this submission for more details on the layout.
As a bear sneaking around a zoo at night, you traverse different animal enclosures and the pathways between them. You start of in the bear enclosure and then go off to search for 5 pieces of clothing to create a disguise.
Once all items are found, go back to the bear enclosure, type ‘GO TO SLEEP’. The bear will go to sleep, wake up in the morning, put on all of the clothes, and walk out of the zoo unnoticed. You win!
You can search, attack, travel (north south, east, west), pickup and drop items. If there is a guard in your location, they will tranquilize you if you perform any actions before attacking them. This is like “dying’ in the game, and you respawn back in your enclosure but your items are dropped. Once a guard is attacked, they go unconscious, and must be hidden. If you don’t hide the body, the next time you visit the location, you’ll get tranquilized by other guards who found the body.

### Item Checks
There are some items and directions that are unlocked only if the player and player’s location have specific items. For example, one of the items are unlocked if a banana is in that location.

### Saving and Loading
You can new/save/load at anytime.
There are two files to care about here, both in prog50016.Project1.AP/TextAdventureGame/Build/Assets/SaveData/ .
Backups of the these files are included with the submission in the Backup folder, in case the they are overwritten and you want them back.
* NEW -> Loads a new game from newGameData.game.json
* SAVE -> Saves data to gameSaveData.json
This file is overwritten every time, so there is only one save file.
*LOAD-> Loads the default game data from newGameData.game.json and then loads the save data from gameSaveData.json

So, newGameData.game.json gameSaveData.json
are used for loading and saving. A third file, newGameData.editor.json, is for loading into the tool editor.
Database
Every time the player uses an action or gets tranquilized, it is recorded. Then when the user quits, this data is stored as a new record in the TextBasedGameAnalytics database in proj50016.Project1.AP/TextAdventureGame/Build/Assets/Database/

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

![DressedBear](https://user-images.githubusercontent.com/15040875/72189950-3bedb300-33cc-11ea-8e48-965d89a64990.PNG)

![GameMap](https://user-images.githubusercontent.com/15040875/72189951-3bedb300-33cc-11ea-8399-5bbfc13491ae.PNG)

![Screenshot1](https://user-images.githubusercontent.com/15040875/72189952-3bedb300-33cc-11ea-88a3-cbf404371805.PNG)

![Screenshot2](https://user-images.githubusercontent.com/15040875/72189953-3bedb300-33cc-11ea-96d5-09272b642214.PNG)

![Screenshot3](https://user-images.githubusercontent.com/15040875/72189954-3c864980-33cc-11ea-8d74-5fef9f93628a.PNG)

![Screenshot4](https://user-images.githubusercontent.com/15040875/72189955-3c864980-33cc-11ea-8c97-3aae078d3e8c.PNG)

![Screenshot](https://user-images.githubusercontent.com/15040875/72189967-4445ee00-33cc-11ea-8b7e-dbf974d87e5c.PNG)
