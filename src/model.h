#pragma once

#include <ge211.h>

//
// Model Constants
//

// The velocity of any missile fired from the ship.
static const ge211::Dimensions missile_velocity = {0, -5};

// The number of the highest level.
static const int max_level = 3;

// Starting number of columns of enemies.
static const int enemy_cols = 4;

// Number of rows of enemies.
static const int initial_enemy_rows = 3;

// The radii of each game object, respectively.
static const int missile_radius = 3;
static const int ship_radius = 20;
static const int enemy_radius = 20;

//
// Model Classes
//

class game_object
{
public:
    // Constructor for game objects.
    game_object(ge211::Position, bool, ge211::Dimensions, int);

    // The center of the object.
    ge211::Position center_;

    // Whether or not the object is alive.
    bool live_;

    // The velocity of the object.
    ge211::Dimensions velocity_;

    // The radius of the object.
    int radius_;
};

class missile : public game_object{
public:
    // Constructor for missiles.
    missile(ge211::Position, bool);
};

class space_ship : public game_object {
public:
    // Constructor for ship.
    space_ship(ge211::Position, bool, ge211::Dimensions);
};

class enemy : public game_object {
public:
    // Constructor for enemies.
    enemy(ge211::Position, bool, ge211::Dimensions);

    // Record of distance traveled.
    int distance_;

};

class Model {
    //
    // PRIVATE DATA MEMBERS
    //
    // The number of remaining lives that the player has.
    int lives_ = 3;

    // The current level number (starts at 0, but when the game starts and when
    // a player completes a level it is incremented by 1.
    int level_number_ = 0;

public:
    //
    // PUBLIC FUNCTIONS
    //

    // Constructor for the model.
    explicit Model();

    // Fires a missile.
    void missile_fires();

    // Updates the model state for one time step.
    void update();

    // Returns the number of enemies remaining.
    size_t enemy_count();

    // If the vector of enemies is empty, advances the level by 1, then
    // refills the vector of enemies.
    void advance_level();

    // Access for the private variables:
    int live_count() const;

    int level_count() const;

    //
    // MEMBER VARIABLES
    //

    // The ship that player is controlling.
    space_ship player_;

    // The dimensions of the model.
    ge211::Dimensions dimensions = {1024, 768};

    // The number of live enemies (should always be 3 if the enemies vector has
    // more than three enemies in it.
    int number_live = 0;

    // The vector containing all of the enemies.
    std::vector<enemy> enemies_;

    // The vector containing any live missiles.
    std::vector<missile> missiles_;

    // ------------------
    // Test access.
    friend struct Test_access;

private:
    //
    // HELPER FUNCTIONS
    //

    // Returns a boolean indicating if a missile hits an enemy.
    bool missile_hits_enemy(missile missile, enemy enemy);

    // Returns true if a game object hits an area of the screen.
    bool missile_hits_top(missile m);

    bool enemy_hits_bottom(enemy e);

    // Checks if an enemy hits a player.
    bool enemy_hits_player(enemy e);

    // Moves an enemy back to the top when it hits the bottom.
    enemy enemy_reverse_bottom(enemy e);

    // Returns the given game object in the next frame (updated position,
    // velocity, live state).
    enemy enemy_next(enemy e);
    space_ship ship_next(space_ship s);
    missile missile_next(missile m);
};

