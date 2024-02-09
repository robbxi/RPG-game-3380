# Game Title

Here's the structure for our game.
This is just a framework to build our game upon (not playable for now).
There is a lot of TODO: in there, find one to work on.

It rework several class from the movement prototype.
Most notably:
- All enums go in `enums.h` now
- No more separate helper class (such as StringParser), all helper function go to the `Helper` class now
- Player and Tile now inherit from the GameObject class and are stored in a vector in the Game class
    - Why? This allow for better 2D render (line 91 of `Game.cpp` go into more details)
- TransitionTile is separated from the Tile class & have enterX and enterY now
- Good way to handle Tile interaction (loadTile(tileId) whenever a tile is interacted with)
- The game resolution will get determine by a new variable `scaling`.
    - This is the simplest way to handle resolution, just add `scaling *`
    whenever you use screenWidth/Height or gridWidth/Height
    - I did not add the ability to resize that Alton discovered
    because it can be complex & difficult to account for all the resolution possible
    (the resize doesn't work properly if the window is smaller than the native resolution)

- I also organized the functions in the `Game.cpp`.
There are fancy separators & 
you can navigate to by just `Ctrl-F-ing` `RENDER` or `INPUT` or `...`


```
Combat
├─ Action/
│  ├─ Action.h
│  ├─ Actions.h
│  ├─ DoNothing.h
│  └─ DoNothing.cpp
├─ Foe/
│  ├─ FoxFoe.h
│  ├─ Foe.h
│  └─ Foes.h
├─ Hero/
│  ├─ FoxHero.h
│  ├─ Hero.h
│  └─ Heroes.h
├─ Token/
│  ├─ Token.h
│  └─ Poison.h
├─ Combat.cpp
├─ Combat.h
└─ Unit.h
```
