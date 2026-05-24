/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-05 23:31:22
 * Problem: P1642 规划
 * Algorithm: 01分数规划 + 树形DP (分组背包)
 * * 核心思想：
 * 1. 二分答案 x (假设最大比值为 x)
 * 2. 判定不等式 sum(w) / sum(c) >= x  =>  sum(w - x*c) >= 0
 * 3. 问题转化为：在树上选 K 个连通点，使得新权值 (w - x*c) 的和最大
 */

#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e2+5;
const double NINF  = -1e9; // 负无穷：因为权值可能是负数，初始化必须足够小

int n, m, K; // K: 最终需要保留的节点数量 (N - M)
int w[maxn]; // 产值
int c[maxn]; // 污染值
double dp[maxn][maxn]; // dp[u][j]: 以u为根的子树，选j个点(必须包含u)的最大权值
int sz[maxn]; // 子树大小

std::vector<int> g[maxn]; // 邻接表存图

// 预处理子树大小 (虽然N=100时可以不优化，但这是个好习惯)
void dfs_get_sz(int u, int fa) {
    sz[u] = 1;
    for(int v : g[u]) {
        if(v == fa) continue;
        dfs_get_sz(v, u);
        sz[u] += sz[v];
    }
}

// 读入数据并建图
void init() {
    std::cin >> n >> m;
    K = n - m; // 题目要求拆除M个，也就是保留 N-M 个
    
    for(int i = 1; i <= n; ++i) std::cin >> w[i];
    for(int i = 1; i <= n; ++i) std::cin >> c[i];
    
    for(int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_get_sz(1, 0); // 先算出每个子树有多大
}

/**
 * 核心 DP 函数
 * u: 当前节点
 * fa: 父节点 (防止往回走)
 * x: 当前二分检查的比值
 */
void dfs(int u, int fa, double x) {
    // 【关键点1】权值转换
    // 将求比值转化为求和：新的点权 = w[u] - x * c[u]
    // 状态初始化：只选 u 自己 1 个点的情况
    dp[u][1] = (double)w[u] - x * c[u];

    // 初始化其他状态为负无穷
    // 因为必须选 u 才能连通，如果凑不够 i 个点，该状态就是非法的
    for(int i = 2; i <= K; ++i) 
        dp[u][i] = NINF;

    // 遍历每一个子节点 (相当于分组背包中的“物品组”)
    for(int v : g[u]) {
        if(v == fa) continue;
        
        // 递归处理子树，先把子树的最优解算出来
        dfs(v, u, x);

        // 【关键点2】树上分组背包合并
        // j: 当前 u 子树准备选的总点数 (背包容量)
        // 必须倒序枚举！防止同一个子树被重复利用 (和 0/1 背包同理)
        for(int j = K; j >= 2; j--) {
            
            // k: 分给子树 v 的点数 (组内物品枚举)
            // k 的上限是 j-1，这是为了保证 u 自己必须占 1 个位置！
            // 如果 k = j，说明全部分给了子树，根节点 u 就没被选中，连通性就断了
            for(int k = 1; k <= j - 1; k++) {
                // 状态转移：尝试把子树 v 选 k 个的方案合并进来
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
            }
        }
    }
}

// 检查函数：判断是否存在一种选法，使得平均值 >= x
bool check(double x) {
    dfs(1, 0, x); // 以1为根进行DP
    
    // 只要树中任意一个位置，凑够了 K 个点，且权值和 >= 0
    // 说明实际比值可以达到 x (甚至更大)
    for(int i = 1; i <= n; ++i) {
        if(dp[i][K] >= 0) return true;
    }
    return false;
}

signed main() {
    // 加速 C++ 输入输出
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    // 【关键点3】二分答案
    // 答案的范围：最小是 0，最大也就是 max(w_i) / min(c_i) <= 10000
    double l = 0, r = 10000;

    // 固定循环 100 次
    // 这是竞赛常用技巧：比 while(r - l > eps) 更快且不用担心精度死循环
    // 2^100 次方在这个范围内精度已经极高了
    for(int i = 0; i < 100; i++) {
        double mid = (l + r) / 2;
        if(check(mid)) 
            l = mid; // 可行，说明答案可能更大，尝试往右找
        else
            r = mid; // 不可行，说明猜大了，往左找
    }

    // 输出结果，保留一位小数
    std::cout << fixed << std::setprecision(1) << l << "\n";
    
    return 0;
}
