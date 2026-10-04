/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:48
 * update_at: 2026-10-05 00:48
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;           // 累加项数上限
ll fact = 1;    // 当前 k!，从 1! 开始递推
double e = 1.0; // 部分和，先放入常数项 1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 递推阶乘并累加 1/k!：fact 先乘 k 得到 k!，再取倒数加入 e
    for (ll k = 1; k <= n; k++) {
        fact *= k;
        e += 1.0 / fact;
    }

    cout << fixed << setprecision(10) << e << "\n";
    return 0;
}
