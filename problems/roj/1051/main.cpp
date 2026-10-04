/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 16:21
 * update_at: 2026-10-04 23:37
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

double x; // 输入的自变量，范围 [0, 20)
double y; // 分段函数值 f(x)

int main () {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> x;

    // 三段左闭右开区间，依次判断 x 落在哪一段
    if (x < 5) {
        y = -x + 2.5;          // [0, 5)
    } else if (x < 10) {
        y = 2 - 1.5 * (x - 3) * (x - 3); // [5, 10)
    } else {
        y = x / 2 - 1.5;       // [10, 20)
    }

    // 保留三位小数输出
    cout << fixed << setprecision(3) << y << endl;

    return 0;
}
