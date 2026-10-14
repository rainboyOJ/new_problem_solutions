/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-14 23:06
 * update_at: 2026-10-15 00:05
 */
// special_b.cpp：仅适用于特殊性质 B：每个字符串恰好有一个 b，其余全为 a。
// 按 b 的位移分组，二维偏序用排序扫描和树状数组计数。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Event {
    ll delta; // b 的位移：目标位置 - 原位置
    ll left;  // 规则中 b 左侧的 a 数，或询问允许的上界
    ll right; // 规则中 b 右侧的 a 数，或询问允许的上界
    ll id;    // 0 表示规则，正数表示询问编号
};

ll n, q;
vector<Event> events;    // 规则事件 + 询问事件，按 delta 分组扫描
vector<ll> coordinates;  // 所有规则的 right，用于离散化
vector<ll> bit, answer;  // bit 是树状数组；answer[id] 是第 id 个询问的答案

// 事件排序：先按 delta 分组，组内按 left 升序，left 相同时规则排在询问前面，
// 从而保证统计的是 left_rule <= left_query。
bool cmp_event(const Event &a, const Event &b) {
    if (a.delta != b.delta) return a.delta < b.delta;
    if (a.left != b.left) return a.left < b.left;
    return a.id < b.id; // left 相等时先加入规则，保证统计的是 <=
}

// 性质 B 保证每个串恰好有一个 'b'，返回它的下标；找不到返回 -1
ll find_b(const string &s) {
    ll len = s.size();
    for (ll i = 0; i < len; i++) {
        if (s[i] == 'b') return i;
    }
    return -1;
}

// 树状数组：按离散化后的 right 值单点加、前缀查
void bit_add(ll pos, ll value) {
    ll size = coordinates.size();
    for (; pos <= size; pos += pos & -pos) bit[pos] += value;
}

ll bit_query(ll pos) {
    ll result = 0;
    for (; pos > 0; pos -= pos & -pos) result += bit[pos];
    return result;
}

// 把规则事件的 right 离散化后计入树状数组；value=1 加入，value=-1 撤销
void add_rule(const Event &event, ll value) {
    ll pos = lower_bound(coordinates.begin(), coordinates.end(), event.right)
             - coordinates.begin() + 1;
    bit_add(pos, value);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    // 规则：记录 b 的位移 delta、左侧 a 数 left、右侧 a 数 right
    for (ll i = 1; i <= n; i++) {
        string a, b;
        cin >> a >> b;
        ll x = find_b(a), y = find_b(b);
        if (x == y) continue; // 不改变字符串的规则不能回答 t1 != t2
        ll len = a.size();
        Event event;
        event.delta = y - x;
        event.left = x;
        event.right = len - 1 - x;
        event.id = 0;
        events.push_back(event);
        coordinates.push_back(event.right);
    }

    answer.assign(q + 1, 0);
    // 询问：把询问也转成同构事件，左、右均以 t1 中 b 的位置为准
    for (ll i = 1; i <= q; i++) {
        string a, b;
        cin >> a >> b;
        if (a.size() != b.size()) continue;
        ll p = find_b(a), r = find_b(b);
        if (p == r) continue;
        ll len = a.size();
        Event event;
        event.delta = r - p;
        event.left = p;
        event.right = len - 1 - p;
        event.id = i;
        events.push_back(event);
    }

    sort(coordinates.begin(), coordinates.end());
    coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());
    bit.assign(coordinates.size() + 1, 0);
    sort(events.begin(), events.end(), cmp_event);

    // 按 delta 分组处理：组内二维偏序，处理完一组就撤销，避免不同 delta 互相干扰
    ll size = events.size();
    for (ll begin = 0; begin < size; ) {
        ll end = begin;
        while (end < size && events[end].delta == events[begin].delta) end++;

        for (ll i = begin; i < end; i++) {
            if (events[i].id == 0) {
                add_rule(events[i], 1);
            } else {
                // 查询统计 right_rule <= right_query 的规则数
                ll pos = upper_bound(coordinates.begin(), coordinates.end(), events[i].right)
                         - coordinates.begin();
                answer[events[i].id] = bit_query(pos);
            }
        }
        // 撤销本组规则，避免不同 delta 之间相互贡献。
        for (ll i = begin; i < end; i++) {
            if (events[i].id == 0) add_rule(events[i], -1);
        }
        begin = end;
    }

    for (ll i = 1; i <= q; i++) cout << answer[i] << '\n';
    return 0;
}
