/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, r; // 水桶深度（厘米），底面半径（厘米）
    cin >> h >> r;
    // 圆柱体积 = π * r^2 * h，除以 1000 换算成升，π 取 3.14
    double volume = 3.14 * r * r * h / 1000;
    // 20 升水除以每桶升数，向上取整得到至少需要的桶数
    int need = ceil(20.0 / volume);
    cout << need << endl;
    return 0;
}
