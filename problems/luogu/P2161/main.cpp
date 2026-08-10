#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;

int tree[MAX + 1];     // Fenwick：每个起点位置是否有区间（0/1）
int end_at[MAX + 1];   // end_at[start] 保存该起点区间的终点
int active;            // 当前区间数

void add(int index, int delta) {
    while (index <= MAX) {
        tree[index] += delta;
        index += index & -index;
    }
}

int prefix(int index) {
    int result = 0;
    while (index) {
        result += tree[index];
        index -= index & -index;
    }
    return result;
}

// 第 rank 个起点（rank 从 1 开始）
int kth(int rank) {
    int index = 0;
    int step = 1 << (31 - __builtin_clz(MAX));
    while (step) {
        int target = index + step;
        if (target <= MAX && tree[target] < rank) {
            index = target;
            rank -= tree[target];
        }
        step >>= 1;
    }
    return index + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
        int before = prefix(l);
        if (before) {
            int start = kth(before);
            if (end_at[start] >= l) {
                add(start, -1);
                end_at[start] = 0;
                active--;
                removed++;
            }
        }
        // 起点 >= l 的区间，只要起点 <= r 就必然相交（终点 >= 起点 >= l）
        while (prefix(MAX) > prefix(l - 1)) {
            int start = kth(prefix(l - 1) + 1);
            if (start > r) {
                break;
            }
            add(start, -1);
            end_at[start] = 0;
            active--;
            removed++;
        }
        add(l, 1);
        end_at[l] = r;
        active++;
        cout << removed << '\n';
    }

    return 0;
}
