#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举删还是不删，直接构造剩余序列并统计有多少个数等于它的新位置。

const int MAXN = 25;

int n;
int a[MAXN];
int ans;
vector<int> cur;

void dfs(int idx) {
    if (idx > n) {
        int cnt = 0;
        for (int i = 0; i < (int)cur.size(); i++) {
            if (cur[i] == i + 1) {
                cnt++;
            }
        }
        ans = max(ans, cnt);
        return;
    }

    // 删除 a[idx]
    dfs(idx + 1);

    // 保留 a[idx]
    cur.push_back(a[idx]);
    dfs(idx + 1);
    cur.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ans = 0;
    dfs(1);

    cout << ans << '\n';
    return 0;
}
