/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:22
 * update_at: 2026-10-04 22:22
 */
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a, b, c;
    // 读入三个整数，按 (a+b)*c 输出
    cin >> a >> b >> c;
    cout << (a + b) * c << "\n";
    return 0;
}
