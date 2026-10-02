/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:28
 * update_at: 2026-10-01 22:28
 */
// main.cpp：给每个据点一个 64 位权值，用全图可用边的权值和判断是否所有据点出度恰好为 1。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;   // n <= 5e5

int n, m, q;

// 权值数组用 unsigned long long，因为哈希要依赖 2^64 的自然回绕做模运算。
// 这里刻意选无符号：有符号溢出是未定义行为，无法当作取模。
unsigned long long value_of_node[MAXN]; // value_of_node[u]：据点 u 的固定权值
unsigned long long full_in_sum[MAXN];   // full_in_sum[v]：原图中所有终点为 v 的虫洞的源点权值和
unsigned long long cur_in_sum[MAXN];    // cur_in_sum[v]：当前可用、终点为 v 的虫洞的源点权值和
unsigned long long target_sum;          // 所有据点出度都恰好为 1 时的全图贡献和
unsigned long long current_sum;         // 当前可用虫洞的全图贡献和

// splitmix64：把一个整数打散成 64 位权值，只是为了让不同据点的权值互不相关。
unsigned long long splitmix64(unsigned long long x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        value_of_node[i] = splitmix64(i);
        target_sum += value_of_node[i];
    }

    // 一条可用虫洞 u -> v 贡献 value_of_node[u]，于是
    // current_sum = sum( value_of_node[u] * 据点 u 当前的出度 )。
    for (ll i = 1; i <= m; i++) {
        ll u, v;
        cin >> u >> v;
        full_in_sum[v] += value_of_node[u];
        cur_in_sum[v] += value_of_node[u];
        current_sum += value_of_node[u];
    }

    cin >> q;
    while (q--) {
        ll type;
        cin >> type;

        if (type == 1) {
            // 摧毁虫洞 u -> v，它对全图贡献 value_of_node[u]。
            ll u, v;
            cin >> u >> v;
            cur_in_sum[v] -= value_of_node[u];
            current_sum -= value_of_node[u];
        } else if (type == 2) {
            // 摧毁据点 v 的全部虫洞，也就是终点为 v 的所有可用虫洞。
            ll v;
            cin >> v;
            current_sum -= cur_in_sum[v];
            cur_in_sum[v] = 0;
        } else if (type == 3) {
            // 修复虫洞 u -> v。
            ll u, v;
            cin >> u >> v;
            cur_in_sum[v] += value_of_node[u];
            current_sum += value_of_node[u];
        } else {
            // 修复据点 v 的全部虫洞，恢复成原图中终点为 v 的那批。
            ll v;
            cin >> v;
            current_sum += full_in_sum[v] - cur_in_sum[v];
            cur_in_sum[v] = full_in_sum[v];
        }

        if (current_sum == target_sum) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
