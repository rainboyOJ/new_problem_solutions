/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 15:26
 * update_at: 2026-07-31 15:27
 */
// P2386 放苹果：DFS 枚举不下降序列，统计不同分法。
#include <bits/stdc++.h>
using namespace std;

int m, n;    // m 个苹果，n 个盘子
int ans;     // 当前一组数据的答案
int a[15];   // a[i] 记录第 i 个盘子放的苹果数，保证 a[1] <= a[2] <= ... <= a[n]

// 当前在填第 depth 个盘子，还剩 apple 个苹果没放。
// 为了保证序列不下降，第 depth 个盘子至少要放 a[depth-1] 个。
void dfs(int depth, int apple) {
    if (depth == n) {
        // 最后一个盘子吃掉所有剩下的苹果；
        // 只要它不比前一个盘子少，就得到一个合法的分法。
        if (apple >= a[depth - 1]) {
            ans++;
        }
        return;
    }

    // 枚举第 depth 个盘子放 i 个苹果：
    // i 既要不小于前一个盘子，又不超过剩余苹果数。
    for (int i = a[depth - 1]; i <= apple; i++) {
        a[depth] = i;
        dfs(depth + 1, apple - i);
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
        dfs(1, m);
        cout << ans << endl;
    }
    return 0;
}
