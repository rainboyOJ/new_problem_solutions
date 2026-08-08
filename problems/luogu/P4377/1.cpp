/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-06 16:06:26
 * Algorithm: 01分数规划 + 01背包 (带状态压缩: 至少装满W)
 * * 核心逻辑：
 * 1. 二分答案 x，判断是否存在一组牛，使得 (总才艺 / 总重量) >= x
 * 2. 变形为：总才艺 - x * 总重量 >= 0
 * 3. 这里的 DP 用于求 max(总才艺 - x * 总重量)，限制是总重量 >= W
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 255;
const int maxw = 1005; 
const ll inf = 1e18; // 足够大，防止负数不够小

int n, m, W;
int w[maxn], t[maxn];
// dp[i] 表示：重量“恰好”为 i 时的最大权值
// 特殊定义：dp[W] 表示重量 “>= W” 时的最大权值 (这是压缩点)
double dp[maxw]; 

void init(){
    std::cin >> n >> W;
    for(int i = 1; i <= n; ++i) {
        std::cin >> w[i] >> t[i];
    }
}

// Check函数：判定比值 x 是否可行
bool check(double x){

    // 1. 初始化 DP
    // 因为权值 t[i] - x*w[i] 可能是负数，且我们要取 max
    // 所以必须初始化为负无穷，只有起点 dp[0] 是合法的 0
    for(int i = 1; i <= W; ++i) 
        dp[i] = -inf;
    dp[0] = 0;

    // 2. 01背包开始
    // 外层枚举物品 (牛)
    for(int i = 1; i <= n; i++) {
        // 当前这头牛的新权值 (分数规划转化后的权值)
        double new_v = (double)t[i] - x * w[i];

        // 内层枚举容量 (重量)
        // 【关键】01背包必须倒序！防止同一头牛被选多次
        // j 代表“加入这头牛之前”的重量状态
        for(int j = W; j >= 0; j--) {

            // 【状态压缩核心】
            // 如果 j + w[i] 超过了 W，我们不需要记录具体是 W+100 还是 W+1000
            // 只要达到 W，对于题目条件“至少W”来说就是等价的
            // 所以我们把所有溢出的重量都截断在 W 这个“桶”里
            int target = min(W, j + w[i]);
            
            // 只有从合法的状态 (非-inf) 转移才有意义
            if( dp[j] != -inf) { 
                dp[target] = std::max(dp[target], dp[j] + new_v);
            }
        }
    }

    // 只要最终状态 (重量 >= W) 的最大权值 >= 0，说明这个平均值 x 是可以达到的
    return dp[W] >= 0;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    // 开始二分答案
    // 最小比值 0
    // 最大比值：假设牛重1，才艺1000，最大也就1000
    double l = 0, r = 1000;

    // 循环100次，精度足够覆盖 double 范围
    // 这种写法比 while(r-l > eps) 更稳健
    for(int i = 1; i <= 100; ++i) {
        double mid = (l + r) / 2;
        if( check(mid) )
            l = mid; // 如果可行，说明答案可能更大 (往右找)
        else
            r = mid; // 如果不可行，说明猜大了 (往左找)
    }
    
    // 题目要求输出 1000 * 答案 的向下取整
    // 这里的 l 就是最终求得的最大比值
    cout << (long long)(l * 1000) << "\n";
    
    return 0;
}
