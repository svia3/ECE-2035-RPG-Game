// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"


// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map();
void init_second_map();
int main ();

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 */
 static int god = 0;
 static int gameOn = 1;
 static int sprint = 0;
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GOD_MODE 7
int get_action(GameInputs inputs)
{
    if (inputs.b1 == 0) {
        return GOD_MODE;
    }   
    if (inputs.b3 == 0) {
        return ACTION_BUTTON;
    }
    if (inputs.ax > .3) {
        return GO_RIGHT;
    } 
    if (inputs.ax < -.3) {
        return GO_LEFT; 
    }
    if (inputs.ay > .3) {
        return GO_UP;    
    } 
    if (inputs.ay < -.3) {
        return GO_DOWN;  
    }  
    if (inputs.b2 == 0) {
        if (sprint == 0) {
            sprint = 1;
        } else {
            sprint = 0;
        }
    }
    if (inputs.b4 == 0) {
        return MENU_BUTTON;
    }
    return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
void* gotKey = 0;
int talkedTo = 0;
int foundCrown = 0;
int foundSword = 0;
int foundShield = 0;
int gotStuff = 0;
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    MapItem* here = get_here(Player.x, Player.y);
    MapItem* north = get_north(Player.x, Player.y);
    MapItem* south = get_south(Player.x, Player.y);
    MapItem* east = get_east(Player.x, Player.y);
    MapItem* west = get_west(Player.x, Player.y);
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GOD_MODE:
            if (god == 0) {
                god = 1;
            } else {
                god = 0;
            }
        break;
        case GO_UP:  
            if (north -> walkable || god) {
                if (sprint) {
                    Player.y =  Player.y - 2;
                } else {
                    Player.y--; 
                }
                return FULL_DRAW;
        }
        break;
        case GO_LEFT:  
            if (west -> walkable || god) {
                if (sprint) {
                     Player.x =  Player.x - 2;
                } else {
                    Player.x--; 
                }
                return FULL_DRAW;
        }
        break;            
        case GO_DOWN:  
            if (south -> walkable || god) {
                if (sprint) {
                     Player.y =  Player.y + 2;
                } else {
                    Player.y++; 
                }
                return FULL_DRAW;
        }
        break;
        case GO_RIGHT:  
            if (east -> walkable || god) {
              if (sprint) {
                     Player.x =  Player.x + 2;
                } else {
                    Player.x++; 
                }
                return FULL_DRAW;
        }
        break;
        case ACTION_BUTTON: 
            if (here -> type == STAIRS) {
                if (talkedTo) {
                    init_second_map(); 
                    return FULL_DRAW;
                }
                break;
            }
            if (south -> type == NPC || west -> type == NPC) {
                if (talkedTo == 0 || (!gotStuff && talkedTo)) {
                    speech("Hello there!", "");
                    GameInputs in = read_inputs();
                    speech("We are under", "attack!");
                    in = read_inputs();
                    speech("I need you", "to find items.");
                    in = read_inputs();
                    speech("First, a token", "of my honor.");
                    in = read_inputs();
                    speech("Second, a barrier", "to protect.");
                    in = read_inputs();
                    speech("Lastly, a weapon", "to attack.");
                    in = read_inputs();
                    speech("Beware of ", "spikes!");
                    in = read_inputs();
                    speech("Good luck!", "");
                    talkedTo = 1;
                    break;
                } else if (gotStuff && talkedTo) {
                    south -> data = (void*) 1;
                    gotKey = (void*) 1;
                    speech("We are ready", "for war!");
                    GameInputs in = read_inputs();
                    speech("Thank you", "commrade!");
                    uLCD.locate(5, 6);
                    uLCD.color(RED);
                    uLCD.printf("YOU WIN");
                    gameOn = 0;
                    break;
                    
                }
            }
            if (south -> type == CROWN || east -> type == CROWN || north -> type == CROWN || west -> type == CROWN ) {
                speech ("A crown fit", "for a king!");
                erase_item(30, 5);
                foundCrown = 1;
                speaker.period(1.0/500.0); // 500hz period
                speaker = 0.3; //50% duty cycle - max volume
                wait(.5);
                speaker=0.0; // turn off audio
                if (foundCrown && foundSword && foundShield) {
                    speech("Find the door", "to return home!");
                    gotStuff = 1;
                }
            }
            if (south -> type == SHIELD || east -> type == SHIELD || north -> type == SHIELD || west -> type == SHIELD ) {
                if (foundCrown) {
                    speech ("Best offense is", "a strong defense!");
                    erase_item(28, 13);
                    foundShield = 1;
                    speaker.period(1.0/500.0); // 500hz period
                    speaker = 0.3; //50% duty cycle - max volume
                    wait(.5);
                    speaker=0.0; // turn off audio
                    if (foundCrown && foundSword && foundShield) {
                        speech("Find the door", "to return home!");
                        gotStuff = 1;
                    }
                } else {
                    speech ("Collect items", "in right order!");
                }
            }
            if (south -> type == SWORD || east -> type == SWORD || north -> type == SWORD || west -> type == SWORD ) {
                if (foundCrown && foundShield) {
                    speech ("Our enemies shall", "tremble!");
                    erase_item(14, 24);
                    foundSword = 1;
                    speaker.period(1.0/500.0); // 500hz period
                    speaker = 0.3; //50% duty cycle - max volume
                    wait(.5);
                    speaker=0.0; // turn off audio
                    if (foundCrown && foundSword && foundShield) {
                        speech("Find the door", "to return home!");
                        gotStuff = 1;
                    }
                } else {
                    speech ("Collect items", "in right order!");
                }
            }
            if (here -> type == DOOR) {
                if (foundCrown && foundSword && foundShield) {
                    set_active_map(0);
                    return FULL_DRAW;
                } else {
                    speech("You aren't", "leaving now");
                    GameInputs in = read_inputs();
                    speech("are you?", "");
                    break;
                }
            }
        break;
        case MENU_BUTTON:
            draw_inventory(foundCrown, foundShield, foundSword);
            return FULL_DRAW;
        default: break;
    }
    return NO_RESULT;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
 int health = 100;
 int lives = 3;
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    if (health == 0) {
        lives--;
        draw_lives(lives);
        if (lives == 0) {
            uLCD.locate(5, 6);
            uLCD.color(RED);
            uLCD.printf("GAME OVER");
            gameOn = 0;
        } else {
            uLCD.locate(5, 6);
            uLCD.color(RED);
            uLCD.printf("LOST A LIFE");
            wait(1);
            Player.x = 5;
            Player.y = 5;
            health = 100;
        }
    }       
    if (sprint) {
        uLCD.locate(0,0);
        uLCD.printf("Run ! ! !");
    } else {
        uLCD.locate(0,0);
        uLCD.printf("Walking...");
    }
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                draw_player(u, v, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        if (get_active_map() == get_map(0)) {
                            draw = draw_dirt;
                        } else {
                            draw = draw_nothing;
                        }
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }
    // Draw status bars    
   
    MapItem* item = get_here(Player.x, Player.y);
    if ((item -> type == PLANT || item -> type == SPIKE) && god == 0) {
        health = health - 10;
        uLCD.locate(12, 2);
        draw_health(health);
        draw_lives(lives);
    }
    uLCD.locate(12, 2);
    draw_health(health);
    draw_lives(lives);
    draw_upper_status();
    draw_lower_status(Player.x, Player.y);
    
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }
    add_NPC(15,16);
    add_stairs(18,15);
    add_wall(14, 14, VERTICAL, 3);
    add_wall(14, 17, HORIZONTAL, 6);
    add_wall(19, 14, VERTICAL, 3);
    
    pc.printf("plants\r\n");
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width() - 20,   0,              VERTICAL,   map_height()/5);
    add_wall(map_width() - 10,   0,              VERTICAL,   map_height()/5);
    add_wall(map_width() - 20,    map_height()/5,              HORIZONTAL,   3);
    add_wall(map_width() - 12,    map_height()/5,              HORIZONTAL,   3);
    pc.printf("Walls done!\r\n");
    print_map();
}

