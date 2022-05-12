#ifndef SNAKE_INCLUDED
#define SNAKE_INCLUDED
#define MAX_SNAKE_LENGTH 200
#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3
#define FOOD_MAX_NUM 200
#define BARRIER_MAX_NUM 200
#define SNAKE_INIT_LENGTH 3
#define LENGTH 80
#define WIDTH 30
#define  RANK_MAX_NUM 20
typedef struct {
    int x;
    int y;
}Pos;
typedef struct {
    Pos pos;
    int dir;
}Snake_node;
typedef struct {
    int length;
    int speed;
    Snake_node nodes[MAX_SNAKE_LENGTH];
}Snake;
typedef struct {
    Pos pos;
}Food;
typedef struct {
    Pos pos;
}Barrier;
typedef struct {
    char name[20];
    int score;
}Player;
void quicksort_player(Player p[],int count);    
Snake new_snake();
void snake_move(Snake *s);
void snake_turn(Snake *s,int dir);
void snake_grow(Snake *s);
int snake_is_alive(Snake *s,int count,Barrier b[]);
void snake_is_eating(Snake *s,int count,Food f[]);
void snake_print(Snake *s);
Food new_food(Pos pos);
Barrier new_barrier(Pos pos);
Pos new_pos(int is_occupied[WIDTH][LENGTH]);
void print_and_check_empty(Snake *s,Food f[],int fcount,Barrier b[],int bcount,int is_occupied[WIDTH][LENGTH]);
int menu();
//print the help
void help();
//print the about
void about();
//print the rank list
void rank();
void start_game();
#endif // SNAKE_INCLUDED