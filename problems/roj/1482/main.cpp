/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:45
 * update_at: 2026-10-05 03:45
 */
// AC 自动机 + fail 树子树聚合统计多模式串出现次数。
#include <cstdio>
#include <cstring>
#include <string>

typedef long long ll;

const int MAXNODE = 1000005; // 节点数不超过所有单词长度和 + 1
const int SIGMA = 26;

int ch[MAXNODE][SIGMA]; // Trie 转移：ch[u][c] = 节点 u 沿字符 c 的儿子
int fail[MAXNODE];      // fail 指针，构成以根为祖先的 fail 树
ll cnt[MAXNODE];        // cnt[u] = 所有模式串的前缀经过节点 u 的次数（后为子树聚合值）
int pos[205];           // pos[i] = 第 i 个单词在 Trie 上对应的终止节点
int order[MAXNODE];     // BFS 出队顺序，天然是 fail 树的拓扑序（父先于子）
int total_node = 1;     // 节点总数，0 号为根，1 号预留给第一个新建节点

// 把所有单词插进 Trie，并在每个经过的节点上累计前缀覆盖次数
void insert_word(const std::string &s, int idx) {
    int u = 0;
    for (unsigned int i = 0; i < s.size(); ++i) {
        int c = s[i] - 'a';
        if (ch[u][c] == 0) {
            ch[u][c] = total_node++;
        }
        u = ch[u][c];
        cnt[u]++; // 这个前缀被该模式串经过了一次
    }
    pos[idx] = u;
}

// BFS 建 fail 指针，同时记录出队顺序
void build_fail() {
    static int q[MAXNODE];
    int head = 0, tail = 0;
    for (int c = 0; c < SIGMA; ++c) {
        if (ch[0][c] != 0) {
            fail[ch[0][c]] = 0;
            q[tail++] = ch[0][c];
        }
    }
    while (head < tail) {
        int u = q[head++];
        order[head - 1] = u; // 出队顺序即拓扑序
        for (int c = 0; c < SIGMA; ++c) {
            int v = ch[u][c];
            if (v != 0) {
                fail[v] = ch[fail[u]][c];
                q[tail++] = v;
            } else {
                ch[u][c] = ch[fail[u]][c]; // 路径压缩成转移自动机
            }
        }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) {
        static char word[2000005]; // 单个单词最长可达总长度 10^6，用静态区避免爆栈
        scanf("%s", word);
        insert_word(word, i);
    }
    build_fail();

    // 按拓扑序的逆序（深度大到深度小）自底向上聚合 fail 树子树权值：
    // 节点 u 的所有出现都会贡献给它的后缀 fail[u]
    for (int i = total_node - 2; i >= 0; --i) {
        int u = order[i];
        cnt[fail[u]] += cnt[u];
    }

    for (int i = 0; i < n; ++i) {
        printf("%lld\n", cnt[pos[i]]);
    }
    return 0;
}
