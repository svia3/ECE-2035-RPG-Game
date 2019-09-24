#include "graphics.h"

#include "globals.h"
char player[] = {
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
};

char spike[] = {
    'O', 'O', 'O', 'O', 'O', '5', 'O', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'O', '5', 'O', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', '5', 'R', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'R', '5', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'R', '5', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', '5', 'R', '5', '5', 'W', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'R', '5', '5', '5', '5', 'O', 'O', 'O',
    
    'O', 'O', '5', '5', 'R', '5', '5', '5', '5', 'O', 'O',
    
    'O', 'O', '5', '5', '5', '5', '5', '5', '5', 'O', 'O',
    
    'O', '5', '5', '5', '5', '5', '5', '5', '5', '5', 'O',
    
    'O', '5', '5', '5', '5', '5', '5', '5', '5', '5', 'O',
};

char heart[] = {
    'O', 'R', 'R', 'R', 'O', 'O', 'O', 'R', 'R', 'R', 'O',
    
    'R', 'R', 'W', 'R', 'R', 'O', 'R', 'R', 'R', 'R', 'R',
    
    'R', 'W', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    
    'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    
    'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    
    'O', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'O',
    
    'O', 'O', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'O', 'O',
    
    'O', 'O', 'O', 'R', 'R', 'R', 'R', 'R', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'R', 'R', 'R', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'O', 'R', 'O', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'
};

char crown[] = {
    'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'O', 'Y', 'O', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'Y', 'P', 'Y', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'O', 'Y', 'O', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'O', 'Y', 'O', 'O', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'O', 'Y', 'Y', 'Y', 'O', 'Y', 'Y', 'Y',
    
    'Y', 'Y', 'Y', 'Y', 'Y', 'O', 'Y', 'Y', 'Y', 'Y', 'Y',
    
    'Y', 'P', 'P', 'Y', 'Y', 'P', 'Y', 'Y', 'P', 'P', 'Y',
    
    'O', 'Y', 'P', 'Y', 'Y', 'P', 'Y', 'Y', 'P', 'Y', 'O',
    
    'O', 'O', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'O', 'O',
    
    'O', 'O', 'O', 'Y', 'Y', 'Y', 'Y', 'Y', 'O', 'O', 'O'
};

char sword[] = {
    'O', 'O', 'O', 'O', 'O', '5', 'O', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'W', '5', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'W', '5', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'W', '5', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'W', '5', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'W', '5', 'W', 'O', 'O', 'O', 'O',
    
    'O', 'L', 'O', 'W', 'W', '5', 'W', 'W', 'O', 'L', 'O',
    
    'O', 'O', 'L', 'L', 'W', '5', 'W', 'L', 'L', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'L', 'Y', 'L', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'L', 'Y', 'L', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'L', 'Y', 'L', 'O', 'O', 'O', 'O'
};

char shield[] = {
    'O', 'O', '5', '5', '5', '5', '5', '5', '5', 'O', 'O',
    
    'O', 'O', '5', 'P', 'P', '5', 'P', 'P', '5', 'O', 'O',
    
    'O', 'O', '5', 'P', 'P', '5', 'P', 'P', '5', 'O', 'O',

    'O', 'O', '5', 'P', 'P', '5', 'P', 'P', '5', 'O', 'O',
    
    'O', 'O', '5', 'P', 'P', '5', 'P', 'P', '5', 'O', 'O',
    
    'O', 'O', '5', 'P', 'P', '5', 'P', 'P', '5', 'O', 'O',
    
    'O', 'O', '5', 'P', 'P', '5', 'P', 'P', '5', 'O', 'O',
    
    'O', 'O', '5', 'P', 'P', '5', 'P', 'P', '5', 'O', 'O',
    
    'O', 'O', 'O', '5', 'O', '5', 'O', '5', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', '5', '5', '5', 'O', 'O', 'O', 'O',
    
    'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'
};

