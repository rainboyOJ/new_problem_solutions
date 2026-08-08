#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
int a[MAXN], b[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 枚举选择哪些挂饰。若选了 k 个挂饰，只要这些挂饰的挂钩总数不少于 k-1，
    // 就一定能把它们排成一棵合法的挂饰树。
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    long long answer = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        int cnt = 0;
        int sum_a = 0;
        long long sum_b = 0;

        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0) {
                continue;
            }
            cnt++;
            sum_a += a[i];
            sum_b += b[i];
        }

        if (cnt == 0 || sum_a >= cnt - 1) {
            answer = max(answer, sum_b);
        }
    }

    cout << answer << '\n';
    return 0;
}
