#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

struct Node {
    int val;
    int id;
};

int n, q;
int a[MAXN];
Node b[MAXN];

int query_rank(int x) {
    for (int i = 1; i <= n; i++) {
        b[i].val = a[i];
        b[i].id = i;
    }

    // 真的按题目的插入排序伪代码做一遍，利用“<”保证稳定性。
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 2; j--) {
            if (b[j].val < b[j - 1].val) {
                swap(b[j], b[j - 1]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (b[i].id == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, v;
            cin >> x >> v;
            a[x] = v;
        }
        else {
            int x;
            cin >> x;
            cout << query_rank(x) << '\n';
        }
    }

    return 0;
}
