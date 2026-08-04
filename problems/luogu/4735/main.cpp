/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-08-04 16:43:42
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

// N, M ≤ 3×10^5，插入总次数 = 1(s[0]) + N + #A ≤ 600001
const int MAX_OP = 600005;
// 值 ≤ 10^7 < 2^24，只需要 24 位二进制（第 0..23 位）
const int MAX_DEP = 23;
// 每次插入新建 MAX_DEP+2 个节点（1 个根 + MAX_DEP+1 个路径节点）
const int MAX_NODES = MAX_OP * (MAX_DEP + 2);

int n,m;
int a[MAX_OP];
int s[MAX_OP]; // 前缀异或和

void init(){
    std::cin >> n >> m;
    for( int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        s[i] = s[i-1] ^ a[i];
    }
}


struct Node {
    int ch[2];
    int time_id;
};

int tot;
Node node[MAX_NODES];
int root[MAX_OP];

auto get_node = [](){ return ++tot; };
auto bit_n = [](int x,int i) { return ( x >> i) & 1;};

// idx  当前节点的时间戳
// val  值 
// pre 上一个版本的节点
// cur 当前的节点  
void insert(int idx,int val,int pre,int cur) {
    // 根节点必然包含当前插入的新元素(值),更新时间戳
    // n位的二进制需要创建n+1个节点
    node[cur].time_id = idx;

    for(int i = MAX_DEP ; i >= 0; --i) {

        int bit = (val >> i) &1;
        node[cur].ch[bit^1] = node[pre].ch[bit^1]; 

        node[cur].ch[bit] = get_node();

        // 指针同样向下移动一层
        cur = node[cur].ch[bit];
        pre = node[pre].ch[bit];

        // 更新新节点时间戳
        node[cur].time_id = idx;

    }
}

// 在版本cur 中查找 val 最大异或的值,且节点的time_id >= limit_l
int query(int cur,int val,int limit_l) {
    int ans = 0;
    for(int i = MAX_DEP; i >=0;i--){
        int bit = bit_n(val, i);
        int expected = bit ^ 1;

        // 🌟 核心判断：期望走的分支存在，并且该分支内包含至少一个下标 >= limit_L 的元素吗？
        // 如果 max_id < limit_L，说明这个分支里的所有数字都太老了，不在我们查询的区间内，视为死路！
        int next = node[cur].ch[expected];
        if( node[next].time_id >= limit_l) {
            ans |= (1<<i);
            cur = node[cur].ch[expected];
        }
        else {
            cur = node[cur].ch[bit];
        }
    }
    return ans;
}



signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    // 0 表示NULL节点,是一个黑洞,表示不存在
    node[0].time_id = -1;

    // 创建 s[0] = 0 的trie
    // 为什么： 
    root[0] = get_node();
    insert(0,0,0,root[0]);


    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        root[i] = get_node();
        insert(i,s[i],root[i-1],root[i]);
    }

    while(m--) {
        char op;
        cin >> op;

        if( op == 'A') {
            // A x：往序列末尾加一个数 x
            // 💡 本质就是再插入一个新版本，和初始插入完全一样，没有特殊处理！
            // 这就是可持久化的好处：新版本不影响旧版本，随时可以回溯
            int x;
            cin >> x;
            ++n;
            s[n] = s[n-1] ^ x;
            root[n] = get_node();
            insert(n,s[n],root[n-1],root[n]);
        }
        else {
            // Q l r x：找到 p ∈ [l, r]，最大化 a[p]^...^a[N]^x
            int l,r,x;
            std::cin >> l >> r >> x;

            // 🌟 本题精髓：两步转化
            // ① 后缀转前缀：a[p]^...^a[N] = s[N]^s[p-1]
            //    所以原式 = (s[N]^x) ^ s[p-1]，问题变成：
            //    在 s[l-1 .. r-1] 中找一个数与 (s[N]^x) 异或最大
            // ② 区间转版本+限制：版本 root[r-1] 里恰好存着 s[0..r-1]，
            // ① 求最大值：a[p]^...^a[N] ^x  = s[N]^s[p-1] ^x 的最大值
            // s[p-1] ^ s[n] ^x, s[n] ^ x 是定值，问题变成找
            // s[p-1] 让 s[p-1] ^ (s[n] ^x)最大
            // p ∈ [l, r] -> p-1 ∈ [l-1, r-1] -> 找版本 r-1 中的数,但是时间戳 >= l-1
            // 每一次都贪心的走 与x相反的位,同时检查时间戳
            int ans = query(root[r-1], s[n]^x, l-1);
            std::cout << ans << "\n";


        }
    }
    
    return 0;
}
