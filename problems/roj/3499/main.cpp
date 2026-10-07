/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:10
 * update_at: 2026-10-06 12:10
 */
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef __int128 i128;

const int MAXP = 300000;      // 价位扫描上限，防止销量永不归零时死循环

ll P;                         // 政府预期价
ll cost;                      // 商品成本
vector<ll> xs;                // 升序已知价位表
vector<ll> ss;                // 对应销量
ll drop;                      // 超过最高已知价位后每涨 1 元减少的销量

// 计算 a/b 的上取整，b != 0
ll ceil_div(i128 a, i128 b) {
    i128 q = a / b;
    i128 r = a % b;
    if (r != 0 && ((r > 0) == (b > 0))) ++q;
    return (ll)q;
}

// 计算 a/b 的下取整，b != 0
ll floor_div(i128 a, i128 b) {
    i128 q = a / b;
    i128 r = a % b;
    if (r != 0 && ((r > 0) != (b > 0))) --q;
    return (ll)q;
}

// 返回价位 p 的销量，以分数 num/den 表示（den > 0）
void get_sales(ll p, ll &num, ll &den) {
    int i = upper_bound(xs.begin(), xs.end(), p) - xs.begin() - 1;
    if (i + 1 < (int)xs.size()) {
        ll p0 = xs[i], p1 = xs[i + 1];
        den = p1 - p0;
        num = ss[i] * den + (ss[i + 1] - ss[i]) * (p - p0);
    } else {
        den = 1;
        num = ss[i] - drop * (p - xs[i]);
    }
}

// 输出 __int128 整数
void print_i128(i128 x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    char buf[50];
    int len = 0;
    while (x > 0) {
        buf[len++] = '0' + (int)(x % 10);
        x /= 10;
    }
    while (len--) putchar(buf[len]);
}

int main() {
    scanf("%lld", &P);

    ll s0;
    scanf("%lld%lld", &cost, &s0);

    map<ll, ll> known;
    known[cost] = s0;

    while (true) {
        ll p, s;
        scanf("%lld%lld", &p, &s);
        if (p == -1 && s == -1) break;
        known[p] = s;
    }

    scanf("%lld", &drop);

    for (auto &kv : known) {
        xs.push_back(kv.first);
        ss.push_back(kv.second);
    }

    // 预期价不能低于成本，否则产品不会在该价位销售
    if (P < cost) {
        printf("NO SOLUTION\n");
        return 0;
    }

    ll t_num, t_den;
    get_sales(P, t_num, t_den);
    // 预期价位上没有销量，谈不上最大总利润
    if (t_num <= 0) {
        printf("NO SOLUTION\n");
        return 0;
    }

    ll base = P - cost;           // 预期价位的不含税单位利润
    i128 lo = 0, hi = 0;
    bool has_lo = false, has_hi = false;

    // 从成本价开始逐价位扫描，销量非正即停止
    for (ll p = cost; p <= MAXP; ++p) {
        ll num, den;
        get_sales(p, num, den);
        if (num <= 0) break;

        ll gain = p - cost;
        // 要求 (base+t) * t_num/t_den >= (gain+t) * num/den
        i128 target_coef = (i128)t_num * den;   // 左边 t 的系数
        i128 price_coef = (i128)num * t_den;    // 右边 t 的系数

        if (target_coef == price_coef) {
            // 销量相同：该价位不含税单位利润不能更高，否则任何 t 都无法使 P 最大
            if (gain > base) {
                printf("NO SOLUTION\n");
                return 0;
            }
        } else if (target_coef > price_coef) {
            // t 有下界
            i128 rhs = (i128)price_coef * gain - (i128)target_coef * base;
            i128 dif = target_coef - price_coef; // > 0
            i128 bound = ceil_div(rhs, dif);
            if (!has_lo || bound > lo) {
                lo = bound;
                has_lo = true;
            }
        } else {
            // t 有上界
            i128 rhs = (i128)price_coef * gain - (i128)target_coef * base;
            i128 dif = target_coef - price_coef; // < 0
            i128 bound = floor_div(rhs, dif);
            if (!has_hi || bound < hi) {
                hi = bound;
                has_hi = true;
            }
        }
    }

    // 无可行补贴额
    if (has_lo && has_hi && lo > hi) {
        printf("NO SOLUTION\n");
        return 0;
    }

    i128 ans;
    if ((!has_lo || lo <= 0) && (!has_hi || hi >= 0)) {
        ans = 0;                // 可行区间包含 0，取绝对值最小
    } else if (has_hi && hi < 0) {
        ans = hi;               // 全负，取右端点
    } else {
        ans = lo;               // 全正，取左端点
    }

    print_i128(ans);
    putchar('\n');
    return 0;
}
