# ECE_6913_LAB3
 Traffic Light System

 The traffic light control system will operate in the following way:
• Both intersections will initially be red and the pedestrian light is red.
• After 10 seconds, the North-South light turns green, and the East-West light is red.
• After 20 seconds, the North-South light turns yellow for 3 seconds before turning red.
• After 5 seconds of red light at the North-South light, the East-West light turns green, and the North-South light remains red.
• After 20 seconds, the East-West light turns yellow for 3 seconds before turning red.
• After 5 seconds of red light, the system returns to the initial state of both lights being red.

### PIN setup instruction
    North-South RED use PIN 2
    North-South YELLOW use PIN 7
    North-South GREEN use PIN 8
    
    East-West RED use PIN 9
    East-West  RED use PIN 17
    East-West  RED use PIN 18

    Pedestrian RED use PIN 19
    Pedestrian GREEN use PIN 4
    
    Pedestrian button use PIN 15

### corner cases
 For this project, we assume that all four buttons are used the same stage (Pedestrian Stage)
 In the real life traffic, this setting may caused heavy traffic, because no matter pedestrian press the button on which intersection, the 4-way traffic light would turn red and cars stop.
 We could separate the pedestrian buttons into different sides, for example two button for north-south intersection, and other two button for east-west intersection. And when north-south pedestrian button pressed, we just interupt the east-west side traffic, and north-south keep go through the cars. when east-west pedestrian button pressed, we just interupt the north-south side traffic, and east-west keep go through the cars. 