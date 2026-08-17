/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 对 n 做试除分解，只保留指数不小于 k 的质因数幂
long long simplify(long long n, long long k) {
    long long value = n;
    long long answer = 1;
    for (long long prime = 2; prime * prime <= value; prime++) {
        if (value % prime != 0) continue;
        // 统计 prime 在 value 中的指数
        long long exponent = 0;
        while (value % prime == 0) {
            value /= prime;
            exponent++;
        }
        // 指数不小于 k 才保留完整的 prime^exponent
        if (exponent >= k) {
            for (long long i = 0; i < exponent; i++) answer *= prime;
        }
    }
    // 试除结束后若剩余 value > 1，它是指数为 1 的质因子；
    // 本题 k>1 所以不会被保留，这里保留 k<=1 时的通用处理
    if (value > 1 && k <= 1) answer *= value;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        long long n, k;
        cin >> n >> k;
        cout << simplify(n, k) << '\n';
    }

    return 0;
}