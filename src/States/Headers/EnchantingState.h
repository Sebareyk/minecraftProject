#pragma once
#include "State.h"

/**
 * @class EnchantingState
 * @brief Represents the state of the game when the player infuses his tools with attributes.
 */
class EnchantingState : public State {
    private:
        ItemContainer toolContainer; ///< Container that holds the tool to be used.
        ItemContainer activatorContainer; //This slot is used for any book or Lapis Lazuli to confirm the enchantment.
        ItemContainer resultContainer; ///< Container that holds the resulting item.
        ItemHandler* instantiator; ///< Pointer to the item handler for item enchantment.
        vector<string> enchantments; // Holds all the enchantments in the game.
        vector<vector<int>> enchantmentList; ///< Holds the enchantments that are applicable to each weapon.
    public:
        /**
         * @brief Constructs a EnchantmentState object with a player and an item handler pointer.
         * @param player Player pointer.
         * @param instantiator Item handler pointer.
         */
        EnchantingState(Player* player, ItemHandler* instantiatr);

        /**
         * @brief Enchant an item based on the tool inside the toolContainer and the item in the activatorContainer.
         */
        void enchantItem();

        /**
         * @brief States the enchantment list for all tools that fit into the toolContainer.
         */
        void generateEnchantmentList();

        /**
         * @brief Updates the state. Mandatory implementation.
         */
        void update(){}; 

        /**
         * @brief Draws the generator state on the screen.
         */
        void draw();

        /**
         * @brief Handles mouse movement events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         */
        void mouseMoved(int x, int y);

        /**
         * @brief Handles mouse press events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         * @param button The mouse button that was pressed.
         */
        void mousePressed(int x, int y, int button);

        /**
         * @brief Handles key press events. Tries to generate an item when the 'g' key is pressed.
         * @param key The key that was pressed.
         */
        void keyPressed(int key) { if (key == 'i' || key == 'I') enchantItem(); }; // Use letter "i" since "e" is already taken.
};