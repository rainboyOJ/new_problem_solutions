/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:08
 * update_at: 2026-08-28 19:08
 */
// A. Number：按位四舍五入的数组模拟。
// 逆序存数字（a[0] 是个位），每步对"当前数"的第 p 位判断：
// 该位 >= 5 就向前一位进 1 并连锁进位，然后把第 p 位及以下全部置 0。
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 105;

int k;
int a[MAXK + 5]; // a[0] 是个位，逆序存放数字，多留几个位置给最高位进位

// 输出当前数：从最高非零位开始，跳过前导零。
void print_num() {
    int top = MAXK + 4;
    while (top > 0 && a[top] == 0) top--;
    for (int i = top; i >= 0; i--) cout << a[i];
}

void solve() {
    string s;
    cin >> k >> s;
    memset(a, 0, sizeof(a));
    for (int i = 0; i < k; i++) a[i] = s[k - 1 - i] - '0';

    print_num();
    for (int p = 0; p < k - 1; p++) { // 从个位向高位依次处理 k-1 步
        // 第 p 位 >= 5：舍去后向前一位进 1
        if (a[p] >= 5) {
            a[p + 1]++;
            // 连锁进位：某位超过 9 就继续向更高位进，直到全部小于 10
            int j = p + 1;
            while (a[j] >= 10) {
                a[j + 1] += a[j] / 10;
                a[j] %= 10;
                j++;
            }
        }
        a[p] = 0; // 舍去第 p 位（更低的位在之前步骤已全部为 0）
        cout << " -> ";
        print_num();
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}