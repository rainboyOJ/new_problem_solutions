#include <bits/stdc++.h>
using namespace std;

// 暴力：每次查询直接向两侧扫前缀和，复杂度 O(nq)。
// 仅用于对拍小数据，不满足题目限制。
int n, q;
vector<long long> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    a.assign(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            long long x;
            cin >> i >> x;
            a[i] = x;
        } else if (op == 2) {
            int l;
            long long t;
            cin >> l >> t;
            // 从 l 往右累加，第一个使和 >= t 的位置就是答案
            long long sum = 0;
            int answer = n + 1;
            for (int r = l; r <= n; r++) {
                sum += a[r];
                if (sum >= t) {
                    answer = r;
                    break;
                }
            }
            cout << answer << '\n';
        } else {
            int r;
            long long t;
            cin >> r >> t;
            // 从 r 往左累加，遇到的第一个使和 >= t 的位置就是最大的 l
            long long sum = 0;
            int answer = 0;
            for (int l = r; l >= 1; l--) {
                sum += a[l];
                if (sum >= t) {
                    answer = l;
                    break;
                }
            }
            cout << answer << '\n';
        }
    }

    return 0;
}
