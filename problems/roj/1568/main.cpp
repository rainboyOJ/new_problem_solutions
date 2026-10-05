/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:58
 * update_at: 2026-10-05 08:58
 */
// main.cpp：普通平衡树，用分块有序表实现（对应题解的主算法）。
// 结构约定：blocks 中每个子列表内部非降序，块间整体有序，
// 即前一块的最大值 <= 后一块的最小值。
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

typedef long long ll;

vector<vector<ll> > blocks; // blocks[i] 为一个有序块，块内非降序
ll block_size;              // 基准块大小 B，单块超过 2B 时整体重构

// 把所有块展平后按 block_size 重新均匀划分，用于插入膨胀后的平衡。
void rebuild_blocks() {
    vector<ll> flat;
    for (int i = 0; i < (int)blocks.size(); i++) {
        for (int j = 0; j < (int)blocks[i].size(); j++) {
            flat.push_back(blocks[i][j]);
        }
    }
    blocks.clear();
    for (int i = 0; i < (int)flat.size(); i += block_size) {
        vector<ll> part;
        for (int j = i; j < (int)flat.size() && j < i + block_size; j++) {
            part.push_back(flat[j]);
        }
        blocks.push_back(part);
    }
}

// 插入 val：找到第一个尾元素 >= val 的块插入，找不到就插入最后一块。
void insert_val(ll val) {
    if (blocks.empty()) {
        vector<ll> part;
        part.push_back(val);
        blocks.push_back(part);
        return;
    }
    for (int i = 0; i < (int)blocks.size(); i++) {
        vector<ll> &b = blocks[i];
        if (b.empty()) {
            continue;
        }
        if (val <= b[b.size() - 1]) {
            vector<ll>::iterator pos = lower_bound(b.begin(), b.end(), val);
            b.insert(pos, val);
            if ((ll)b.size() > 2 * block_size) {
                rebuild_blocks();
            }
            return;
        }
    }
    // 所有块的尾元素都小于 val，直接放入最后一块
    vector<ll> &last = blocks[blocks.size() - 1];
    vector<ll>::iterator pos = lower_bound(last.begin(), last.end(), val);
    last.insert(pos, val);
    if ((ll)last.size() > 2 * block_size) {
        rebuild_blocks();
    }
}

// 删除一个 val：定位到可能含 val 的块，二分找到后删除一个。
void remove_val(ll val) {
    for (int i = 0; i < (int)blocks.size(); i++) {
        vector<ll> &b = blocks[i];
        if (b.empty()) {
            continue;
        }
        if (val <= b[b.size() - 1]) {
            vector<ll>::iterator pos = lower_bound(b.begin(), b.end(), val);
            if (pos != b.end() && *pos == val) {
                b.erase(pos);
            }
            return;
        }
    }
}

// 查询 val 的排名：严格小于 val 的个数 + 1。
ll query_rank(ll val) {
    ll smaller = 0;
    for (int i = 0; i < (int)blocks.size(); i++) {
        vector<ll> &b = blocks[i];
        if (b.empty()) {
            continue;
        }
        if (b[b.size() - 1] < val) {
            smaller += (ll)b.size(); // 整块都比 val 小
        } else {
            smaller += lower_bound(b.begin(), b.end(), val) - b.begin();
            break; // 后面的块只会更大，无需继续统计
        }
    }
    return smaller + 1;
}

// 查询第 k 小（k 从 1 开始）的数。
ll query_kth(ll k) {
    ll cur = k;
    for (int i = 0; i < (int)blocks.size(); i++) {
        vector<ll> &b = blocks[i];
        if (cur <= (ll)b.size()) {
            return b[cur - 1];
        }
        cur -= (ll)b.size();
    }
    return -1;
}

// 查询前趋：小于 val 且最大的数。
ll query_prev(ll val) {
    int found = 0;
    ll ans = 0;
    for (int i = 0; i < (int)blocks.size(); i++) {
        vector<ll> &b = blocks[i];
        if (b.empty()) {
            continue;
        }
        if (b[0] >= val) {
            break; // 该块及之后所有元素都 >= val
        }
        if (b[b.size() - 1] < val) {
            ans = b[b.size() - 1]; // 整块都是候选，取块内最大
            found = 1;
        } else {
            vector<ll>::iterator pos = lower_bound(b.begin(), b.end(), val);
            if (pos != b.begin()) {
                ans = *(pos - 1);
                found = 1;
            }
            break;
        }
    }
    if (!found) {
        return -1; // 题目保证前驱存在，这里只作兜底
    }
    return ans;
}

// 查询后继：大于 val 且最小的数。
ll query_next_val(ll val) {
    for (int i = 0; i < (int)blocks.size(); i++) {
        vector<ll> &b = blocks[i];
        if (b.empty()) {
            continue;
        }
        if (b[b.size() - 1] <= val) {
            continue; // 整块都 <= val，不是后继
        }
        vector<ll>::iterator pos = upper_bound(b.begin(), b.end(), val);
        if (pos != b.end()) {
            return *pos;
        }
    }
    return -1; // 题目保证后继存在，这里只作兜底
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    if (!(cin >> n)) {
        return 0;
    }
    block_size = 2 * (ll)sqrt((double)n) + 10; // 取 B ≈ 2√n，兼顾块内与块间代价

    for (ll i = 0; i < n; i++) {
        ll opt;
        ll x;
        cin >> opt >> x;
        if (opt == 1) {
            insert_val(x);
        } else if (opt == 2) {
            remove_val(x);
        } else if (opt == 3) {
            cout << query_rank(x) << '\n';
        } else if (opt == 4) {
            cout << query_kth(x) << '\n';
        } else if (opt == 5) {
            cout << query_prev(x) << '\n';
        } else if (opt == 6) {
            cout << query_next_val(x) << '\n';
        }
    }
    return 0;
}
