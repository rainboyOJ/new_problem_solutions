/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:03
 * update_at: 2026-10-08 07:03
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 5005; // 农民数量上限

struct Farmer {
    ll price; // 每加仑牛奶的单价 P_i
    ll amount; // 该农民一天能提供的最大牛奶量 A_i
};

Farmer f[MAXM]; // f[1..m] 存每个农民的价格与供应量

// 按单价升序排序：单价相同时谁在前无所谓，牛奶完全同质
bool cmp_price(const Farmer &x, const Farmer &y) {
    return x.price < y.price;
}

int main() {
    ll need; // 每日需求量 N
    ll m;    // 农民数量 M
    if (scanf("%lld %lld", &need, &m) != 2) {
        return 0;
    }

    for (ll i = 1; i <= m; i++) {
        scanf("%lld %lld", &f[i].price, &f[i].amount);
    }

    sort(f + 1, f + m + 1, cmp_price);

    ll remain = need; // 还差多少牛奶没买到
    ll cost = 0;      // 累计花费，最坏 2e6 * 1000 = 2e9，必须用 64 位
    for (ll i = 1; i <= m && remain > 0; i++) {
        if (f[i].amount <= remain) {
            // 该农民的牛奶全部买下还不够（或刚好够），整批拿走
            cost += f[i].amount * f[i].price;
            remain -= f[i].amount;
        } else {
            // 只买凑满需求的那一部分，买完就结束
            cost += remain * f[i].price;
            remain = 0;
        }
    }

    printf("%lld\n", cost);
    return 0;
}
