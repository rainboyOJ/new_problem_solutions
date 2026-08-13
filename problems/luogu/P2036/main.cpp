/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:21
 * update_at: 2026-08-13 13:21
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int s[MAXN], b[MAXN]; // 第 i 种配料的酸度与苦度
int choose[MAXN];     // choose[i] = 1 表示选第 i 种配料
int ans = 2e9;        // |总酸度 - 总苦度| 的最小值

// 叶子节点：检查当前完整 choose[1..n] 是否合法，并更新答案。
void check() {
    int sour = 1;   // 总酸度是乘积，初值为 1
    int bitter = 0; // 总苦度是求和，初值为 0
    int cnt = 0;    // 统计选了几种配料

    for (int i = 1; i <= n; i++) {
        if (choose[i] == 1) {
            cnt++;
            sour *= s[i];
            bitter += b[i];
        }
    }

    if (cnt == 0) // 至少选一种配料，全不选的情况直接跳过
        return;

    int diff = abs(sour - bitter);
    if (diff < ans)
        ans = diff;
}

// dfs(dep) 枚举第 dep 种配料选不选，生成完整 01 选择序列。
void dfs(int dep) {
    if (dep == n + 1) { // 一条完整 01 序列已经生成
        check();
        return;
    }

    choose[dep] = 0; // 不选第 dep 种配料
    dfs(dep + 1);
    choose[dep] = 1; // 选第 dep 种配料
    dfs(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> b[i];
    }

    dfs(1); // 从第 1 种配料开始枚举

    cout << ans << endl;
    return 0;
}
