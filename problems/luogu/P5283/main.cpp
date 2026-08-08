/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 21:58
 * update_at: 2026-08-04 21:58
 */
// main.cpp：全局 01-Trie 解法，struct Node + get_node 风格
// 核心转化：无序对翻倍 → 在全局 Trie 上求前 2k 大有序对，最后除以 2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_OP = 500005;
// 值 ≤ 2^32-1，需要 32 位二进制（第 0..31 位）
const int MAX_DEP = 31;
const int MAX_NODES = MAX_OP * (MAX_DEP + 2);

int n;
ll k;
ll S[MAX_OP]; // 前缀异或和 S[0..n]

// 全局 01-Trie 节点
// size: 经过该节点的元素个数（以该节点路径为前缀的数字数量）
//       即子树中的元素个数，叶子节点的 size 是该具体值的出现次数
//       第 rank 大查询用 size 判断期望分支里有多少个数字
struct Node {
    int ch[2];
    int size;
};

int tot;
Node node[MAX_NODES];

auto get_node = [](){ return ++tot; };
auto bit_n = [](ll x, int i) { return (x >> i) & 1; };

// val: 插入的值
void insert(ll val) {
    int cur = 1; // 根节点（节点 1）
    node[cur].size++; // 根节点也被这个值经过，计数 +1

    for(int i = MAX_DEP; i >= 0; --i) {
        int bit = bit_n(val, i);

        // 全局 Trie：不存在的分支才新建节点
        if(node[cur].ch[bit] == 0) {
            node[cur].ch[bit] = get_node();
        }

        cur = node[cur].ch[bit];
        node[cur].size++; // 沿途每个经过的节点计数 +1
    }
}

// 在全局 Trie 中查询 val 的第 rank 大异或值
ll query(int cur, ll val, int rank) {
    ll ans = 0;
    for(int i = MAX_DEP; i >= 0; i--) {
        int bit = bit_n(val, i);
        int expected = bit ^ 1;

        int next_node = node[cur].ch[expected];
        int expected_size = node[next_node].size;

        // 期望走的分支，里面包含的数字个数是否足够支撑第 rank 大
        if(expected_size >= rank) {
            ans |= (1LL << i);
            cur = next_node;
        } else {
            // 不够用，被迫走同位分支，同时从 rank 中扣除跳过的大值个数
            rank -= expected_size;
            cur = node[cur].ch[bit];
        }
    }
    return ans;
}

// 大根堆中的元素状态
struct Element {
    ll val;   // 异或值
    int i;    // 下标
    int rank; // 当前是下标 i 的第几大组合

    bool operator<(const Element& other) const {
        return val < other.val; // 大根堆，按 val 降序
    }
};

void init(){
    std::cin >> n >> k;
    S[0] = 0;

    for(int i = 1; i <= n; ++i) {
        ll a;
        std::cin >> a;
        S[i] = S[i-1] ^ a;
    }

    // 建立全局 Trie，插入所有 S[0..n]
    get_node(); // 创建根节点（节点 1）
    for(int i = 0; i <= n; ++i) {
        insert(S[i]);
    }
}

signed main () {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();

    // 无序转有序：求前 2k 大有序对，最后除以 2
    // 将每个下标的第 1 大异或值放入大根堆
    priority_queue<Element> pq;
    for(int i = 0; i <= n; ++i) {
        ll max_val = query(1, S[i], 1);
        pq.push({max_val, i, 1});
    }

    ll total_ans = 0;
    ll remaining = 2LL * k;

    // 贪心提取前 2k 大
    while(remaining > 0 && !pq.empty()) {
        Element top = pq.top();
        pq.pop();

        total_ans += top.val;
        remaining--;

        // 每个下标最多与其他 n 个值配对（排除自身 S[i]^S[i]=0）
        if(top.rank < n) {
            ll next_val = query(1, S[top.i], top.rank + 1);
            pq.push({next_val, top.i, top.rank + 1});
        }
    }

    std::cout << total_ans / 2 << "\n";

    return 0;
}