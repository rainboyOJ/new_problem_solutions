/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-05 08:48:02
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义新物品结构体
struct Goods {
    int v, w;
};

int n, W;
// dp数组，大小需要超过最大载重
int dp[40005];
vector<Goods> goods_list;

int main() {
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> W;

    // 1. 二进制拆分过程
    for (int i = 0; i < n; ++i) {
        int v, w, m;
        cin >> v >> w >> m;
        // 将m拆分为 1, 2, 4, ...
        for (int k = 1; k <= m; k <<= 1) {
            goods_list.push_back({k * v, k * w});
            m -= k;
        }
        // 处理剩下的余数 R
        if (m > 0) {
            goods_list.push_back({m * v, m * w});
        }
    }

    // 2. 0/1 背包过程
    for (const auto& g : goods_list) {
        // 0/1 背包内层循环倒序
        for (int j = W; j >= g.w; --j) {
            dp[j] = max(dp[j], dp[j - g.w] + g.v);
        }
    }

    cout << dp[W] << endl;

    return 0;
}
