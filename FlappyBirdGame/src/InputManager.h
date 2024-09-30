#pragma once
#include <map>
#include <SDL.h>

class InputManager {
public:

    enum InputKey {
        RIGHT_ARROW,
        LEFT_ARROW,
        UP_ARROW,
        DOWN_ARROW,
        SPACE,
        ESCAPE
    };

    // Static method to access the singleton instance
    static InputManager& GetInstance() {
        static InputManager instance;
        return instance;
    }

    // Prevent copying and assignment
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;


    // Update the state of all keys
    void update() {

        if (currentKeyStates != nullptr) {
            // Copy the current key states into the previous key states array
            memcpy(previousKeyStates, currentKeyStates, SDL_NUM_SCANCODES);
        }

        // Fetch the latest keyboard state for the current frame
        currentKeyStates = SDL_GetKeyboardState(NULL);
    }

    // Check if a specific key is currently being pressed
    bool is_key_pressed(InputKey key) {
        if (keyMap.find(key) != keyMap.end()) {
            return currentKeyStates[keyMap[key]];  // Check the SDL scancode in the current state
        }
        return false;
    }

    // Check if a specific key was just pressed down (rising edge)
    bool is_key_just_pressed(InputKey key) {
        if (keyMap.find(key) != keyMap.end()) {
            return currentKeyStates[keyMap[key]] && !previousKeyStates[keyMap[key]];
        }
        return false;
    }

    // Check if a specific key was just released (falling edge)
    bool is_key_just_released(InputKey key) {
        if (keyMap.find(key) != keyMap.end()) {
            return !currentKeyStates[keyMap[key]] && previousKeyStates[keyMap[key]];
        }
        return false;
    }

private:
    // Private constructor for singleton pattern
    InputManager() : currentKeyStates(nullptr) {
        memset(previousKeyStates, 0, SDL_NUM_SCANCODES);  // Initialize previous states to 0
    }
    const Uint8* currentKeyStates = nullptr;  // Pointer to the current state of the keyboard
    Uint8 previousKeyStates[SDL_NUM_SCANCODES] = { 0 };  // Array to store the previous state of the keyboard

    std::map<InputKey, SDL_Scancode> keyMap = {
        {RIGHT_ARROW, SDL_SCANCODE_RIGHT},
        {LEFT_ARROW, SDL_SCANCODE_LEFT},
        {UP_ARROW, SDL_SCANCODE_UP},
        {DOWN_ARROW, SDL_SCANCODE_DOWN},
        {SPACE, SDL_SCANCODE_SPACE},
        {ESCAPE, SDL_SCANCODE_ESCAPE}
    };
};