void init_second_map() {
    Map* map = set_active_map(1);
    Player.x = 5;
    Player.y = 5;
    add_door(3,3);
    add_crown(30, 5);
    add_shield(28, 13);
    add_sword(14, 24);
    // enemies 
    for(int i = map_width() + 6; i < map_area(); i+= 30)
    {
        add_spike(i % map_width(), i / map_width());
    }
    for(int i = map_width() + 2; i < map_area(); i+= 16)
    {
        add_spike(i % map_width(), i / map_width());
    }
    add_wall(0, 0,  HORIZONTAL, 10);
    add_wall(0, 10, HORIZONTAL, 10);
    add_wall(0, 0, VERTICAL, 10);
    add_wall(10, 0, VERTICAL, 4);
    add_wall(10, 6, VERTICAL, 5);
    
    add_wall(20, 6, VERTICAL, 5);
    add_wall(20, 6, HORIZONTAL, 5);
    add_wall(15, 10, HORIZONTAL, 5);
    
    add_wall(20, 5, HORIZONTAL, 5);
    add_wall(20, 5, VERTICAL, 5);
    
    add_wall(13, 20, VERTICAL, 5);
    add_wall(13, 20, HORIZONTAL, 5);
    add_wall(7, 15, HORIZONTAL, 5);
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    // Initialize the maps
    draw_start();
    GameInputs in = read_inputs(); 
    while (in.b3) {
        in = read_inputs();
    }
    maps_init();
    init_main_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 10;

    // Initial drawing
    draw_game(true);

    // Main game loop
    while(gameOn)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        GameInputs in = read_inputs(); 
        int action = get_action(in);
        int updated = update_game(action);
        //if (result == GAME_OVER) {
            
        //}
        draw_game(updated);
        
        
        // Actuall do the game update:
        // 1. Read inputs        
        // 2. Determine action (get_action)        
        // 3. Update game (update_game)
        // 3b. Check for game over
        // 4. Draw frame (draw_game)
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
}
