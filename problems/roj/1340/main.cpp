/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-12 14:55
 */
// main.cpp：扩展二叉树还原：顺序消费扩展先序序列递归建树，再输出中序与后序。
//
// 扩展先序序列满足「根 + 左子树 + 右子树」的递归结构，从左到右消费字符即可建树：
// 遇大写字母就开一个结点并递归构造左右子树，遇空结点标记就返回空子树。
// 结点的字母、左儿子、右儿子聚合成 struct Node，node[u] 就是编号 u 的结点。

#include <cstdio>

typedef long long ll;

const int maxn = 1 << 20; // 序列长度不超过 1M，结点数不会超过序列长度

struct Node {
    char label; // 结点上的大写字母
    int lch;    // 左儿子编号，0 表示空子树
    int rch;    // 右儿子编号，0 表示空子树
};

Node node[maxn]; // node[u]：编号 u 的结点
char buf[maxn];  // 读入的扩展先序序列
int node_cnt;    // 已建立的结点个数，新结点的编号就是它加一
int scan_pos;    // 当前扫描到序列的下标

// 取序列中下一个有效字符：跳过空白
// 多字节符号（题面插图里的空结点 `·`）整体算一个字符，避免它的 UTF-8 续字节被当成多个空结点
char next_char() {
    while (buf[scan_pos] == ' ' || buf[scan_pos] == '\n' || buf[scan_pos] == '\r' || buf[scan_pos] == '\t') {
        ++scan_pos;
    }
    char ch = buf[scan_pos];
    if (ch == '\0') return ch;
    ++scan_pos;
    if ((ch & 0x80) != 0) { // 非 ASCII 是多字节符号的首字节
        while ((buf[scan_pos] & 0xC0) == 0x80) ++scan_pos; // 跳过它剩下的续字节
        return '.';                                        // 统一按空结点返回
    }
    return ch;
}

// 按扩展先序序列递归建树，返回子树的根编号（0 表示空子树）
int build_tree() {
    char ch = next_char();
    if (ch == '\0') return 0;           // 序列已耗尽，按空子树处理
    if (ch < 'A' || ch > 'Z') return 0; // 非大写字母的符号表示空结点

    node_cnt++;
    int root = node_cnt;
    node[root].label = ch;
    node[root].lch = build_tree(); // 消费掉紧接着的一段，那是左子树
    node[root].rch = build_tree(); // 再往后一段是右子树
    return root;
}

// 中序遍历：左 — 根 — 右
void print_inorder(int u) {
    if (u == 0) return;
    print_inorder(node[u].lch);
    std::putchar(node[u].label);
    print_inorder(node[u].rch);
}

// 后序遍历：左 — 右 — 根
void print_postorder(int u) {
    if (u == 0) return;
    print_postorder(node[u].lch);
    print_postorder(node[u].rch);
    std::putchar(node[u].label);
}

int main() {
    if (std::fgets(buf, sizeof buf, stdin) == NULL) return 0; // 输入只有一行

    node_cnt = 0;
    scan_pos = 0;
    int root = build_tree();

    print_inorder(root);
    std::putchar('\n');
    print_postorder(root);
    std::putchar('\n');
    return 0;
}
