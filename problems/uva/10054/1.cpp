/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-18 13:22:33
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 55;
int n,m;

int g[maxn][maxn]; // 邻接矩阵
int deg[maxn]; // 每个点的度
int color;

void init(){
    memset(g,0,sizeof(g));
    memset(deg,0,sizeof(deg));
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int u,v;
        std::cin >> u >> v;
        deg[u]++;
        deg[v]++;
        g[u][v]++;
        g[v][u]++;

        // 记录一个出现过的颜色
        // 起点只能是出现过的颜色
        color = u;
    }
}

void euler(int u) {

    // v 是u相邻的点
    for(int v = 1;v <= 50 ;++v ) // v: 1->50
    {
        if( g[u][v] ) {

            //删除这条边
            g[u][v]--;
            g[v][u]--;
            euler(v);

            //回溯的时候输出
            std::cout << v  << " " << u << "\n";
        }
    }
}

bool check_deg() {
    // 是否存在度为奇数点
    for(int i = 1;i <= 50 ;++i ) // i: 1->50
    {
        if( deg[i] % 2 == 1) 
        {
            return 0;
        }
    }
    return 1;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int T;
    std::cin >> T;
    int cnt = 0;
    while (T--) {
        cnt++;
        //在相邻两组输出之间应有一个空行
        if( cnt != 1 ) cout << "\n";
        std::cout << "Case #" << cnt << "\n";
        init();
        if( check_deg() ) {
            euler(color);
        }
        else {
            std::cout << "some beads may be lost" << "\n";
        }
        
    }
    
    return 0;
}
