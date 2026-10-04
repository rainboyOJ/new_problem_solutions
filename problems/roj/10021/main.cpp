/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:00
 * update_at: 2026-10-04 23:00
 */
// main.cpp：roj 10021 游戏
// 把 Alice 的宝石数看成 [0, n+m] 上的反射随机游走，游戏结束时它恰好回到出发点 n。
// 由 Kac 回返定理，期望回返时间 E = 1/pi(n)，其中平稳分布 pi(k) 正比于 (q/p)^k，
// 约去公共因子后 E = sum_{k=0}^{n+m} ((1-p)/p)^(k-n)。
// 注意 (1-p)/p 最大约 1e6、指数最大 200，直接求幂会溢出到 1e600；
// 所以先定位最大项、把它提到外面，再用 log10 分离指数与尾数，手工拼出定点小数。
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

ll n, m;      // Alice、Bob 的初始宝石数
ll scale;     // 概率 p 的小数位数对应的 10 的幂，例如 p = 0.125 时 scale = 1000
ll p_scaled;  // p 按 scale 缩放后的整数分子，p = p_scaled / scale
ll q_scaled;  // q = 1 - p 同分母下的整数分子，q_scaled = scale - p_scaled

// 读入 n、m 和有限小数 p。
// p 用字符串读入并按小数位数缩放成整数，避免直接读浮点带来的表示误差。
void read_input() {
    string p_text;
    cin >> n >> m;
    cin >> p_text;

    ll point = p_text.size();  // 小数点位置；没有小数点时保持在末尾
    for (ll i = 0; i < (ll)p_text.size(); i++) {
        if (p_text[i] == '.') point = i;
    }

    scale = 1;
    for (ll i = point + 1; i < (ll)p_text.size(); i++) scale *= 10;

    p_scaled = 0;
    for (ll i = 0; i < (ll)p_text.size(); i++) {
        if (p_text[i] == '.') continue;
        p_scaled = p_scaled * 10 + (p_text[i] - '0');
    }
    q_scaled = scale - p_scaled;
}

// 输出 value * 10^exponent 的定点小数（保留 8 位小数）。
// value 落在 [1, 10)，exponent >= 0，整数部分不足的位用 0 补齐；
// 超出浮点有效位数的低位补 0，相对误差仍可忽略。
void print_scaled(long double value, ll exponent) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%.17Lf", value);

    char digits[64];  // value 的有效数字，去掉小数点后按位存放
    ll len = 0;
    for (ll i = 0; buffer[i] != '\0' && len < 40; i++) {
        if (buffer[i] == '.') continue;
        digits[len] = buffer[i];
        len++;
    }

    string out;
    for (ll i = 0; i <= exponent; i++) out.push_back(i < len ? digits[i] : '0');
    out.push_back('.');
    for (ll i = 0; i < 8; i++) {
        ll pos = exponent + 1 + i;
        out.push_back(pos < len ? digits[pos] : '0');
    }
    printf("%s\n", out.c_str());
}

int main() {
    read_input();

    ll total = n + m;                                              // 宝石总数，也是随机游走状态的上界
    long double r = (long double)q_scaled / (long double)p_scaled;  // 反向概率比 q/p

    // 找出答案 sum r^(k-n) 中绝对值最大的一项所在下标 dominant。
    // r >= 1 时最大项在 k = total（指数为 m），r < 1 时最大项在 k = 0（指数为 -n）。
    ll dominant = total;
    if (r < 1.0L) dominant = 0;

    // 提出最大项后 sum = r^(dominant-n) * s，其中 s = sum r^(k-dominant) 落在 [1, total+1]。
    // 从 dominant 向两侧扩展时每项都不超过 1，因此不会溢出。
    long double s = 1.0L;
    long double term = 1.0L;
    for (ll k = dominant - 1; k >= 0; k--) {
        term /= r;
        s += term;
    }
    term = 1.0L;
    for (ll k = dominant + 1; k <= total; k++) {
        term *= r;
        s += term;
    }

    // log10(答案) = (dominant - n) * log10(r) + log10(s)。
    long double log10_answer = (long double)(dominant - n) * log10l(r) + log10l(s);

    ll exponent = (ll)floorl(log10_answer);
    long double mantissa_part = log10_answer - (long double)exponent;  // 答案的小数尾数部分，落在 [0, 1)
    while (mantissa_part < 0.0L) {
        mantissa_part += 1.0L;
        exponent--;
    }
    while (mantissa_part >= 1.0L) {
        mantissa_part -= 1.0L;
        exponent++;
    }
    long double mantissa = powl(10.0L, mantissa_part);  // 尾数，落在 [1, 10)

    print_scaled(mantissa, exponent);
    return 0;
}
