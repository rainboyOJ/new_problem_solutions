/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:03
 * update_at: 2026-11-10 23:03
 */
// brute.cpp：小数据暴力搜索，每个序列 a_1 ... a_n 直接枚举检验
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int n, m, K;
int v[105];
long long ans = 0;
vector<int> a;

void dfs(int step) {
    if (step == n) {
        // 计算 S = sum(2^{a_i})
        long long s = 0;
        long long cur_w = 1;
        for (int x : a) {
            s += (1LL << x);
            cur_w = (cur_w * v[x]) % MOD;
        }

        if (__builtin_popcountll(s) <= K) {
            ans = (ans + cur_w) % MOD;
        }
        return;
    }

    for (int x = 0; x <= m; ++x) {
        a.push_back(x);
        dfs(step + 1);
        a.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> K)) return 0;
    for (int i = 0; i <= m; ++i) {
        cin >> v[i];
    }

    dfs(0);

    cout << ans << "\n";

    return 0;
}
