/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:20
 * update_at: 2026-07-11 18:24
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
int a[MAXN];

void solve_one_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<pair<int, int> > b;

    // 不移动时，b 由原数组中的后缀最大值组成。
    int suffix_max = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] >= suffix_max) {
            suffix_max = a[i];
            b.push_back(make_pair(a[i], i));
        }
    }
    reverse(b.begin(), b.end());

    // 哨兵方便统一处理第一个和最后一个后缀最大值。
    b.insert(b.begin(), make_pair(n + 1, -1));
    b.push_back(make_pair(-1, n));

    for (int i = 1; i + 1 < (int)b.size(); i++) {
        vector<pair<int, int> > add;
        suffix_max = b[i + 1].first;

        // 尝试把 b[i] 前移后，哪些中间元素会变成新的后缀最大值。
        for (int j = b[i + 1].second - 1; j > b[i - 1].second; j--) {
            if (j == b[i].second) {
                continue;
            }
            if (a[j] >= suffix_max) {
                suffix_max = a[j];
                add.push_back(make_pair(a[j], j));
            }
        }

        reverse(add.begin(), add.end());
        if (!add.empty()) {
            b.insert(b.begin() + i + 1, add.begin(), add.end());
            break;
        }
    }

    for (int i = 1; i + 1 < (int)b.size(); i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << b[i].first;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one_case();
    }

    return 0;
}
