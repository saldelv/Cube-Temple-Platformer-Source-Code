# Cube-Temple-Platformer-Source-Code
Cube Temple Platformer is a small game made in Unreal Engine 5.4.1 using mostly C++. This repo contains all of the code written specifically for this game.

# Source Files
* *BreakableActor*: Actor that can be destroyed by a projectile
* *CollectableActor*: Actor that can be collected by the player or other actors
* *MainMenuWidget*: Sets up the interactable buttons on the main menu
* *MoveSceneComponent*: Component that can be added to actors to move them dynamically
* *MyBoss*: Boss actor and fight
* *MyBossHUD*: Updates and displays boss health
* *MyCharacter*: Character components, movement, abilities, and stats
* *MyGameInstance*: Allows getting and setting of character stat variables across different levels
* *MyGameModeBase*: Initializes default game mode settings
* *MyHUD*: Can display character values, currently displays coin count
* *MyProjectile*: Flexible actor used for the player and boss projectiles
* *SpawnActor*: Actor that can randomly spawn other actors in a set area and time
