# ZOOrk — Space Station Text Adventure

A Zork-style text adventure game built in C++..

You wake up aboard the **ISS Nomad** — a deep-space research station that has gone dark. Navigate 10 rooms, scavenge items, and uncover what happened in the Alien Chamber.

---

## Gameplay

Type commands to interact with the world:

| Command | Description |
|---|---|
| `go [direction]` | Move between rooms — north, south, east, west |
| `look` | Describe the current room |
| `look [item]` | Examine a specific item |
| `take [item]` | Pick up an item |
| `drop [item]` | Drop an item |
| `inventory` or `i` | Check what you are carrying |
| `unlock [direction]` | Unlock a locked door in that direction |
| `help` | Show all available commands |
| `quit` | Exit the game |

---

## Map

```
        [Crew Quarters]
               |
           [Bridge]
               |
[Cargo] -- [Corridor A] -- [Medical Bay] -- [Research Lab] -- [Alien Chamber]
               |
         [Engine Room]
               |
         [Reactor Core]

[Airlock] --> east --> Corridor A
```

---

## Features

- **10-room space station map** with unique descriptions and atmosphere
- **Item system** — pick up, drop, and examine items across rooms
- **Inventory management** — track what you are carrying at all times
- **Locked Door mechanic** — the Alien Chamber requires a keycard to enter
- **unlock command** — use items from your inventory to open locked doors
- **help command** — always available to remind you of available actions

---

## Building

Requires a C++20 compiler (g++ or clang++).

```bash
g++ -std=c++20 -o zoork \
  main.cpp ZOOrkEngine.cpp Player.cpp Room.cpp \
  Item.cpp Character.cpp GameObject.cpp Passage.cpp \
  NullPassage.cpp NullRoom.cpp NullCommand.cpp \
  RoomDefaultEnterCommand.cpp PassageDefaultEnterCommand.cpp \
  Location.cpp Door.cpp
```

Then run:

```bash
./zoork
```

---

## Project Structure

```
ZOOrk/
├── main.cpp                      ← Game map, rooms, items, entry point
├── ZOOrkEngine.h / .cpp          ← Game loop and command handlers
├── Player.h / .cpp               ← Player singleton with inventory
├── Room.h / .cpp                 ← Rooms with items and passages
├── Item.h / .cpp                 ← Collectible items
├── Character.h / .cpp            ← Base class for Player
├── GameObject.h / .cpp           ← Base class for all game objects
├── Passage.h / .cpp              ← Connections between rooms
├── Door.h / .cpp                 ← Locked door requiring a key item
├── Location.h / .cpp             ← Base class for Room and Passage
├── NullRoom.h / .cpp             ← Null object for invalid rooms
├── NullPassage.h / .cpp          ← Null object for invalid passages
├── NullCommand.h / .cpp          ← Null object for commands
├── RoomDefaultEnterCommand.h     ← Default room entry behaviour
└── PassageDefaultEnterCommand.h  ← Default passage entry behaviour
```

---

Starter code provided by Richard Skarbez. Extended with:
- look, take, drop, and inventory commands
- 10-room space station map with items
- Door class with keycard-based locking mechanic
- unlock and help commands
- UML class diagrams (Part 1 and Part 2)
