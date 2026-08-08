/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-21 13:41
 * update_at: 2026-07-19 11:35
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
int a[MAXN]; // 当前组输入

// 保序去重：第一次出现留下，后面重复丢掉
void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    unordered_set<int> seen;
    bool first = true;
    for (int i = 1; i <= n; i++) {
        // 已经出现过，跳过
        if (seen.count(a[i])) {
            continue;
        }
        seen.insert(a[i]);

        if (!first) {
            cout << ' ';
        }
        cout << a[i];
        first = false;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
