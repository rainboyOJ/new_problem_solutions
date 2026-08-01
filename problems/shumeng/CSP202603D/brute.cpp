/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 10:37
 */
// brute.cpp：直接逐个元素计算，适合小数据验证正式代码。
#include <bits/stdc++.h>
using namespace std;

long long k;

long long digit_xor(long long a, long long b) {
    long long result = 0;
    long long power = 1;
    while (a > 0 || b > 0) {
        long long digit = (a % k + b % k) % k;
        result += digit * power;
        power *= k;
        a /= k;
        b /= k;
    }
    return result;
}

long long f_value(long long n) {
    long long d0 = n % k;
    long long result = d0 * (d0 + 1) / 2 % k;
    long long power = k;
    n /= k;
    long long factor = d0 + 1;
    while (n > 0) {
        result += (n % k * factor % k) * power;
        power *= k;
        n /= k;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m >> k;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int op = 0; op < m; op++) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            long long v;
            cin >> v;
            for (int i = l; i <= r; i++) {
                a[i] = digit_xor(a[i], v);
            }
        } else {
            vector<long long> digit_sum(32, 0);
            for (int i = l; i <= r; i++) {
                long long current = f_value(a[i]);
                int digit = 0;
                while (current > 0) {
                    digit_sum[digit] = (digit_sum[digit] + current % k) % k;
                    current /= k;
                    digit++;
                }
            }
            long long answer = 0;
            long long power = 1;
            for (int digit = 0; digit < (int)digit_sum.size(); digit++) {
                answer += digit_sum[digit] * power;
                power *= k;
            }
            cout << answer << '\n';
        }
    }
    return 0;
}
