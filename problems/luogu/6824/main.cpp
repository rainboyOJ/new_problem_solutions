/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* P6824 「EZEC-4」可乐 */
/* 思路（与 index.md 样例图的"贡献覆盖"一致）：在"x 的 01-Trie"上为每个 a_i
 * 打 +1 懒标记——k 位 = 1 时，异或位取 0 的整棵子树打标（严格小于，低位任取），
 * 深入异或位取 1 的分支；k 位 = 0 时只能深入异或位取 0 的分支；走到底的叶子 +1。
 * 最后 DFS 把标记下传，覆盖数最大的叶子就是最佳 x。
 * 01-Trie 复用 rbook 文章《Trie 字典树》模板的结构（tree/Node 为公开成员），
 * 打标与下传都写在模板外部。 */

#include <bits/stdc++.h>
using namespace std;

// 字典树 Trie 模板：插入字符串、判断是否存在、统计前缀出现次数
// 模板参数：ALPHA 字符集大小，OFFSET 字符起点（如 'a'）
// 节点维护 pass(经过次数) 和 end(单词结尾次数)
// 用法：Trie<26,'a'> tr; tr.insert("abc"); tr.contains("abc"); tr.count_prefix("ab");
template <int ALPHA = 26, char OFFSET = 'a'>
struct Trie {
    struct Node {
        array<int, ALPHA> ch{}; // ch[c] 子节点编号，0 为空（根也是 0）
        int pass = 0;           // 经过该节点的字符串个数
        int end = 0;            // 以该节点结尾的完整字符串个数
    };

    vector<Node> tree;          // tree[0] 为根

    Trie() { tree.push_back(Node()); }

    // 插入 s
    void insert(const string &s) {
        int u = 0;
        tree[u].pass++;
        for (char cc : s) {
            int c = cc - OFFSET;
            if (tree[u].ch[c] == 0) {       // 无子节点则新建
                tree[u].ch[c] = (int)tree.size();
                tree.push_back(Node());
            }
            u = tree[u].ch[c];
            tree[u].pass++;
        }
        tree[u].end++;
    }

    // 判断 s 是否完整插入过
    bool contains(const string &s) const {
        int u = 0;
        for (char cc : s) {
            int c = cc - OFFSET;
            if (tree[u].ch[c] == 0) return false;
            u = tree[u].ch[c];
        }
        return tree[u].end > 0;  // 必须作为完整单词结尾
    }

    // 统计以 prefix 为前缀的字符串个数
    int count_prefix(const string &prefix) const {
        int u = 0;
        for (char cc : prefix) {
            int c = cc - OFFSET;
            if (tree[u].ch[c] == 0) return 0;
            u = tree[u].ch[c];
        }
        return tree[u].pass;
    }
};

const int MAXN = 100000 + 5;

int n, k;                   // n 箱可乐，上限 k
int a[MAXN];
int top_bit;                // 最高有效位（k 与所有 a_i 的最大位数 - 1）

Trie<2, '0'> trie;          // x 的 01-Trie：每条根到叶子的路径就是一个可能的 x
vector<int> tag(1, 0);      // tag[u]：节点 u 的懒标记，与 trie.tree 下标对齐

// 确保 u 存在 c 儿子；不存在则新建节点并返回其编号。
// 注意：被打标记的分支即使没有 a_i 走过也要显式建出来，
// 否则 DFS 下传会漏掉只靠祖先标记覆盖的隐式叶子。
int ensure_child(int u, int c) {
    if (trie.tree[u].ch[c] == 0) {
        trie.tree[u].ch[c] = (int)trie.tree.size();
        trie.tree.push_back(Trie<2, '0'>::Node());
        tag.push_back(0);
    }
    return trie.tree[u].ch[c];
}

// 为 a_i 打标记：把能接受 a_i 的所有 x 在 x-Trie 上打 +1
void mark(int x) {
    int u = 0;
    for (int bit = top_bit; bit >= 0; bit--) {
        int ab = (x >> bit) & 1; // a_i 的第 bit 位
        if ((k >> bit) & 1) {
            // k 位 = 1（分水岭）：异或位取 0 的分支（x 位 = ab）整棵严格小于 k → +1
            tag[ensure_child(u, ab)] += 1;
            // 异或位取 1 的分支（x 位 = ab^1）等于 k → 继续深入
            u = ensure_child(u, ab ^ 1);
        } else {
            // k 位 = 0（关卡）：异或位只能取 0（x 位 = ab），只能深入
            u = ensure_child(u, ab);
        }
    }
    tag[u] += 1; // 走到底：异或结果恰好等于 k 的 x 打 +1
}

int best = 0;

// DFS 下传：acc = 从根到 u 的标记累计（每个隐式叶子继承祖先标记）。
// 标记只会增加，所以任意节点 u 的 acc 都是其子树内叶子的覆盖数下界，
// 全局最大 acc 就是最大覆盖数。
void push_down(int u, int acc) {
    acc += tag[u];
    best = max(best, acc);
    if (trie.tree[u].ch[0])
        push_down(trie.tree[u].ch[0], acc);
    if (trie.tree[u].ch[1])
        push_down(trie.tree[u].ch[1], acc);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int m = max(k, *max_element(a + 1, a + n + 1));
    top_bit = 31 - __builtin_clz(m); // m >= 1，最高有效位 = floor(log2(m))

    for (int i = 1; i <= n; i++)
        mark(a[i]);

    push_down(0, 0);
    cout << best << '\n';
    return 0;
}
