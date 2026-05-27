//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"

class Player : public Character {
public:
    static Player *instance() {
        // Note: lazy instantiation of the singleton Player object
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    void addItem(Item* item) { inventory.push_back(item); }

    void removeItem(const std::string &itemName) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if ((*it)->getName() == itemName) {
                inventory.erase(it);
                return;
            }
        }
    }

    Item* getItem(const std::string &itemName) {
        for (auto item : inventory) {
            if (item->getName() == itemName) return item;
        }
        return nullptr;
    }

    std::vector<Item*> getInventory() const { return inventory; }

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
