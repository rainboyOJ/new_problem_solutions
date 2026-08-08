/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-12 17:56
 * update_at: 2026-07-12 17:56
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8000 + 5;

struct Node {
    int value;
    int id;
};

int n, q;
int a[MAXN];      // a[i] 表示原下标 i 的元素当前值
Node ord[MAXN];   // ord[pos] 表示稳定排序后第 pos 个元素

bool node_less(const Node &x, const Node &y) {
    if (x.value != y.value) {
        return x.value < y.value;
    }
    return x.id < y.id;
}

// 在 ord[1..len] 中找到第一个不小于 target 的位置。
int lower_bound_pos(const Node &target, int len) {
    int left = 1;
    int right = len;
    int answer = len + 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (!node_less(ord[mid], target)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return answer;
}

// 删除旧二元组，再把新二元组插入有序数组。
void modify_value(int x, int value) {
    Node old_node;
    old_node.value = a[x];
    old_node.id = x;

    int old_pos = lower_bound_pos(old_node, n);
    for (int i = old_pos; i < n; i++) {
        ord[i] = ord[i + 1];
    }

    a[x] = value;
    Node new_node;
    new_node.value = a[x];
    new_node.id = x;

    int new_pos = lower_bound_pos(new_node, n - 1);
    for (int i = n; i > new_pos; i--) {
        ord[i] = ord[i - 1];
    }
    ord[new_pos] = new_node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ord[i].value = a[i];
        ord[i].id = i;
    }
    sort(ord + 1, ord + n + 1, node_less);

    while (q--) {
        int op, x;
        cin >> op >> x;

        if (op == 1) {
            int value;
            cin >> value;
            modify_value(x, value);
        } else {
            Node target;
            target.value = a[x];
            target.id = x;
            cout << lower_bound_pos(target, n) << '\n';
        }
    }

    return 0;
}
