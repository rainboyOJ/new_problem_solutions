/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:45
 * update_at: 2026-10-05 03:45
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

// 求三个数的最大值（题面要求定义成函数，用返回值交回结果）
ll max3(ll x, ll y, ll z) {
    ll top = x;
    if (top < y) top = y;
    if (top < z) top = z;
    return top;
}

ll a, b, c;      // 输入的三个数
ll out_proc;     // 过程版的输出参数（用全局变量模拟 Pascal 的 var 参数）

// 求三个数的最大值（题面要求定义成过程，无返回值，结果写进输出参数）
void max3_proc(ll x, ll y, ll z) {
    ll top = x;
    if (top < y) top = y;
    if (top < z) top = z;
    out_proc = top;
}

int main() {
    scanf("%lld %lld %lld", &a, &b, &c);

    // 分子：max(a,b,c)，用函数版的返回值
    ll numerator = max3(a, b, c);

    // 分母左因子：max(a+b, b,c)，用过程版的输出参数
    max3_proc(a + b, b, c);
    ll left = out_proc;

    // 分母右因子：max(a, b, b+c)，再用一次过程版
    max3_proc(a, b, b + c);
    ll right = out_proc;

    // 1.0 * 抬成浮点除法，防止整数除法丢小数
    double m = 1.0 * numerator / (left * right);

    printf("%.3f\n", m);
    return 0;
}
