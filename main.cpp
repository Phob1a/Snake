//
//  main.cpp
//  leetcode
//
//  Created by Samaritan on 20/11/2018.
//  Copyright © 2018 Samaritan. All rights reserved.
//
//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include<stdlib.h>
#include <unistd.h>
#include<time.h>
//#include <windows.h>

using namespace std;


//class Solution {
//public:
const int size=22;
char a[size+1][size+1];

int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};

bool flag=true;

struct node{
    int x;
    int y;
};

struct snake{
    node head;
    node body[3333];
    int len;
};

node food;
snake s;

void gfood(){
    int rg=(size-2)*(size-2)-s.len;
    int d=rand()%rg;
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-1;j++){
            if(a[i][j]!=' ') continue;
            if(d==0){
                a[i][j]='o';
                food.x=i;
                food.y=j;
                return;
            }
            d--;
        }
    }
}

void update(node x){
    if(a[x.x][x.y]=='o'){
        int k=s.len-1;
        while(k>0){
            s.body[k]=s.body[k-1];
            k--;
        }
        s.body[0]=s.head;
        s.head=x;
        a[x.x][x.y]='*';
        s.len++;
        gfood();
    }
    else if(a[x.x][x.y]==' '){
        int k=s.len-2;
        if(k>=0){
            a[s.body[k].x][s.body[k].y]=' ';
        }
        else{
            a[s.head.x][s.head.y]=' ';
        }
        while(k>0){
            s.body[k]=s.body[k-1];
            k--;
        }
        if(s.len!=1){
            s.body[0]=s.head;}
        s.head=x;
        a[x.x][x.y]='*';
    }
    else{
        int k=s.len-1;
        
        if(k>=0){
            a[s.body[k].x][s.body[k].y]=' ';
        }
        else{
            a[s.head.x][s.head.y]=' ';
        }
        while(k>0){
            s.body[k]=s.body[k-1];
            k--;
        }
        s.body[0]=s.head;
        s.head=x;
        a[x.x][x.y]='*';
        flag=false;
    }
}


int caldis(node n1,node n2){
    return (n1.x-n2.x)*(n1.x-n2.x)+(n1.y-n2.y)*(n1.y-n2.y);
}

void move(){
    int d=999999;
    node res={-1,-1};
    node m;
    for(int i=0;i<4;i++){
            m.x=s.head.x+dx[i];
            m.y=s.head.y+dy[i];
            if(a[m.x][m.y]!='o'&&a[m.x][m.y]!=' ') continue;
            int k=caldis(m,food);
            if(k<d){
                res=m;
                d=k;
        }
    }
    if(d==99999){
        res=s.head;
        res.x++;
    }
    update(res);
}

void init(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i==0||i==size-1) a[i][j]='-';
            else if(j==0||j==size-1) a[i][j]='|';
            else a[i][j]=' ';
        }
    }
}

void print(){
    for(int i=0;i<size;i++){
        cout<<a[i]<<endl;
    }
}



int main(){
    srand((unsigned)time(NULL));
    init();
    s.head.x=1;
    s.head.y=1;
    s.len=1;
    a[s.head.x][s.head.y]='*';
    gfood();
    while(1){
        print();
        if(!flag) break;
        sleep(1);
        move();
        system("clear");
    }
    //sleep(0.5);
    //Sleep(200);
    cout<<"game over;"<<endl;
//};
}
