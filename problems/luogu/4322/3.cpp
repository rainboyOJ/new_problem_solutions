/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-07 09:17:48
 * * Problem: P4322 [JSOI2016] 最佳团体
 * Algorithm: 01分数规划 + 树形DP (带 sz 剪枝优化)
 * Time Complexity: O(N^2)
 */
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const double  ninf = -1e10; // 初始化负无穷，保证非法状态不被选中

// 题目 N <= 2500，必须开到 2500 以上，否则最后几个点会 RE
const int maxn = 2505;
const int maxe = 5005; // 边数 N-1，开大点无妨

int n,m;
int K;
int a[maxn];
int S[maxn]; // 招募费用
int P[maxn]; // 战斗值
double dp[maxn][maxn]; // dp[u][i] 表示子树u选i个点的最大权值
int sz[maxn]; // 子树的大小 (用于优化时间复杂度)

//oisnip_beginlinklist_mini_struct.cpp
// 链式前向星存图
struct linkList {
    struct edge { int u, v,w, next; };
    edge e[maxe];
    int h[maxn], edge_cnt;
    linkList() { edge_cnt = 0; memset(h, -1, sizeof(h)); }
    void add(int u, int v,int w = 0) { e[edge_cnt] = {u, v,w, h[u]}; h[u] = edge_cnt++; }
    void add2(int u, int v,int w = 0) {
        add(u, v,w); add(v, u,w);
    }
} e;
//oisnip_end

void init(){
    std::cin >> K >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int s,p,r;
        std::cin >> s >> p >> r;
        e.add(r,i); // r 是 i 的推荐人，建立有向边 r -> i (树的父子关系)
        S[i] = s;
        P[i] = p;
    }

}

// 核心 DP 函数：计算比值为 x 时的最大收益
void dfs_dp_tree(int u,double x) {

    sz[u] = 1; // 刚开始只有根节点自己
    
    // 【关键点2】01分数规划权值转化
    // 判定 P/S >= x  <==>  P - x*S >= 0
    if( u == 0) 
        dp[u][1] = 0; // 0号点是虚拟根(JYY)，费用战斗值均为0
    else 
        dp[u][1] = (double)P[u] - x * S[u];

    // 初始化：除了选1个点(自己)的情况，其他容量都设为不可达
    for(int i = 2 ;i <= K+1 ;i++) dp[u][i] = ninf;

    // 遍历子节点 (物品组)
    for(int i = e.h[u] ; ~i ;i = e.e[i].next){
        int v = e.e[i].v;
        
        // 1. 先递归处理子树，得到子树的最优解
        dfs_dp_tree(v,x);

        // 【关键点3】sz 优化核心
        // 先把子树大小加进来，现在的 sz[u] 是合并了 v 之后的总大小
        sz[u] += sz[v];
        
        // 2. 分组背包合并 (树形背包)
        // J_UP: 循环上限。
        // min(K+1, sz[u]): 既不需要超过题目要求的 K+1，也不可能超过当前拥有的节点总数 sz[u]
        // 这行代码将复杂度从 O(N*K^2) 限制到了 O(N^2)
        int J_UP = std::min(K+1, sz[u]);
        
        // j 必须倒序枚举 (背包模板)
        for(int j = J_UP; j>=2;j--) {

            // K_UP: 分给子树 v 的名额上限
            // 1. 不能超过子树 v 的实际大小 sz[v]
            // 2. 不能把 j 占满 (j-1)，必须留 1 个名额给根节点 u 自己，否则不连通
            int K_UP = std::min(sz[v],j-1);
            
            // 枚举给子树 v 分多少个点
            for(int k = 1 ;k <= K_UP;k++) {
                // 状态转移：尝试把子树 v 选 k 个的方案合并进来
                // 必须保证两个状态都是合法的 (不是 ninf)
                if( dp[v][k] > ninf && dp[u][j-k] > ninf)
                    dp[u][j] = max(dp[u][j],dp[u][j-k] + dp[v][k]);
            }
        }

    }
}

// 检查函数：二分的判定条件
bool check(double x) {
    dfs_dp_tree(0,x);

    // 只要根节点(0号)选够 K+1 个人 (JYY + K个候选人) 的最大权值 >= 0
    // 说明平均值可以达到 x
    return  dp[0][K+1] >=0;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    // 二分答案
    // 范围 0 ~ 10000 (因为单个物品最大收益也就这么大)
    double l  = 0, r= 10000;
    
    // 循环 60 次，足以保证 double 精度
    for(int i = 1;i <= 60 ;++i ) // i: 1->60
    {
        double mid = (l+r) /2;
        if( check(mid))
            l = mid; // 可行，尝试更大的比值
        else
            r = mid; // 不可行，尝试更小的比值
    }
    std::cout << fixed << setprecision(3) << l << "\n";
    
    return 0;
}
