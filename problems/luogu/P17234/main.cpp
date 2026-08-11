/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 10:05
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;

int n;
int a[MAXV];
vector<int> pos[MAXV];

long long count_zero_mex() {
    long long ans = 0;
    int last = 0;
    for (int i = 0; i < (int)pos[0].size(); i++) {
        int len = pos[0][i] - last - 1;
        ans += 1LL * len * (len + 1) / 2;
        last = pos[0][i];
    }
    int len = n - last;
    ans += 1LL * len * (len + 1) / 2;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i <= n + 1; i++) pos[i].clear();
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= n) pos[a[i]].push_back(i);
    }

    long long ans = 0;
    if (pos[0].empty()) {
        cout << 0 << '\n';
        return 0;
    }

    ans += count_zero_mex();

    int left_bound = n + 1;
    int right_bound = 0;
    for (int x = 1; x <= n; x++) {
        for (int i = 0; i < (int)pos[x - 1].size(); i++) {
            int p = pos[x - 1][i];
            if (p < left_bound) left_bound = p;
            if (p > right_bound) right_bound = p;
        }

        if (pos[x].empty()) break;

        vector<int>::iterator it = lower_bound(pos[x].begin(), pos[x].end(), left_bound);
        if (it != pos[x].end() && *it <= right_bound) continue;

        int prev_x = 0;
        int next_x = n + 1;
        if (it != pos[x].end()) next_x = *it;
        if (it != pos[x].begin()) {
            --it;
            prev_x = *it;
        }

        ans += 1LL * (left_bound - prev_x) * (next_x - right_bound);
    }

    cout << ans << '\n';
    return 0;
}
