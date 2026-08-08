#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

struct Query {
    int l, r, id;
};

int n, m;
int a[MAXN];
int last_pos[MAXN]; // last_pos[color] 表示这种颜色最近一次出现的位置。
int bit_tree[MAXN]; // 树状数组维护每种颜色在当前前缀中的最后一次出现位置。
int answer[MAXN];
Query queries[MAXN];

bool cmp_query(const Query &x, const Query &y) {
    return x.r < y.r;
}

void add(int pos, int value) {
    while (pos <= n) {
        bit_tree[pos] += value;
        pos += pos & -pos;
    }
}

int prefix_sum(int pos) {
    int sum = 0;
    while (pos > 0) {
        sum += bit_tree[pos];
        pos -= pos & -pos;
    }
    return sum;
}

int range_sum(int l, int r) {
    return prefix_sum(r) - prefix_sum(l - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }
    sort(queries + 1, queries + m + 1, cmp_query);

    int now_r = 0;
    for (int i = 1; i <= m; i++) {
        while (now_r < queries[i].r) {
            now_r++;
            // 每种颜色只在它最新出现的位置贡献 1。
            if (last_pos[a[now_r]] != 0) {
                add(last_pos[a[now_r]], -1);
            }
            add(now_r, 1);
            last_pos[a[now_r]] = now_r;
        }
        answer[queries[i].id] = range_sum(queries[i].l, queries[i].r);
    }

    for (int i = 1; i <= m; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
