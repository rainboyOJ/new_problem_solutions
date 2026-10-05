/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:49
 * update_at: 2026-10-05 08:50
 */
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXLEN = 305; // 输入位数上限 300，开到 305 留余量

char str_a[MAXLEN];
char str_b[MAXLEN];
int a[MAXLEN];   // 被除数 A 的数位，a[0] 是最高位
int b[MAXLEN];   // 除数 B 的数位，b[0] 是最高位
int rem[MAXLEN]; // 当前部分被除数（余数），rem[0] 是最高位，无前导零
int q[MAXLEN];   // 商的数位，q[0] 是最高位
ll la;           // A 的位数
ll lb;           // B 的位数
ll lr;           // 当前余数的位数
ll lq = 0;       // 商的位数

// 把 rem 与 b 比较：rem > b 返回 1，相等返回 0，小于返回 -1。
int cmp_rem_b() {
    if (lr != lb) {
        return lr > lb ? 1 : -1;
    }
    for (ll i = 0; i < lr; i++) {
        if (rem[i] != b[i]) {
            return rem[i] > b[i] ? 1 : -1;
        }
    }
    return 0;
}

// 执行 rem = rem - b，要求调用前 rem >= b；b 的最低位对齐到 rem 的最低位。
void sub_b() {
    ll shift = lr - lb; // b[j] 对齐到 rem 的下标 j + shift
    ll borrow = 0;
    for (ll i = lr - 1; i >= 0; i--) {
        ll j = i - shift;
        ll sub = (j >= 0) ? b[j] : 0;
        ll t = rem[i] - sub - borrow;
        if (t < 0) {
            t += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        rem[i] = t;
    }
    // 去掉最高位上的前导零，保持 rem 是规范表示。
    ll start = 0;
    while (start + 1 < lr && rem[start] == 0) {
        start++;
    }
    if (start > 0) {
        for (ll i = start; i < lr; i++) {
            rem[i - start] = rem[i];
        }
        lr -= start;
    }
}

int main() {
    if (scanf("%s", str_a) != 1) {
        return 0;
    }
    if (scanf("%s", str_b) != 1) {
        return 0;
    }
    la = strlen(str_a);
    lb = strlen(str_b);
    for (ll i = 0; i < la; i++) {
        a[i] = str_a[i] - '0';
    }
    for (ll i = 0; i < lb; i++) {
        b[i] = str_b[i] - '0';
    }

    lr = 1;
    rem[0] = 0; // 余数从 0 开始
    for (ll i = 0; i < la; i++) {
        // 竖式的一步：把 A 的下一位拉下来，rem = rem * 10 + a[i]
        rem[lr] = a[i];
        lr++;
        // 去掉新产生的前导零
        ll start = 0;
        while (start + 1 < lr && rem[start] == 0) {
            start++;
        }
        if (start > 0) {
            for (ll j = start; j < lr; j++) {
                rem[j - start] = rem[j];
            }
            lr -= start;
        }
        // 反复减 B，减的次数就是这一位的商数字
        ll digit = 0;
        while (cmp_rem_b() >= 0) {
            sub_b();
            digit++;
        }
        q[lq] = digit;
        lq++;
    }

    // 输出商，去掉前导零
    ll qs = 0;
    while (qs + 1 < lq && q[qs] == 0) {
        qs++;
    }
    for (ll i = qs; i < lq; i++) {
        printf("%d", q[i]);
    }
    printf("\n");
    // 输出余数（rem 已无前导零，至少有一位）
    for (ll i = 0; i < lr; i++) {
        printf("%d", rem[i]);
    }
    printf("\n");
    return 0;
}
