#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define constants
#define TARGET_DISTANCE_THRESHOLD 3.0
#define PROPORTIONAL_GAIN 0.1

// Drone state
struct Drone {
    double x;           // Drone's x-coordinate
    double y;           // Drone's y-coordinate
    double heading;     // Drone's heading (in radians)
    double speed;       // Drone's speed
};

// Target state
struct Target {
    double x;           // Target's x-coordinate
    double y;           // Target's y-coordinate
    double heading;     // Target's heading (in radians)
    double speed;       // Target's speed
};

// Function to calculate distance between two points
double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to update drone's position and heading based on guidance
void updateDrone(struct Drone *drone, struct Target *target) {
    // Calculate angle to target
    double angleToTarget = atan2(target->y - drone->y, target->x - drone->x);

    // Calculate distance to target
    double distanceToTarget = calculateDistance(drone->x, drone->y, target->x, target->y);

    // Calculate heading error
    double headingError = angleToTarget - drone->heading;

    // Proportional control to adjust heading and speed
    drone->heading += PROPORTIONAL_GAIN * headingError;
    drone->speed = distanceToTarget; // Adjust speed to close in on the target
}

int main() {
    struct Drone chaser = {0.0, 0.0, 0.0, 1.0};  // Initial position, heading, and speed of the chaser
    struct Target target = {10.0, 10.0, 0.0, 0.5}; // Initial position, heading, and speed of the target

    // Main loop
    while (1) {
        // Update drone based on guidance
        updateDrone(&chaser, &target);

        // Print drone and target information (for testing)
        printf("Chaser: x=%.2f, y=%.2f, heading=%.2f, speed=%.2f\n", chaser.x, chaser.y, chaser.heading, chaser.speed);
        printf("Target: x=%.2f, y=%.2f, heading=%.2f, speed=%.2f\n", target.x, target.y, target.heading, target.speed);

        // Check for interception
        if (calculateDistance(chaser.x, chaser.y, target.x, target.y) < TARGET_DISTANCE_THRESHOLD) {
            printf("Interception successful!\n");
            break;
        }

        // Add simulation delay (adjust as needed)
        usleep(100000); // 100ms delay
    }

    return 0;
}