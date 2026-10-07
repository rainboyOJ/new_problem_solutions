/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 14:46
 * update_at: 2026-10-04 14:46
 */
#include <iostream>
using namespace std;

typedef long long ll;

// 第 n 个卡特兰数：C_0=1, C_k = C_{k-1} * 2(2k-1) / (k+1)，整除在乘法之后做。
ll catalan(int n) {
    ll res = 1; // C_0 = 1
    for (int k = 2; k <= n; ++k)
        res = res * 2 * (2 * k - 1) / (k + 1);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    cout << catalan(n) << "\n";
    return 0;
}
