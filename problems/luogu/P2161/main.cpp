#include <bits/stdc++.h>
using namespace std;

// 单点加、前缀和、区间和、按秩查找（模拟有序集合）。
// 下标必须从 1 开始。
template <typename T>
struct Fenwick {
    int n = 0;
    vector<T> tree;

    Fenwick(int n = 0) { init(n); }

    void init(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }

    static int lowbit(int x) { return x & -x; }

    void add(int pos, T value) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tree[i] += value;
        }
    }

    T prefix_sum(int pos) const {
        T answer = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            answer += tree[i];
        }
        return answer;
    }

    T range_sum(int left, int right) const {
        return prefix_sum(right) - prefix_sum(left - 1);
    }

    // 第 rank 个 1 的位置（rank 从 1 开始），用于动态集合按秩查找
    int kth(int rank) const {
        int index = 0;
        int step = 1 << (31 - __builtin_clz(n));
        while (step) {
            int target = index + step;
            if (target <= n && tree[target] < rank) {
                index = target;
                rank -= tree[target];
            }
            step >>= 1;
        }
        return index + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX = 100000;
    Fenwick<int> bit(MAX);       // 每个起点位置是否有区间（0/1）
    vector<int> end_at(MAX + 1); // end_at[start] 保存该起点区间的终点
    int active = 0;              // 当前区间数

    int n;
    cin >> n;
    while (n--) {
        char op;
        cin >> op;
        if (op == 'B') {
            cout << active << '\n';
            continue;
        }
        int l, r;
        cin >> l >> r;
        int removed = 0;
        // 起点 <= l 的区间中，只有最后一个可能延伸到 l
        int before = bit.prefix_sum(l);
        if (before) {
            int start = bit.kth(before);
            if (end_at[start] >= l) {
                bit.add(start, -1);
                end_at[start] = 0;
                active--;
                removed++;
            }
        }
        // 起点 >= l 的区间，只要起点 <= r 就必然相交（终点 >= 起点 >= l）
        while (bit.range_sum(l, MAX) > 0) {
            int start = bit.kth(bit.prefix_sum(l - 1) + 1);
            if (start > r) {
                break;
            }
            bit.add(start, -1);
            end_at[start] = 0;
            active--;
            removed++;
        }
        bit.add(l, 1);
        end_at[l] = r;
        active++;
        cout << removed << '\n';
    }

    return 0;
}
