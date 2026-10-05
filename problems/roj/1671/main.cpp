/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:45
 * update_at: 2026-10-06 01:45
 */

#include <iostream>
using namespace std;

typedef long long ll;

const ll THRESHOLDS[] = {7960, 11200, 16700, 115000, 2000000}; // 五级宇宙速度门槛（米/秒）
const int THRESHOLD_CNT = 5; // 门槛个数

ll v; // 输入速度
int k; // 达到的级别数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> v;

    // 统计 v 大于等于多少个门槛
    for (int i = 0; i < THRESHOLD_CNT; i++) {
        if (v >= THRESHOLDS[i]) k++;
    }

    cout << v << " ";
    if (k == 0) {
        cout << "0";
    } else {
        // 输出 1 到 k 的连续数字串
        for (int i = 1; i <= k; i++) {
            cout << i;
        }
    }
    cout << "\n";

    return 0;
}
