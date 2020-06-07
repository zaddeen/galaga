#include "model.h"
#include <catch.h>

struct Test_access
{
    Model& m_;

    bool missile_hits_enemy(missile missile, enemy enemy)
    {
        return m_.missile_hits_enemy(missile, enemy);
    }

    bool enemy_hits_bottom(enemy e)
    {
        return m_.enemy_hits_bottom(e);
    }

    enemy enemy_next(enemy e)
    {
        return m_.enemy_next(e);
    }

    missile missile_next(missile m)
    {
        return m_.missile_next(m);
    }

    bool hits_top(missile m)
    {
        return m_.missile_hits_top(m);
    }

};

TEST_CASE("Missile is Fired")
{
    Model m;

    // Fires a missile, checks that it is in the missile vector and that its
    // position, live state, and velocity are correct.
    m.missile_fires();
    CHECK(m.missiles_.size() == 1);
    CHECK(m.missiles_[0].velocity_.width == 0);
    CHECK(m.missiles_[0].velocity_.height == -5);
    CHECK(m.missiles_[0].live_);
}

TEST_CASE("Missile hits Top and is Destroyed")
{
    Model m;
    Test_access t{m};

    missile m1 = missile({m.dimensions.width / 2, 3}, true);
    m.missiles_.push_back(m1);
    CHECK(t.hits_top(t.missile_next(m1)));

    // Updates the model, updating the position of the missile so that it is
    // touching the top of the screen.
    m.update();
    // Updates the model again, now removing the missile from the vector.
    m.update();

    CHECK(m.missiles_.empty());
}

TEST_CASE("Missile hits Enemy and Both are Destroyed")
{
    Model m;
    Test_access t{m};

    // Initializes a missile and an enemy, putting them both in their respective
    // vectors.
    missile m1 = missile({100, 110}, true);
    enemy e1 = enemy({100, 110}, false, {0,0});
    m.missiles_.push_back(m1);
    m.enemies_.push_back(e1);

    // Based on their position, checks that the missile and enemy will collide.
    CHECK(t.missile_hits_enemy(t.missile_next(m1), t.enemy_next(e1)));

    // Updates the model, destroying both the missile and the enemy upon
    // collision.
    m.update();
    CHECK(m.enemies_.empty());
    CHECK(m.missiles_.empty());
}

TEST_CASE("Enemy Hits Bottom, Enemy Distance")
{
    Model m;
    Test_access t{m};
    // Initializes an enemy in the enemy vector, checks that its next position
    // will hit the bottom of the screen.
    enemy e1 = enemy({m.dimensions.width / 2, m.dimensions.height - 10}, true,
                      {0, 15});
    m.enemies_.push_back(e1);
    CHECK(t.enemy_hits_bottom(t.enemy_next(e1)));

    // Updates the model, now checking that the enemy is at the top.
    m.update();
    CHECK(m.enemies_[0].center_.y == 0 + m.enemies_[0].velocity_.height);

    // A test to show that when the enemy has traversed the distance of the
    // screen, its distance is reset to 0. This allows for the effect of placing
    // the enemy back in the grid, since when their distance is set back to 0,
    // their live state is also set to false. However, due to the random
    // assignment of moving enemies, their live state could be set back to true
    // in the same iteration of model.update().
    m.enemies_[0].distance_ = m.dimensions.height - 12;
    m.update();
    CHECK(m.enemies_[0].distance_ == 0);

}
TEST_CASE("Level Advancing and Update")
{
    Model m;
    // Updates the model, advancing the level count by one and initializing the
    // vector of enemies.
    m.update();
    CHECK(m.enemies_.size() == enemy_cols * initial_enemy_rows);
    int previous_level = m.level_count();
    int previous_enemy_count = m.enemies_.size();
    ge211::Dimensions previous_velocity = m.enemies_[0].velocity_;

    // Manually clears the vector of enemies.
    m.enemies_.clear();

    // Updates the model again. This should advance the level count by one and
    // initialize the vector of enemies again, with a higher number of
    // faster enemies.
    m.update();
    CHECK(m.level_count() == previous_level + 1);
    CHECK(m.enemies_.size() == previous_enemy_count + enemy_cols);
    CHECK(m.enemies_[0].velocity_.height == previous_velocity.height + 1);
}

TEST_CASE("Game Ends, Player Wins")
{
    Model m;

    // Checks that the player's live state is true, and that the max level is 3.
    CHECK(m.player_.live_);
    CHECK(max_level == 3);
    // Advances to level 1, since model.update() advances the level by checking
    // if the vector of enemies is empty (advancing if it is).
    m.update();
    m.enemies_.clear();
    // Advances to level 2.
    m.update();
    m.enemies_.clear();
    // Advances to level 3.
    m.update();
    m.enemies_.clear();
    // Attempts to advance again, but finds that the maximum level has been
    // reached, so the player's live state is set to false.
    m.update();
    CHECK_FALSE(m.player_.live_);
}

TEST_CASE("Game Ends, Player Loses")
{
    Model m;

    // Checks that the player's live state is true, and that the max level is 3.
    CHECK(m.player_.live_);
    CHECK(m.live_count() == 3);
    // Initializes the player, with 3 enemies above them.
    m.player_.center_ = {500, 500};
    enemy e = enemy({500, 460}, true, {0, 10});
    enemy e1 = enemy({500, 450}, true, {0, 10});
    enemy e2 = enemy({500, 440}, true, {0, 10});
    // Add each enemy to the vector of enemies.
    m.enemies_.push_back(e);
    m.enemies_.push_back(e1);
    m.enemies_.push_back(e2);
    // Advance the model 6 times, which causes each enemy to collide with the
    // player, each time causing the player to lose a life. This also causes the
    // enemy to be removed from the vector of enemies.
    m.update();
    m.update();
    CHECK(m.live_count() == 2);
    CHECK(m.enemy_count() == 2);
    m.update();
    m.update();
    CHECK(m.live_count() == 1);
    CHECK(m.enemy_count() == 1);
    m.update();
    m.update();
    CHECK(m.live_count() == 0);
    CHECK_FALSE(m.player_.live_);
}