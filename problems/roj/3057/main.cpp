/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:03
 * update_at: 2026-10-06 17:03
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXS = 2 * MAXN + 5; // 链上点数最多 2K-1，K 为压缩后的正段数

typedef long long ll;

ll n, m;
ll a[MAXN];
ll seg[MAXN]; // 压缩后的段和：正段为正，负段为负，0 已被丢弃

ll w[MAXS];      // 链上点权，下标 1..s，0 与 s+1 是 +INF 哨兵
ll prv[MAXS];    // 双向链表前驱
ll nxt[MAXS];    // 双向链表后继
char dead[MAXS]; // 懒删除标记，只有 0/1，用 char 控制内存

const ll INF = 1000000000000000LL; // 1e15：远大于任何合法代价之和，且相加不会溢出

priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > heap;

// 在链上选恰好 t 个两两不相邻的点，返回最小点权和（堆 + 双向链表反悔贪心）。
// 每步取当前最小点 i，再让 i 原地变成左右邻居的"后悔药"：
// 删掉左右邻居，令 w[i] = w[left] + w[right] - w[i] 放回堆，
// 于是再选一次 i 的净代价变成 w[left] + w[right]，等价于撤销本次并改选左右两点。
ll min_nonadjacent_sum(int s, ll t) {
    w[0] = INF;
    w[s + 1] = INF;
    prv[0] = 0;         // 左哨兵指向自己，反悔到左边界时不会读到越界下标
    nxt[s + 1] = s + 1; // 右哨兵同理
    for (int i = 1; i <= s; i++) {
        prv[i] = i - 1;
        nxt[i] = i + 1;
    }
    nxt[0] = 1;
    prv[s + 1] = s;
    for (int i = 0; i <= s + 1; i++) {
        dead[i] = 0;
    }
    while (!heap.empty()) {
        heap.pop();
    }
    for (int i = 1; i <= s; i++) {
        heap.push(make_pair(w[i], i));
    }

    ll cost = 0;
    for (ll step = 1; step <= t; step++) {
        pair<ll, int> cur = heap.top();
        heap.pop();
        ll value = cur.first;
        int i = cur.second;
        while (dead[i]) { // 已被左右邻居吞并的历史记录
            cur = heap.top();
            heap.pop();
            value = cur.first;
            i = cur.second;
        }
        cost += value;
        int left = prv[i];
        int right = nxt[i];
        dead[left] = 1;
        dead[right] = 1;
        w[i] = w[left] + w[right] - value;
        prv[i] = prv[left];
        nxt[i] = nxt[right];
        nxt[prv[left]] = i;
        prv[nxt[right]] = i;
        heap.push(make_pair(w[i], i));
    }
    return cost;
}

void solve() {
    // 1. 压缩：跳过 0，把同号连续元素合并成符号交替的段
    int cnt = 0;
    int i = 1;
    while (i <= n) {
        if (a[i] == 0) {
            i++;
            continue;
        }
        int positive = (a[i] > 0) ? 1 : 0;
        ll sum = 0;
        while (i <= n) {
            if (a[i] == 0) { // 0 不影响和，直接跳过，不打断同号段
                i++;
                continue;
            }
            if (((a[i] > 0) ? 1 : 0) != positive) {
                break;
            }
            sum += a[i];
            i++;
        }
        cnt++;
        seg[cnt] = sum;
    }

    // 2. 统计正段个数、正段总和，以及首尾正段的下标
    ll total = 0;
    int pos_cnt = 0;
    int first_pos = -1;
    int last_pos = -1;
    for (int j = 1; j <= cnt; j++) {
        if (seg[j] > 0) {
            total += seg[j];
            pos_cnt++;
            if (first_pos == -1) {
                first_pos = j;
            }
            last_pos = j;
        }
    }

    // 3. 平凡情形：一段都取不了，或段数不超过 M，全部正段都取
    if (m == 0 || pos_cnt == 0) {
        cout << 0 << "\n";
        return;
    }
    if (pos_cnt <= m) {
        cout << total << "\n";
        return;
    }

    // 4. 建链：从第一个正段到最后一个正段，正段记删除代价，负段记并过代价。
    //    需要在全部正段里做 t = pos_cnt - m 次操作，对应链上取 t 个不相邻的点。
    int s = 0;
    for (int j = first_pos; j <= last_pos; j++) {
        s++;
        if (seg[j] > 0) {
            w[s] = seg[j];
        } else {
            w[s] = -seg[j];
        }
    }
    ll t = pos_cnt - m;
    cout << total - min_nonadjacent_sum(s, t) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
