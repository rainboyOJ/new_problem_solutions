/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* CF19D Points */
/* 离线坐标压缩：每个 x 组用 Fenwick 维护活跃 y，外层线段树存每组最大 y。
 * find 时先在线段树找第一个 x 更大且最大 y 更大的组，
 * 再在该组 Fenwick 里找第一个大于 query_y 的活跃 y。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

int n;                         // 操作数
char op[MAXN];
long long ox[MAXN], oy[MAXN];  // 操作参数
vector<long long> xs;          // 所有出现过的 x（升序去重），下标即组号
vector<long long> ys;          // 每个组的 y 连续存放
vector<int> yoff;              // yoff[g]..yoff[g+1] 是组 g 的 y 区间
vector<long long> fenwick;     // 所有组的 Fenwick 共享一块数组
vector<int> bit_off;           // 组 g 的 Fenwick 起点
vector<int> cnt;               // 组 g 当前活跃点数
vector<long long> seg;         // 线段树：组 g 当前最大 y（空组为 -1）
int groups, seg_size;

int bit_len(int g) {
    return yoff[g + 1] - yoff[g];
}

void bit_add(int g, int idx, int delta) {
    int base = bit_off[g];
    int len = bit_len(g);
    while (idx <= len) {
        fenwick[base + idx] += delta;
        idx += idx & -idx;
    }
}

long long bit_sum(int g, int idx) {
    int base = bit_off[g];
    long long res = 0;
    while (idx > 0) {
        res += fenwick[base + idx];
        idx -= idx & -idx;
    }
    return res;
}

// 组内找第 target 个活跃 y 的压缩下标（Fenwick 二进制提升）
int bit_kth(int g, long long target) {
    int base = bit_off[g];
    int len = bit_len(g);
    int idx = 0;
    int step = 1 << (31 - __builtin_clz(len)); // 不超过 len 的最大 2 的幂
    while (step) {
        int nxt = idx + step;
        if (nxt <= len && fenwick[base + nxt] < target) {
            idx = nxt;
            target -= fenwick[base + nxt];
        }
        step >>= 1;
    }
    return idx + 1;
}

void seg_set(int idx, long long value) {
    int node = seg_size + idx;
    seg[node] = value;
    for (node >>= 1; node; node >>= 1)
        seg[node] = max(seg[node << 1], seg[node << 1 | 1]);
}

// 找下标 >= start 且最大 y > y 的最小组号；没有则 -1
int first_x(int node, int l, int r, int start, long long y) {
    if (r <= start || seg[node] <= y)
        return -1;
    if (r - l == 1)
        return l;
    int mid = (l + r) >> 1;
    int res = first_x(node << 1, l, mid, start, y);
    if (res != -1)
        return res;
    return first_x(node << 1 | 1, mid, r, start, y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    set<pair<long long, long long>> points;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s >> ox[i] >> oy[i];
        op[i] = s[0];
        if (op[i] == 'a')
            points.insert({ox[i], oy[i]});
    }

    // 坐标压缩：x 升序去重，每个 x 的 y 升序去重
    for (auto &p : points) {
        if (xs.empty() || xs.back() != p.first) {
            xs.push_back(p.first);
            yoff.push_back((int)ys.size());
        }
        ys.push_back(p.second);
    }
    yoff.push_back((int)ys.size());
    groups = (int)xs.size();

    bit_off.assign(groups + 1, 0);
    for (int g = 0; g < groups; g++)
        bit_off[g + 1] = bit_off[g] + bit_len(g) + 1;
    fenwick.assign(bit_off[groups], 0);
    cnt.assign(groups, 0);

    seg_size = 1;
    while (seg_size < groups)
        seg_size <<= 1;
    seg.assign(2 * seg_size, -1);

    for (int i = 0; i < n; i++) {
        if (op[i] != 'f') {
            int g = (int)(lower_bound(xs.begin(), xs.end(), ox[i]) - xs.begin());
            int s = yoff[g], e = yoff[g + 1];
            int pos = (int)(lower_bound(ys.begin() + s, ys.begin() + e, oy[i]) - ys.begin()) - s + 1;
            int delta = (op[i] == 'a') ? 1 : -1;
            bit_add(g, pos, delta);
            cnt[g] += delta;
            long long maxy = -1;
            if (cnt[g] > 0)
                maxy = ys[s + bit_kth(g, cnt[g]) - 1]; // 第 cnt 个即最大
            seg_set(g, maxy);
            continue;
        }

        // find：先找第一个 x 更大的可行组
        int start = (int)(upper_bound(xs.begin(), xs.end(), ox[i]) - xs.begin());
        int g = first_x(1, 0, seg_size, start, oy[i]);
        if (g == -1 || g >= groups) {
            cout << "-1\n";
            continue;
        }
        int s = yoff[g], e = yoff[g + 1];
        int pos = (int)(upper_bound(ys.begin() + s, ys.begin() + e, oy[i]) - ys.begin()) - s;
        long long target = bit_sum(g, pos) + 1; // 第一个严格大于 query_y 的活跃 y 的秩
        long long ans_y = ys[s + bit_kth(g, target) - 1];
        cout << xs[g] << ' ' << ans_y << '\n';
    }
    return 0;
}
