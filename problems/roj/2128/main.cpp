/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:50
 * update_at: 2026-10-08 07:50
 */

// 2128 高精度乘法（II）
// 输入两个小于 200000 位的十进制正整数 a、b，输出 a*b。
//
// 做法：把两个数看成以 10 为底的多项式，两数相乘就是多项式乘积（系数卷积），
//       用 FFT 在 O((La+Lb) log(La+Lb)) 内算出卷积，最后从低位到高位统一进位。
// 精度：单个系数最大为 min(La,Lb)*9*9 < 200000*81 ≈ 1.62e7，
//       远小于 double 尾数能精确表示的整数上限 9e15，不会有取整误差。
// 边界：输入可能出现 "0" 或前导零（如 "00000001"），按数值语义解析。
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double PI = acos(-1.0);
const int MAXN = 1 << 19;  // 524288：不小于 (200000+200000) 的最小 2 的幂

// 手写复数：只用到加、减、乘，避免引入额外头文件依赖
struct Complex {
    double r, i;
    Complex() : r(0.0), i(0.0) {}
    Complex(double _r, double _i) : r(_r), i(_i) {}
    Complex operator+(const Complex &o) const { return Complex(r + o.r, i + o.i); }
    Complex operator-(const Complex &o) const { return Complex(r - o.r, i - o.i); }
    Complex operator*(const Complex &o) const {
        return Complex(r * o.r - i * o.i, r * o.i + i * o.r);
    }
};

Complex fa[MAXN], fb[MAXN];  // 两个多项式的系数（实部存数字，虚部为 0）
int rev[MAXN];               // 位反转置换，三次变换共用同一张表

// 迭代式 FFT：先按 rev 重排，再自底向上做蝶形合并。
// inv = 0 正变换，inv = 1 逆变换（最后除以 n）。
void fft(Complex *a, int n, int inv) {
    for (int i = 0; i < n; ++i) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2.0 * PI / len * (inv ? -1.0 : 1.0);
        Complex wn(cos(ang), sin(ang));  // 本层的单位根
        for (int i = 0; i < n; i += len) {
            Complex w(1.0, 0.0);
            for (int j = 0; j < len / 2; ++j) {
                Complex u = a[i + j];
                Complex v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w = w * wn;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; ++i) {
            a[i].r /= n;
            a[i].i /= n;
        }
    }
}

// 去掉前导零；全是零时保留一个 '0'，方便统一判断零值
string stripLeadingZeros(const string &s) {
    ll p = 0;
    while (p + 1 < (ll)s.size() && s[p] == '0') ++p;
    return s.substr(p);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    if (!(cin >> a >> b)) return 0;
    a = stripLeadingZeros(a);
    b = stripLeadingZeros(b);

    // 有一边为 0，乘积必为 0（题面说正整数，但数据里有 0 与前导零）
    if (a == "0" || b == "0") {
        printf("0\n");
        return 0;
    }

    ll la = a.size(), lb = b.size();
    int lim = 1;
    while (lim < la + lb) lim <<= 1;  // 不小于结果位数的 2 的幂

    // 倒序填入：下标 i 对应 10^i 位
    for (ll i = 0; i < la; ++i) fa[i] = Complex(a[la - 1 - i] - '0', 0.0);
    for (ll i = 0; i < lb; ++i) fb[i] = Complex(b[lb - 1 - i] - '0', 0.0);

    // 位反转表：rev[i] = rev[i>>1]>>1 再补上最高位
    rev[0] = 0;
    for (int i = 1; i < lim; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    }

    fft(fa, lim, 0);
    fft(fb, lim, 0);
    for (int i = 0; i < lim; ++i) fa[i] = fa[i] * fb[i];  // 频域逐点相乘
    fft(fa, lim, 1);                                      // 逆变换回系数

    // 浮点结果带微小误差，必须四舍五入而不是截断
    ll carry = 0;
    string out;
    for (ll i = 0; i < la + lb; ++i) {
        ll cur = (ll)(fa[i].r + 0.5) + carry;
        out.push_back(char('0' + cur % 10));
        carry = cur / 10;
    }
    while (carry > 0) {
        out.push_back(char('0' + carry % 10));
        carry /= 10;
    }
    while (out.size() > 1 && out.back() == '0') out.pop_back();  // 去掉高位多余零

    reverse(out.begin(), out.end());
    printf("%s\n", out.c_str());
    return 0;
}
