/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:24
 * update_at: 2026-10-04 23:24
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll n; // 输入的正整数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    // 判断 n 是否在 [10, 99] 区间内，是则输出 1，否则输出 0
    cout << (n >= 10 && n <= 99 ? 1 : 0) << "\n";
    return 0;
}
