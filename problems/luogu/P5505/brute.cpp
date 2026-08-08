#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 1000000007LL;

int n, m;
int a[12];
int sum_get[12];
int give[12][12];
i64 ans;

void dfs_type(int kind);
void dfs_person(int kind, int person, int remain);

// 逐种特产枚举分配方案。
void dfs_type(int kind) {
    if (kind > m) {
        for (int i = 1; i <= n; i++) {
            if (sum_get[i] == 0) {
                return;
            }
        }
        ans++;
        if (ans >= MOD) {
            ans -= MOD;
        }
        return;
    }

    dfs_person(kind, 1, a[kind]);
}

// 枚举第 kind 种特产分给每个同学多少个。
void dfs_person(int kind, int person, int remain) {
    if (person == n) {
        give[kind][person] = remain;
        for (int i = 1; i <= n; i++) {
            sum_get[i] += give[kind][i];
        }

        dfs_type(kind + 1);

        for (int i = 1; i <= n; i++) {
            sum_get[i] -= give[kind][i];
        }
        return;
    }

    for (int x = 0; x <= remain; x++) {
        give[kind][person] = x;
        dfs_person(kind, person + 1, remain - x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    dfs_type(1);
    cout << ans << '\n';

    return 0;
}
