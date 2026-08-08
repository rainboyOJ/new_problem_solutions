/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 15:26
 * update_at: 2026-07-31 15:27
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// 每一层为第 depth 个盘子选择一个苹果数（0..m），
// 到叶子节点统一检查：总数等于 m，且序列不下降，这样每个分法只被数一次。
#include <bits/stdc++.h>
using namespace std;

int m, n;
int choose[15]; // choose[i] 记录第 i 个盘子选了几个苹果
int ans;        // 当前一组数据的答案

void dfs(int depth) {
    if (depth == n + 1) {
        // 完整选择序列已生成，在叶子统一检查合法性。
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += choose[i];
        }
        if (sum != m) {
            return;
        }

        // 同一组分法只保留“不下降序列”这一种写法，避免重复计数。
        for (int i = 2; i <= n; i++) {
            if (choose[i] < choose[i - 1]) {
                return;
            }
        }
        ans++;
        return;
    }

    // 第 depth 个盘子可以选择 0..m 个苹果。
    for (int i = 0; i <= m; i++) {
        choose[depth] = i;
        dfs(depth + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> m >> n;
        ans = 0;
        dfs(1);
        cout << ans << endl;
    }
    return 0;
}
