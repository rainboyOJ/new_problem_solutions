/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:00
 * update_at: 2026-10-04 23:00
 */
#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;

const double TARGET = 20000.0; // 20 升 = 20000 立方厘米
const double PI = acos(-1.0);  // π

ll h, r; // 桶深、底面半径

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> h >> r;
    double volume = PI * r * r * h; // 每桶圆柱体积 πr²h
    ll ans = ceil(TARGET / volume); // 至少喝够，向上取整
    cout << ans << "\n";
    return 0;
}