char wall[] = {
    '5', '5', '5', '5', '5', '5', '5', '5', '5', '5', '5',
    
    '5', 'L', 'L', 'L', 'W', 'W', 'W', 'L', 'L', 'L', '5',
    
    '5', 'L', 'L', 'L', 'W', 'W', 'W', 'L', 'L', 'L', '5',
    
    '5', 'L', 'L', 'L', 'W', 'W', 'W', 'L', 'L', 'L', '5',
    
    '5', 'W', 'W', 'W', 'L', 'L', 'L', 'W', 'W', 'W', '5',
    
    '5', 'W', 'W', 'W', 'L', 'L', 'L', 'W', 'W', 'W', '5',
    
    '5', 'W', 'W', 'W', 'L', 'L', 'L', 'W', 'W', 'W', '5',
    
    '5', 'L', 'L', 'L', 'W', 'W', 'W', 'L', 'L', 'L', '5',
    
    '5', 'L', 'L', 'L', 'W', 'W', 'W', 'L', 'L', 'L', '5',
    
    '5', 'L', 'L', 'L', 'W', 'W', 'W', 'L', 'L', 'L', '5',
    
    '5', '5', '5', '5', '5', '5', '5', '5', '5', '5', '5',
};

char stairs[] = {
    'Y', 'Y', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
    
    'Y', 'Y', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'O', 'O', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'O', 'O', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'O', 'O', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'O',
    
    'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'O',
    
    'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
};

char door[] = {
    'O', 'O', 'K', 'K', 'K', 'K', 'K', 'K', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'D', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'D', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'D', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'Y', 'Y', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'Y', 'Y', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'D', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'D', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'D', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'D', 'D', 'K', 'D', 'D', 'K', 'O', 'O',
    
    'O', 'O', 'K', 'K', 'K', 'K', 'K', 'K', 'K', 'O', 'O',
};

char plant[] = {
    'D', 'D', 'D', 'D', 'G', 'D', 'D', 'D', 'D', 'D', 'D',
    
    'D', 'D', 'D', 'D', 'G', 'G', 'G', 'G', 'D', 'D', 'D',
    
    'D', 'D', 'G', 'G', 'G', 'G', 'G', 'G', 'D', 'D', 'D',
    
    'D', 'D', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'D', 'D',
    
    'D', 'D', 'D', 'G', 'G', 'G', 'G', 'G', 'G', 'D', 'D',
    
    'D', 'D', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'D',
    
    'D', 'D', 'D', 'D', 'X', 'G', 'G', 'X', 'G', 'D', 'D',
    
    'D', 'D', 'D', 'D', 'X', 'X', 'X', 'X', 'D', 'D', 'D',
    
    'D', 'D', 'D', 'D', 'X', 'X', 'X', 'X', 'D', 'D', 'D',
    
    'D', 'D', 'D', 'D', 'X', 'X', 'X', 'X', 'D', 'D', 'D',
    
    'D', 'D', 'D', 'X', 'X', 'X', 'X', 'X', 'X', 'D', 'D',
};

char doneNPC[] = {
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    
    'P', 'P', 'Y', 'Y', 'P', 'P', 'P', 'Y', 'Y', 'P', 'P',
    
    'P', 'P', 'Y', 'Y', 'P', 'P', 'P', 'Y', 'Y', 'P', 'P',
    
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    
    'P', 'Y', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'Y', 'P',
    
    'P', 'P', 'Y', 'P', 'P', 'P', 'P', 'P', 'Y', 'P', 'P',
    
    'P', 'P', 'Y', 'Y', 'P', 'P', 'P', 'Y', 'Y', 'P', 'P',
    
    'P', 'P', 'P', 'Y', 'Y', 'Y', 'Y', 'Y', 'P', 'P', 'P',
    
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
};
void draw_player(int u, int v, int key)
{
    draw_img(u, v, player);
}

#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   BROWN
#define WHITE  0xFFFFFF
#define NOTHING 0x00000000
#define LIGHTBLUE 0x7ccee2
#define PURPLE 0xb929e5
#define LIGHTBROWN 0x915c35
#define DARKBROWN  0x5b2c0a
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'W') colors[i] = WHITE; 
        else if (img[i] == 'O') colors[i] = NOTHING;
        else if (img[i] == 'L') colors[i] = LIGHTBLUE;
        else if (img[i] == 'P') colors[i] = PURPLE;
        else if (img[i] == 'K') colors[i] = LIGHTBROWN;
        else if (img[i] == 'X') colors[i] = DARKBROWN;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

