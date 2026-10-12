/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-12 15:09
 */
// main.cpp：按题面规则构造 FBI 树（动态化静态建结点），再后序遍历输出结点类型。
//
// 一段 01 串就对应一棵 FBI 子树：全 0 为 B，全 1 为 I，既有 0 又有 1 为 F；
// 串长大于 1 时从中间切成等长两半，递归建左右子树。
// 结点的类型、左儿子、右儿子聚合成 struct Node，node[u] 就是编号 u 的结点，
// 后序走一遍（左 -> 右 -> 根）就是答案。

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int maxn = 2050; // N ≤ 10，串长 2^10 = 1024，FBI 树共 2*1024-1 = 2047 个结点

struct Node {
    char type; // 结点类型：全 0 为 B，全 1 为 I，既有 0 又有 1 为 F
    int lch;   // 左儿子编号，叶子为 0
    int rch;   // 右儿子编号，叶子为 0
};

Node node[maxn]; // node[u]：编号 u 的结点（编号按建树顺序分配）
int node_cnt;    // 已分配的结点个数
string s;        // 输入的 01 串，子串 s[l..r-1] 就是一棵待建的子树

// 动态化静态开点：静态数组 + 分配指针 node_cnt，返回新结点的编号
int new_node(char type) {
    node_cnt++;
    node[node_cnt].type = type;
    node[node_cnt].lch = 0;
    node[node_cnt].rch = 0;
    return node_cnt;
}

// 判断子串 s[l..r-1] 的结点类型：全 0 为 B，全 1 为 I，否则为 F
char node_kind(int l, int r) {
    bool has0 = false, has1 = false;
    for (int i = l; i < r; i++) {
        if (s[i] == '0') {
            has0 = true;
        } else {
            has1 = true;
        }
        if (has0 && has1) {
            return 'F'; // 0 和 1 都出现了，不用再看后面
        }
    }
    if (has0) {
        return 'B';
    }
    return 'I';
}

// 递归构造子串 s[l..r-1] 对应的 FBI 子树，返回根编号
int build(int l, int r) {
    int u = new_node(node_kind(l, r)); // 根的类型由整段串决定
    if (r - l > 1) {                   // 串长为 1 时是叶子，不再往下分
        int mid = (l + r) / 2;         // 从中间切成等长的左右两半
        node[u].lch = build(l, mid);
        node[u].rch = build(mid, r);
    }
    return u;
}

// 后序遍历：左子树 -> 右子树 -> 根，依次输出结点类型
void postorder(int u) {
    if (u == 0) {
        return;
    }
    postorder(node[u].lch);
    postorder(node[u].rch);
    cout << node[u].type;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> s;
    int len = 1 << n; // 串长 2^N
    postorder(build(0, len));
    cout << '\n';
    return 0;
}
