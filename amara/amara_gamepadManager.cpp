namespace Amara {
    class GamepadManager {
    public:
        static int numGamepads;

        std::deque<Amara::Gamepad> gamepads;
        std::vector<Amara::Gamepad*> connected;
        std::vector<Amara::Gamepad*> disconnected;

        bool isActivated = false;

        GamepadManager() {}
        GamepadManager(Amara::GameProperties* gProperties): GamepadManager() {
            gamepads.clear();

            for (int i = 0; i < numGamepads; i++) {
                gamepads.push_back(Amara::Gamepad(gamepads.size()));
                Amara::Gamepad* gamepad = getLastGamepad();
                gamepad->setup();
            }
        }

        void connectGamepad(SDL_GameController* controller) {
            SDL_JoystickID id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.controller == nullptr && !gamepad.isConnected) {
                    gamepad.connect(controller);
                    connected.push_back(&gamepad);
                    SDL_Log("Game Info: Controller connected, Name: %s\n", SDL_GameControllerName(controller));
                    return;
                }
                else if (gamepad.id == id) {
                    return;
                }
            }
            
            gamepads.push_back(Amara::Gamepad(gamepads.size()));
            Amara::Gamepad* gamepad = getLastGamepad();
            gamepad->setup();
            gamepad->connect(controller);
            connected.push_back(gamepad);
            SDL_Log("Game Info: Controller connected, Name: %s\n", SDL_GameControllerName(controller));
        }

        void disconnectGamepad(SDL_GameController* controller) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.controller == controller) {
                    gamepad.disconnect();
                    SDL_Log("Game Info: Controller disconnected, Name: %s\n", SDL_GameControllerName(controller));
                    disconnected.push_back(&gamepad);
                    return;
                }
            }
        }

        int numConnected() {
            int count = 0;
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    count += 1;
                }
            }
            return count;
        }

        Amara::Gamepad* get(int index) {
            if (index < 0 || index >= gamepads.size()) {
                return nullptr;
            }
            return &gamepads[index];
        }

        Amara::Gamepad* get(SDL_GameController* controller) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.controller == controller) {
                    return &gamepad;
                }
            }
            return nullptr;
        }

        Amara::Gamepad* getLastGamepad() {
            return &gamepads[gamepads.size() - 1];
        }

        std::vector<Amara::Gamepad*> getJustConnected() {
            return connected;
        }

        std::vector<Amara::Gamepad*> getJustDisconnected() {
            return disconnected;
        }

        bool isDown(Amara::Buttoncode bcode) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    if (gamepad.isDown(bcode)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool justDown(Amara::Buttoncode bcode) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    if (gamepad.justDown(bcode)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool justUp(Amara::Buttoncode bcode) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    if (gamepad.justUp(bcode)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool tapped(Amara::Buttoncode bcode) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    if (gamepad.tapped(bcode)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool held(Amara::Buttoncode bcode) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    if (gamepad.held(bcode)) {
                        return true;
                    }
                }
            }
            return false;
        }

        int downTime(Amara::Buttoncode bcode) {
            int t = 0;
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    if (gamepad.downTime(bcode) > t) {
                        t = gamepad.downTime(bcode);
                    }
                }
            }
            return t;
        }

        bool activated(Amara::Buttoncode bcode) {
            for (Amara::Gamepad& gamepad: gamepads) {
                if (gamepad.isConnected && gamepad.controller != nullptr) {
                    if (gamepad.activated(bcode)) {
                        return true;
                    }
                }
            }
            return false;
        }

        void manage() {
            connected.clear();
            disconnected.clear();
            for (Amara::Gamepad& gamepad: gamepads) {
                gamepad.manage();
            }
            isActivated = false;
        }
    };
    int GamepadManager::numGamepads = 4;
}