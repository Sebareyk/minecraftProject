#include "EnchantingState.h"

EnchantingState::EnchantingState(Player* player, ItemHandler* instantiatr) : State(player){
    this->instantiator = instantiatr;
    this->background.load("images/states/enchanting.png");
    this->toolContainer = ItemContainer(144, 132);
    this->activatorContainer = ItemContainer(305, 132);
    this->resultContainer = ItemContainer(510, 132);
    this->generateEnchantmentList();
}

void EnchantingState::generateEnchantmentList(){
    // This is a similar process to the Loot Tables in the generator, in which every item has a set of enchantments they may use.
    // This next line states all the Enchantments currently in the game.
    this->enchantments.assign({"none", "Looting", "Sharpness", "Efficiency", "Fire Aspect", "Knockback"});
    // 0 is no enchantment, 1 is Looting, 2 is Sharpness, 3 is Efficiency, 4 is Fire Aspect and 5 is Knockback
    // These next lines are the Lists that hold which enchantment can fit into a weapon.
    this->enchantmentList.push_back({1,2,2,2,3,3,4,4,5,5,5,5}); // Book Enchantment List
    this->enchantmentList.push_back({1,1,3,3,3,5,5,5,5}); // Pickaxe Enchantment List
    this->enchantmentList.push_back({1,2,2,2,4,4}); // Sword Enchantment List
    this->enchantmentList.push_back({1,1,3,3,3,4,4,5,5}); // Axe Enchantment List
    this->enchantmentList.push_back({1,1,1,3,3}); // Shovel and Hoe Enchantment List
}