//void draw_img_updated(int u, int v, const int* img) {
//    for (int i = 0; i < 121; i++) {
//        uLCD.BLIT(u, v, 11, 11, img[i]);
//    }
//    wait_us(250); // Recovery time!
//}
    
    
void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_start () 
{
    uLCD.text_string("Stephen's quest!", 2, 3, FONT_7X8, WHITE);
    uLCD.text_string("Press Start", 3, 6, FONT_7X8, WHITE);
}

void draw_wall(int u, int v)
{
    draw_img(u, v, wall);
}

void draw_crown(int u, int v)
{
    draw_img(u, v, crown);
}

void draw_sword(int u, int v) 
{
    draw_img(u, v, sword);    
}

void draw_shield(int u, int v) 
{
    draw_img(u, v, shield);   
}

void draw_stairs(int u, int v) 
{
    draw_img(u, v, stairs);
}

void draw_door(int u, int v) 
{
    draw_img(u, v, door);
}

void draw_spike(int u, int v)
{
    draw_img(u, v, spike);   
}
// FIX THIS
void draw_plant(int u, int v)
{
    draw_img(u, v, plant);
}

void draw_dirt(int u, int v) 
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}
void draw_NPC(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLUE);   
}

void draw_health(int health)
{
     uLCD.filled_rectangle(70, 17, 120,20, WHITE);
     
     if (health == 100) {
         uLCD.filled_rectangle(70, 17, 120,20, RED);
     }
     if (health == 90) {
         uLCD.filled_rectangle(70, 17, 115,20, RED);
     }
     if (health == 80) {
         uLCD.filled_rectangle(70, 17, 110,20, RED);
     }
     if (health == 70) {
         uLCD.filled_rectangle(70, 17, 105,20, RED);
     }
     if (health == 60) {
         uLCD.filled_rectangle(70, 17, 100,20, RED);
     }
     if (health == 50) {
         uLCD.filled_rectangle(70, 17, 95,20, RED);
     }
     if (health == 40) {
         uLCD.filled_rectangle(70, 17, 90,20, RED);
     }
     if (health == 30) {
         uLCD.filled_rectangle(70, 17, 85,20, RED);
     }
     if (health == 20) {
         uLCD.filled_rectangle(70, 17, 80,20, RED);
     }
     if (health == 10) {
         uLCD.filled_rectangle(70, 17, 75,20, RED);
     }
     if (health == 0) {
         uLCD.filled_rectangle(70, 17, 70,20, RED);
     }
    uLCD.rectangle(70, 17, 120,20, WHITE);
}

void draw_lives(int lives)
{
    if (lives == 3) {
        draw_heart(92, 22);
        draw_heart(102, 22);
        draw_heart(112, 22);
    }
    if (lives == 2) {
        draw_heart(102, 22);
        draw_heart(112, 22);
    }
    if (lives == 1) {
        draw_heart(112, 22);
    }
    if (lives == 0) {
        return;
    }
}

void draw_heart(int u, int v) {
    draw_img(u, v, heart);
} 
void draw_upper_status()
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);

    // Add other status info drawing code here
}

void draw_lower_status(int x, int y)
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);
    uLCD.locate(0,15);
    uLCD.color(BLUE);
    uLCD.printf("(%d,%d)", x, y);
    
    // Add other status info drawing code here
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

void draw_inventory(int foundCrown, int foundShield, int foundSword) {
    uLCD.filled_rectangle(0, 98, 127, 130, BLACK);
    uLCD.filled_rectangle(2, 100, 125, 128, LGREY);
    uLCD.textbackground_color(LGREY);
    uLCD.locate(5,13);
    uLCD.printf("INVENTORY");
    if (foundCrown) {
        draw_crown(13, 113);
    }
    if (foundShield) {
        draw_shield(40, 113);
    }
    if (foundSword) {
        draw_sword( 70, 113);
    }
    wait(2);
    uLCD.filled_rectangle(0, 98, 127, 130, BLACK);
    uLCD.textbackground_color(BLACK);
}

void draw_doneNPC(int u, int v) {
    draw_img(u, v, doneNPC);
}
    


