/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-10-28 15:10
 */

/* CF19D Points —— 解法一：每组一个 std::set + 外层线段树带剪枝单路下降 */
/* 外层按 x 分组建线段树，结点存该区间内所有点的最大 y；
 * 剪枝条件 seg[p] <= query_y 表示整段一个答案都没有，直接砍掉，
 * 于是「第一个 x 更大且组内存在 y 更大」的组可以在 O(log n) 内单路下降定位；
 * 组内 y 交给 std::set 的顺序性，upper_bound 一次就拿到最小可行 y。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;                  // 操作数
char op[MAXN];          // 'a' add / 'r' remove / 'f' find
int ox[MAXN], oy[MAXN]; // 操作参数；坐标不超过 1e9，用 int 省内存
vector<int> xs;         // 所有 add 出现过的 x（升序去重），组号 = 下标 + 1
set<int> group_y[MAXN]; // group_y[g]：第 g 组当前挂着的所有 y
int seg[MAXN * 4];      // seg[p]：第 p 个结点覆盖的组区间内最大 y，空组为 -1
int groups;             // 组数，线段树下标范围是 [1, groups]

// 点更新：把第 pos 组的叶子值改成 value，并向上合并区间最大值。
void seg_update(int p, int l, int r, int pos, int value) {
    if (l == r) {
        seg[p] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        seg_update(p << 1, l, mid, pos, value);
    else
        seg_update(p << 1 | 1, mid + 1, r, pos, value);
    seg[p] = max(seg[p << 1], seg[p << 1 | 1]);
}

// 在线段树上找最小的组号 g 使 start <= g 且第 g 组的最大 y > y（线段树二分），
// 不存在返回 0。start 之前（含）的区间整体没有意义，用 r < start 一并剪掉。
int find_first(int p, int l, int r, int start, int y) {
    if (r < start || seg[p] <= y) return 0; // 整段在起点左边，或整段最大值都够不到 y
    if (l == r) return l;                   // 走到叶子，它一定满足最大 y > y
    int mid = (l + r) >> 1;
    int res = find_first(p << 1, l, mid, start, y); // 先左后右，返回的组号自然最小
    if (res) return res;
    return find_first(p << 1 | 1, mid + 1, r, start, y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s >> ox[i] >> oy[i];
        op[i] = s[0];
        if (op[i] == 'a') xs.push_back(ox[i]);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    groups = xs.size();

    fill(seg, seg + 4 * groups + 4, -1); // 初始一个点都没有，所有组都按空组算

    for (int i = 0; i < n; i++) {
        if (op[i] != 'f') { // add / remove：只改动一个组的点集
            int g = lower_bound(xs.begin(), xs.end(), ox[i]) - xs.begin() + 1; // 组号从 1 开始
            if (op[i] == 'a')
                group_y[g].insert(oy[i]);
            else
                group_y[g].erase(oy[i]);
            seg_update(1, 1, groups, g, group_y[g].empty() ? -1 : *group_y[g].rbegin());
            continue;
        }

        // find：先定位最左的可行组，再在组内取第一个严格大于 query_y 的 y
        int start = upper_bound(xs.begin(), xs.end(), ox[i]) - xs.begin() + 1; // 严格大于 query_x 的第一个组号
        int g = find_first(1, 1, groups, start, oy[i]);
        if (g == 0) {
            cout << "-1\n";
            continue;
        }
        int answer_y = *group_y[g].upper_bound(oy[i]);
        cout << xs[g - 1] << ' ' << answer_y << '\n';
    }
    return 0;
}
