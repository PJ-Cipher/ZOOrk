//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <utility>
#include <algorithm>
#include <memory>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "inventory" || command == "i") {
            handleInventoryCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        Room* room = player->getCurrentRoom();
        std::cout << room->getDescription() << "\n";
    } else {
        std::string target = arguments[0];
        Room* room = player->getCurrentRoom();
        Item* item = room->getItem(target);
        if (!item) item = player->getItem(target);
        if (item) {
            std::cout << item->getDescription() << "\n";
        } else {
            std::cout << "You don't see any " << target << " here.\n";
        }
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }
    std::string itemName = arguments[0];
    Room* room = player->getCurrentRoom();
    Item* item = room->retrieveItem(itemName);
    if (item) {
        player->addItem(item);
        std::cout << "You pick up the " << itemName << ".\n";
    } else {
        std::cout << "There is no " << itemName << " here.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }
    std::string itemName = arguments[0];
    Item* item = player->getItem(itemName);
    if (item) {
        player->removeItem(itemName);
        player->getCurrentRoom()->addItem(item);
        std::cout << "You drop the " << itemName << ".\n";
    } else {
        std::cout << "You don't have a " << itemName << ".\n";
    }
}

void ZOOrkEngine::handleInventoryCommand(std::vector<std::string> arguments) {
    auto inv = player->getInventory();
    if (inv.empty()) {
        std::cout << "You are not carrying anything.\n";
    } else {
        std::cout << "You are carrying:\n";
        for (auto item : inv) {
            std::cout << "  - " << item->getName() << "\n";
        }
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
