#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300000 + 5;

static int n;
static int value_arr[MAXN];
static int left_son[MAXN];
static int right_son[MAXN];
static int depth_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> value_arr[i];
    }

    int max_depth = 1;
    depth_arr[1] = 1;
    set<pair<int, int>> ordered_values;
    ordered_values.insert({value_arr[1], 1});

    for (int i = 2; i <= n; ++i) {
        int parent;
        auto it = ordered_values.lower_bound({value_arr[i], 0});

        if (it == ordered_values.begin()) {
            // 没有前驱，只能接到后继的左边。
            parent = it->second;
            left_son[parent] = i;
        } else if (it == ordered_values.end()) {
            // 没有后继，只能接到前驱的右边。
            auto pre_it = prev(it);
            parent = pre_it->second;
            right_son[parent] = i;
        } else {
            auto pre_it = prev(it);
            int pre_idx = pre_it->second;
            int nxt_idx = it->second;

            // 前驱和后继里，插入更晚的那个就是当前点的父亲。
            if (pre_idx > nxt_idx) {
                parent = pre_idx;
                right_son[parent] = i;
            } else {
                parent = nxt_idx;
                left_son[parent] = i;
            }
        }

        depth_arr[i] = depth_arr[parent] + 1;
        max_depth = max(max_depth, depth_arr[i]);
        ordered_values.insert({value_arr[i], i});
    }

    stack<int> s1;
    stack<int> s2;
    s1.push(1);

    // 用双栈迭代输出后序遍历，避免极端链状树导致递归爆栈。
    while (!s1.empty()) {
        int u = s1.top();
        s1.pop();
        s2.push(u);

        if (left_son[u] != 0) {
            s1.push(left_son[u]);
        }
        if (right_son[u] != 0) {
            s1.push(right_son[u]);
        }
    }

    cout << "deep=" << max_depth << '\n';
    while (!s2.empty()) {
        cout << value_arr[s2.top()] << '\n';
        s2.pop();
    }
    return 0;
}
