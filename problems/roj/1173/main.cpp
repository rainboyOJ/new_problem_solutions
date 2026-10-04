/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:18
 * update_at: 2026-10-05 04:18
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int LEN = 200;        // 数组长度，50! 只有 65 位十进制数字，这里留足余量
int fact[LEN], sumv[LEN];   // fact: 当前阶乘；sumv: 当前累加和，均按低位在前存
int lf = 1, ls = 1;         // 两个数的当前有效位数

// 高精度乘单精度：大整数 a（共 len 位）乘以一个小整数 x，结果仍放在 a 中
void mul(int a[], int &len, int x) {
    for (int i = 0; i < len; i++) a[i] *= x;
    int carry = 0;
    for (int i = 0; i < len || carry; i++) {
        if (i >= len) a[len++] = 0;          // 进位产生新位时扩展长度
        a[i] += carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
}

// 高精度加：把大整数 a 加到 c 上
void add(int c[], int &lc, int a[], int la) {
    if (lc < la) lc = la;    // 结果位数至少取两者较大者
    int carry = 0;
    for (int i = 0; i < lc || carry; i++) {
        if (i >= lc) c[lc++] = 0;            // 进位产生新位
        int t = c[i] + (i < la ? a[i] : 0) + carry;
        c[i] = t % 10;
        carry = t / 10;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    fact[0] = 1;   // 0! = 1，作为滚动起点
    lf = 1;
    sumv[0] = 0;
    ls = 1;

    for (int i = 1; i <= n; i++) {
        mul(fact, lf, i);   // f_i = f_{i-1} * i
        add(sumv, ls, fact, lf); // S_i = S_{i-1} + f_i
    }

    // 从最高位开始输出
    for (int i = ls - 1; i >= 0; i--) cout << sumv[i];
    cout << '\n';

    return 0;
}
