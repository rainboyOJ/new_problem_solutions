// main.cpp：用源点随机权值的哈希和维护“每个点出度是否都为 1”。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, m, q;
unsigned long long value_of_node[MAXN];
unsigned long long full_in_sum[MAXN]; // 终点为 v 的所有原始边的源点权值和
unsigned long long cur_in_sum[MAXN];  // 终点为 v 的当前可用边的源点权值和
unsigned long long target_sum;
unsigned long long current_sum;

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
    for (int i = 1; i <= n; i++) {
        value_of_node[i] = splitmix64((unsigned long long)i);
        target_sum += value_of_node[i];
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        full_in_sum[v] += value_of_node[u];
        cur_in_sum[v] += value_of_node[u];
        current_sum += value_of_node[u];
    }

    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            cur_in_sum[v] -= value_of_node[u];
            current_sum -= value_of_node[u];
        } else if (type == 2) {
            int v;
            cin >> v;
            current_sum -= cur_in_sum[v];
            cur_in_sum[v] = 0;
        } else if (type == 3) {
            int u, v;
            cin >> u >> v;
            cur_in_sum[v] += value_of_node[u];
            current_sum += value_of_node[u];
        } else {
            int v;
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
