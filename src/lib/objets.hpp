#include <raylib.h>
#include <math.h>
#include <iostream>

class Ball {
    //position variables for calculating speed
    float lastXPos;
    float lastYPos;


    float xPos, 
    yPos, 
    xSpeed, 
    ySpeed;
    bool alive = false;
    Color mycolor;
    float gravity = 1;
    bool gravity_enabled = true;
    unsigned int radius = 15;
    float penetration;

    public:
    bool CalcSpeed=true;
    void randomspawn() {
        xPos=10, 
        yPos=30,
        xSpeed=0, 
        ySpeed=0;
        xPos = GetRandomValue(radius, 1000);
        //xSpeed = GetRandomValue(100, 500);
        //ySpeed = GetRandomValue(100, 500);
        mycolor = (Color){
            (unsigned char)GetRandomValue(10, 255),
            (unsigned char)GetRandomValue(10, 255),
            (unsigned char)GetRandomValue(10, 255),
            (unsigned char)GetRandomValue(10, 255),
        };
        alive = true;
    }


    void toggle_gravity() {
        if (gravity_enabled) {
            gravity_enabled = false;
        } else {
            gravity_enabled = true;
        }
    }


    void safespawn(int offset) {
        xPos=60*offset*2, 
        yPos=50,
        xSpeed=0,
        ySpeed=2;
        mycolor = WHITE;
        alive = true;
    }

    void simple_spawn() {
        xPos=10+GetRandomValue(0,20), 
        yPos=10,
        xSpeed=0,
        ySpeed=0;
        alive = true;
    }

    void follow_cursor() {
        mycolor = WHITE;
        xPos=GetMouseX();
        yPos=GetMouseY();
    }

    void update_velocity(float frametime) {
        //std::clog << frametime << "\n";
        //frametime = 0.016;//fix frametime for debugging
        if (alive) {
            lastXPos = xPos;
            lastYPos = yPos;


            xPos += xSpeed*frametime;
            yPos += ySpeed*frametime;

            ySpeed*=0.98;
            xSpeed*=0.98;
            

            //Never out of bounds
            if (yPos > GetScreenHeight()-(radius+1)) {
                yPos = GetScreenHeight()-(radius+1);
            }
            if (yPos < radius) {
                yPos = radius+1;
            }


            if (xPos > GetScreenWidth()-(radius+1)) {
                xPos = GetScreenWidth()-(radius+1);
                xSpeed*=-0.9;
            }
            if (xPos < radius+1) {
                xSpeed*=-0.9;
                xPos = radius+1;
            }

            
            
        }
        
    }
    void draw() {
        if (alive) {
            DrawCircle(xPos, yPos, radius, mycolor);
        }
    }

    Vector2 Position() {
        return (Vector2){xPos, yPos};
    }

    float distancex(Vector2 target) {
        float distancex = xPos-target.x;
        return distancex;
    }

    float distancey(Vector2 target) {
        float distancey = yPos-target.y;
        return distancey;
    }

    bool is_clipping_with(Vector2 target) {
        if (sqrtf(
            fabs(distancex(target))*fabs(distancex(target))+
            fabs(distancey(target))*fabs(distancey(target))) < radius*2) {
            
            return true;
        }
        else {
            return false;
        }
    }
    
    void fix_clipping_with(Vector2 target) {
        if (is_clipping_with(target)) {
            
        // Calculate the penetration depth
            penetration = radius * 2 - sqrt(distancex(target) * distancex(target) + distancey(target) * distancey(target));

            // Calculate the correction vector
            float correctionX = distancex(target) / sqrt(distancex(target) * distancex(target) + distancey(target) * distancey(target)) * penetration / 2;
            float correctionY = distancey(target) / sqrt(distancex(target) * distancex(target) + distancey(target) * distancey(target)) * penetration / 2;

            // Apply the correction to the positions of the balls
            
            xPos += correctionX;
            yPos += correctionY;


            if (CalcSpeed) {
                    //Gain Velocity from collision by calculating movement speed
                std::clog << yPos-lastYPos << ": Calculated yspeed\n";
                std::clog << xPos-lastXPos << ": Calculated xspeed\n";
                if (xPos != lastXPos) {
                   xSpeed -= (lastXPos-xPos);
                }
                if (yPos != lastYPos) {
                    ySpeed -= (lastYPos-yPos);

                }
                
            }
            
            
        }
    }
};