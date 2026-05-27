#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include "Item.h"
#include <string>
#include <iostream>

class Door : public Passage {
public:
    Door(const std::string &name, const std::string &description,
         Room* from, Room* to, const std::string &requiredItem)
        : Passage(name, description, from, to),
          requiredItemName(requiredItem),
          locked(true) {}

    // Called when player tries to go through
    void enter() override {
        if (locked) {
            std::cout << "The door is locked. You need a " 
                      << requiredItemName << " to open it.\n";
        } else {
            Passage::enter();
        }
    }

    // Called when player uses unlock command
    bool unlock(const std::string &itemName) {
        if (itemName == requiredItemName) {
            locked = false;
            std::cout << "You use the " << itemName 
                      << " to unlock the door. It swings open.\n";
            return true;
        } else {
            std::cout << "The " << itemName 
                      << " doesn't work on this door.\n";
            return false;
        }
    }
    bool isPassable() const override { return !locked; } 
    bool isLocked() const { return locked; }
    std::string getRequiredItem() const { return requiredItemName; }

private:
    std::string requiredItemName;
    bool locked;
};

#endif