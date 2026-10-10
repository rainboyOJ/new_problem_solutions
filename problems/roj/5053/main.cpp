/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:36
 * update_at: 2026-10-09 00:39
 */
#include <iostream>

using namespace std;

typedef long long ll;

// 读入正整数 a，a 为偶数输出 yes；奇数什么也不输出（0 字节）
void solve() {
    ll a;
    if (!(cin >> a)) return;  // 无输入时静默退出

    if (a % 2 == 0) {
        cout << "yes\n";  // 只有偶数分支才产生输出
    }
    // 奇数分支刻意不输出任何字节：连一个换行都不能多写
}

int main() {
    ios_base::sync_with_stdio(false);  // 关闭与 stdio 的同步，加快读写
    cin.tie(NULL);

    solve();
    return 0;
}
