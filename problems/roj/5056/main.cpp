/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:36
 * update_at: 2026-10-09 00:38
 */

#include <iostream>

using namespace std;

typedef long long ll;

const ll LOW = 25;   // 适合晨练的温度下界（含）
const ll HIGH = 30;  // 适合晨练的温度上界（含）

// 读入温度 t，闭区间 [25, 30] 内输出 ok!，否则输出 no!
void solve() {
    ll t;
    if (cin >> t) {
        if (t >= LOW && t <= HIGH) {
            cout << "ok!\n";
        } else {
            cout << "no!\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
