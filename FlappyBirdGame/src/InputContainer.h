#pragma once
#include <map>
#include <SDL.h>

class InputContainer {
public:

    enum InputKey {
        INPUTKEY_RIGHT_ARROW,
        INPUTKEY_LEFT_ARROW,
        INPUTKEY_UP_ARROW,
        INPUTKEY_DOWN_ARROW,
        INPUTKEY_SPACE,
        INPUTKEY_ESCAPE,
        INPUTKEY_F1
    };

    // Static method to access the singleton instance
    static InputContainer& GetInstance() {
        static InputContainer instance;
        return instance;
    }

    // Prevent copying and assignment
    InputContainer(const InputContainer&) = delete;
    InputContainer& operator=(const InputContainer&) = delete;


    // Update the state of all keys
    void update() {

        //static const unsigned char* keys = SDL_GetKeyboardState(NULL);
        SDL_Event e;
        static int mx = -1, my = -1;

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                _user_quitted = true;
                return;
            case SDL_KEYDOWN:
                read_key_down(e.key.keysym.sym);
            case SDL_KEYUP:
                read_key_up(e.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                mx = e.motion.x;
                my = e.motion.y;
                break;
            }
        }

        if (currentKeyStates != nullptr) {
            // Copy the current key states into the previous key states array
            memcpy(previousKeyStates, currentKeyStates, SDL_NUM_SCANCODES);
        }

        // Fetch the latest keyboard state for the current frame
        currentKeyStates = SDL_GetKeyboardState(NULL);
    }

    void read_key_down(SDL_Keycode key)
    {
        switch (key) {
        case SDLK_LEFT:
            break;
        case SDLK_RIGHT:
            break;
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        default:
            break;
        }
    }

    void read_key_up(SDL_Keycode key)
    {
        switch (key) {
        case SDLK_LEFT:
            break;
        case SDLK_RIGHT:
            break;
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        default:
            break;
        }
    }

    bool user_quitted() {
        return _user_quitted;
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
    // Singleton
    InputContainer() : currentKeyStates(nullptr) {
        memset(previousKeyStates, 0, SDL_NUM_SCANCODES);  // Initialize previous states to 0
    }

    // States
    const Uint8* currentKeyStates = nullptr;  // Pointer to the current state of the keyboard
    Uint8 previousKeyStates[SDL_NUM_SCANCODES] = { 0 };  // Array to store the previous state of the keyboard
    bool _user_quitted = false;

    // Config
    std::map<InputKey, SDL_Scancode> keyMap = {
        {INPUTKEY_RIGHT_ARROW, SDL_SCANCODE_RIGHT},
        {INPUTKEY_LEFT_ARROW, SDL_SCANCODE_LEFT},
        {INPUTKEY_UP_ARROW, SDL_SCANCODE_UP},
        {INPUTKEY_DOWN_ARROW, SDL_SCANCODE_DOWN},
        {INPUTKEY_SPACE, SDL_SCANCODE_SPACE},
        {INPUTKEY_ESCAPE, SDL_SCANCODE_ESCAPE},
        {INPUTKEY_F1, SDL_SCANCODE_F1}
    };
};

