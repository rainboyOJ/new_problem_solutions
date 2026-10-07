/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:58
 * update_at: 2026-10-05 08:58
 */
// main.cpp：昆虫繁殖。按月的双序列线性递推求第 z+1 个月的成虫对数。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXZ = 60; // z <= 50，数组开到 53 够用

ll a[MAXZ]; // a[i] 表示第 i 个月的成虫对数
ll b[MAXZ]; // b[i] 表示第 i 个月新产下的卵对数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y, z;
    cin >> x >> y >> z;

    // 成虫不死：前 x 个月尚未到产卵时间，始终只有最初那 1 对
    for (int i = 1; i <= x; ++i) {
        a[i] = 1;
    }

    for (int i = x + 1; i <= z + 1; ++i) {
        b[i] = a[i - x] * y; // 第 i-x 月已有的每对成虫，过 x 个月在本月产 y 对卵
        ll hatch = 0;        // 两月前产的卵在本月长成的新成虫
        if (i >= 2) {
            hatch = b[i - 2];
        }
        a[i] = a[i - 1] + hatch; // 上月成虫 + 新孵化的成虫
    }

    cout << a[z + 1] << '\n'; // 从第 1 个月再过 z 个月即第 z+1 个月

    return 0;
}
