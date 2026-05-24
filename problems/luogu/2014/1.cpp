/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-05 21:45:08
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 305;
int n,m;
int w[maxn];

// dp[u][j] u在容量j的情况下的最大解
int dp[maxn][maxn];

std::vector<int> adj[maxn];

void init(){
    std::cin >> n >> m;
    m++;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int fa;
        std::cin >> fa >> w[i];
        adj[fa].push_back(i);
    }

    for(int i = 0;i < maxn ;++i ) // i: 0->n
    {
        for(int j = 0;j < maxn ;++j ) // j: 0->n
        {
            dp[i][j] = -1e8;
            if( j == 0) dp[i][j] = 0;
        }
    }

}

void dfs(int u) {
    //1. 初始化,边界就是至少可以选自己
    // for(int i = 1;i <= m ;++i ) // i: 1->m
    //     dp[u][i] = w[u];

    // 似乎和上面的写法的效果是一样的
    // 不知道为什么?
    dp[u][1] = w[u];
    // 知道了,这是一种严格的写法,类似01背包恰好装满
    // 如果你不理解: 根据样例 ,进行手动dp填表

    //2. 枚举物品
    for(int v : adj[u]){
        dfs(v); 


        // j最少是1
        for(int j = m ;j >= 1;j--) {

            // 不用知道 v 子树的大小吗?
            for(int k = 1 ; k < j ;k ++) {
                dp[u][j] = std::max(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
        }
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    dfs(0);

    std::cout << dp[0][m] << "\n";
    
    return 0;
}
