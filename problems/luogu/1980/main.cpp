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
    int n, x; // 范围上限，目标数字
    cin >> n >> x;
    int count = 0; // 累计出现次数
    // 枚举 1 到 n 的每个整数，逐位判断
    for (int i = 1; i <= n; i++) {
        int temp = i;
        while (temp > 0) {
            if (temp % 10 == x) { // 当前位等于目标数字
                count++;
            }
            temp /= 10; // 去掉最后一位
        }
    }
    cout << count << endl;
    return 0;
}
