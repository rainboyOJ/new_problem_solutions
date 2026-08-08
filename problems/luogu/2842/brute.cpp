// brute.cpp：小数据暴力解，使用递归枚举每种纸币的使用张数，求最少总张数。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;

int n;          // 纸币种类数
int w;          // 要凑出的金额
int a[MAXN];    // 每种纸币的面额
int answer;     // 最少张数

// dep：当前正在决定第 dep 种纸币的使用张数
// used：已经使用的纸币总张数
// remain：剩余需要凑出的金额
void dfs(int dep, int used, int remain) {
    if (dep == n + 1) {
        if (remain == 0 && used < answer)
            answer = used;
        return;
    }

    // 枚举第 dep 种纸币用 cnt 张
    int max_cnt = remain / a[dep];
    for (int cnt = 0; cnt <= max_cnt; cnt++) {
        dfs(dep + 1, used + cnt, remain - cnt * a[dep]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    answer = INF;
    dfs(1, 0, w);
    cout << answer << '\n';

    return 0;
}
