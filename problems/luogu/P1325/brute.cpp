/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 17:28
 * update_at: 2026-09-27 17:30
 */
// brute.cpp：小数据暴力解，使用 01 序列枚举「在哪些小岛区间的右端点放雷达」。
// 每层递归决定第 dep 个区间的右端点是否放雷达，生成完整 choose[1..n] 后在叶子检查。
// 结论：一定存在一个最优解，它的每个雷达都落在某个区间的右端点，所以这样枚举不会漏解。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 25; // 枚举 2^n 种方案，只适合 n 很小的情况
const double EPS = 1e-9;

int n;
double d;
double L[MAXN], R[MAXN]; // 第 i 个小岛对应的雷达可选区间
int choose[MAXN];        // choose[i] = 1 表示在第 i 个区间的右端点放雷达
int ans;

// 检查当前放置方案是否覆盖了所有小岛
bool check() {
    for (int j = 1; j <= n; j++) {
        bool covered = false;
        for (int i = 1; i <= n; i++) {
            // 雷达放在 R[i]，能覆盖小岛 j <=> R[i] 落在 [L[j], R[j]] 内
            if (choose[i] == 1 && L[j] <= R[i] + EPS && R[i] <= R[j] + EPS) {
                covered = true;
            }
        }
        if (!covered) return false;
    }
    return true;
}

// 统计当前方案使用的雷达数量
int calc_answer() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 1) cnt++;
    }
    return cnt;
}

void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (value < ans) ans = value;
        }
        return;
    }

    // 这一层决定第 dep 个区间的右端点要不要放雷达
    for (int v = 0; v <= 1; v++) {
        choose[dep] = v;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        if (y > d) {
            ok = false;
        }
        double half = sqrt(max(0.0, d * d - (double)y * y));
        L[i] = x - half;
        R[i] = x + half;
    }

    if (!ok) {
        cout << -1 << "\n";
        return 0;
    }

    ans = n + 1;
    dfs(1);
    cout << ans << "\n";
    return 0;
}
