// brute.cpp：枚举所有子序列，统计最长不下降子序列长度和方案数，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int T;
int n;
int a[MAXN];
int best_len;
long long ways;

void dfs(int pos, int last_value, int cur_len) {
    if (pos > n) {
        if (cur_len > best_len) {
            best_len = cur_len;
            ways = 1;
        }
        else if (cur_len == best_len) {
            ways++;
        }
        return;
    }

    // 不选当前位置
    dfs(pos + 1, last_value, cur_len);

    // 选当前位置，必须保持不下降
    if (a[pos] >= last_value) {
        dfs(pos + 1, a[pos], cur_len + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        best_len = 0;
        ways = 0;
        dfs(1, -1000000000, 0);

        cout << best_len << ' ' << ways << '\n';
    }

    return 0;
}
