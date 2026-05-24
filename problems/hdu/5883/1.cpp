/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-08 15:30:03
 * * Problem: HDU 5883 The Best Path
 * Algorithm: 欧拉回路/欧拉路径判定 + 异或性质 + 并查集
 * * 核心思想:
 * 1. 欧拉路径/回路要求：图必须连通（忽略孤立点）。
 * 2. 经过次数 = 度数 / 2 (中间点) 或 度数 / 2 + 1 (起终点)。
 * 3. 利用 A^A=0 的性质，偶数次经过的点贡献为0，奇数次经过的点贡献为 A。
 */

#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

// 数据范围：N <= 100,000。开到 1e6 虽然安全但要注意 memset 的开销
const int maxn = 1e6+5;
const int maxe = 1e6+5;
int n,m;
int a[maxn];    // 存储每个点的权值
int deg[maxn];  // 存储每个点的度数


// === 并查集 (DSU) ===
// 用于维护图的连通性
struct DSU {
    int fa[maxn];
    
    // 初始化：每个点的父节点指向自己
    void init(int n) {
        for(int i = 1;i <= n ;++i ) 
        {
            fa[i] = i;
        }
    }

    // 查找 + 路径压缩
    // 修正后的写法：find(fa[x]) 防止无限递归
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    // 合并集合
    void merge(int u,int v) {
        int a = find(u);
        int b = find(v);
        if( a != b) fa[a] = b;
    }

} dsu;


// === 初始化函数 ===
void init(){
    // 【注意】如果 T 很大且 N 很小，这里 memset 整个大数组会导致 TLE
    // 建议使用 for(int i=1; i<=n; ++i) deg[i]=0; 来清空
    memset(deg,0,sizeof(deg));
    
    std::cin >> n >> m;
    dsu.init(n);
    
    // 读取点权
    for(int i = 1;i <= n ;++i ) 
    {
        std::cin >> a[i];
    }
    
    // 读取边，维护度数和连通性
    for(int i = 1;i <= m ;++i ) 
    {
        int u,v;
        std::cin >> u >> v;
        deg[u]++;
        deg[v]++;
        dsu.merge(u, v);
    }
}

// === 连通性检查 ===
// 返回图中“有效连通分量”的个数
// 有效：指包含边（度数>0）的连通块
int check_component_cnt() {
    int cnt = 0;
    for(int i = 1;i <= n ;++i ) 
    {
        // 只统计作为根节点，且不是孤立点（度数>0）的集合
        // 如果 cnt > 1，说明有两条独立的、不连通的路径，无法一笔画
        if( dsu.fa[i] == i && deg[i] > 0 ) cnt++;
    }
    return cnt;
}

std::vector<int> nodes; // 存储奇数度数的点

signed main () {
    // IO 加速
    ios::sync_with_stdio(false); cin.tie(0);
    
    int T;
    std::cin >> T;
    while (T--) {
        init(); // 每组数据初始化
        
        // 1. 连通性判定：如果图分裂成多块（非孤立点），直接不可能
        if( check_component_cnt() > 1) {
            std::cout << "Impossible" << "\n";
            continue;
        }

        int od_dg_cnt = 0;
        nodes.clear();

        // 2. 统计奇数度数点的个数
        for(int i = 1;i <= n ;++i ) 
        {
            if( deg[i] % 2  ) {
                od_dg_cnt++;
                nodes.push_back(i);
            }
        }

        // 3. 计算基础异或和 (Base XOR)
        // 逻辑：计算所有作为"中间点"经过次数为奇数的贡献
        // 中间经过次数 = deg[i] / 2
        int base_xor = 0; 
        for(int i = 1;i <= n ;++i ) 
        {
            // 【注意】这里你只计算了偶数度数的点。
            // 实际上通用的写法是：if ( (deg[i]/2) % 2 == 1 ) base_xor ^= a[i];
            // 这样包含了所有点作为中间点的贡献，后续处理会更统一。
            // 但按照你当前的逻辑，奇数点稍后单独处理。
            if(deg[i] % 2 == 0  &&  (deg[i] / 2 ) %2  == 1 )
                base_xor ^= a[i];
        }

        // 4. 欧拉路径判定：奇点数必须为 0 或 2
        if( od_dg_cnt !=0 && od_dg_cnt != 2) {
            std::cout << "Impossible" << "\n";
            continue;
        }

        // === 情况 A: 欧拉路径 (2个奇点) ===
        if( od_dg_cnt == 2) {
            // 起点和终点固定是这两个奇点
            // 结果 = 中间贡献 ^ 起点(多1次) ^ 终点(多1次)
            // 注意：如果 deg[u]=3 (deg/2=1)，按你的 base_xor 逻辑它没加进去，
            // 这里 ^ a[nodes[0]] 把它加进去，是对的。
            // 但如果 deg[u]=5 (deg/2=2)，按你的逻辑没加，这里加进去，可能导致错误 (多算了一次)。
            // 建议检查度数很大的奇点情况。
            int result = base_xor ^ a[nodes[0]] ^ a[nodes[1]];
            std::cout << result << "\n";
        } 

        // === 情况 B: 欧拉回路 (0个奇点) ===
        if( od_dg_cnt == 0) {
            int result = -1; // 初始化为一个较小值，寻找最大幸运数字

            // 欧拉回路可以从任意有边的点出发
            // 枚举每个点作为起点 i
            // 贡献变化：该点作为起点，经过次数从 deg[i]/2 变为 deg[i]/2 + 1
            // 异或性质：X ^ A 相当于翻转了 A 的奇偶贡献
            for(int i = 1;i <= n ;++i ) 
            {
                if( deg[i] > 0) 
                    result = max(result, base_xor ^ a[i]);
            }
            // 特判：如果没有边 (result仍为-1)，输出 Impossible
            if (result == -1) std::cout << "Impossible" << "\n";
            else std::cout << result << "\n";
        }
        
    }
    
    return 0;
}
