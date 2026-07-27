/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

// 判断一个数是否为质数
bool is_prime(int x) {
    if (x < 2) return false;
    // 只需检查到平方根，因为因子成对出现
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

int n, x;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (is_prime(x)) cout << x << " ";
    }
    return 0;
}
