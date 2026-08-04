/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 21:58
 * update_at: 2026-08-04 21:58
 */
// P5283 [十二省联考 2019] 异或粽子
// 基于可持久化 01-Trie + 大根堆多路归并
// struct Node 用 size 取代 time_id，直接维护子树元素个数
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_OP = 500005;
// 值 ≤ 2^32-1，需要 32 位二进制（第 0..31 位）
const int MAX_DEP = 31;
// 每次插入新建 MAX_DEP+2 个节点（1 个根 + MAX_DEP+1 个路径节点）
const int MAX_NODES = MAX_OP * (MAX_DEP + 2);

int n, k;
ll a[MAX_OP];
ll s[MAX_OP]; // 前缀异或和

struct Node {
    int ch[2];
    // size: 经过该节点的元素个数（以该节点路径为前缀的数字数量）
    //       即子树中的元素个数，叶子节点的 size 是该具体值的出现次数
    int size; // 🌟 改造点 1：取代 time_id，维护经过该节点的元素个数
};

int tot;
Node node[MAX_NODES];
int root[MAX_OP];

auto get_node = [](){ return ++tot; };
auto bit_n = [](ll x, int i) { return (x >> i) & 1; };

// val: 插入的值
// pre: 上一个版本的节点
// cur: 当前的新节点
void insert(ll val, int pre, int cur) {
    // 根节点元素个数 = 旧版本根节点个数 + 1
    node[cur].size = node[pre].size + 1;

    for(int i = MAX_DEP; i >= 0; --i) {
        int bit = bit_n(val, i);
        
        // 复制不需要改变的分支
        node[cur].ch[bit ^ 1] = node[pre].ch[bit ^ 1]; 
        // 创建新分支
        node[cur].ch[bit] = get_node();

        // 指针向下移动
        cur = node[cur].ch[bit];
        pre = node[pre].ch[bit];

        // 🌟 核心维护：沿途所有经过的新节点，size 都比旧版本多 1
        node[cur].size = node[pre].size + 1;
    }
}

// 🌟 改造点 2：在版本 cur 中，查找与 val 异或后第 rank 大的值
ll query(int cur, ll val, int rank) {
    ll ans = 0;
    for(int i = MAX_DEP; i >= 0; i--) {
        int bit = bit_n(val, i);
        int expected = bit ^ 1;

        int next_node = node[cur].ch[expected];
        int expected_size = node[next_node].size;

        // 检查期望走的分支，里面包含的数字个数是否足够支撑第 rank 大
        if(expected_size >= rank) {
            // 够用！第 rank 大的数一定在这个分支里，直接走
            ans |= (1LL << i);
            cur = next_node;
        } else {
            // 不够用！被迫去另一个较差的分支
            // 同时，排在前面的 expected_size 个较大值已经被跳过，需要从 rank 中扣除
            rank -= expected_size;
            cur = node[cur].ch[bit];
        }
    }
    return ans;
}

// 定义大根堆中的元素状态
struct Element {
    ll val;     // 异或和的值
    int r;      // 右端点下标
    int rank;   // 当前是 r 这个右端点的第几大组合
    
    bool operator<(const Element& other) const {
        return val < other.val; // 大根堆，按 val 降序
    }
};

void init(){
    std::cin >> n >> k;
    
    // 初始化 s[0] 的历史版本
    root[0] = get_node();
    insert(0, 0, root[0]);
    
    for(int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        s[i] = s[i-1] ^ a[i];
        
        root[i] = get_node();
        insert(s[i], root[i-1], root[i]);
    }
}

signed main () {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    
    init();

    priority_queue<Element> pq;

    // 🌟 改造点 3：多路归并初始化
    // 将每个右端点 r，去与其对应的历史版本 root[r-1] 组合
    // 找出每个右端点的最大异或值（rank = 1），放入大根堆
    for(int i = 1; i <= n; ++i) {
        ll max_val = query(root[i-1], s[i], 1);
        pq.push({max_val, i, 1});
    }

    ll total_ans = 0;

    // 贪心提取前 k 大
    while(k--) {
        Element top = pq.top();
        pq.pop();

        total_ans += top.val;

        // root[r-1] 中一共插入了 0 到 r-1 也就是 r 个前缀和
        // 如果当前右端点还有次大的组合（rank < r），就查出来塞回堆里
        if(top.rank < top.r) {
            ll next_val = query(root[top.r - 1], s[top.r], top.rank + 1);
            pq.push({next_val, top.r, top.rank + 1});
        }
    }

    std::cout << total_ans << "\n";
    
    return 0;
}