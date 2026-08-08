// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 105;

int n, k;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    int min_a = (int)1e9;
    int max_a = -(int)1e9;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        min_a = min(min_a, a[i]);
        max_a = max(max_a, a[i]);
    }

    vector<i64> cost_list;

    // 小数据暴力：把候选位置限制在 [min_a-k, max_a+k]，
    // 直接算每个整数位置的总代价，再取最小的 k 个。
    for (int x = min_a - k; x <= max_a + k; x++) {
        i64 cost = 0;
        for (int i = 1; i <= n; i++) {
            cost += llabs((i64)x - a[i]);
        }
        cost_list.push_back(cost);
    }

    sort(cost_list.begin(), cost_list.end());

    i64 answer = 0;
    for (int i = 0; i < k; i++) {
        answer += cost_list[i];
    }

    cout << answer << '\n';
    return 0;
}
