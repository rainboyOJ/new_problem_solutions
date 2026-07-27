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
    int x; // 待判断的整数
    cin >> x;
    // 两个布尔性质
    int a = (x % 2 == 0);       // 性质 a：是偶数
    int b = (x > 4 && x <= 12); // 性质 b：大于 4 且不大于 12
    // 四个布尔运算结果，用 1/0 输出
    cout << (a && b) << " " << (a || b) << " " << (a != b) << " " << !(a || b) << endl;
    return 0;
}
