#include <iostream>
using namespace std;
typedef long long ll;

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:15
 * update_at: 2026-10-05 01:15
 */

// 数组逆序重存放：读入 n 和 n 个整数，逆序输出

const int MAXN = 105; // 题目 n<100，开 105 足够
int a[MAXN];
int n;

int main() {
    // 读入 n 与数组
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 逆序输出：i 从 n 倒着遍历到 1
    for (int i = n; i >= 1; i--) {
        if (i != n) cout << ' ';
        cout << a[i];
    }
    cout << '\n';

    return 0;
}