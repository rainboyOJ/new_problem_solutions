/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:32
 * update_at: 2026-10-05 05:32
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005; // 小朋友数上限
const int MAXM = 700005; // 边数上限：K 条约束最多 2K 条边 + 超级源点 N 条边

typedef long long ll;

int n, k;
int head[MAXN], nxt[MAXM], to[MAXM], edge_cnt; // 链式前向星
ll weight[MAXM]; // 边权：不等式右边的常数
ll dist_arr[MAXN]; // dist_arr[v] = x_v 的最小值（最长路距离）
int cnt[MAXN]; // cnt[v] = v 被松弛的次数，用来检测正环
bool in_stack[MAXN]; // v 是否在栈里
int stk[MAXN]; // 手写栈：后进先出，比队列更快检测出正环
ll top_p; // 栈顶指针

// 加一条 u -> v、权为 w 的边，含义是 x_v >= x_u + w。
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) {
            // x_A = x_B：双向 0 边
            add_edge(a, b, 0);
            add_edge(b, a, 0);
        }
        else if (x == 2) {
            // x_A < x_B，即 x_B >= x_A + 1；A = B 时自相矛盾，靠正环判无解
            add_edge(a, b, 1);
        }
        else if (x == 3) {
            // x_A >= x_B，即 x_A >= x_B + 0
            add_edge(b, a, 0);
        }
        else if (x == 4) {
            // x_A > x_B，即 x_A >= x_B + 1
            add_edge(b, a, 1);
        }
        else {
            // x_A <= x_B，即 x_B >= x_A + 0
            add_edge(a, b, 0);
        }
    }
    // 超级源点 0：每个小朋友至少 1 颗糖果，即 x_i >= x_0 + 1
    for (int i = 1; i <= n; i++) {
        add_edge(0, i, 1);
    }
}

// 从超级源点 0 跑最长路；返回糖果总和，存在正环（无解）时返回 -1。
ll solve() {
    // 距离初始化为 0（x_0 = 0），所有点先入栈
    top_p = 0;
    for (int i = 0; i <= n; i++) {
        dist_arr[i] = 0;
        cnt[i] = 0;
        in_stack[i] = true;
        top_p++;
        stk[top_p] = i;
    }

    while (top_p > 0) {
        int u = stk[top_p];
        top_p--;
        in_stack[u] = false;
        ll du = dist_arr[u];
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (dist_arr[v] < du + weight[i]) {
                dist_arr[v] = du + weight[i];
                cnt[v] = cnt[u] + 1; // 借助路径长度判正环
                if (cnt[v] > n) return -1;
                if (!in_stack[v]) {
                    top_p++;
                    stk[top_p] = v;
                    in_stack[v] = true;
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dist_arr[i];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << solve() << endl;

    return 0;
}
