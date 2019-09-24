#include "map.h"

#include "globals.h"
#include "graphics.h"
#define NUM_BUCKETS 50
#define NUM_MAPS 2

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static int active_map = 0;
static Map map[NUM_MAPS];


/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    // TODO: Fix me!
    // Cantor pairing function
    // N x N => N
    unsigned key;
    //key = ((1/2) * (X + Y) * ( X + Y + 1)) + Y;
    key = (X * map[active_map].w) + Y;
    return key;
    
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    // TODO: Fix me!
    return key % NUM_BUCKETS;
}

void maps_init()
{
    // TODO: Implement!    
    // Initialize hash table
    // Set width & height

        map[0].items = createHashTable(&map_hash, NUM_BUCKETS);
        map[0].w = 60;
        map[0].h = 60;
        
        map[1].items = createHashTable(&map_hash, NUM_BUCKETS);
        map[1].w = 50;
        map[1].h = 50;
}


Map* get_active_map()
{
    // There's only one map
    return &map[active_map];
}

Map* set_active_map(int m)
{
    active_map = m;
    return &map[active_map];
}

Map* get_map(int m) {
    return &map[m];
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P', 'N'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    return map[active_map].w;
}

int map_height()
{
    return map[active_map].h;
}

int map_area()
{
    return map_height() * map_width();
}

MapItem* get_north(int x, int y)
{
   return get_here(x, y - 1);
}

MapItem* get_south(int x, int y)
{
    return get_here(x, y + 1);
}

MapItem* get_east(int x, int y)
{
    return get_here(x + 1, y);
}

MapItem* get_west(int x, int y)
{
   return get_here(x - 1, y);
}

MapItem* get_here(int x, int y)
{
     unsigned key = XY_KEY(x, y);
     MapItem* item = (MapItem*) getItem(get_active_map()->items, key); 
     return item;
}

void map_erase(int x, int y)
{
    draw_nothing(x, y);
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void* hasKey = 0;
void add_NPC(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = NPC;
    w1->draw = draw_NPC;
    w1->walkable = false;
    w1->data = hasKey;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_stairs(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = STAIRS;
    w1->draw = draw_stairs;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_crown(int x, int y) 
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CROWN;
    w1->draw = draw_crown;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_sword(int x, int y) 
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SWORD;
    w1->draw = draw_sword;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_shield(int x, int y) 
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SHIELD;
    w1->draw = draw_shield;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void erase_item(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = NULL;
    w1->draw = draw_nothing;
    w1->walkable = true;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_door(int x, int y) 
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = DOOR;
    w1->draw = draw_door;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}


void add_spike(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SPIKE;
    w1->draw = draw_spike;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
