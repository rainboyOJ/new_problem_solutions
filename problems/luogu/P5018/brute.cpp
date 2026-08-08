#include <bits/stdc++.h>
using namespace std;

static vector<int> value_arr;
static vector<int> left_son;
static vector<int> right_son;
static vector<int> subtree_size;

int calc_size(int u) {
    if (u == -1) {
        return 0;
    }
    subtree_size[u] = calc_size(left_son[u]) + calc_size(right_son[u]) + 1;
    return subtree_size[u];
}

bool mirror_same(int a, int b) {
    if (a == -1 && b == -1) {
        return true;
    }
    if (a == -1 || b == -1) {
        return false;
    }
    if (value_arr[a] != value_arr[b]) {
        return false;
    }
    return mirror_same(left_son[a], right_son[b]) &&
           mirror_same(right_son[a], left_son[b]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    value_arr.assign(n + 1, 0);
    left_son.assign(n + 1, -1);
    right_son.assign(n + 1, -1);
    subtree_size.assign(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> value_arr[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> left_son[i] >> right_son[i];
    }

    calc_size(1);

    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (mirror_same(left_son[i], right_son[i])) {
            ans = max(ans, subtree_size[i]);
        }
    }
    cout << ans << '\n';
    return 0;
}
