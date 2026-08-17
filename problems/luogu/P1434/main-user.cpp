/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-17 14:42
 * update_at: 2026-08-17 14:42
 */
/*============================================================================
* Title : tvoj 1004 滑雪
* Author: Rainboy
* Time  : 2016-05-03 17:44
* update: 2016-05-03 17:44
* © Copyright 2016 Rainboy. All Rights Reserved.
*=============================================================================*/


#include <cstdio>

#define N 110       //定义最大量

/* 数据存储 */
int r,c;
int ha[N][N];//滑雪场的大小
int f[N][N];//记录某个点开始滑雪的最大值
bool vis[N][N]={0};//有没有访问过

int dir[4][2]  = {{-1,0},{1,0},{0,-1},{0,1}}; //四个方向

/* 判断i,j是否在范围内 */
bool judge(int i,int j){
    if(i >=1 && i<= r && j>=1 && j<=c)
        return true;
    return false;
}

int dfs(int i,int j){
    if( vis[i][j] != 0) return f[i][j]; //已经访问过,返回
    vis[i][j] =1;   //设置已经访问过
    int ii,ij;
    int max =-1,tmp;
    int k;
    for (k=0;k<4;k++){ //访问周围的4个点
        ii=i+dir[k][0],ij=j+dir[k][1];
        /* 点在范围内 且 能到达 */
        if( judge(ii,ij) && ha[ii][ij] < ha[i][j]){
            tmp = dfs(ii,ij);
            if(max<=tmp)
                max=tmp;
        }
    }
    if(f[i][j] < max+1) //更新
        f[i][j] = max+1;
    return f[i][j];
}

int main(){
    int i,j;
    /* 数据读取 */
    scanf("%d%d",&r,&c);
    for (i=1;i<=r;i++){
        for (j=1;j<=c;j++){
            scanf("%d",&ha[i][j]);
            f[i][j]=1;
        }
    }

    int max=0,tmp;
    for (i=1;i<=r;i++){ //尝试所有点
        for (j=1;j<=c;j++){
            tmp = dfs(i,j);
            if( max < tmp)
                max = tmp;
        }
    }
    printf("%d",max);
    return 0;
} 
