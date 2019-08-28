#include<iostream>
#include"../bfs.h"
int test();
int _W = 26;
int _H = 9;
char map []= {
//      0,4,2,3,4,5,6,7,8,9,0,4,2,3,4,5,6,7,8,9,0,4,2,3,4,5
/*0*/   4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
/*4*/   4,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,4,4,4,
/*2*/   4,0,4,4,4,0,4,4,0,0,0,0,4,4,4,4,4,0,0,4,4,4,0,4,4,4,
/*3*/   4,0,0,0,0,4,4,4,0,0,4,0,0,0,0,0,0,0,0,0,4,4,0,4,4,4,
/*4*/   4,4,4,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,0,0,4,4,0,0,0,4,
/*5*/   4,4,4,0,0,0,0,0,4,0,0,4,4,0,0,0,4,0,0,0,0,0,0,0,0,4,
/*6*/   4,4,0,0,0,0,4,4,4,0,0,0,4,0,0,0,4,4,0,0,0,0,4,4,0,0,
/*7*/   4,4,4,4,0,0,0,0,0,0,0,0,4,0,0,0,4,4,4,0,0,0,0,0,0,0,
/*8*/   4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
};
void print(tool::pos *s) {
    while(s) {
        map[s->y*_W+s->x] = 2;
        s= s->pre;
    }
    for(int i = 0; i< _H;i++) {
        for (int j = 0; j < _W; j++)
        {
            switch (map[i*_W+j])
            {
            case 4:
                printf("#");
                break;
            case 0:
                printf(" ");
                break;
            case 2:
                printf("0");
                break;
            default:
                break;
            }
        }
        printf("\n");
        
    }
}

int main() {
    tool::queue<tool::pos> qpos;
    tool::bfs _bfs;
    _bfs.set(map,26,9);
    tool::pos s;
    tool::pos t;
    s.x =1;
    s.y = 1;
    t.x = 24;
    t.y = 7;
    print( _bfs.BFS(s,t,qpos));
    return 0;
}
