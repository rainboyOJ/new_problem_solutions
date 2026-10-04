/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.cn  https://rbook2.roj.cn
 * rainboy的学习导航网站: https://idx.roj.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-05 00:27
 */

#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; // 小朋友人数
    if (!(cin >> n)) return 0;

    // 每人苹果数互不相同且至少 1 个，最省的取法是 1,2,...,n
    // 总和 = n(n+1)/2，整数除法避免浮点输出
    cout << n * (n + 1) / 2 << "\n";

    return 0;
}