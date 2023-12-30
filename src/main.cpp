#include <iostream>
#include <raylib.h>
#include <math.h>
#include "lib/objets.hpp"

float frametime;
int ball_amount = 20;
int stopcount = 0;
int framecount = 0;
int living_balls = 0;
int collision_quality = 10;


int main()
{
     SetTargetFPS(60);
    //SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "Collision detection");

    Ball ball[ball_amount];
    ball[0].simple_spawn();
    //ball[1].CalcSpeed = true;
    /*
    for (int i = 0; i < ball_amount; i++)
    {
        ball[i].randomspawn();
    }*/
    

    while (!WindowShouldClose())
    {
        frametime = GetFrameTime();
        if (IsKeyPressed(KEY_R))
        {
            for (int i = 1; i < ball_amount; i++)
            {
                ball[i].safespawn(i);
            }
        }

        if (IsKeyPressed(KEY_G)) {
            for (int i = 1; i < ball_amount; i++) {
                ball[i].toggle_gravity();
            }

        }

        if (IsKeyDown(KEY_S)) {
            if (living_balls < 20) {
                collision_quality = living_balls;
            }
            if (living_balls < ball_amount) {
                ball[living_balls].simple_spawn();
                living_balls++;

            } else {
                living_balls = 0;
            }
            
        }


        if (IsKeyPressed(KEY_Q)) {
            if (collision_quality < 30) {
                collision_quality += 1;
            }  else {
                collision_quality = 1;
            }
        }

        if (IsKeyPressed(KEY_E)) {
            collision_quality = 1;
        }
        for (int i = 1; i < ball_amount; i++) {
                ball[i].update_velocity(frametime);
        }
        ball[0].follow_cursor();

        //std::cout << "\n\nxDistance: " << ball[0].distancex(ball[1].Position()) << "\nDistancey: " << ball[0].distancey(ball[1].Position()) << "\n";
        for (int collida = 0; collida < ball_amount; collida++) {
            for (int collidb = 0; collidb < ball_amount; collidb++) {
                // std::clog << "Checking: " << collida << " contact with: " <<collidb <<"\n\n";
                if (collida != collidb) {
                    for (int i = 0; i < collision_quality; i++) {

                        if (ball[collida].is_clipping_with(ball[collidb].Position()) || ball[collidb].is_clipping_with(ball[collida].Position())) {
                            //std::clog << collida << " contact with: " << collidb << "\n\n";

                            ball[collida].fix_clipping_with(ball[collidb].Position());
                            ball[collidb].fix_clipping_with(ball[collida].Position());

                            /*
                            ball[collida].x_bounce();
                            ball[collidb].x_bounce();
                            */

                        }
                    }


                }
            }
        }

        BeginDrawing();
        if (framecount < 1)
        {
            framecount++;
        }
        else
        {
            framecount++;
            ClearBackground(BLACK);
            // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.2));
            DrawFPS(10, 10);
            DrawText(TextFormat("Collision Quality Level: %d",collision_quality), 50, 50, 10, RED);

            for (int i = 0; i < ball_amount; i++)
            {
                ball[i].update_velocity(frametime);
                ball[i].draw();
            }
        }

        EndDrawing();
    }
    return 0;
}