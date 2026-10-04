/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:32
 * update_at: 2026-10-05 03:32
 */

#include <iostream>
using namespace std;

typedef long long ll;

// 判断 i 是否为完全数：真因子之和是否等于 i
// 利用因子成对性，只枚举 d ∈ [2, √i)，把 d 和 i/d 一起累加
bool is_perfect(int i) {
    int s = 1; // 1 一定是真因子，先记上
    int d = 2;
    while ((ll)d * d < i) {
        if (i % d == 0) {
            s += d + i / d;
        }
        d++;
    }
    // 完全平方数的平方根因子要单独加一次：循环结束时 d = ⌊√i⌋+1
    d--; // 回到最后一个满足 d*d <= i 的 d
    if ((ll)d * d == i) {
        s += d;
    }
    return s == i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // 上界 n

    // 枚举 [2, n]，按升序输出所有完全数
    for (int i = 2; i <= n; i++) {
        if (is_perfect(i)) {
            cout << i << "\n";
        }
    }

    return 0;
}