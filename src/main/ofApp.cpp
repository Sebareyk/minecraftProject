#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup() {
    this->instantiator = new ItemHandler();
    this->player = new Player();
    this->chestState = new ChestState(player);
    this->craftingState = new CraftingState(player,instantiator);
    this->furnaceState = new FurnaceState(player,instantiator);
    this->generatorState= new GeneratorState(player,instantiator);
    this->enchantingState = new EnchantingState(player, instantiator);

    this->relaxingMusic.load("audio/miceOnVenus.mp3");
    this->relaxingMusic.play();

    giveItems();
    this->currentState = chestState;
}

/**
 * Handles mouse press events and manages state transitions.
 * 
 * This method is called whenever a mouse button is pressed. It delegates the event to the current state's
 * mousePressed method and checks if the left mouse button (button 0) was pressed. If so, it iterates through
 * the StateButtons and checks if any button was pressed. If a button is pressed, it changes the current state
 * to the target state of the button and plays the button's sound effect.
 * 
 * Basics of the state machine:
 * - The state machine consists of different states (e.g., "chest", "crafting", "furnace").
 * - Transitions between states occur based on user interactions with StateButton objects.
 * - Each state can have its own behavior and actions.
 * - The current state determines the system's behavior at any given time.
 * 
 * @param x The x-coordinate of the mouse cursor.
 * @param y The y-coordinate of the mouse cursor.
 * @param button The mouse button that was pressed (0 for left button, 2 for right button).
 */
void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x,y,button);
    if (button == 0) {
        // Iterate through StateButtons
        for (auto stateButton : player->getStateButtons()) {
            if (stateButton.onPress(x,y)) {
                if (stateButton.getTargetState() == "chest") {
                    this->currentState = chestState;
                }
                else if (stateButton.getTargetState() == "crafting") {
                    this->currentState = craftingState;
                }
                else if (stateButton.getTargetState() == "furnace") {
                    this->currentState = furnaceState;
                }
                else if (stateButton.getTargetState() == "generator") {
                    this->currentState = generatorState;
                }
                else if (stateButton.getTargetState() == "enchanting"){
                    this->currentState = enchantingState;
                }
                stateButton.playSoundEffect();
            }
        }
    }
}
void ofApp::update() { 
    if (!relaxingMusic.isPlaying()) relaxingMusic.play();
        currentState->update();
    }
void ofApp::draw() { currentState->draw();}
void ofApp::mouseMoved(int x, int y) { currentState->mouseMoved(x,y); }

void ofApp::keyPressed(int key) { 
    if (key == 'b' || key == 'B') {debugTool(1);} // Beacon Test
    if (key == 'e' || key == 'E') {debugTool(2);} // Ender Weapon Test
    if (key == 't' || key == 'T') {debugTool(3);} // Enchantment Table and Book Crafting Test
    if (key == 'x' || key == 'X') {debugTool(4);} // Enchanting a Book and Sword Test
    currentState->keyPressed(key); }

void ofApp::debugTool(int debug_num){
    if (debug_num == 1) { 
        // Beacon Items
        this->player->addItem(instantiator->getItemFromNumber(40), 5);
        this->player->addItem(instantiator->getItemFromNumber(41), 3);
        this->player->addItem(instantiator->getItemFromNumber(37), 1);
    } else if (debug_num == 2){ 
        // Ender Weapon Items
        this->player->addItem(instantiator->getItemFromNumber(42), 5);
        this->player->addItem(instantiator->getItemFromNumber(50), 16);
        this->player->addItem(instantiator->getItemFromNumber(50), 16);
        this->player->addItem(instantiator->getItemFromNumber(50), 16);
        this->player->addItem(instantiator->getItemFromNumber(50), 16);
        // Weapons
        this->player->addItem(instantiator->getItemFromNumber(8),1);
        this->player->addItem(instantiator->getItemFromNumber(13),1);
        this->player->addItem(instantiator->getItemFromNumber(18), 1);
        this->player->addItem(instantiator->getItemFromNumber(23), 1);
        this->player->addItem(instantiator->getItemFromNumber(28), 1);
    } else if (debug_num == 3){ 
        // Paper Items
        this->player->addItem(instantiator->getItemFromNumber(68), 64);
        // Book Items
        this->player->addItem(instantiator->getItemFromNumber(62), 64);
        this->player->addItem(instantiator->getItemFromNumber(63), 64);
        // Enchantment Table Items
        this->player->addItem(instantiator->getItemFromNumber(64), 64);
        this->player->addItem(instantiator->getItemFromNumber(41), 64);
        this->player->addItem(instantiator->getItemFromNumber(36), 64);
    } else if (debug_num == 4) {
        // Items to create an Enchanted Book
        this->player->addItem(instantiator->getItemFromNumber(65), 1);
        this->player->addItem(instantiator->getItemFromNumber(66), 64);
        // Items to Enchant a Sword with Sharpness
        this->player->addItem(instantiator->getItemFromNumber(59), 1);
        Item enchantedBook = instantiator->getItemFromNumber(67); // Spawns the Enchanted Book
        enchantedBook.setEnchantments("Sharpness"); //Sets its Enchantment to Sharpness
        this->player->addItem(enchantedBook, 1); // Adds it to the player's inventory
    }
}

// Helper function that gives the player, or the chest, items.
void ofApp::giveItems() {
    this->player->addItem(instantiator->getItemFromNumber(55), 1, 26);

    // adds wooden tools to chest state
    this->chestState->addItem(instantiator->getItemFromNumber(2), 4,0);
    this->chestState->addItem(instantiator->getItemFromNumber(15), 1, 1);
    this->chestState->addItem(instantiator->getItemFromNumber(5), 1, 2);
    this->chestState->addItem(instantiator->getItemFromNumber(10), 1, 3);
    this->chestState->addItem(instantiator->getItemFromNumber(20), 1, 4);
    this->chestState->addItem(instantiator->getItemFromNumber(25), 1, 5);
}

//------------------UNUSED--------------------------------------
void ofApp::keyReleased(int key) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}