/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:31
 * update_at: 2026-10-06 12:31
 */

#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    double s = 0.0; // 当前调和级数部分和 S_n
    int n = 0;      // 当前项数
    while (s <= k) { // 严格大于 K 时停止
        ++n;
        s += 1.0 / n;
    }

    cout << n << "\n";
    return 0;
}
