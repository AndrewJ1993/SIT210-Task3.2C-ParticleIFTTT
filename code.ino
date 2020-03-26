#define LIGHT_PIN A0 // Replace A0 with your pin 
#define LIGHT_LEVEL_THRESHOLD 800 // Replace with your own light level 
#define THRESHOLD_SENSITIVITY 50 // higher number = lower sensitivity, lower number = higher sensitivity 
void setup() {
} 

// The light level is simulated by incrementing the light level every two seconds until it reaches the threshold. After which, an email is sent and the light will progressively decrement 
// every 5 seconds until it is below the threshold, then another email is sent. The max_light_reached boolean is used to prevent the device sending an email every iteration of the loop
// before it ever reached the maximum light threshold.
void loop(int light_level = 700, bool max_light_reached = false) { 
    if (light_level > LIGHT_LEVEL_THRESHOLD) { 
        Particle.publish("light-level-changed", "bright"); 
        max_light_reached = true;
        // Once dark is triggered, the threshold is temporarily shifted so that the state will not float between dark and bright when it's on the threshold. This is how street lights work.
        while (light_level > LIGHT_LEVEL_THRESHOLD - THRESHOLD_SENSITIVITY) {
            light_level -= 1;
            delay(5000);
        } 
    }
    if (max_light_reached) { 
        Particle.publish("light-level-changed", "dark"); 
        max_light_reached = false;
    }
    light_level += 1;
    delay(2000);
} 
