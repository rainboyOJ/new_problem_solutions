/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 区间加 + 区间和：两个树状数组维护差分序列 d[i] 与 i·d[i]。
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

typedef long long ll;

const ll MAXN = 100005;

ll n, m;
ll bit1[MAXN]; // 差分数组 d 的树状数组
ll bit2[MAXN]; // i·d[i] 的树状数组

// 在下标 i 处加 delta：沿 i += i & -i 上溯
void bit_add(ll* bit, ll i, ll delta) {
    while (i <= n) {
        bit[i] += delta;
        i += i & -i;
    }
}

// 求 bit 维护序列的前 i 项和
ll bit_sum(ll* bit, ll i) {
    ll total = 0;
    while (i > 0) {
        total += bit[i];
        i -= i & -i;
    }
    return total;
}

// 把 [l, r] 整体加 delta：差分序列上只需改 d[l] 和 d[r+1] 两个位置
void range_add(ll l, ll r, ll delta) {
    bit_add(bit1, l, delta);
    bit_add(bit2, l, delta * l);
    if (r < n) { // r = n 时 d[n+1] 落在序列之外，不记录
        bit_add(bit1, r + 1, -delta);
        bit_add(bit2, r + 1, -delta * (r + 1));
    }
}

// Σ_{i≤x} A[i] = (x+1)·Σ d[j] - Σ j·d[j]
ll prefix_sum(ll x) {
    return (x + 1) * bit_sum(bit1, x) - bit_sum(bit2, x);
}

int main() {
    std::string line;
    // 第一行：n m（跳过空行）
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        if (iss >> n >> m) {
            break;
        }
    }

    // 数列可能被折成多行，读满 n 个数为止
    std::vector<ll> values;
    while ((ll)values.size() < n && std::getline(std::cin, line)) {
        std::istringstream iss(line);
        ll v;
        while (iss >> v) {
            values.push_back(v);
        }
    }

    ll prev = 0; // 前一个数，用来就地算差分 d[i] = A[i] - A[i-1]
    for (ll i = 1; i <= n; i++) {
        ll diff = values[i - 1] - prev;
        prev = values[i - 1];
        bit_add(bit1, i, diff);
        bit_add(bit2, i, diff * i);
    }

    std::vector<std::string> out;
    for (ll q = 0; q < m; q++) {
        if (!std::getline(std::cin, line)) {
            break;
        }
        std::istringstream iss(line);
        std::string op;
        ll parts[8];
        ll cnt = 0;
        if (!(iss >> op)) {
            q--; // 空行不算一条指令
            continue;
        }
        while (cnt < 8 && iss >> parts[cnt]) {
            cnt++;
        }
        ll left = parts[0];
        if (op == "C") {
            ll right = parts[1], delta = parts[2];
            range_add(left, right, delta);
        } else { // 单点询问少一个操作数，取 right = left
            ll right = (cnt > 1) ? parts[1] : left;
            std::ostringstream oss;
            oss << (prefix_sum(right) - prefix_sum(left - 1));
            out.push_back(oss.str());
        }
    }

    for (size_t i = 0; i < out.size(); i++) {
        printf("%s\n", out[i].c_str());
    }
    return 0;
}
