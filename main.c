#include<stdio.h>
#include<time.h>
#include<curses.h>
#include<pthread.h> 
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<math.h>
#include "snake.h"
#include<string.h>
Player p[RANK_MAX_NUM];
int player_num=0;
Snake snake;
int alive = 1;
void init_curses(){
    noecho();
    initscr();
    keypad(stdscr,1);
    curs_set(0);
}
int main(){
    srand((unsigned int)time(0));
    init_curses();
    while(1){
        int ch=menu();
        switch(ch){
            case 1:
                start_game();
                break;
            case 2:
                help();
                break;
            case 3:
                about();
                break;
            case 4:
                rank();
                break;
            default:
                endwin();
                return 0;
        }        
    }        
	endwin();
	return 0;
}
int menu(){
    move(WIDTH/2-6,LENGTH/2-10);
    printw("Hugry Snake");
    move(WIDTH/2-5,LENGTH/2-10);
    printw("1.Start");
    move(WIDTH/2-4,LENGTH/2-10);
    printw("2.Help");
    move(WIDTH/2-3,LENGTH/2-10);
    printw("3.About");
    move(WIDTH/2-2,LENGTH/2-10);
    printw("4.Rank");
    move(WIDTH/2-1,LENGTH/2-10);
    printw("press any other key to exit");
    refresh();
    int ch;
    ch=getch();
    ch-=48;
    clear();
    return ch;
}
void *run_game(){
    int fcount=0,bcount=0;
    Food f[FOOD_MAX_NUM];
    Barrier b[BARRIER_MAX_NUM];
    int is_occupied[WIDTH][LENGTH]={0};
    int random;
    clear();
    while(alive){
        print_and_check_empty(&snake,f,fcount,b,bcount,is_occupied);
        random=rand()%100;
        if(random<5){
            if(fcount<FOOD_MAX_NUM){
                f[fcount]=new_food(new_pos(is_occupied));
                fcount++;
            }    
        }
        random=rand()%100;
        if(random<2){
            if(bcount<BARRIER_MAX_NUM){
                b[bcount]=new_barrier(new_pos(is_occupied));
                bcount++;
            }    
        }
        snake_is_eating(&snake,fcount,f);
        alive=snake_is_alive(&snake,fcount,b);
        snake_move(&snake);
        usleep(300000/snake.speed);
    }           
}
void *change_dir(){
    while (alive){
        int key=getch();
        switch (key) {
            case KEY_UP:
                snake_turn(&snake,UP);
                break;
            case KEY_DOWN:
                snake_turn(&snake,DOWN);
                break;
            case KEY_LEFT:
                snake_turn(&snake,LEFT);
                break;
            case KEY_RIGHT:
                snake_turn(&snake,RIGHT);
                break;                              
        }    
    }
}
void start_game(){
    snake=new_snake();
    int is_occupied[WIDTH][LENGTH]={0};
    pthread_t t1,t2;
    alive=1;
    pthread_create(&t1,NULL,run_game,NULL);
    pthread_create(&t2,NULL,change_dir,NULL);
    while(alive);
    clear();
    move(WIDTH/2-5,LENGTH/2-10);
    printw("YOU DIED");
    move(WIDTH/2-4,LENGTH/2-10);
    printw("Your score is %d",snake.length-SNAKE_INIT_LENGTH);
    move(WIDTH/2-3,LENGTH/2-10);
    printw("Please leave your name:");
    refresh();
    move(WIDTH/2-2,LENGTH/2-10);
    char name[20];
    scanw("%s",name);
    FILE *fp;
    fp=fopen("rank.txt","a");
    fprintf(fp,"%s %d\n",name,snake.length-SNAKE_INIT_LENGTH);
    fclose(fp);
    clear();
    move(WIDTH/2-5,LENGTH/2-10);
    printw("Press any key to continue...");
    refresh();
    getch();
    clear();
    fp=fopen("rank.txt","r");
    fscanf(fp,"%d",&player_num);
    for(int i=0;i<player_num;i++){
        fscanf(fp,"%s %d",p[i].name,&p[i].score);
    }
    fclose(fp);
    strcpy(p[player_num].name,name);
    p[player_num].score=snake.length-SNAKE_INIT_LENGTH;
    player_num++;
    quicksort_player(p,player_num);
    fp=fopen("rank.txt","w");
    fprintf(fp,"%d\n",player_num);
    for(int i=0;i<player_num;i++){
        fprintf(fp,"%s %d\n",p[i].name,p[i].score);
    }
    fclose(fp);
}    
void help(){
    move(WIDTH/2-6,LENGTH/2-10);
    printw("use UP to turn up");
    move(WIDTH/2-5,LENGTH/2-10);
    printw("use DOWN to turn down");
    move(WIDTH/2-4,LENGTH/2-10);
    printw("use RIGHT to turn right");
    move(WIDTH/2-3,LENGTH/2-10);
    printw("use LEFT to turn left");
    move(WIDTH/2-2,LENGTH/2-20);
    printw("die when meet the wall,barriers or itself");
    move(WIDTH/2-1,LENGTH/2-10);
    printw("press any key to return");
    refresh();
    getch();
    clear();
}
void about(){
    move(WIDTH/2-6,LENGTH/2-10);
    printw("product by hanxinqiuyun");
    move(WIDTH/2-5,LENGTH/2-10);
    printw("programmed by moefulye");
    move(WIDTH/2-4,LENGTH/2-20);
    printw("https://github.com/MoefulYe/hungrySnake");
    move(WIDTH/2-3,LENGTH/2-10);
    printw("press any key to return");
    refresh();
    getch();
    clear();
}
void rank(){
    FILE *fp=fopen("rank.txt","r");
    fscanf(fp,"%d\n",&player_num);
    for(int i=0;i<player_num;i++){
        fscanf(fp,"%s %d\n",p[i].name,&p[i].score);
    }
    fclose(fp);
    move(WIDTH/2-6,LENGTH/2-10);
    printw("Rank");
    move(WIDTH/2-5,LENGTH/2-10);
    printw("rank\t\tName\t\tScore");
    for(int i=0;i<player_num;i++){
        move(WIDTH/2-4+i,LENGTH/2-10);
        printw("%d\t\t%s\t\t%d",i+1,p[i].name,p[i].score);
    }    
    move(WIDTH/2-4+player_num,LENGTH/2-10);
    printw("press any key to return");
    refresh();
    getch();
    clear();   
}
void quicksort_player(Player p[],int n){
    if(n<=1)return;
    int i=0,j=n-1;
    Player tmp=p[i];
    while(i<j){
        while(i<j&&p[j].score<=tmp.score)j--;
        if(i<j){
            p[i]=p[j];
            i++;
        }
        while(i<j&&p[i].score>tmp.score)i++;
        if(i<j){
            p[j]=p[i];
            j--;
        }
    }
    p[i]=tmp;
    quicksort_player(p,i);
    quicksort_player(p+i+1,n-i-1);    
}    
Pos new_pos(int is_occupied[WIDTH][LENGTH]){
    Pos p;
    int i,j;
    do{
        i=rand()%(WIDTH-2)+1;
        j=rand()%(LENGTH-2)+1;
    }while(is_occupied[i][j]==1);
    p.x=i;
    p.y=j;
    return p;
}    

