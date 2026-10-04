/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:37
 * update_at: 2026-10-04 22:37
 */

#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    double x; // 读入的浮点数，用 double 读入即可，整数部分不会失真
    cin >> x;

    // double 转 ll 时隐式截断小数部分，正是题目要求的向零舍入
    // 正数向下（2.3 -> 2），负数向上（-2.3 -> -2）
    ll answer = x;

    cout << answer << endl;
    return 0;
}
