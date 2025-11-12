========= Title ========
---Plants vs. Zombies---

====== Info =====
OOP2 Project  ||  Authors:       Shachar Ben Senyor  ||  ID: 211748470
                                 Roi Mazon           ||  ID: 211845045
                                 Amnon Yaakov        ||  ID: 316158328

====== Description ======
A C++ implementation of Plants vs. Zombies game using SFML 2.6 for graphics, audio, and input handling.
Players strategically place plants on a 5x9 grid to defend against waves of zombies advancing from the right side of the screen.
The game features multiple plant types with unique abilities, various zombie types, power-ups, and 18 progressive levels with increasing difficulty.
Built with extensive use of design patterns including Strategy, State, Command, Factory, Observer, and Singleton patterns.

===== Files Created =====

**Core System:**

  * `main.cpp` – Program entry point, creates `Controller` and handles exceptions with `Logger`.
  * `Controller.h` / `Controller.cpp` – Main game loop with fixed 60 FPS timestep, manages SFML window and `StateMachine`.

**State Management (State Pattern):**

  * `StateMachine.h` / `StateMachine.cpp` – Manages game state stack (push/pop), handles mute button and back navigation.
  * `State.h` / `State.cpp` – Abstract base class for all game states with event handling, update, and draw methods.
  * `GameState.h` / `GameState.cpp` – Core gameplay state managing all game systems and level progression.
  * `MenuState.h` / `MenuState.cpp` – Main menu with navigation buttons to level selection and help.
  * `PauseState.h` / `PauseState.cpp` – Pause overlay during gameplay with resume/restart options.
  * `HelpState.h` / `HelpState.cpp` – Manages the help system's state machine, switching between different help screens.
  * `LevelSelectionState.h` / `LevelSelectionState.cpp` – Level selection interface with unlock progression.
  * `GameOverState.h` / `GameOverState.cpp` – Game over screen for player defeat.
  * `WinState.h` / `WinState.cpp` – Victory screen for level completion.

**Game Objects:**

  * `GameObject.h` / `GameObject.cpp` – Abstract base class for all game entities with position, sprite, health, and factory registration.
  * `Plant.h` / `Plant.cpp` – Base plant class with health, damage handling, and Observer pattern implementation.
  * `ShootingPlant.h` / `ShootingPlant.cpp` – Plants that fire projectiles at zombies using shooting and targeting strategies.
  * `ResourcePlant.h` / `ResourcePlant.cpp` – Sunflower-type plants that generate sun currency.
  * `TrapPlant.h` / `TrapPlant.cpp` – Plants with state-based behavior (arming, ready, exploding) and trap strategies.
  * `WallPlant.h` / `WallPlant.cpp` – Defensive plants that block zombie advancement.
  * `Zombie.h` / `Zombie.cpp` – Base zombie class with movement, health, states (Walking, Eating, Frozen), and collision handling.
  * `RegularZombie.h` / `RegularZombie.cpp` – Standard walking zombies that eat plants.
  * `ShootingZombie.h` / `ShootingZombie.cpp` – Zombies that can shoot projectiles at plants.
  * `Bullet.h` / `Bullet.cpp` – Projectile objects with movement, damage, effects, and lifetime strategies.
  * `CollectableObject.h` / `CollectableObject.cpp` – Base class for clickable, collectible items.
  * `Sun.h` / `Sun.cpp` – Collectible currency objects that fall from the sky or are produced by plants.
  * `Gift.h` / `Gift.cpp` – Power-up collectibles that provide temporary bonuses.

