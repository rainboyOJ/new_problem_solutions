/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:10
 * update_at: 2026-10-05 23:10
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int LIMIT = 100000; // 题目值域上限

bool is_prime[LIMIT + 1]; // is_prime[i] = true 表示 i 是素数

// 埃氏筛预处理 2~LIMIT 的素数表
void sieve() {
    for (int i = 2; i <= LIMIT; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false; // 0 和 1 不是素数
    for (int i = 2; i * i <= LIMIT; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= LIMIT; j += i)
                is_prime[j] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int x, y;
    cin >> x >> y;
    int lo = min(x, y);
    int hi = max(x, y);

    int ans = 0;
    for (int i = lo; i <= hi; i++)
        if (is_prime[i]) ans++;

    cout << ans << "\n";
    return 0;
}
