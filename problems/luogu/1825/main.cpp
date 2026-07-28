/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 02月 13日 星期日 19:37:03 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e3+5,maxe = 1e3+5; //点与边的数量

/* 顺时针-4个方向 */
int fx[][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
int n,m;

// 判断 (x,y) 是否在迷宫范围内
bool in_mg(int x,int y){
    return x >= 1 && x <=n && y >=0  && y<m;
}

// BFS 队列节点：x,y 为坐标，s 为起点到该点的最少步数
struct node {
    int x,y,s;
};
bool vis[maxn][maxn];   // 访问标记

string mg[maxn];        // 迷宫，每行一个字符串
int sx,sy,tx,ty;        // 起点 @，终点 =

vector<node> v[30];     // v[c] 存储所有大写字母 c 对应的传送门坐标（每字母恰好两个）


void init(){
    std::cin >> n >> m;
    for(int i=1;i<=n;++i){
        std::cin >> mg[i];
        for(int j=0;j<=m-1;++j){
            if( mg[i][j] == '='){
                tx = i;
                ty = j;
            }
            else if(mg[i][j] == '@'){
                sx = i;
                sy = j;
            }
            else if(std::isupper(mg[i][j])){
                v[mg[i][j] - 'A'].push_back({i,j,0}); // 记录传送门位置
            }
        }
    }
}

// BFS 求最短路，遇到传送门立即跳到另一端
int bfs(){
    queue<node> q;
    q.push({sx,sy,0});
    vis[sx][sy] = 1;

    while ( !q.empty() ) {
        node h = q.front();
        q.pop();
        if( h.x == tx && h.y == ty ) return h.s; // 到达终点

        for(int i=0;i<=3;++i){
            int nx = h.x + fx[i][0];
            int ny = h.y + fx[i][1];

            // 越界、撞墙、已访问 则跳过
            if( !in_mg(nx, ny) || mg[nx][ny] == '#' || vis[nx][ny] ) continue;

            if( isupper(mg[nx][ny])){ // 踩到传送门
                int t = mg[nx][ny] - 'A';
                vis[nx][ny] = 1;
                // 找到同一字母的另一个传送门，跳转过去
                for(int k = 0 ;k < v[t].size() ; ++k){
                    if( v[t][k].x != nx ||  v[t][k].y != ny  ){
                        nx = v[t][k].x;
                        ny = v[t][k].y;
                        break;
                    }
                }
                q.push({nx,ny,h.s+1});
            }
            else { // 普通格子
                q.push({nx,ny,h.s+1});
                vis[nx][ny] = 1;
            }
        }
    }
    return -1; // 无法到达
}

int main(int argc,char * argv[]){
    init();
    int ans = bfs();
    std::cout << ans << std::endl;
    return 0;
}