**Strategy Pattern Implementations:**

  * **Movement:**
      * `IMovementStrategy.h` – Interface for object movement behaviors.
      * `LinearMovementStrategy.h` / `LinearMovementStrategy.cpp` – Straight-line movement.
      * `StationaryMovementStrategy.h` – No movement.
  * **Shooting:**
      * `IShootStrategy.h` – Interface for shooting behaviors.
      * `SingleShotStrategy.h` / `SingleShotStrategy.cpp` – Single projectile shooting.
      * `BurstFireStrategy.h` / `BurstFireStrategy.cpp` – Multiple projectiles in rapid succession.
      * `BidirectionalShootStrategy.h` / `BidirectionalShootStrategy.cpp` – Shoots in two opposite directions.
  * **Targeting:**
      * `ITargetingStrategy.h` – Interface for target acquisition.
      * `ForwardTargetingStrategy.h` / `ForwardTargetingStrategy.cpp` – Targets enemies directly ahead.
      * `BidirectionalTargetingStrategy.h` / `BidirectionalTargetingStrategy.cpp` – Targets enemies in front and behind.
  * **Effects:**
      * `IEffectStrategy.h` – Interface for applying effects (e.g., damage, slow) to game objects.
      * `DamageEffect.h` / `DamageEffect.cpp` – Applies damage to targets.
      * `SlowEffect.h` / `SlowEffect.cpp` – Applies a slowing effect to zombies.
  * **Lifetime:**
      * `ILifetimeStrategy.h` – Interface for object lifetime management.
      * `BulletLifetimeStrategy.h` / `BulletLifetimeStrategy.cpp` – Deletes objects that go off-screen.
      * `TimerLifetimeStrategy.h` – Deletes objects after a set time.
      * `OffScreenLifetimeStrategy.h` – Deletes objects once they are fully off the screen.
  * **Trap Behavior:**
      * `ITrapBehaviorStrategy.h` – Interface for how a trap plant acts on collision.
      * `PassiveStrategy.h` / `PassiveStrategy.cpp` – Applies continuous damage on contact.
      * `ExplodeStrategy.h` / `ExplodeStrategy.cpp` – Explodes on contact, dealing high damage.
  * **Zombie's Response to Traps:**
      * `ITrapResponseStrategy.h` – Interface for how a zombie reacts to a trap.
      * `DefaultResponseStrategy.h` / `DefaultResponseStrategy.cpp` – Takes damage over time from traps like SpikeWeed.
      * `InstaKillResponseStrategy.h` / `InstaKillResponseStrategy.cpp` – Is instantly killed by certain traps (used for Zomboni).
  * **Gift Effects:**
      * `IGiftEffectStrategy.h` – Interface for gift/power-up effects.
      * `DamageBoostGiftStrategy.h` / `DamageBoostGiftStrategy.cpp` – Temporarily boosts all plant damage.
      * `FireRateGiftStrategy.h` / `FireRateGiftStrategy.cpp` – Temporarily boosts plant fire rate.
      * `FreezeGiftStrategy.h` / `FreezeGiftStrategy.cpp` – Freezes all zombies on screen.
      * `SunGiftStrategy.h` / `SunGiftStrategy.cpp` – Instantly grants the player a sum of sun currency.

**State Pattern for Game Objects:**

  * **Zombie States:**
      * `IZombieState.h` – Interface for zombie behavioral states (Walking, Eating, Frozen).
      * `WalkingState.h` / `WalkingState.cpp` – Normal zombie movement behavior.
      * `EatingState.h` / `EatingState.cpp` – Zombie attacking plants behavior.
      * `FrozenState.h` / `FrozenState.cpp` – Zombie temporarily frozen behavior.
  * **Trap Plant States:**
      * `ITrapState.h` – Interface for trap plant states.
      * `SpawningState.h` / `SpawningState.cpp` – Trap plant initial deployment animation.
      * `ArmingState.h` / `ArmingState.cpp` – Trap plant preparation phase (e.g., Potato Mine).
      * `ReadyState.h` / `ReadyState.cpp` – Trap plant ready to be triggered.
      * `ExplodingState.h` / `ExplodingState.cpp` – Trap plant explosion animation sequence.

**Command Pattern:**

  * `Icommand.h` – Interface for executing commands.
  * `SelectPlantCommand.h` / `SelectPlantCommand.cpp` – Command for plant selection in the UI.
  * `MuteCommand.h` / `MuteCommand.cpp` – Command for audio mute toggle.
  * `PopStateCommand.h` – Command for returning to the previous state in `StateMachine`.
  * `PushStateCommand.h` – Command for pushing a new state onto the `StateMachine`.
  * `RestartLevelCommand.h` / `RestartLevelCommand.cpp` – Command for restarting the current level.
  * `ActivateGiftCommand.h` / `ActivateGiftCommand.cpp` – Command for power-up activation from the GiftBar.
  * `ExitCommand.h` – Command to close the game window.
  * `SwitchHelpScreenCommand.h` / `SwitchHelpScreenCommand.cpp` – Command to switch between different help screens.
  * `SelectAlmanacCommand.h` / `SelectAlmanacCommand.cpp` – Command to select an item in the Almanac for viewing details.
  * `CloseInfoCardCommand.h` – Command to close the detailed view in the Almanac.

**Factory Pattern:**

  * `Factory.h` / `Factory.cpp` – Registration-based factory for dynamic `GameObject` creation.
  * `CreationParams.h` – Parameter structure passed to the factory for object creation.

