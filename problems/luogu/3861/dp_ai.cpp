#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 题目要求的模数
const int MOD = 998244353;

long long n;
long long ans;
vector<long long> divs;

void solve() {
    long long n;
    cin >> n;
    
    // 1. 获取所有因子
    vector<long long> divs;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i * i != n) divs.push_back(n / i);
        }
    }
    sort(divs.begin(), divs.end());
    
    // 映射：数值 -> 下标 (为了快速查找状态)
    // 注意：用 map 会增加 log 复杂度，会让本来就慢的 DP 更慢
    // 我们可以用二分查找 (lower_bound) 代替 map
    
    int m = divs.size();
    vector<long long> dp(m, 0);
    
    // 初始状态：乘积为 1 的方案数为 1
    dp[0] = 1; 

    // 2. 0/1 背包 DP
    // 外层枚举“物品”：每一个可能的因子（除了1）
    for (int i = 1; i < m; i++) {
        long long factor = divs[i];
        
        // 内层倒序枚举“容量”：即 divs 中的每一个数
        for (int j = m - 1; j >= 0; j--) {
            long long target = divs[j];
            
            // 如果 target 是 factor 的倍数，且除去 factor 后的数也在因子列表中
            if (target % factor == 0) {
                long long pre_val = target / factor;
                
                // 二分查找 pre_val 对应的下标
                // 因为我们是对所有因子做 DP，target 是 n 的因子，factor 是 n 的因子
                // target / factor 一定也是 n 的因子，所以一定能找到
                int pre_idx = lower_bound(divs.begin(), divs.end(), pre_val) - divs.begin();
                
                // 必须保证 pre_val < factor 吗？
                // 不！0/1背包的逻辑是：对于当前物品 factor，我们要么选，要么不选。
                // dp[j] 目前存储的是“不选 factor 凑出 j 的方案数”
                // 加上 dp[pre_idx] 就是“选了 factor 凑出 j 的方案数”
                // 这里的 dp[pre_idx] 是还没放入 factor 的状态，天然保证了互不相同。
                
                // 核心问题：0/1 背包只保证每个物品用一次，不保证顺序。
                // 题目要求的是组合数（顺序无关），0/1背包算的正是组合数。
                // 但题目要求因子 > 1。
                
                dp[j] = (dp[j] + dp[pre_idx]) % MOD;
            }
        }
    }

    // 答案是凑出 n 的方案数，减去 n 本身作为因子的情况（题目要求分解成多个）
    // 但这里的逻辑有点微妙，因为上面的背包其实算出的是“任意个不同因子的乘积”。
    // 其中包含 1 * n 这种情况。
    // 如果 dp[m-1] 算出来包含 n 本身，那就要 -1。
    cout << (dp[m - 1] - 1 + MOD) % MOD << endl;
}

int main() {
    // 优化 I/O
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
