/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:40
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        long long n, k;
        cin >> n >> k;
        long long value = n;
        long long answer = 1;
        for (long long prime = 2; prime * prime <= value; prime++) {
            if (value % prime != 0) continue;
            long long exponent = 0;
            while (value % prime == 0) {
                value /= prime;
                exponent++;
            }
            if (exponent >= k) {
                for (long long i = 0; i < exponent; i++) answer *= prime;
            }
        }
        if (value > 1 && k <= 1) answer *= value;
        cout << answer << '\n';
    }

    return 0;
}