**Manager Classes (Singletons & Others):**

  * `TextureManager.h` / `TextureManager.cpp` – (Singleton) Manages loading and caching of fonts and textures.
  * `AudioManager.h` / `AudioManager.cpp` – (Singleton) Manages music and sound effects with volume and mute control.
  * `LevelManager.h` / `LevelManager.cpp` – (Singleton) Manages level unlock progression, saving/loading the highest unlocked level.
  * `Logger.h` / `Logger.cpp` – (Singleton) A simple file-based error logging system.
  * `GameObjectManager.h` / `GameObjectManager.cpp` – Manages all active game objects, handling updates, drawing, events, and collision checks.
  * `PlayerResourceManager.h` / `PlayerResourceManager.cpp` – Manages the player's sun currency and validates plant purchases.
  * `LevelLogicManager.h` / `LevelLogicManager.cpp` – Handles level-specific logic, win/lose conditions, zombie spawning, and progress tracking.
  * `TargetingSystem.h` / `TargetingSystem.cpp` – Manages target acquisition logic for plants and zombies.
  * `SunSpawnerManager.h` / `SunSpawnerManager.cpp` – Controls the automatic generation of sun that falls from the sky.
  * `CardManager.h` / `CardManager.cpp` – Manages the display and interaction of cards in the Almanac help screens.

**Level Management:**

  * `LevelScripter.h` / `LevelScripter.cpp` – Parses and executes level script files (`.txt`) to create timed events like zombie spawns and announcements.
  * `LevelScriptFunctors.h` / `LevelScriptFunctors.cpp` – Contains the functor logic for parsing and executing each command in the level scripts.

**UI System:**

  * `UIManager.h` / `UIManager.cpp` – Manages all user interface elements, including plant/shovel selection, the preview sprite, and announcements.
  * `Button.h` / `Button.cpp` – A generic, command-driven button component used throughout the UI.
  * `PlantButtons.h` / `PlantButtons.cpp` – Manages the plant selection buttons in the game UI, including cost display and cooldowns.
  * `PlantButtonData.h` / `PlantButtonData.cpp` – A data structure holding the state for each plant button (cost, cooldown, etc.).
  * `SunCounter.h` / `SunCounter.cpp` – Displays the player's current sun currency.
  * `GiftBar.h` / `GiftBar.cpp` – Manages the UI for collected gifts/power-ups, allowing the player to activate them.
  * `ProgressBar.h` / `ProgressBar.cpp` – Visualizes the level's progress and the timing of zombie waves/flags.
  * **Help Screens:**
      * `IHelpScreen.h` – Abstract base class for all help screen variations.
      * `MainHelpScreen.h` / `MainHelpScreen.cpp` – The main entry point for the help section.
      * `GameplayHelpScreen.h` / `GameplayHelpScreen.cpp` – A static screen explaining game mechanics.
      * `AlmanacScreen.h` / `AlmanacScreen.cpp` – The Almanac menu to choose between Plants, Zombies, and Gifts.
      * `AlmanacHelpScreen.h` / `AlmanacHelpScreen.cpp` – Base class for Almanac screens, managing card layouts and selection.
      * `PlantsHelpScreen.h` / `PlantsHelpScreen.cpp` – Displays information about all plant types.
      * `ZombiesHelpScreen.h` / `ZombiesHelpScreen.cpp` – Displays information about all zombie types.
      * `GiftHelpScreen.h` / `GiftHelpScreen.cpp` – Displays information about all gift types.

**Game Systems:**

  * `Board.h` / `Board.cpp` – Represents the 5x9 game grid, handles plant placement logic and pixel-to-grid conversions.
  * `CollisionHandler.h` / `CollisionHandler.cpp` – A type-based lookup system (using `std::map` and `type_index`) to resolve collisions between different `GameObject` types.
  * `Animation.h` / `Animation.cpp` – A generic sprite-sheet animation system with frame timing, looping, and offsets.
  * `ShootingLogicHandler.h` / `ShootingLogicHandler.cpp` – A reusable handler for the logic of shooting, including cooldowns and interfacing with shoot strategies.

**Observer Pattern:**

  * `IObserver.h` – Interface for objects that need to be notified of events (e.g., a zombie observing a plant).
  * `ISubject.h` – Interface for objects that can be observed (e.g., a plant notifying zombies upon its death).

