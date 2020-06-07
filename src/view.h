#pragma once

#include "model.h"

struct View : ge211::Abstract_game
{
    explicit View(Model&);

    ///
    /// MEMBER FUNCTIONS (for the view)
    ///

    ge211::Dimensions initial_window_dimensions() const override;

    // Draws each of the sprites on the screen (all enemies, missiles, and the
    // player).
    void draw(ge211::Sprite_set&) override;

    ///
    /// MEMBER FUNCTIONS (for the controller)
    ///

    //  Defines the recognized inputs of the game.
    //
    //  - On 'q', quits.
    //
    //  - On ' ', launches a missile.
    //
    //  - On 'left', moves the player left.
    //
    //  - On 'right', moves the player right.
    void on_key(ge211::Key) override;

    // Updates the model to reflect the passage of time, by calling
    // `Model::update`.
    void on_frame(double dt) override;

    ///
    /// MEMBER VARIABLE (model reference)
    ///

    Model& model_;

    ///
    /// MEMBER VARIABLES (for the view)
    ///

    ge211::Circle_sprite    const
            missile_sprite_    {missile_radius,  {255, 255, 255}};

    ge211::Image_sprite enemy_sprite_{"wasp.png"};
    ge211::Rectangle_sprite const
            enemy_sprite1_  {{enemy_radius, enemy_radius}, {0, 0, 0}};

    ge211::Image_sprite ship_sprite_{"ship.jpeg"};
    ge211::Rectangle_sprite const
            ship_sprite1_   {{ship_radius, ship_radius}, {0, 0, 0}};

    ge211::Font sans_{"sans.ttf", 60};
    ge211::Font sans_small{"sans.ttf", 20};
    ge211::Text_sprite lives_;
    ge211::Text_sprite level_;
    ge211::Text_sprite game_over_;
    ge211::Text_sprite victory_;

};
