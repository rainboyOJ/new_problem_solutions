/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

// 判断 x 是否是质数（试除法，只需检查到 sqrt(x)）
bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int main() {
    int L;        // 口袋容量上限
    int total = 0; // 已放入质数的和
    int primes[1005]; // 存储能放入的质数
    int cnt = 0;     // 质数个数
    cin >> L;
    // 从 2 开始逐个检查自然数
    for (int candidate = 2; total + candidate <= L; candidate++) {
        if (is_prime(candidate)) {
            total += candidate;
            primes[cnt++] = candidate;
        }
    }
    // 输出所有质数
    for (int i = 0; i < cnt; i++) {
        cout << primes[i] << endl;
    }
    cout << cnt << endl; // 最后一行输出质数个数
    return 0;
}