**Configuration:**

  * `GameConfig.h` – Defines global constants for window dimensions and grid layout.
  * `PlantData.h` / `PlantData.cpp` – Defines statistics (health, cooldown) and sprite information for all plant types.
  * `ZombieData.h` / `ZombieData.cpp` – Defines statistics (health, speed, damage) and sprite information for all zombie types.
  * `BulletData.h` / `BulletData.cpp` – Defines properties (damage, speed) for projectile types.
  * `GiftData.h` / `GiftData.cpp` – Defines IDs and sprite information for power-ups.
  * `SunData.h` / `SunData.cpp` – Defines properties for sun currency objects.
  * `SpriteDef.h` – Defines a common structure for sprite properties (rect, origin, scale).
  * `AlmanacData.h` – Contains the data collections (`std::vector<CardMeta>`) for populating the Almanac screens.

**Utilities:**

  * `Utiles.h` / `Utiles.cpp` – Contains common utility functions like `createText`, `calculateSpriteRect`, and `centerOrigin`.

**Build System:**

  * `CMakeLists.txt` – CMake configuration files located in the root, `src`, and `include` directories to define the project structure, source files, and include directories for the build process.

===== Data Structures =====

**Game Object Management:**

  * `GameObjectManager`: `std::array<std::list<std::unique_ptr<GameObject>>, 5>` for row-based object storage, enabling efficient collision checks within each row.
  * `StateMachine`: `std::vector<std::unique_ptr<State>>` is used as a stack to manage the current game state.
  * `Factory`: `std::unordered_map<std::string, Creator>` maps string IDs to object creation functions for dynamic instantiation.

**Grid System:**

  * `Board::Grid`: `std::array<std::array<bool, 9>, 5>` tracks which cells in the 5x9 grid are occupied by plants.

**Resource Management:**

  * `TextureManager`: `std::unordered_map<std::string, sf::Texture>` and `std::unordered_map<std::string, sf::Font>` for caching loaded asset resources.
  * `AudioManager`: `std::unordered_map<std::string, std::unique_ptr<sf::Music>>` for music tracks and `std::deque<sf::Sound>` for managing a pool of reusable sound effect instances.

**Observer Pattern:**

  * `Plant`: `std::list<IObserver*>` holds pointers to all zombies currently eating the plant, to notify them upon its death.

**Collision Handling:**

  * `CollisionHandler`: `std::map<std::pair<std::type_index, std::type_index>, HitFunctionPtr>` maps pairs of object types to the correct collision handling function.

===== Algorithms =====

**Collision Detection:**

  * Utilizes row-based spatial partitioning via `GameObjectManager`'s structure. Collision checks are primarily performed between objects within the same row list, reducing the number of pairwise checks needed.
  * Collision is determined by testing for bounding box intersection using SFML's `sf::FloatRect::intersects` method.
  * A double dispatch mechanism using a map of `std::type_index` pairs to function pointers resolves the specific interaction between any two colliding object types.

**Pathfinding:**

  * Zombies and bullets use a simple `LinearMovementStrategy`, moving in a straight line at a constant speed without complex pathfinding.
  * State transitions for zombies are triggered by collisions (e.g., a `WalkingState` zombie transitions to `EatingState` upon hitting a plant), not by pathfinding logic.

**Level Scripting:**

  * A priority queue (`std::priority_queue<Event>`) stores time-stamped events read from level script files. The game loop processes events whose timestamps have been reached.
  * The scripting system uses command-based functors to parse and execute different script commands:
      - `SPAWN`: Creates a single zombie of a specified type in a given row.
      - `WAIT`: Pauses script execution for a specified duration.
      - `ANNOUNCE`: Displays a message on the screen for a short duration.
      - `FLAG`: Marks a key point in the level's timeline, used to update the `ProgressBar`.
      - `SPAWN_GROUP`: Creates a group of zombies with a specified count, interval, and type distribution.
      - `CONFIG`: Sets initial level parameters like starting sun and level theme (day/night).

**Target Acquisition:**

  * The `TargetingSystem` maintains row-based lists of active plants and zombies.
  * `ShootingPlant`s use the `ITargetingStrategy` to determine when to shoot. For example, `ForwardTargetingStrategy` checks if any zombie exists in the same row with a greater x-coordinate. `BidirectionalTargetingStrategy` checks for zombies in both directions.

**Resource Economy:**

  * The `PlayerResourceManager` manages the player's sun total.
  * Sun is collected by clicking on `Sun` objects, which are either generated periodically by the `SunSpawnerManager` (falling from the sky) or produced by `ResourcePlant`s.
  * Before placing a plant, the `Board` checks with the `PlayerResourceManager` if the player has sufficient sun by comparing against a cost map.

