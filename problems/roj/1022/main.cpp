/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:43
 * update_at: 2026-10-04 22:43
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll n; // 输入的整数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    // 先转 bool（非零为真），再转 int（真为 1，假为 0）
    cout << (n != 0 ? 1 : 0) << "\n";
    return 0;
}
