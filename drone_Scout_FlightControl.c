#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Define your drone control parameters
struct DroneControl {
    float throttle;
    float aileron;
    float elevator;
    float rudder;
};

// Function to initialize SDL and the joystick
int initializeSDL(SDL_Joystick **joystick) {
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Check for joysticks
    if (SDL_NumJoysticks() < 1) {
        fprintf(stderr, "No joystick connected!\n");
        return 0;
    }

    // Open joystick
    *joystick = SDL_JoystickOpen(0);
    if (*joystick == NULL) {
        fprintf(stderr, "Unable to open joystick! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    printf("Joystick connected: %s\n", SDL_JoystickName(*joystick));
    return 1;
}

// Function to handle joystick input
void handleJoystick(SDL_Joystick *joystick, struct DroneControl *droneControl) {
    // Read joystick axes
    droneControl->throttle = SDL_JoystickGetAxis(joystick, 1) / 32767.0; // Throttle
    droneControl->aileron = SDL_JoystickGetAxis(joystick, 0) / 32767.0;  // Aileron
    droneControl->elevator = SDL_JoystickGetAxis(joystick, 4) / 32767.0; // Elevator
    droneControl->rudder = SDL_JoystickGetAxis(joystick, 3) / 32767.0;    // Rudder

    // You can add additional logic to map joystick values to drone control values
}

int main() {
    SDL_Joystick *joystick = NULL;
    struct DroneControl droneControl;

    if (!initializeSDL(&joystick)) {
        return 1;
    }

    // Main loop
    while (1) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        handleJoystick(joystick, &droneControl);

        // Add logic here to send droneControl values to your drone

        // Print joystick values for testing
        printf("Throttle: %.2f, Aileron: %.2f, Elevator: %.2f, Rudder: %.2f\n",
               droneControl.throttle, droneControl.aileron, droneControl.elevator, droneControl.rudder);

        SDL_Delay(20); // Add a small delay to control loop speed
    }

    // Close joystick
    SDL_JoystickClose(joystick);

    // Quit SDL
    SDL_Quit();

    return 0;
}