#include "view.h"
#include <ge211.h>

View::View(Model& model)
        : model_(model)
        , lives_ ( std::string("Lives: ") + std::to_string(model.live_count()),
                   sans_small)
        , level_ ( std::string("Level: ") + std::to_string(model.level_count()),
                   sans_small)
        , game_over_ ( std::string("GAME OVER"), sans_)
        , victory_ ( std::string("Player Wins!"), sans_)
{ }

ge211::Dimensions View::initial_window_dimensions() const
{
    return model_.dimensions;
}

void View::draw(ge211::Sprite_set& sprites)
{
    if (model_.player_.live_) {
        sprites.add_sprite(ship_sprite_,
                           {model_.player_.center_.x - ship_radius,
                            model_.player_.center_.y - ship_radius});
        sprites.add_sprite(ship_sprite1_,
                           {model_.player_.center_.x - ship_radius,
                            model_.player_.center_.y - ship_radius});
        lives_.reconfigure(ge211::Text_sprite::Builder(sans_small).message(
                std::string("Lives: ") + std::to_string(model_.live_count())));
        sprites.add_sprite(lives_, {940, 720});
        level_.reconfigure(ge211::Text_sprite::Builder(sans_small).message(
                std::string("Level: ") + std::to_string(model_.level_count())));
        sprites.add_sprite(level_, {940, 680});

        for (missile m: model_.missiles_) {
            sprites.add_sprite(missile_sprite_,
                               {m.center_.x - missile_radius,
                                m.center_.y - missile_radius});
        }
        for (enemy e: model_.enemies_) {
            sprites.add_sprite(enemy_sprite_,
                               {e.center_.x - enemy_radius,
                                e.center_.y - enemy_radius}, 1);
            sprites.add_sprite(enemy_sprite1_,
                               {e.center_.x - enemy_radius,
                                e.center_.y - enemy_radius}, 0);
        }
    }
    else if (!model_.player_.live_ && model_.live_count() == 0)
    {
        sprites.add_sprite(game_over_, {model_.dimensions.width / 2 - 170,
                                        model_.dimensions.height / 2 - 100} );
    }
    else {
        sprites.add_sprite(victory_, {model_.dimensions.width / 2 - 170,
                                      model_.dimensions.height / 2 - 100} );
    }
}


void View::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }
    if (model_.player_.live_) {
        if (key == ge211::Key::right()) {
            model_.player_.center_ += {15, 0};
        }
        if (key == ge211::Key::left()) {
            model_.player_.center_ -= {15, 0};
        }
        if (key == ge211::Key::code(' ')) {
            model_.missile_fires();
        }
    }
}

void View::on_frame(double dt)
{
    model_.update();
}