===== Design =====

**Design Patterns:**

  * **State Pattern:** Used extensively to manage distinct behaviors. `StateMachine` handles high-level game states (Menu, Game, Pause). `IZombieState` and `ITrapState` manage the complex, state-dependent behaviors of `Zombie` and `TrapPlant` objects.
  * **Strategy Pattern:** Decouples algorithms from the objects that use them. This is central to the game's design, used for `IMovementStrategy`, `IShootStrategy`, `ITargetingStrategy`, `IEffectStrategy`, and others, allowing for flexible and reusable behaviors.
  * **Command Pattern:** Encapsulates actions as objects. Used for all UI interactions (`Button` class) and for queuing state changes (`PushStateCommand`, `PopStateCommand`), ensuring a clean separation between UI and game logic.
  * **Factory Pattern:** A registration-based `Factory` creates all `GameObject` instances from a string ID. This allows new object types to be added without changing the factory's code and enables level data to specify objects by name.
  * **Observer Pattern:** Used to decouple objects. `Plant`s act as Subjects, and `Zombie`s as Observers. When a plant is destroyed, it notifies all observing zombies so they can transition back to a `WalkingState` without the plant needing to know about the zombie's implementation.
  * **Singleton Pattern:** Used for global manager classes like `TextureManager`, `AudioManager`, `LevelManager`, and `Logger` to provide a single point of access to shared resources and systems.

**Architecture Principles:**

  * **Single Responsibility Principle:** Classes are designed to have a single, well-defined purpose. For example, `PlayerResourceManager` only handles sun currency, while `GameObjectManager` only handles object lifecycle and collisions.
  * **Open/Closed Principle:** The use of Strategy and Factory patterns allows the game to be extended with new plants, zombies, and behaviors with minimal modification to existing code. For example, a new plant can be created by defining its data, registering it with the factory, and providing its strategies.
  * **Polymorphism:** Leveraged through abstract base classes and virtual methods for game objects (`GameObject::update`), states (`IState::handleEvent`), strategies (`IShootStrategy::update`), and commands (`ICommand::execute`), enabling uniform handling of diverse object types and behaviors.

**Game Loop:**

  * The `Controller` implements a fixed-timestep game loop to ensure deterministic physics and game logic, independent of rendering speed. An accumulator keeps track of elapsed time, and the `update` function is called in fixed steps (`1.f / 60.f`).
  * Input handling is event-driven, processed once per frame. Events are passed to the current state, which then delegates to UI elements or game objects.

**Memory Management:**

  * Modern C++ practices are used, with `std::unique_ptr` managing the ownership of almost all heap-allocated objects, including game objects in `GameObjectManager`, states in `StateMachine`, and commands in `Button`s. This enforces RAII and prevents memory leaks.
  * `GameObjectManager` performs garbage collection each frame by removing objects that have been marked for deletion (`isToDelete()`).

==== Known Bugs ====

=== Notes ===

**Open_Levels.txt:**
This file contains the highest level unlocked that available in the game, 
which is used by the `LevelManager` to determine which levels are accessible in the `LevelSelectionState`.
if you want to check specific levels, you can edit this file to change the highest level number.
there are 18 levels available in the game, numbered from 1 to 18.

**Level File Format:**
Each level file (e.g., `level_1.txt`) is a plain text file that uses a series of commands to define the level's structure and timeline.

  - `CONFIG initial_sun <amount>` - Sets the player's starting sun currency.
  - `CONFIG level_type <day/night>` - Sets the visual theme and determines if sun will fall from the sky.
  - `WAIT <seconds>` - Pauses the script execution for the given number of seconds.
  - `ANNOUNCE <message>` - Displays a text message (e.g., "A huge wave of zombies is approaching\!") to the player.
  - `SPAWN <zombie_type> <row|random>` - Spawns a single zombie of the specified type in a specific row or a random row.
  - `SPAWN_GROUP <row|random> <count> <interval> <zombie_type_1> [zombie_type_2] ...` - Spawns a group of zombies, picking randomly from the provided list of types.
  - `FLAG` - Marks a major wave or progression point in the level, which is visualized on the progress bar.
* row can be a number from 0 to 4, representing the rows of the grid from top to bottom.

**Controls:**
  - **Left-click:** Plant selection from the left-side UI, plant placement on the grid, sun and gift collection, and general UI interaction.
  - **Right-click:** Cancel plant or shovel selection.