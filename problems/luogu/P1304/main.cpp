/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

bool is_prime[10005]; // 质数表
int n;

// 埃氏筛法预处理质数表
void sieve(int limit) {
    fill(is_prime, is_prime + limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
}

int main() {
    cin >> n;
    sieve(n);
    for (int even = 4; even <= n; even += 2) { // 枚举偶数
        for (int first = 2; first < even; first++) {
            int second = even - first;
            if (is_prime[first] && is_prime[second]) {
                cout << even << "=" << first << "+" << second << "\n";
                break; // 找到第一个加数最小的方案
            }
        }
    }
    return 0;
}
