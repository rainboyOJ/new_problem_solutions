#include <iostream>
#include <cstring> // 用来支持 memset 清空数组
#include <algorithm> // 用来支持 max 函数

using namespace std;

// 估算一下数组大小：
// 40年后资产大概翻40-50倍，差不多是 5000万。
// 题目有个优化：投资额都除以 1000。
// 所以 50000000 / 1000 = 50000。
// 我们开大一点点，开到 50005 就够了。
int dp[50005]; 

// 题目说 d <= 10，这两个数组开 20 就足够安全了
int a[20]; // 存放每种债券的投资额 (重量)
int b[20]; // 存放每种债券的年利息 (价值)

int main() {
    int s, n, d;
    cin >> s >> n >> d;

    // 1. 输入数据
    for(int i = 1; i <= d; i++) {
        cin >> a[i] >> b[i];
    }

    // 2. 循环每一年的投资
    for(int k = 1; k <= n; k++) {
        // --- 优化 ---
        // 把总资产除以 1000，作为背包的容量
        int max_cap = s / 1000;

        // --- 清空 DP 数组 ---
        // 每年开始都要把 dp 数组清零，因为本金变了，要重新算
        // sizeof(dp) 表示清空整个数组
        memset(dp, 0, sizeof(dp));

        // 3. 完全背包核心代码
        for(int i = 1; i <= d; i++) {
            // 拿出第 i 种债券的信息
            // 记得重量（投资额）也要除以 1000
            int weight = a[i] / 1000; 
            int value = b[i];

            // 从小到大遍历 -> 完全背包
            for(int j = weight; j <= max_cap; j++) {
                if (dp[j - weight] + value > dp[j]) {
                    dp[j] = dp[j - weight] + value;
                }
                // 上面这三行也可以写成：
                // dp[j] = max(dp[j], dp[j - weight] + value);
            }
        }

        // 4. 年终结算
        // s (新本金) = s (旧本金) + dp[max_cap] (这一年赚的最大利息)
        s += dp[max_cap];
    }

    cout << s << endl;

    return 0;
}
