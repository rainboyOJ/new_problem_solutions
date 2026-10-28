/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-10-28 10:00
 */

/* CF19D Points —— 解法一：每组一个 std::set + 外层线段树带剪枝单路下降 */
/* 外层按 x 分组建线段树，结点存该区间内所有点的最大 y；
 * 剪枝条件 mx <= query_y 表示整段一个答案都没有，直接砍掉，
 * 于是「第一个 x 更大且组内存在 y 更大」的组可以在 O(log n) 内单路下降定位；
 * 组内 y 交给 std::set 的顺序性，upper_bound 一次就拿到最小可行 y。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

int n;                                     // 操作数
char op[MAXN];                             // 'a' add / 'r' remove / 'f' find
int ox[MAXN], oy[MAXN];                    // 操作参数；坐标不超过 1e9，用 int 省内存
vector<int> xs;                            // 所有 add 出现过的 x（升序去重），下标即组号
set<int> group_y[MAXN];                    // group_y[g]：第 g 组当前挂着的所有 y
int seg[MAXN * 2];                         // 线段树：结点覆盖的组区间内最大 y，空组为 -1
int groups, seg_size;

// 把第 pos 组当前的最大 y 写进线段树叶子，并向上更新
void seg_set(int pos, int value) {
    int p = seg_size + pos;
    seg[p] = value;
    for (p >>= 1; p; p >>= 1)
        seg[p] = max(seg[p << 1], seg[p << 1 | 1]);
}

// 找组号 >= start 且该组最大 y > y 的最小者；不存在返回 -1
int find_first(int p, int l, int r, int start, int y) {
    if (r <= start || seg[p] <= y) return -1; // 整段落在起点左边，或整段最大值都够不到 y：剪掉
    if (r - l == 1) return l;                 // 走到叶子，它一定满足最大 y > y

    int mid = (l + r) >> 1;
    int res = find_first(p << 1, l, mid, start, y); // 先左后右，返回的组号自然最小
    if (res != -1) return res;
    return find_first(p << 1 | 1, mid, r, start, y);
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

    seg_size = 1;
    while (seg_size < groups) seg_size <<= 1;
    fill(seg, seg + seg_size * 2, -1);

    for (int i = 0; i < n; i++) {
        if (op[i] != 'f') { // add / remove：只改动一个叶子的组内集合
            int g = lower_bound(xs.begin(), xs.end(), ox[i]) - xs.begin();
            if (op[i] == 'a')
                group_y[g].insert(oy[i]);
            else
                group_y[g].erase(oy[i]);
            seg_set(g, group_y[g].empty() ? -1 : *group_y[g].rbegin());
            continue;
        }

        // find：先定位最左的可行组，再在组内取第一个大于 query_y 的 y
        int start = upper_bound(xs.begin(), xs.end(), ox[i]) - xs.begin();
        int g = find_first(1, 0, seg_size, start, oy[i]);
        if (g == -1 || g >= groups) {
            cout << "-1\n";
            continue;
        }
        int answer_y = *group_y[g].upper_bound(oy[i]);
        cout << xs[g] << ' ' << answer_y << '\n';
    }
    return 0;
}
