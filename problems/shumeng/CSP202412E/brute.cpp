/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 02:58
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，把每次选择左端或右端看成递归分支。
int n;
vector<long long> a;
vector<long long> b;

long long dfs(int left, int right) {
    if (left == 0 && right == n + 1) return 0;

    long long answer = (1LL << 62);
    if (left > 0) {
        long long need_after = dfs(left - 1, right);
        long long need_now = max(a[left], need_after - b[left]);
        answer = min(answer, need_now);
    }
    if (right <= n) {
        long long need_after = dfs(left, right + 1);
        long long need_now = max(a[right], need_after - b[right]);
        answer = min(answer, need_now);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<long long> base_a(n + 2);
    vector<long long> base_b(n + 2);
    a.assign(n + 2, 0);
    b.assign(n + 2, 0);

    for (int i = 1; i <= n; i++) cin >> base_a[i];
    for (int i = 1; i <= n; i++) cin >> base_b[i];

    int q;
    cin >> q;
    for (int query = 0; query < q; query++) {
        a = base_a;
        b = base_b;

        int changed;
        cin >> changed;
        for (int i = 0; i < changed; i++) {
            int position;
            cin >> position >> a[position] >> b[position];
        }

        long long answer = 0;
        for (int split = 1; split < n; split++) {
            answer ^= dfs(split, split + 1);
        }
        cout << answer << '\n';
    }

    return 0;
}
