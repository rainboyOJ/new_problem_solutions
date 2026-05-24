/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-05 12:31:53
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e3+5;
int n,m;
int deg[maxn];
bool vis[maxn];
vector<int> G[maxn]; // 邻接表存图，用于 DFS

// 简单的 DFS 遍历
void dfs(int u) {
    vis[u] = true;
    for (int v : G[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

void init(){
    memset(deg,0,sizeof(deg));
    memset(vis,0,sizeof(vis));
    for (int i = 0; i <= n; i++) G[i].clear(); // 清空邻接表
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        deg[u]++;
        deg[v]++;
        G[u].push_back(v);
        G[v].push_back(u);
    }

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    while (1) {
        std::cin >> n;
        if( n == 0) break;
        std::cin >> m;
        init();

        //检查度的数量
        int odd = 0; // 奇数的度的数量
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            if( deg[i] % 2 == 1) odd++;
        }

        if( odd != 0 ) {
            std::cout << 0 << "\n";
            continue;
        }
        // 2. 检查连通性
        // 找到第一个有边的点作为起点
        int start_node = -1;
        for(int i = 1; i <= n; i++){
            if(deg[i] > 0) {
                start_node = i;
                break;
            }
        }

        // 如果一张图没有边 (m=0)，通常认为存在欧拉回路（空路），或者根据题目定义。
        // 但如果 m > 0，start_node 一定存在。
        if (start_node != -1) {
            dfs(start_node);

            bool connected = true;
            for (int i = 1; i <= n; i++) {
                // 核心判断：如果一个点有度数（连了边），但没被 DFS 访问到
                // 说明这个点在另一个独立的连通块里
                if (deg[i] > 0 && !vis[i]) {
                    connected = false;
                    break;
                }
            }
            
            if (connected) cout << 1 << "\n";
            else cout << 0 << "\n";
            
        } else {
            // 没有边的情况，一般视为符合（或者根据题目特判，这里输出1比较稳妥）
            cout << 1 << "\n";
        }
        
    }
    
    return 0;
}
