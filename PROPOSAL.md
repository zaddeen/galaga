# Proposal: [PROPOSAL GALAGA]

## Synopsis

Our final project is a recreation of the classic 80s arcade game Galaga. The game involves the player controlling a
spaceship that moves around the screen, shooting enemies that spawn from the top. The enemies move down the environment
in a straight line, moving at a set velocity relative to the player. The player's spaceship has a laser gun that kills
the enemies, with the projectiles moving straight up from the position they were shot in at a specific velocity. If the
an enemy hits the spaceship, the player loses a life. When the player loses 3 lives, the game ends. When the bugs hit
the bottom of the screen, they return back to the top and are placed back into the vector of enemies. Every few seconds,
the enemies will change their direction so that they move towards where the player is in that instant. Once the player
eliminates all of the enemies in the initial vector, the level changes. Each consecutive level features more enemies
that are faster than the previous level's. When the player beats the final level, they win.

## Functional requirements

1.  The bugs are spawned in a grid at the top of the screen.
2.  The player's movement is mapped to the left and right arrow keys.
3.  The player cannot move up and down.
4.  The player's gun is mapped to the space bar.
5.  Missiles travel in the y-direction and have constant velocity, they travel
    directly upwards from where they were fired.
6.  When the projectile strikes the enemies, they are removed from the grid.
7.  When the enemies hit the bottom of the screen, they are moved back to the top and will continue to move back into their initial
   position. Once they reach their initial position in the grid, they will stop.
8.  The enemies descend three at a time.
9.  The enemies' initial velocity will be straight down and constant.
10. If the enemy hits the player, they lose a life.
11. After 3 lives are lost, the game is over.
12. Once the player eliminates all enemies in the grid, initializes a new level with a larger vector of faster enemies.
13. When the player beats the final level, they win, and the game ends.
14. The spacing of the enemies is determined by the number of enemies and the dimensions of the scene.
15. If a missile hits the top of the screen, it becomes dead and disappears.

## Open questions

1. How will we store the enemies back in the grid after they've hit the bottom?
2. What dimensions will work best for the game?
3. What velocity should we give the ship/missiles in order to make the game adequately challenging?
4. How will we determine the enemies' velocity? How will it change as the game progresses?
5. How will we move to different levels?