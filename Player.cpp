//
// Created by dekel on 23/01/2025.
//
#include "Player.h"

Player::Player(const char* name, int max_life, int damage) : Entity(name, max_life, damage) {}

Player:: ~Player() {}

// update the monster that the player is fighting with
void Player::set_fighting_who(Monster* fighting_who) {
    this->fighting_who = fighting_who;
}

//update turn for special power
void Player::updateTurn() {
    this->special_attack_wait = (this->special_attack_wait + 1) % WAITING_TIME;
}