void EnchantingState::enchantItem(){
    // In this one I also used concepts similar to the Generator. 
    if (toolContainer.isEmpty() || activatorContainer.isEmpty()) return;
    // Note, to create an Enchanted Book, the items placed will be an Enchanting Table in the Tool slot, 
    // and 1 Lapis Lazuli in the Activator slot. 
    string toolName = this->toolContainer.getCurrentItem().getName(); // Tools Name
    string toolPreviousEnchantments = this->toolContainer.getCurrentItem().getEnchantments(); // The Tool's Previous Enchantments
    string newResultEnchantments = ""; // Initialize the variable for the new enchantments of the tool.
    int resultItemNumber = 0; // Air
    int resultItemEnchantmentNum = 0; // Set the randomizer for the enchantment
    int enchantmentListNumber = 0; // Initialize the selected Enchantment list to Book Enchantment
    bool alreadyDone = false; // Just a check for when the Resulting Enchantment has already been picked.
    // This next line checks if the item in the tool container is an Enchanting Table.
    if (toolContainer.getCurrentItem().getItemNumber() == 65) {
        if (activatorContainer.getCurrentItem().getItemNumber() == 66){ //Checks if the Activator is a Lapis Lazuli
            activatorContainer.deductOne(); // Removes 1 Lapis Lazuli
            resultItemNumber = 67; // Makes the result item to be an Enchanted Book
            enchantmentListNumber = 0; // Sets the list to the Book Enchantment list.
        } else {return;}
    } 
    // The next Few lines contain the Enchantment of each weapon. For example let's explain the first one.
    else if (toolName.find("Pickaxe") != string::npos) { // This checks if the Tool is a pickaxe. 
        if (activatorContainer.getCurrentItem().getItemNumber() == 66 || activatorContainer.getItemCount() >= 9){ // This line checks if the item in the Activator slot is 9 Lapis Lazuli.
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber(); // This sets the result item to the same current tool.
            enchantmentListNumber = 1; // This sets the variable to the number of the Pickaxe Enchantments list 
            for (int i=0; i < 9; i++) { // Removes the 9 Lapis lazuli
                activatorContainer.deductOne(); 
            }
            toolContainer.deductOne(); // Eliminate the original Tool
        } else if (activatorContainer.getCurrentItem().getItemNumber()==67) { // This line checks if the item in the Activator slot is an Enchanted book.
            // Since the Book already has the desired enchantment we just add it to the other enchantments and get the enchantment we wanted.
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber(); // Again, sets the result item to the same current tool.
            if (toolPreviousEnchantments == "none"){ 
                newResultEnchantments = activatorContainer.getCurrentItem().getEnchantments(); // The book's enchantment is now the Tool's
            } else {
                if (toolPreviousEnchantments.find(activatorContainer.getCurrentItem().getEnchantments()) != string::npos){
                    newResultEnchantments = toolPreviousEnchantments + "I"; // If the enchantment is already in the tool, it updates it to a new level.
                } else {
                    newResultEnchantments = toolPreviousEnchantments + ", " + activatorContainer.getCurrentItem().getEnchantments(); // The book's enchantment plus the tool's
                }
            }
            alreadyDone = true; // Marks it as done so that later in the code we don't repeat the process and mess up the variable.
            activatorContainer.deductOne(); // Removes the Enchanted Book
            toolContainer.deductOne(); // Removes the original Tool
        } else {return;} // Just in case XD
    } 
    // The following codes do the exact same thing but for the different tool types.
    else if (toolName.find("Sword")!= string::npos) {
        if (activatorContainer.getCurrentItem().getItemNumber() == 66 || activatorContainer.getItemCount() >= 9){
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber();
            enchantmentListNumber = 2;
            for (int i=0; i < 9; i++) { 
                activatorContainer.deductOne(); 
            }
            toolContainer.deductOne();
        } else if (activatorContainer.getCurrentItem().getItemNumber()==67) {
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber();
            if (toolPreviousEnchantments == "none"){
                newResultEnchantments = activatorContainer.getCurrentItem().getEnchantments();
            } else {
                if (toolPreviousEnchantments.find(activatorContainer.getCurrentItem().getEnchantments()) != string::npos){
                    newResultEnchantments = toolPreviousEnchantments + "I";
                } else {
                    newResultEnchantments = toolPreviousEnchantments + ", " + activatorContainer.getCurrentItem().getEnchantments(); 
                }
            }
            alreadyDone = true;
            activatorContainer.deductOne();
            toolContainer.deductOne();
        } else {return;}
    } else if (toolName.find("Axe") != string::npos) {
        if (activatorContainer.getCurrentItem().getItemNumber() == 66 || activatorContainer.getItemCount() >= 9){
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber();
            enchantmentListNumber = 3;
            for (int i=0; i < 9; i++) { // Removes the 9 Lapis lazuli
                activatorContainer.deductOne(); 
            }
            toolContainer.deductOne();
        } else if (activatorContainer.getCurrentItem().getItemNumber()==67) {
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber();
            if (toolPreviousEnchantments == "none"){
                newResultEnchantments = activatorContainer.getCurrentItem().getEnchantments();
            } else {
                if (toolPreviousEnchantments.find(activatorContainer.getCurrentItem().getEnchantments()) != string::npos){
                    newResultEnchantments = toolPreviousEnchantments + "I";
                } else {
                    newResultEnchantments = toolPreviousEnchantments + ", " + activatorContainer.getCurrentItem().getEnchantments(); 
                }
            }
            alreadyDone = true;
            activatorContainer.deductOne();
            toolContainer.deductOne();
        } else {return;}
    } else if (toolName.find("Hoe") != string::npos || toolName.find("Shovel") != string::npos) {
        if (activatorContainer.getCurrentItem().getItemNumber() == 66 || activatorContainer.getItemCount() >= 9){
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber();
            enchantmentListNumber = 4;
            for (int i=0; i < 9; i++) { // Removes the 9 Lapis lazuli
                activatorContainer.deductOne(); 
            }
            toolContainer.deductOne();
        } else if (activatorContainer.getCurrentItem().getItemNumber()==67) {
            resultItemNumber = this->toolContainer.getCurrentItem().getItemNumber();
            if (toolPreviousEnchantments == "none"){
                newResultEnchantments = activatorContainer.getCurrentItem().getEnchantments();
            } else {
                if (toolPreviousEnchantments.find(activatorContainer.getCurrentItem().getEnchantments()) != string::npos){
                    newResultEnchantments = toolPreviousEnchantments + "I";
                } else {
                    newResultEnchantments = toolPreviousEnchantments + ", " + activatorContainer.getCurrentItem().getEnchantments(); 
                }
            }
            alreadyDone = true;
            activatorContainer.deductOne();
            toolContainer.deductOne();
        } else {return;}
    }

    // Creates the randomizer for the number enchantment
    // The odds for each tool are NOT dependant on its rarity. 
    int randomEnchantmentIndex = rand()%enchantmentList[enchantmentListNumber].size();
    resultItemEnchantmentNum = enchantmentList[enchantmentListNumber][randomEnchantmentIndex];

    if (resultItemEnchantmentNum != 0 && alreadyDone == false) {
        if (toolPreviousEnchantments == "none"){
            newResultEnchantments = enchantments[resultItemEnchantmentNum];
        } else {
            if (toolPreviousEnchantments.find(enchantments[resultItemEnchantmentNum]) != string::npos){
                newResultEnchantments = toolPreviousEnchantments + "I";
            } else {
                newResultEnchantments = toolPreviousEnchantments + ", " + enchantments[resultItemEnchantmentNum]; 
            }
        }
    }

    // Set the new item if the resultContainer it empty
    if (this->resultContainer.isEmpty()) {
        // The line 57 Gives the result Item its new Enchantments.
        Item resultItem = instantiator->getItemFromNumber(resultItemNumber);
        resultItem.setEnchantments(newResultEnchantments);
        resultContainer.setCurrentItem(resultItem);
        resultContainer.setItemCount(1);
    } // There is no need to check if the items can stack because the only outputs of this state are items with a stack size of 1.
}

                                                  
void EnchantingState::draw() {
    this->background.draw(0,0);
    this->toolContainer.draw();
    this->activatorContainer.draw();
    this->resultContainer.draw();
    this->getPlayer()->draw();
}

