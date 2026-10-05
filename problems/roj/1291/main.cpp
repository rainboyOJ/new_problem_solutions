/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:09
 * update_at: 2026-10-05 08:09
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXT = 1005;

int n;      // 正整数的个数
int t;      // 目标组合和
int a[25];  // 输入的 n 个正整数

ll ways[MAXT]; // ways[s] = 从已考虑的数中选出若干、和恰为 s 的组合数

int main() {
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // ways[0] = 1：一个数都不选时和恰好为 0，方案数为 1
    ways[0] = 1;
    for (int i = 1; i <= n; i++) {
        // 每个数至多用一次，所以容量必须倒序枚举，读到的是上一轮的旧值
        for (int s = t; s >= a[i]; s--) {
            ways[s] += ways[s - a[i]];
        }
    }

    cout << ways[t] << endl;
    return 0;
}
