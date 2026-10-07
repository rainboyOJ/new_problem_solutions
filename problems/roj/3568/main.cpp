/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:15
 * update_at: 2026-10-06 14:15
 */

#include <iostream>
using namespace std;

typedef long long ll;
const int MAXN = 105; // n <= 100

ll a[MAXN]; // 降幂排列的系数，a[i] 对应 x^(n-i)
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i <= n; i++) cin >> a[i];

    bool first = true; // 是否还未输出任何非零项
    for (int i = 0; i <= n; i++) {
        ll coeff = a[i];
        if (coeff == 0) continue; // 只输出非零项

        int deg = n - i; // 当前项次数

        // 符号：首项正号省略，其余按正负输出 + 或 -
        if (first) {
            if (coeff < 0) cout << '-';
        } else {
            cout << (coeff < 0 ? '-' : '+');
        }

        // 系数：高于 0 次且绝对值为 1 时省略
        ll aval = coeff < 0 ? -coeff : coeff;
        if (!(aval == 1 && deg > 0)) cout << aval;

        // 幂次：>1 输出 x^b，=1 输出 x，=0 不输出
        if (deg > 1) cout << 'x' << '^' << deg;
        else if (deg == 1) cout << 'x';

        first = false;
    }

    cout << '\n';
    return 0;
}
