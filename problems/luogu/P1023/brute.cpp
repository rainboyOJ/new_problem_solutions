#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXM = 100005;

struct Fraction {
    i64 num; // 分子
    i64 den; // 分母，恒为正数
};

int target_price;
int point_cnt;
int tail_drop;
int raw_price[MAXM], raw_sale[MAXM];

// brute.cpp：教学用暴力。
// 直接枚举整数 k，并按题意计算每个价格下的销量和利润。

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

int get_upper_price() {
    int last_price = raw_price[point_cnt];
    int last_sale = raw_sale[point_cnt];
    if (tail_drop == 0) {
        return last_price;
    }
    return last_price + (last_sale - 1) / tail_drop;
}

// 返回售价 x 在税收/补贴 k 下的总利润。
// 这里利润也保存成分数，避免插值时的除法误差。
Fraction get_profit(int x, int k, int cost_price) {
    Fraction sale = get_sale_fraction(x);
    return {sale.num * (x - cost_price + k), sale.den};
}

bool check(int k, int cost_price, int upper_price) {
    if (target_price < cost_price || target_price > upper_price) {
        return false;
    }

    Fraction target_sale = get_sale_fraction(target_price);
    if (target_sale.num <= 0) {
        return false;
    }

    Fraction target_profit = get_profit(target_price, k, cost_price);

    for (int x = cost_price; x <= upper_price; x++) {
        if (x == target_price) {
            continue;
        }
        Fraction sale = get_sale_fraction(x);
        if (sale.num <= 0) {
            continue;
        }

        Fraction profit = get_profit(x, k, cost_price);
        if (cmp_fraction(profit, target_profit) >= 0) {
            return false;
        }
    }
    return true;
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

    // 暴力范围开大一些，供随机对拍使用。
    for (int d = 0; d <= 2000; d++) {
        if (check(d, cost_price, upper_price)) {
            cout << d << '\n';
            return 0;
        }
        if (d != 0 && check(-d, cost_price, upper_price)) {
            cout << -d << '\n';
            return 0;
        }
    }

    cout << "NO SOLUTION\n";
    return 0;
}
