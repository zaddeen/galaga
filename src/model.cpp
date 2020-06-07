#include "model.h"

game_object::game_object(ge211::Position p, bool alive, ge211::Dimensions velo,
                         int rad)
        : center_ (p)
        , live_ (alive)
        , velocity_ (velo)
        , radius_ (rad)
{}

missile::missile(ge211::Position p, bool alive)
        :game_object(p,alive,missile_velocity, 3)
{}

space_ship::space_ship(ge211::Position p, bool alive, ge211::Dimensions velo)
        :game_object(p, alive, velo, 10)
{}

enemy::enemy(ge211::Position p, bool alive, ge211::Dimensions velo)
        :game_object(p,alive,velo, 10)
{}

Model::Model()
        :player_({1024 / 2, 768 - 20}, true, {0, 0})
{}

void Model::missile_fires()
{
    missile m = missile(player_.center_, true);
    missiles_.push_back(m);
}

void Model::advance_level()
{
    enemies_.clear();
    int enemy_rows = initial_enemy_rows + (level_number_ - 1);
    int current_count = (enemy_cols * enemy_rows);
    int enemy_space = (enemy_radius * 2) * (current_count / enemy_rows);
    int empty_space = dimensions.width - enemy_space;
    int enemy_spacing = empty_space / enemy_cols;
    for (int i = 0; i < enemy_cols; ++i) {
        for (int j = 0; j < enemy_rows; ++j) {
            enemy e = enemy({190 + (enemy_spacing * i), 30 * (1+j)},
                            false, {0, 2 + level_number_});
            e.distance_ = 0;
            enemies_.push_back(e);
        }
    }
}

void Model::update()
{
    if (player_.live_) {
        if (enemies_.empty()) {
            level_number_ += 1;
            advance_level();
        }
        number_live = 0;
        if (lives_ == 0 || level_number_ > max_level) {
            player_.live_ = false;
        }
        for (int i = 0; i < enemy_count(); ++i) {
            if (enemy_hits_bottom(enemy_next(enemies_[i]))) {
                enemies_[i] = enemy_reverse_bottom(enemies_[i]);
            }
            if (enemies_[i].live_) {
                number_live += 1;
                enemies_[i] = enemy_next(enemies_[i]);
                enemies_[i].distance_ += enemies_[i].velocity_.height;
                if (enemy_next(enemies_[i]).distance_ >= dimensions.height) {
                    enemies_[i].live_ = false;
                    enemies_[i].distance_ = 0;
                    number_live -= 1;
                }
            }
            if (enemy_hits_player(enemies_[i])) {
                lives_ -= 1;
                std::swap(enemies_[i], enemies_.back());
                enemies_.pop_back();
                number_live -= 1;
            }
            for (int j = 0; j < missiles_.size(); ++j) {
                if (missile_hits_enemy(missile_next(missiles_[j]),
                                       enemy_next(enemies_[i]))) {
                    std::swap(enemies_[i], enemies_.back());
                    enemies_.pop_back();
                    number_live -= 1;
                    std::swap(missiles_[j], missiles_.back());
                    missiles_.pop_back();
                }
            }
        }
        if (number_live == 0 && enemy_count() > 3) {
            while (number_live < 3) {
                int random = rand() % enemy_count();
                if (!enemies_[random].live_) {
                    enemies_[random].live_ = true;
                    number_live += 1;
                }
            }
        }
        else if (enemy_count() <= 3) {
            int i = 0;
            while (i < enemy_count()) {
                enemies_[i].live_ = true;
                ++i;
            }
        }
        for (int i = 0; i < missiles_.size(); ++i) {
            if (missile_hits_top(missiles_[i])) {
                std::swap(missiles_[i], missiles_.back());
                missiles_.pop_back();
            }
            missiles_[i] = missile_next(missiles_[i]);
        }
        player_ = ship_next(player_);
    }
}

size_t Model::enemy_count()
{
    return enemies_.size();
}

bool Model::missile_hits_enemy(missile missile, enemy enemy)
{
    int m_top = missile.center_.y - missile.radius_;
    int m_left = missile.center_.x - missile.radius_;
    int m_bot = missile.center_.y + missile.radius_;
    int m_right = missile.center_.x + missile.radius_;

    int e_top = enemy.center_.y - enemy.radius_;
    int e_left = enemy.center_.x - enemy.radius_;
    int e_bot = enemy.center_.y + enemy.radius_;
    int e_right = enemy.center_.x + enemy.radius_;

    if (e_right < m_left || m_right < e_left) {
        return false;
    }
    else if (e_top > m_bot || e_bot < m_top) {
        return false;
    }
    else {
        return true;
    }
}

bool Model::missile_hits_top(missile m)
{
    int m_top = m.center_.y - m.radius_;
    if (m_top < 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Model::enemy_hits_bottom(enemy e)
{
    int e_bot = e.center_.y;
    if (e_bot > dimensions.height) {
        return true;
    }
    else {
        return false;
    }
}

bool Model::enemy_hits_player(enemy enemy)
{
    int p_top = player_.center_.y - player_.radius_;
    int p_left = player_.center_.x - player_.radius_;
    int p_bot = player_.center_.y + player_.radius_;
    int p_right = player_.center_.x + player_.radius_;

    int e_top = enemy.center_.y - enemy.radius_;
    int e_left = enemy.center_.x - enemy.radius_;
    int e_bot = enemy.center_.y + enemy.radius_;
    int e_right = enemy.center_.x + enemy.radius_;

    if (e_right < p_left || p_right < e_left) {
        return false;
    }
    else if (e_top > p_bot || e_bot < p_top) {
        return false;
    }
    else {
        return true;
    }
}

enemy Model::enemy_reverse_bottom(enemy e)
{
    e.center_.y = 0;
    return e;
}

enemy Model::enemy_next(enemy e)
{
    e.center_ += e.velocity_;
    return e;
}

space_ship Model::ship_next(space_ship ship)
{
    ship.center_ += ship.velocity_;
    return ship;
}

missile Model::missile_next(missile m)
{
    m.center_ += m.velocity_;
    return m;
}

int Model::live_count() const
{
    return lives_;
}

int Model::level_count() const
{
    return level_number_;
}