/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:45
 * update_at: 2026-10-05 03:45
 */
// roj 1481 Censoring：AC 自动机 + 栈回退
// 思路：把屏蔽词建成 AC 自动机并补全转移表，让每个字符只需 O(1) 转移；
// 再用两个同步的栈（保留的字符、读入每个字符后的自动机状态）保存历史，
// 命中屏蔽词时弹掉对应长度并把自动机回退到弹完后的栈顶状态，
// 等价于"从头重新找"，从而把反复重扫压成一趟线性扫描。
#include <cstdio>

typedef long long ll;

const int MAXNODE = 100015; // 结点数上界 1 + sum|t_i| <= 100001
const int MAXS = 100005;    // |S| 上界

int go[MAXNODE][26]; // go[v][c]：状态 v 读入字符 c 后的去向（BFS 时补全，缺边继承 fail）
int fail[MAXNODE];   // fail[v]：状态 v 的最长真后缀结点
int lend[MAXNODE];   // lend[v]：以 v 结尾的屏蔽词长度，v 不是词尾时为 0
int node_cnt = 1;    // 结点数，0 号是根

char text[MAXS];    // 主串 S
char kept[MAXS];    // kept[0..top) 是当前保留下来的字符，即答案
int state[MAXS];    // state[i]：读完 kept[0..i) 之后自动机所在的状态，state[0] = 0
ll top = 0;         // kept / state 的共用栈顶

int que[MAXNODE]; // BFS 队列

// 把屏蔽词 word（长度 len）插入 trie
void insert_word(char *word, ll len) {
    int v = 0;
    for (ll i = 0; i < len; i++) {
        int c = word[i] - 'a';
        if (go[v][c] == 0) {
            go[v][c] = node_cnt;
            node_cnt++;
        }
        v = go[v][c];
    }
    lend[v] = len; // 词尾记录长度；题目保证无子串关系，一个结点至多是一个词尾
}

// BFS 求 fail，同时补全转移表：缺边直接继承 fail 的同一字符转移
void build_automaton() {
    int head = 0;
    int tail = 0;
    for (int c = 0; c < 26; c++) {
        if (go[0][c] != 0) {
            que[tail] = go[0][c];
            tail++;
        }
    }
    while (head < tail) {
        int v = que[head];
        head++;
        int f = fail[v]; // fail[v] 已在更浅的层处理过，它的转移表是完整的
        for (int c = 0; c < 26; c++) {
            int u = go[v][c];
            if (u != 0) {
                fail[u] = go[f][c];
                que[tail] = u;
                tail++;
            } else {
                go[v][c] = go[f][c]; // 补全：等价于沿 fail 链回退直到能读 c
            }
        }
    }
}

// 从左到右扫描主串，边扫边删屏蔽词
void censor() {
    int node = 0;
    state[0] = 0;
    for (ll i = 0; text[i] != '\0'; i++) {
        int c = text[i] - 'a';
        node = go[node][c];
        kept[top] = text[i];
        top++;
        state[top] = node;
        if (lend[node] != 0) {
            top = top - lend[node]; // 弹掉命中的屏蔽词
            node = state[top];      // 回退到删除前的位置，等价于从头重新找
        }
    }
}

int main() {
    ll n;
    scanf("%s", text);
    scanf("%lld", &n);
    for (ll i = 0; i < n; i++) {
        char word[MAXS];
        scanf("%s", word);
        ll len = 0;
        while (word[len] != '\0') {
            len++;
        }
        insert_word(word, len);
    }
    build_automaton();
    censor();
    for (ll i = 0; i < top; i++) {
        putchar(kept[i]);
    }
    putchar('\n');
    return 0;
}
