/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:46
 * update_at: 2026-10-08 22:46
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105; // 题面保证数组元素个数小于 50，留一倍余量防越界

ll n;       // 数组元素个数
ll a[MAXN]; // a[0..n-1] 为输入的 n 个正整数，值均小于 1000

// 把数组整体左移一位：先存下队首，其余元素依次前移一格，最后把队首写到末位。
// n = 1 时左移前后相同，循环不执行、a[n-1] = a[0]，天然正确。
void shift_left() {
    ll first = a[0];
    for (ll i = 1; i < n; i++) {
        a[i - 1] = a[i];
    }
    a[n - 1] = first;
}

void solve() {
    cin >> n;
    if (n <= 0) return; // 防御性处理：题面保证 n >= 1，真出现非法 n 就不输出

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    shift_left();

    // 每个数之间一个空格，行末不留空格，最后补一个换行
    for (ll i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
