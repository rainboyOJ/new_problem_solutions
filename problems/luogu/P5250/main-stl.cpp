/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 01:22
 * update_at: 2026-10-07 01:33
 */
// 这是 STL 写法：用 set<ll> 的成员 lower_bound 找第一个不小于需求长度的木材，
// 再把它和它的前一个位置比较，取出距离更近的一根（并列取较短的前驱）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

set<ll> stock; // 仓库中现存的所有木材长度；set 自动去重并按长度升序保存

// 进货：仓库里已经有这个长度就报告 Already Exist，否则插入。
void add(ll len) {
    if (stock.count(len) > 0) {
        cout << "Already Exist" << '\n';
        return;
    }
    stock.insert(len);
}

// 出货：取出一根最接近需求长度 len 的木材，返回取出的长度。
// len 本身存在就取它；否则比较它的前驱和后继，距离相同取较短的前驱。
ll take(ll len) {
    auto it = stock.lower_bound(len); // 第一个不小于 len 的位置

    if (it != stock.end() && *it == len) { // 刚好有这个长度
        ll chosen = *it;
        stock.erase(it);
        return chosen;
    }

    // 此时 len 不在仓库里：it 指向后继（可能不存在），it 的前一个位置指向前驱（可能不存在）
    bool has_right = (it != stock.end());
    bool has_left = (it != stock.begin());

    if (!has_left) { // 没有比 len 短的木材，只能取后继
        ll chosen = *it;
        stock.erase(it);
        return chosen;
    }

    auto left_it = it;
    --left_it; // 前驱位置
    ll left_len = *left_it;

    if (!has_right) { // 没有比 len 长的木材，只能取前驱
        stock.erase(left_it);
        return left_len;
    }

    ll right_len = *it;
    // 距离相同时取较短的一根，也就是前驱
    if (len - left_len <= right_len - len) {
        stock.erase(left_it);
        return left_len;
    }
    stock.erase(it);
    return right_len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll q;
    cin >> q;
    while (q--) {
        ll op, len;
        cin >> op >> len;
        if (op == 1) {
            add(len);
        } else {
            if (stock.empty()) {
                cout << "Empty" << '\n';
                continue;
            }
            cout << take(len) << '\n';
        }
    }

    return 0;
}
