#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
vector<int> children[MAXN];

int brute_height(int u) {
    if (children[u].empty()) {
        return 0;
    }

    vector<int> perm = children[u];
    sort(perm.begin(), perm.end());

    int ans = 0;
    do {
        for (size_t i = 0; i < perm.size(); i++) {
            // 从 u 走到第 i 个孩子，需要先走 1 条左边，再走 i 条右兄弟边。
            ans = max(ans, 1 + (int)i + brute_height(perm[i]));
        }
    } while (next_permutation(perm.begin(), perm.end()));

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个小数据精确暴力：
    // 枚举每个结点儿子的排列顺序，直接按左孩子右兄弟定义求最高高度。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        children[i].clear();
    }

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        children[p].push_back(i);
    }

    cout << brute_height(1) << '\n';
    return 0;
}
