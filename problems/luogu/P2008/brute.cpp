#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> len(n + 1), sum(n + 1), pre(n + 1);

    auto seq_less = [&](int x, int y) -> bool {
        if (x == y) return false;
        vector<int> px, py;
        for (int p = x; p; p = pre[p]) px.push_back(p);
        for (int p = y; p; p = pre[p]) py.push_back(p);
        reverse(px.begin(), px.end());
        reverse(py.begin(), py.end());
        return px < py;
    };

    for (int i = 1; i <= n; ++i) {
        len[i] = 1;
        sum[i] = a[i];
        for (int j = 1; j < i; ++j) {
            if (a[j] > a[i]) continue;
            int clen = len[j] + 1;
            if (clen > len[i]) {
                len[i] = clen;
                sum[i] = sum[j] + a[i];
                pre[i] = j;
            } else if (clen == len[i]) {
                if (seq_less(j, pre[i])) {
                    sum[i] = sum[j] + a[i];
                    pre[i] = j;
                }
            }
        }
        cout << sum[i] << " \n"[i == n];
    }

    return 0;
}
