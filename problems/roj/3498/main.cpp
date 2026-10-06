/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:08
 * update_at: 2026-10-06 12:08
 */

// 解一元一次方程：无括号，只有整数、一个未知数字母和 + - = 三种符号。
// 思路：把 = 右边整体移到左边（逐项变号），合并同类项得 coef*x + const = 0，
// 答案 x = -const / coef。
#include <cstdio>
#include <cstring>

typedef long long ll;

char s[1005];   // 存整个方程
ll len;         // 方程长度
ll pos;         // 当前解析到的下标
ll coef;        // 未知数系数和（移项后）
ll cst;         // 常数项和（移项后）
char name;      // 未知数字母

// 判断是否字母（未知数）
bool is_alpha(char c) {
    return c >= 'a' && c <= 'z';
}

// 解析一项：该项必带符号（用 side 修正右半边方向），累加进 coef / cst
// side：左半边为 1，右半边为 -1（相当于右边整体乘 -1 移到左边）
void parse_term(ll side) {
    ll sign = 1;        // 这一项的符号
    if (s[pos] == '-') {
        sign = -1;
        pos++;
    } else if (s[pos] == '+') {
        pos++;
    }
    // 项体：要么是数字串（后面可跟字母），要么是单个字母（省略系数 1）
    ll num = 0;
    bool has_digit = false;
    while (pos < len && s[pos] >= '0' && s[pos] <= '9') {
        num = num * 10 + (s[pos] - '0');
        has_digit = true;
        pos++;
    }
    if (pos < len && is_alpha(s[pos])) { // 未知数项：6a / a / -a
        if (!has_digit) num = 1;         // 省略了系数 1
        coef += side * sign * num;
        if (name == 0) name = s[pos];    // 记下未知数字母
        pos++;
    } else {                             // 常数项
        cst += side * sign * num;
    }
}

int main() {
    scanf("%s", s);
    len = strlen(s);
    pos = 0;
    coef = 0;
    cst = 0;
    name = 0;

    // 左半边：遇到 = 停
    while (pos < len && s[pos] != '=') parse_term(1);
    pos++; // 跳过 =
    // 右半边：side = -1 表示移项到左边要变号
    while (pos < len) parse_term(-1);

    // 此时方程化为 coef * x + cst = 0，x = -cst / coef（ll 除法转 double 隐式完成）
    double ans = -1.0 * cst / coef;
    if (ans == 0.0) ans = 0.0; // 消除 -0.000 的情况
    printf("%c=%.3f\n", name, ans);
    return 0;
}
