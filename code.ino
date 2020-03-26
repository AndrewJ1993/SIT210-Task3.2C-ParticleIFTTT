#define LIGHT_PIN A0 // Replace A0 with your pin 
#define LIGHT_LEVEL_HIGH_THRESHOLD 800 // Replace with your own light level 
#define LIGHT_LEVEL_LOW_THRESHOLD 200
void setup() {
} 

// The light level is simulated by incrementing the light level every two seconds until it reaches the threshold. After which, an email is sent and the light will progressively decrement 
// every 5 seconds until it is below the low threshold, then another email is sent. The max_light_reached boolean is used to prevent the device sending an email every iteration of the loop
// before it ever reached the maximum light threshold.
void loop() { 
    int light_level = 700;
    bool max_light_reached = false;
    while (true) {
        if (light_level > LIGHT_LEVEL_HIGH_THRESHOLD) { 
            Particle.publish("light-level-changed", "bright"); 
            max_light_reached = true;
            
            while (light_level > LIGHT_LEVEL_LOW_THRESHOLD) {
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
} 
