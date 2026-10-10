/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll d[35];
ll score[35][35];   // 区间最高加分
int root[35][35];   // 取到最高加分的根

// best(l, r)：返回 (最高加分, 根)
ll best(int l, int r) {
    if (l > r) return 1;
    if (l == r) { root[l][r] = l; return d[l]; }
    if (score[l][r] != -1) return score[l][r];
    ll top = 0; int top_k = l;
    for (int k = l; k <= r; k++) {
        ll s = best(l, k - 1) * best(k + 1, r) + d[k];
        if (s > top) { top = s; top_k = k; }
    }
    score[l][r] = top;
    root[l][r] = top_k;
    return top;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            score[i][j] = -1;
    cout << best(1, n) << "\n";

    // 前序遍历：根 -> 左 -> 右
    vector<int> order;
    vector<pair<int, int> > stack;
    stack.push_back(make_pair(1, n));
    while (!stack.empty()) {
        int l = stack.back().first, r = stack.back().second;
        stack.pop_back();
        if (l <= r) {
            int k = root[l][r];
            order.push_back(k);
            stack.push_back(make_pair(k + 1, r));
            stack.push_back(make_pair(l, k - 1));
        }
    }
    for (size_t i = 0; i < order.size(); i++) {
        if (i) cout << " ";
        cout << order[i];
    }
    cout << "\n";
    return 0;
}
