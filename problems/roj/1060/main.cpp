/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:49
 * update_at: 2026-10-04 23:49
 */

#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;

typedef long long ll;

int n;            // 样本容量
double sum;       // 样本总和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;              // 读入 n
    for (int i = 1; i <= n; i++) {
        double x;          // 第 i 个样本
        cin >> x;
        sum += x;          // 累加
    }
    cout << fixed << setprecision(4) << sum / n << '\n';
    return 0;
}
