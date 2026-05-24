/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-14 15:07:09
 * Modified for P4617 Solution
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 5000+5;
int n, m;

// 邻接表：存左边点 u 指向的右边点 v
std::vector<int> adj[maxn];

// match[v] = u : 表示右边点 v 匹配了 左边点 u
int match[maxn];

// 匈牙利算法用的访问标记
int vis[maxn];

// 最终答案标记：如果为 true，表示该点作为起点 Mirko 必胜
bool mirko_win[maxn];

// 辅助数组：记录左边点 u 是否在最大匹配中
bool left_matched[maxn];

//oisnip_beginhungarian.cpp
// ------------------- 模板开始 -------------------

// DFS 寻找增广路
// 这里的 u 是左边的点
bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue; 
        vis[v] = true;       

        if (match[v] == 0 || dfs(match[v])) {
            match[v] = u; 
            return true;
        }
    }
    return false; 
}

// 匈牙利算法主函数
int hungarian(int n) { 
    int ans = 0;
    memset(match, 0, sizeof(match)); 
    
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis)); 
        if (dfs(i)) {
            ans++;
        }
    }
    return ans;
}
// ------------------- 模板结束 -------------------
//oisnip_end

// === 新增逻辑：交错路标记 ===
// 从左边点 u 出发，沿着 "非匹配边 -> 匹配边" 走
// 能走到的所有左边点，都是 Mirko 必胜点
void dfs_mark_mirko(int u) {
    if (mirko_win[u]) return; // 如果已经标记过，不仅不用重复标记，也防止环路死循环
    mirko_win[u] = true;      // 标记：Mirko 赢

    // 遍历 u 的邻居 (右边点 v)
    // 这里的边 u->v 一定是非匹配边 (因为 u 要么是单身，要么是通过匹配边跳过来的)
    for (int v : adj[u]) {
        // 我们需要沿着“匹配边”跳回左边。
        // 所以，只有当 v 已经被匹配时，我们才能继续走下去。
        // 如果 v 没有匹配 (match[v] == 0)，说明我们找到了一条增广路？
        // 不可能！因为我们已经跑过匈牙利算法了，不存在增广路。
        if (match[v] != 0) {
            // 沿着匹配边跳回左边点 match[v]，继续搜索
            dfs_mark_mirko(match[v]);
        }
    }
}

void init(){
    std::cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    init();
    
    // 1. 先跑一遍最大匹配
    hungarian(n);
    
    // 2. 统计哪些左边点被匹配了
    // match[v] 存的是右边点 v 匹配了谁
    memset(left_matched, 0, sizeof(left_matched));
    for (int i = 1; i <= n; i++) {
        if (match[i] != 0) {
            left_matched[match[i]] = true;
        }
    }
    
    // 3. 核心逻辑：寻找不一定在最大匹配中的点
    // 从所有“单身”的左边点出发，跑一遍交错路
    for (int i = 1; i <= n; i++) {
        if (!left_matched[i]) {
            dfs_mark_mirko(i);
        }
    }
    
    // 4. 输出答案
    for (int i = 1; i <= n; i++) {
        if (mirko_win[i]) {
            // 如果被标记了，说明它不一定在最大匹配中 (或者根本不在)
            cout << "Mirko\n";
        } else {
            // 如果没被标记，说明它是“铁打的”匹配点
            cout << "Slavko\n";
        }
    }
    
    return 0;
}
/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-14 15:07:09
 * Modified for P4617 Solution
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 5000+5;
int n, m;

// 邻接表：存左边点 u 指向的右边点 v
std::vector<int> adj[maxn];

// match[v] = u : 表示右边点 v 匹配了 左边点 u
int match[maxn];

// 匈牙利算法用的访问标记
int vis[maxn];

// 最终答案标记：如果为 true，表示该点作为起点 Mirko 必胜
bool mirko_win[maxn];

// 辅助数组：记录左边点 u 是否在最大匹配中
bool left_matched[maxn];

//oisnip_beginhungarian.cpp
// ------------------- 模板开始 -------------------

// DFS 寻找增广路
// 这里的 u 是左边的点
bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue; 
        vis[v] = true;       

        if (match[v] == 0 || dfs(match[v])) {
            match[v] = u; 
            return true;
        }
    }
    return false; 
}

// 匈牙利算法主函数
int hungarian(int n) { 
    int ans = 0;
    memset(match, 0, sizeof(match)); 
    
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis)); 
        if (dfs(i)) {
            ans++;
        }
    }
    return ans;
}
// ------------------- 模板结束 -------------------
//oisnip_end

// === 新增逻辑：交错路标记 ===
// 从左边点 u 出发，沿着 "非匹配边 -> 匹配边" 走
// 能走到的所有左边点，都是 Mirko 必胜点
void dfs_mark_mirko(int u) {
    if (mirko_win[u]) return; // 如果已经标记过，不仅不用重复标记，也防止环路死循环
    mirko_win[u] = true;      // 标记：Mirko 赢

    // 遍历 u 的邻居 (右边点 v)
    // 这里的边 u->v 一定是非匹配边 (因为 u 要么是单身，要么是通过匹配边跳过来的)
    for (int v : adj[u]) {
        // 我们需要沿着“匹配边”跳回左边。
        // 所以，只有当 v 已经被匹配时，我们才能继续走下去。
        // 如果 v 没有匹配 (match[v] == 0)，说明我们找到了一条增广路？
        // 不可能！因为我们已经跑过匈牙利算法了，不存在增广路。
        if (match[v] != 0) {
            // 沿着匹配边跳回左边点 match[v]，继续搜索
            dfs_mark_mirko(match[v]);
        }
    }
}

void init(){
    std::cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    init();
    
    // 1. 先跑一遍最大匹配
    hungarian(n);
    
    // 2. 统计哪些左边点被匹配了
    // match[v] 存的是右边点 v 匹配了谁
    memset(left_matched, 0, sizeof(left_matched));
    for (int i = 1; i <= n; i++) {
        if (match[i] != 0) {
            left_matched[match[i]] = true;
        }
    }
    
    // 3. 核心逻辑：寻找不一定在最大匹配中的点
    // 从所有“单身”的左边点出发，跑一遍交错路
    for (int i = 1; i <= n; i++) {
        if (!left_matched[i]) {
            dfs_mark_mirko(i);
        }
    }
    
    // 4. 输出答案
    for (int i = 1; i <= n; i++) {
        if (mirko_win[i]) {
            // 如果被标记了，说明它不一定在最大匹配中 (或者根本不在)
            cout << "Mirko\n";
        } else {
            // 如果没被标记，说明它是“铁打的”匹配点
            cout << "Slavko\n";
        }
    }
    
    return 0;
}

