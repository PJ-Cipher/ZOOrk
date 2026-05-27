#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Item.h"
#include <memory>
#include "Door.h"




int main() {

    // === ROOMS ===

    std::shared_ptr<Room> airlock = std::make_shared<Room>("Airlock",
        "You are in the airlock of the ISS Nomad. Warning lights flash red. "
        "A cracked helmet visor lies on the floor. A keycard glints on the shelf. "
        "The station interior lies to the east.\n");

    std::shared_ptr<Room> corridor = std::make_shared<Room>("Corridor A",
        "A long metallic corridor stretches before you. Flickering strip lights "
        "cast eerie shadows. Passages lead north, south, east, and west. "
        "Scorch marks line the walls.\n");

    std::shared_ptr<Room> bridge = std::make_shared<Room>("Bridge",
        "The command bridge of the Nomad. Banks of monitors display static. "
        "A captain's chair sits in the centre, and star maps are scattered across the floor. "
        "A faint humming comes from somewhere below.\n");

    std::shared_ptr<Room> crew_quarters = std::make_shared<Room>("Crew Quarters",
        "Six bunk beds are bolted to the walls. Personal belongings float gently "
        "in the low gravity. A photo of Earth is pinned above one bunk. "
        "Something moved under one of the beds.\n");

    std::shared_ptr<Room> medical_bay = std::make_shared<Room>("Medical Bay",
        "Sterile white walls, now stained with something dark. Medical equipment "
        "is overturned. A biohazard container sits in the corner, sealed. "
        "The emergency light pulses weakly overhead.\n");

    std::shared_ptr<Room> research_lab = std::make_shared<Room>("Research Lab",
        "Sophisticated equipment lines the benches, much of it smashed. "
        "Holographic displays still flicker with alien glyphs. "
        "A reinforced door to the north is slightly ajar.\n");

    std::shared_ptr<Room> alien_chamber = std::make_shared<Room>("Alien Chamber",
        "You should not be here. The walls are covered in organic material that "
        "pulses with a soft blue glow. Strange pods line the walls. "
        "The air smells of something ancient.\n");

    std::shared_ptr<Room> cargo_hold = std::make_shared<Room>("Cargo Hold",
        "Massive crates are stacked to the ceiling, many cracked open. "
        "Supply containers drift lazily in zero gravity. "
        "Something large knocked these over from the inside.\n");

    std::shared_ptr<Room> engine_room = std::make_shared<Room>("Engine Room",
        "The roar of the engines is deafening. Pipes and conduits cover every "
        "surface. A wrench floats past your head. The reactor access hatch "
        "leads further down.\n");

    std::shared_ptr<Room> reactor_core = std::make_shared<Room>("Reactor Core",
        "Intense heat radiates from the glowing reactor. Warning alarms blare. "
        "You can see the reactor is critically overloaded. "
        "If someone does not fix this soon, the Nomad is doomed.\n");


    // === PASSAGES ===

    Passage::createBasicPassage(airlock.get(), corridor.get(), "east", true);
    Passage::createBasicPassage(corridor.get(), bridge.get(), "north", true);
    Passage::createBasicPassage(corridor.get(), medical_bay.get(), "east", true);
    Passage::createBasicPassage(corridor.get(), engine_room.get(), "south", true);
    Passage::createBasicPassage(corridor.get(), cargo_hold.get(), "west", true);
    Passage::createBasicPassage(bridge.get(), crew_quarters.get(), "north", true);
    Passage::createBasicPassage(medical_bay.get(), research_lab.get(), "east", true);
    // Locked door between research lab and alien chamber
    auto alienDoor = std::make_shared<Door>(
        "Alien Chamber Door",
        "A heavy reinforced door covered in alien markings.",
        research_lab.get(), alien_chamber.get(),
        "keycard"
    );
    research_lab.get()->addPassage("north", alienDoor);
    alien_chamber.get()->addPassage("south", 
        std::make_shared<Passage>("Return passage", 
            "The way back to the research lab.", 
            alien_chamber.get(), research_lab.get()));
    Passage::createBasicPassage(engine_room.get(), reactor_core.get(), "south", true);


    // === ITEMS ===

    Item* keycard = new Item("keycard",
        "A magnetic keycard stamped with the Nomad crew insignia. "
        "It looks like it could open something important.\n");

    Item* oxygen_tank = new Item("oxygen-tank",
        "A portable oxygen tank. Still has about 20 minutes of air left. "
        "Useful if you need to survive somewhere with no atmosphere.\n");

    Item* wrench = new Item("wrench",
        "A heavy titanium wrench. Standard issue for station maintenance. "
        "Could be used to fix — or break — machinery.\n");

    Item* alien_artifact = new Item("artifact",
        "A small crystalline object covered in glowing alien glyphs. "
        "It hums faintly in your hand and feels warm to the touch.\n");

    Item* flashlight = new Item("flashlight",
        "A heavy-duty torch. Battery is almost full. "
        "Useful in dark places.\n");

    airlock.get()->addItem(keycard);
    medical_bay.get()->addItem(oxygen_tank);
    engine_room.get()->addItem(wrench);
    research_lab.get()->addItem(alien_artifact);
    cargo_hold.get()->addItem(flashlight);


    // === START GAME ===

    ZOOrkEngine zoork(airlock);
    zoork.run();

    return 0;
}