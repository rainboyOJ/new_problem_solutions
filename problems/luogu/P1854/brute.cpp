/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:36
 * update_at: 2026-10-26 16:36
 */
// brute.cpp: 小数据暴力解, 枚举 F 个花瓶编号的全部递增组合并取最大美学值.
// 输出格式与 main.cpp 完全一致(第一行最大值, 第二行 F 个递增花瓶编号).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 15;  // 暴力只用于小数据, F/V 取 10 左右, 组合数约 C(10,5)=252

ll F, V;
ll a[MAXN][MAXN];     // a[i][j]: 花束 i 放入花瓶 j 的美学值
ll choose[MAXN];      // choose[t]: 第 t 束花当前选择的花瓶编号
ll best[MAXN];        // best[t]: 当前最优方案中第 t 束花的花瓶编号
ll best_val = LLONG_MIN;

// dep: 正在决定第 dep 束花, pos: 第 dep 束花可选的最小花瓶编号(严格递增), sum: 已选美学值之和.
void dfs(ll dep, ll pos, ll sum) {
    if (dep == F + 1) {
        if (sum > best_val) {
            best_val = sum;
            for (int i = 1; i <= F; i++) {
                best[i] = choose[i];
            }
        }
        return;
    }
    for (int j = pos; j <= V; j++) {
        choose[dep] = j;
        dfs(dep + 1, j + 1, sum + a[dep][j]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> F >> V;
    for (int i = 1; i <= F; i++) {
        for (int j = 1; j <= V; j++) {
            cin >> a[i][j];
        }
    }

    dfs(1, 1, 0);

    cout << best_val << "\n";
    for (int i = 1; i <= F; i++) {
        cout << best[i] << (i == F ? '\n' : ' ');
    }

    return 0;
}
