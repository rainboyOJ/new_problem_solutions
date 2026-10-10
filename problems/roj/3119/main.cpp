/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 普通平衡树（无旋树状数组版）：离线坐标压缩 + 树状数组上倍增求第 k 小。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Op {
    ll opt;
    ll x;
};

std::vector<ll> coords; // 离线坐标：所有可能出现过的数值（操作 4 的 x 是排名，必须排除）
std::vector<ll> tree;   // 树状数组，1-based

// 把坐标 pos（0-based）上的出现次数改变 delta
void add(ll pos, ll delta) {
    ll i = pos + 1;
    while (i < (ll)tree.size()) {
        tree[i] += delta;
        i += i & -i;
    }
}

// 统计下标严格小于 pos 的坐标上已有的元素总数
ll count_below(ll pos) {
    ll total = 0;
    while (pos) {
        total += tree[pos];
        pos -= pos & -pos;
    }
    return total;
}

// 返回第 rank 小（1-based）的数值
ll value_at(ll rank) {
    ll i = 0;
    ll step = 1;
    while (step * 2 < (ll)tree.size()) step *= 2;
    while (step) {
        ll nxt = i + step;
        if (nxt < (ll)tree.size() && tree[nxt] < rank) {
            i = nxt;
            rank -= tree[nxt];
        }
        step >>= 1;
    }
    return coords[i];
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    std::vector<Op> ops(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld %lld", &ops[i].opt, &ops[i].x);
    }

    coords.clear();
    for (ll i = 0; i < n; i++) {
        if (ops[i].opt != 4) coords.push_back(ops[i].x);
    }
    std::sort(coords.begin(), coords.end());
    coords.erase(std::unique(coords.begin(), coords.end()), coords.end());
    tree.assign(coords.size() + 1, 0);

    std::vector<ll> out;
    for (ll i = 0; i < n; i++) {
        ll opt = ops[i].opt, x = ops[i].x;
        if (opt == 1) {
            add(std::lower_bound(coords.begin(), coords.end(), x) - coords.begin(), 1);
        } else if (opt == 2) {
            add(std::lower_bound(coords.begin(), coords.end(), x) - coords.begin(), -1);
        } else if (opt == 3) { // 排名 = 严格小于 x 的个数 + 1
            ll pos = std::lower_bound(coords.begin(), coords.end(), x) - coords.begin();
            out.push_back(count_below(pos) + 1);
        } else if (opt == 4) { // 第 x 小的数值
            out.push_back(value_at(x));
        } else if (opt == 5) { // 前驱
            ll pos = std::lower_bound(coords.begin(), coords.end(), x) - coords.begin();
            out.push_back(value_at(count_below(pos)));
        } else { // 后继
            ll pos = std::upper_bound(coords.begin(), coords.end(), x) - coords.begin();
            out.push_back(value_at(count_below(pos) + 1));
        }
    }

    for (size_t i = 0; i < out.size(); i++) {
        printf("%lld\n", out[i]);
    }
    return 0;
}
