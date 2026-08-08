#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXM = 100005;
const i64 INF64 = (1LL << 60);

struct Fraction {
    i64 num; // 分子
    i64 den; // 分母，恒为正数
};

int target_price;
int point_cnt;
int tail_drop;
int raw_price[MAXM], raw_sale[MAXM];

// 比较两个分数 a 和 b 的大小，返回：
// -1: a < b
//  0: a = b
//  1: a > b
int cmp_fraction(Fraction a, Fraction b) {
    __int128 left = (__int128) a.num * b.den;
    __int128 right = (__int128) b.num * a.den;
    if (left < right) {
        return -1;
    }
    if (left > right) {
        return 1;
    }
    return 0;
}

// 计算 floor(a / b)，其中 b > 0，支持 a 为负数。
i64 floor_div(i64 a, i64 b) {
    if (a >= 0) {
        return a / b;
    }
    return -((-a + b - 1) / b);
}

// 计算 ceil(a / b)，其中 b > 0，支持 a 为负数。
i64 ceil_div(i64 a, i64 b) {
    if (a >= 0) {
        return (a + b - 1) / b;
    }
    return -((-a) / b);
}

// 返回售价 x 对应的销量。
// 为了避免中间插值产生误差，这里把销量写成分数。
Fraction get_sale_fraction(int x) {
    for (int i = 1; i < point_cnt; i++) {
        int x1 = raw_price[i];
        int y1 = raw_sale[i];
        int x2 = raw_price[i + 1];
        int y2 = raw_sale[i + 1];
        if (x1 <= x && x <= x2) {
            i64 num = 1LL * y1 * (x2 - x1) + 1LL * (y2 - y1) * (x - x1);
            i64 den = x2 - x1;
            return {num, den};
        }
    }

    int last_price = raw_price[point_cnt];
    int last_sale = raw_sale[point_cnt];
    return {1LL * last_sale - 1LL * tail_drop * (x - last_price), 1};
}

// 计算某个给定售价下，销量变成非正数前最后还需要检查到哪个价格。
int get_upper_price() {
    int last_price = raw_price[point_cnt];
    int last_sale = raw_sale[point_cnt];

    if (tail_drop == 0) {
        // 题面通常不会出现这种情况；若真的出现，销量不会继续下降，
        // 说明高价可以无限延伸，这时利润不会有唯一最大值。
        return last_price;
    }

    // 当销量 > 0 时才有意义，所以只需检查到最后一个正销量价格。
    return last_price + (last_sale - 1) / tail_drop;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target_price;
    while (true) {
        int x, y;
        cin >> x >> y;
        if (x == -1 && y == -1) {
            break;
        }
        raw_price[++point_cnt] = x;
        raw_sale[point_cnt] = y;
    }
    cin >> tail_drop;

    int cost_price = raw_price[1];
    int upper_price = get_upper_price();

    // 目标价本身如果已经没有正销量，那么一定无解。
    Fraction target_sale = get_sale_fraction(target_price);
    if (target_price < cost_price || target_price > upper_price || target_sale.num <= 0) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    // 对每个竞争价格 x，都有：
    // (tp - cost + k) * st > (x - cost + k) * sx
    // 化简成：
    // k * (st - sx) > (x - cost) * sx - (tp - cost) * st
    // 这是关于 k 的一次严格不等式。
    i64 low = -INF64; // k 的下界，满足 k >= low
    i64 high = INF64; // k 的上界，满足 k <= high

    for (int x = cost_price; x <= upper_price; x++) {
        if (x == target_price) {
            continue;
        }

        Fraction sale_x = get_sale_fraction(x);
        if (sale_x.num <= 0) {
            continue;
        }

        __int128 a128 = (__int128) target_sale.num * sale_x.den - (__int128) sale_x.num * target_sale.den;
        __int128 b128 = (__int128) (x - cost_price) * sale_x.num * target_sale.den
            - (__int128) (target_price - cost_price) * target_sale.num * sale_x.den;

        i64 a = (i64) a128;
        i64 b = (i64) b128;

        if (a == 0) {
            // 这时不等式退化成 0 > b。
            // 若不成立，说明无论怎么调税收/补贴，目标价都无法严格更优。
            if (!(0 > b)) {
                cout << "NO SOLUTION\n";
                return 0;
            }
            continue;
        }

        if (a > 0) {
            // k > b / a，所以 k >= floor(b / a) + 1
            low = max(low, floor_div(b, a) + 1);
        }
        else {
            // k < b / a。
            // 由于 a < 0，改写成 k * (-a) < (-b)，其中 (-a) > 0。
            // 对整数来说，等价于：
            // k <= ceil((-b) / (-a)) - 1
            high = min(high, ceil_div(-b, -a) - 1);
        }
    }

    if (low > high) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    // 在整数区间 [low, high] 中找绝对值最小的 k。
    i64 answer;
    if (low <= 0 && 0 <= high) {
        answer = 0;
    }
    else if (high < 0) {
        answer = high;
    }
    else {
        answer = low;
    }

    cout << answer << '\n';

    return 0;
}
