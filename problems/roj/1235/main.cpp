/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:12
 * update_at: 2026-10-05 06:12
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

// a[i]：第 i 个数组元素；值域是 ±1e9，用 ll 保存。
ll a[MAXN];

ll n; // 数组长度
ll k; // 要输出的最大数个数

void read_input() {
    // 按 token 流读入，容忍前导空行与任意空白分隔（也能处理负数）。
    string buf;
    vector<ll> tok;
    while (cin >> buf) {
        tok.push_back(atoll(buf.c_str()));
    }
    n = tok[0];
    for (ll i = 1; i <= n; i++) {
        a[i] = tok[i];
    }
    k = tok[n + 1];
}

void solve() {
    // 前 k 大 = 降序排序后的前 k 项，sort 默认升序，再用 greater<ll>() 翻成降序。
    sort(a + 1, a + n + 1, greater<ll>());
    // 逐行输出前 k 项
    for (ll i = 1; i <= k; i++) {
        cout << a[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}