void EnchantingState::mouseMoved(int x,int y) {
    State::mouseMoved(x,y);
    // Check if the mouse enters any of the state's containers
    this->toolContainer.mouseEntered(x,y);
    this->resultContainer.mouseEntered(x,y);
    this->activatorContainer.mouseEntered(x,y);
}

void EnchantingState::mousePressed(int x, int y, int button) {
    State::mousePressed(x,y,button);
    if (button == 0) {
        // Only allow interaction if the player's container is empty
        if (this->getPlayer()->getCursorContainer().isEmpty()) this->resultContainer.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
        // Only allow interaction if the player's tool container is empty (extracting) or if the player's item is a tool
        if (this->getPlayer()->getCursorContainer().isEmpty() || this->getPlayer()->getCursorContainer().isTool()) this->toolContainer.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
        // Only allow interaction if the player's activating container is empty (extracting) or if the player's item is a Book, Enchanted Book or Lapis Lazuli.
        if (this->getPlayer()->getCursorContainer().isEmpty() || this->getPlayer()->getCursorContainer().getCurrentItem().getItemNumber() == 67 ||
            this->getPlayer()->getCursorContainer().getCurrentItem().getItemNumber() == 66 || this->getPlayer()->getCursorContainer().getCurrentItem().getItemNumber() == 64) {
                this->activatorContainer.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
            }
    }
    if (button == 2) {
        // Only allow interaction with the the player's container is empty. 
        if (this->getPlayer()->getCursorContainer().isEmpty()) this->resultContainer.rightMouseClicked(x,y,this->getPlayer()->getCursorContainer()); 
        // Only allow interaction if the player's container is empty (taking half) or if the player's item is a tool
        if (this->getPlayer()->getCursorContainer().isEmpty() || this->getPlayer()->getCursorContainer().isTool()) this->toolContainer.rightMouseClicked(x,y,this->getPlayer()->getCursorContainer());
        // Only allow interaction if the player's container is empty (taking half) or if the player's item is a Book, Enchanted book or Lapis Lazuli.
        if (this->getPlayer()->getCursorContainer().isEmpty() || this->getPlayer()->getCursorContainer().getCurrentItem().getItemNumber() == 67 ||
            this->getPlayer()->getCursorContainer().getCurrentItem().getItemNumber() == 66 || this->getPlayer()->getCursorContainer().getCurrentItem().getItemNumber() == 64) {
                this->activatorContainer.rightMouseClicked(x,y,this->getPlayer()->getCursorContainer());
            }
    }
}

