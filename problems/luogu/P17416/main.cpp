/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-27 11:30
 */
// main.cpp：P17416 正解。
//
// 思路：把 a 从小到大排序，枚举“子序列里的最大值” a[i]，
//       其余 k-1 个数只能从它前面（a[0..i-1]）里选。
//       固定最大值 m = a[i] 后，要让 sum(value xor m) 最大，
//       就是要求前面这些数里「前 k-1 大的 (value xor m) 之和」。
//
// 结构：01 Trie（按二进制位建的 Trie），可以理解成把上面的字典树模板
//       从「26 个小写字母」换成「0/1 两个二进制位」：
//       - ch[26]  -> ch[2]，每个节点只有 0/1 两个儿子；
//       - pass    不变，表示「落在这个节点子树里的已插入元素个数」；
//       - end     本题所有数长度一样（都是 31 位），叶子上的 pass
//                 就是相同数值的重复个数，相当于 end，所以不用另存。
//       另外因为要用「整棵子树一起取走」来加速，节点还需要记录它
//       对应的排序区间 [left, right)，见下面 Node 的注释。
//
// 查询：从高位往低位贪心。当前位希望异或出来是 1，所以优先走与 m
//       当前位相反的分支；这一支不够取就整支拿走，再从另一支补。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;   // n 的上界
const int MAX_BIT = 30;    // a_i <= 1e9 < 2^30，二进制第 0..30 位
const int DIGIT = 2;       // 01 Trie：每个节点只有 0 和 1 两个分支

int n, k;
int a[MAXN];               // 排序后的输入序列

// bit_one[b][i] = 排序后前 i 个数（a[0..i-1]）里，二进制第 b 位为 1 的个数。
// 有了它，就能 O(1) 算出一段连续下标区间中第 b 位为 1 的元素个数。
int bit_one[MAX_BIT + 1][MAXN];

// 01 Trie 的节点
struct Node {
    int ch[DIGIT]; // ch[c] 是第 c 位上的子节点编号，0 表示没有这个分支
    int pass;      // 落在这个节点子树里的已插入元素个数
    int left;      // 这个节点子树对应排序数组里的最左下标
    int right;     // 这个节点子树对应排序数组里的最右下标 + 1（即 [left, right)）
};

// 01 Trie：插入元素，以及查询前若干大的异或和
struct Trie {
    vector<Node> tree; // tree[0] 是根节点，节点编号 0 也表示空分支

    Trie() { tree.push_back(Node()); }

    // 新建一个节点，left 是它对应的排序下标，返回新节点编号
    int new_node(int left) {
        Node node;
        node.ch[0] = 0;
        node.ch[1] = 0;
        node.pass = 0;
        node.left = left;
        node.right = left + 1;
        tree.push_back(node);
        return (int)tree.size() - 1;
    }

    // 插入一个数 value，它是排序数组里第 rank 个（从 0 开始）。
    // 因为按 rank 递增的顺序插入，所以能顺便维护好每个子树的 [left, right)。
    void insert(int value, int rank) {
        int u = 0; // 从根出发
        tree[u].pass++;
        for (int bit = MAX_BIT; bit >= 0; bit--) {
            int c = (value >> bit) & 1; // 取出当前这一位
            if (tree[u].ch[c] == 0) {   // 没有这个分支就先建一个
                tree[u].ch[c] = new_node(rank);
            }
            u = tree[u].ch[c];
            tree[u].pass++;
            tree[u].right = rank + 1;   // 子树里目前的最大下标就是这个 rank
        }
    }

    // 求节点 u 的子树里，所有已插入元素与 x 异或之后的和。
    // highest_bit：这个子树里的元素与 x 异或后，不为 0 的最高位。
    long long xor_sum(int u, int x, int highest_bit) {
        long long result = 0;
        for (int bit = 0; bit <= highest_bit; bit++) {
            int ones = bit_one[bit][tree[u].right] - bit_one[bit][tree[u].left];
            int total = tree[u].right - tree[u].left;
            // x 这一位是 0：异或结果里这一位的 1，来自原本这一位是 1 的数；
            // x 这一位是 1：则来自原本这一位是 0 的数。
            int xor_ones = ((x >> bit) & 1) ? total - ones : ones;
            result += (long long)xor_ones * (1LL << bit);
        }
        return result;
    }

    // 在当前 Trie（只装了排序前缀里的元素）里，
    // 求最大的 need 个 (value xor x) 的和。
    // 调用前保证 need <= 节点 u 子树里的元素个数。
    // u 当前trie节点编号 , 当前的bit是第几层
    // x 表明 需要异或的那个M_b ,need 前need个最大的异或值
    long long top_k_xor_sum(int u, int bit, int x, int need) {
        if (need <= 0 || bit < 0) {
            return 0;
        }

        int x_bit = (x >> bit) & 1; // x 的当前位
        int prefer = x_bit ^ 1; //异时为1 这一位异或结果为 1 的分支，优先走
        int other = x_bit;
        int p = tree[u].ch[prefer];// 走perfer的孩子的编号
        int prefer_count = (p == 0) ? 0 : tree[p].pass; // 数量

        if (prefer_count >= need) {
            // 优先分支里就够 need 个，这一位全都能拿到 1
            return (long long)need * (1LL << bit)
                + top_k_xor_sum(p, bit - 1, x, need);
        }

        // 优先分支不够：整支取走，再去另一分支补剩下的
        long long result = 0;
        if (prefer_count > 0) {
            result += xor_sum(p, x, bit);
        }
        int q = tree[u].ch[other]; // 因为 need <= pass，这里 q 一定不为 0
        return result + top_k_xor_sum(q, bit - 1, x, need - prefer_count);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n); // 排序后，子序列元素就是连续的一段前缀里挑

    // 预处理每一位的前缀 1 的个数
    for (int bit = 0; bit <= MAX_BIT; bit++) {
        for (int i = 0; i < n; i++) {
            bit_one[bit][i + 1] = bit_one[bit][i] + ((a[i] >> bit) & 1);
        }
    }

    Trie trie;
    trie.tree.reserve((long long)n * (MAX_BIT + 1) + 5);

    long long answer = 0;
    for (int i = 0; i < n; i++) {
        // 用 a[i] 当最大值，其余 k-1 个数从 a[0..i-1] 里取
        if (i >= k - 1) {
            long long now = trie.top_k_xor_sum(0, MAX_BIT, a[i], k - 1);
            answer = max(answer, now);
        }
        // 查询完再插入 a[i]，保证自己不会选到自己
        trie.insert(a[i], i);
    }

    cout << answer << '\n';
    return 0;
}