Snake new_snake(){
    Snake snake;
    snake.length=SNAKE_INIT_LENGTH;
    snake.speed=1;
    for(int i=0;i<snake.length;i++){
        snake.nodes[i].dir=RIGHT;
        snake.nodes[i].pos.x=LENGTH/2-i;
        snake.nodes[i].pos.y=WIDTH/2;
    }
    return snake;
}    

void snake_move(Snake *s){
    for(int i=s->length-1;i>0;i--){
        s->nodes[i].pos.x=s->nodes[i-1].pos.x;
        s->nodes[i].pos.y=s->nodes[i-1].pos.y;
    }
    switch (s->nodes[0].dir) {
        case RIGHT:
            s->nodes[0].pos.x++;
            break;
        case UP:
            s->nodes[0].pos.y--;
            break;
        case LEFT:
            s->nodes[0].pos.x--;
            break;
        case DOWN:
            s->nodes[0].pos.y++;
            break;
    }                                
}

void snake_is_eating(Snake *s,int count,Food f[]){
    for(int i=0;i<count;i++){
        if(s->nodes[0].pos.x==f[i].pos.x&&s->nodes[0].pos.y==f[i].pos.y){
            snake_grow(s);
            f[i].pos.x=-1;
            f[i].pos.y=-1;
        }
    }        
}    

