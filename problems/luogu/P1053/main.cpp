#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
int want1[MAXN], want2[MAXN];
vector<int> g[MAXN];
int order_a[MAXN], order_b[MAXN];
int shift_cnt[MAXN];
bool vis[MAXN];

// 判断 u 是否把 v 当成自己希望相邻的同学。
bool like_each_other(int u, int v) {
    return want1[u] == v || want2[u] == v;
}

// 检查输入本身是否可能对应一个合法的环。
bool check_basic() {
    for (int i = 1; i <= n; i++) {
        if (want1[i] == i || want2[i] == i) {
            return false;
        }
        if (want1[i] == want2[i]) {
            return false;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!like_each_other(want1[i], i)) {
            return false;
        }
        if (!like_each_other(want2[i], i)) {
            return false;
        }
    }

    return true;
}

// 判断“愿望图”是否是一整个 n 个点的单环。
bool check_connected_cycle() {
    queue<int> q;
    int visited_cnt = 0;

    memset(vis, 0, sizeof(vis));
    vis[1] = true;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited_cnt++;

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    return visited_cnt == n;
}

// 从 1 号点出发，沿着一个方向把整条环序写出来。
bool build_order(int start_next, int order_arr[]) {
    memset(vis, 0, sizeof(vis));

    order_arr[0] = 1;
    order_arr[1] = start_next;
    vis[1] = true;
    vis[start_next] = true;

    for (int i = 2; i < n; i++) {
        int prev = order_arr[i - 2];
        int u = order_arr[i - 1];
        int nxt = (g[u][0] == prev ? g[u][1] : g[u][0]);

        if (vis[nxt]) {
            return false;
        }
        order_arr[i] = nxt;
        vis[nxt] = true;
    }

    int last = order_arr[n - 1];
    bool close_to_one = false;
    for (int i = 0; i < 2; i++) {
        if (g[last][i] == 1) {
            close_to_one = true;
        }
    }

    return close_to_one;
}

// 对一个固定方向的环序，统计所有旋转里最多能保留多少人不动。
int calc_best_keep(int order_arr[]) {
    int best = 0;

    for (int i = 0; i < n; i++) {
        shift_cnt[i] = 0;
    }

    for (int pos = 0; pos < n; pos++) {
        int student = order_arr[pos];
        int original_pos = student - 1;
        int shift = pos - original_pos;
        shift %= n;
        if (shift < 0) {
            shift += n;
        }
        shift_cnt[shift]++;
    }

    for (int i = 0; i < n; i++) {
        best = max(best, shift_cnt[i]);
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> want1[i] >> want2[i];
        g[i].push_back(want1[i]);
        g[i].push_back(want2[i]);
    }

    if (!check_basic()) {
        cout << -1 << '\n';
        return 0;
    }

    if (!check_connected_cycle()) {
        cout << -1 << '\n';
        return 0;
    }

    if (!build_order(g[1][0], order_a)) {
        cout << -1 << '\n';
        return 0;
    }

    // 反方向的环序，就是把正方向除了 1 号之外反过来。
    order_b[0] = order_a[0];
    for (int i = 1; i < n; i++) {
        order_b[i] = order_a[n - i];
    }

    int best_keep = max(calc_best_keep(order_a), calc_best_keep(order_b));

    // 每个最终不在原位的人至少要被移动一次；
    // 而一个置换环可以用一次循环换位直接完成，所以答案就是“离开原位的人数”。
    cout << n - best_keep << '\n';

    return 0;
}
