#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
const int MAXR = 1000000 + 5;

using i128 = __int128_t;

struct HeapNode {
    int u;
    i128 dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n;
i128 normal_cost[MAXN], magic_cost[MAXN];
i128 dist_arr[MAXN];   // 杀死一只 i 号怪兽的最小体力
i128 sum_cost[MAXN];   // 如果选择普通攻击，当前已经知道的总代价
int remain_need[MAXN]; // 这个普通攻击方案里，还有多少只后继怪兽代价没汇总完
bool vis[MAXN];

int head_rev[MAXN], to_rev[MAXR], nxt_rev[MAXR], rev_cnt;

void add_rev_edge(int child, int parent) {
    rev_cnt++;
    to_rev[rev_cnt] = parent;
    nxt_rev[rev_cnt] = head_rev[child];
    head_rev[child] = rev_cnt;
}

string to_string_i128(i128 x) {
    if (x == 0) {
        return "0";
    }

    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }

    string s;
    while (x > 0) {
        int digit = (int) (x % 10);
        s.push_back(char('0' + digit));
        x /= 10;
    }
    if (neg) {
        s.push_back('-');
    }
    reverse(s.begin(), s.end());
    return s;
}

void solve() {
    priority_queue<HeapNode> pq;

    for (int i = 1; i <= n; i++) {
        dist_arr[i] = magic_cost[i];
        if (remain_need[i] == 0 && sum_cost[i] < dist_arr[i]) {
            dist_arr[i] = sum_cost[i];
        }
        pq.push({i, dist_arr[i]});
    }

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        // 当子怪兽 u 的最优代价确定后，它会让一批“父怪兽”的普通攻击方案更便宜。
        for (int i = head_rev[u]; i != 0; i = nxt_rev[i]) {
            int parent = to_rev[i];
            remain_need[parent]--;
            sum_cost[parent] += dist_arr[u];

            if (remain_need[parent] == 0 && sum_cost[parent] < dist_arr[parent]) {
                dist_arr[parent] = sum_cost[parent];
                pq.push({parent, dist_arr[parent]});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    rev_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head_rev[i] = 0;
        vis[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        long long s, k;
        int r;
        cin >> s >> k >> r;

        normal_cost[i] = (i128) s;
        magic_cost[i] = (i128) k;
        sum_cost[i] = normal_cost[i];
        remain_need[i] = r;

        for (int j = 1; j <= r; j++) {
            int child;
            cin >> child;
            add_rev_edge(child, i);
        }
    }

    solve();
    cout << to_string_i128(dist_arr[1]) << '\n';

    return 0;
}