void snake_turn(Snake *s,int dir){
    if(s->nodes[0].dir==dir)return;
    if(s->nodes[0].dir==UP&&dir==DOWN)return;
    if(s->nodes[0].dir==DOWN&&dir==UP)return;
    if(s->nodes[0].dir==LEFT&&dir==RIGHT)return;
    if(s->nodes[0].dir==RIGHT&&dir==LEFT)return;
    s->nodes[0].dir=dir;
}

void snake_grow(Snake *s){
    s->length++;
    if(s->length==7)s->speed++;
    if(s->length==10)s->speed++;
    if(s->length==13)s->speed++;
    s->nodes[s->length].dir=s->nodes[s->length-1].dir;
    switch (s->nodes[s->length-1].dir) {
        case UP:
            s->nodes[s->length].pos.y=s->nodes[s->length-1].pos.y+1;
            s->nodes[s->length].pos.x=s->nodes[s->length-1].pos.x;
            break;
        case DOWN:
            s->nodes[s->length].pos.y=s->nodes[s->length-1].pos.y-1;
            s->nodes[s->length].pos.x=s->nodes[s->length-1].pos.x;
            break;
        case LEFT:
            s->nodes[s->length].pos.y=s->nodes[s->length-1].pos.y;
            s->nodes[s->length].pos.x=s->nodes[s->length-1].pos.x+1;
            break;
        case RIGHT:
            s->nodes[s->length].pos.y=s->nodes[s->length-1].pos.y;
            s->nodes[s->length].pos.x=s->nodes[s->length-1].pos.x-1;
            break; 
            //TODO 有问题？？
    }    
}

int snake_is_alive(Snake *s,int count,Barrier b[]){
    if(s->nodes[0].pos.x==0||s->nodes[0].pos.x==LENGTH-1||s->nodes[0].pos.y==0||s->nodes[0].pos.y==WIDTH-1){
       return 0;
    }
    for(int i=1;i<s->length;i++){
        if(s->nodes[0].pos.x==s->nodes[i].pos.x&&s->nodes[0].pos.y==s->nodes[i].pos.y){
            return 0;
        }
    }
    for(int i=0;i<count;i++){
        if(s->nodes[0].pos.x==b[i].pos.x&&s->nodes[0].pos.y==b[i].pos.y){
            return 0;
        }
    }
    return 1;              
}

Food new_food(Pos pos){
    Food f;
    f.pos=pos;
    return f;
}

Barrier new_barrier(Pos pos){
    Barrier b;
    b.pos=pos;
    return b;
}

void print_and_check_empty(Snake *s,Food f[],int fcount,Barrier b[],int bcount,int is_occupied[WIDTH][LENGTH]){
    erase();
    for(int i=0;i<LENGTH;i++){
        move(0,i);
        printw("--");
        move(WIDTH-1,i);
        printw("--");
    }
    for(int i=0;i<WIDTH;i++){
        move(i,0);
        printw("|");
        move(i,LENGTH-1);
        printw("|");
    }
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<LENGTH;j++){
            is_occupied[i][j]=0;
        }
    }
    for(int i=0;i<s->length;i++){
        is_occupied[s->nodes[i].pos.y][s->nodes[i].pos.x]=1;
        mvprintw(s->nodes[i].pos.y,s->nodes[i].pos.x,"#");
    }
    for(int i=0;i<fcount;i++){
        if(f[i].pos.x!=-1){
            is_occupied[f[i].pos.y][f[i].pos.x]=1;
            mvprintw(f[i].pos.y,f[i].pos.x,"O");
        }
    }
    for(int i=0;i<bcount;i++){
        is_occupied[b[i].pos.y][b[i].pos.x]=1;
        mvprintw(b[i].pos.y,b[i].pos.x,"X");
    }
    for(int i=1;i<WIDTH-1;i++){
        for(int j=1;j<LENGTH-1;j++){
            if(is_occupied[i][j]==0){
                mvprintw(i,j," ");
            }
        }
    }    
    refresh();                                 
}     