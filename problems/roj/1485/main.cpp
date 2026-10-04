/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:57
 * update_at: 2026-10-05 03:57
 */
// roj 1485「文本生成器」：AC 自动机 + 计数 DP（正难则反）
// 直接数"至少含一个单词"的串要做重叠容斥，很难；反过来数"一个单词都不含"的串
// 可以边构造边判断，于是 答案 = 26^M - (长度 M、不含任何单词的串数)。
// "当前前缀是否已命中单词"只需记住它的最长可匹配后缀，这正是 AC 自动机的状态：
// 建 trie -> BFS 求 fail 时补全转移表并把命中标记 dead 沿 fail 链下传 ->
// 按长度做滚动数组 DP 数路径。复杂度 O(26 * |V| * M)。
#include <cstdio>

typedef long long ll;

const int MOD = 10007; // 题面要求的结果模数
const int ALPHA = 26;  // 字符集：26 个大写字母

const int MAXNODE = 6100; // 自动机节点数上界 1 + sum|w| <= 1 + 60 * 100
const int MAXLEN = 105;   // 单个单词长度上界

int go[MAXNODE][ALPHA]; // go[v][c]：状态 v 读到字符 c 后的去向；BFS 时补全，缺边继承 fail
int fail[MAXNODE];      // fail[v]：状态 v 的最长真后缀节点
char dead[MAXNODE];     // dead[v] = 1 表示到达 v 时已经命中过某个单词（只有 0/1，用 char 省内存）
int node_cnt = 1;       // 节点数，0 号是根

int dp[MAXNODE];  // dp[v]：当前长度、全程未命中且停在 v 的串数
int nxt[MAXNODE]; // 下一长度的 dp
int que[MAXNODE]; // BFS 队列

char word[MAXLEN]; // 当前读入的单词

// 把长度为 len 的单词 word 插入 trie，并在词尾打上命中标记
void insert_word(int len) {
    int v = 0;
    for (int i = 0; i < len; i++) {
        int c = word[i] - 'A';
        if (go[v][c] == 0) { // 0 号是根，真实边不会指回根，可用 0 表示"这条边还不存在"
            go[v][c] = node_cnt;
            node_cnt++;
        }
        v = go[v][c];
    }
    dead[v] = 1; // 节点本身是词尾，走到这里就命中了
}

// BFS 求 fail，同时补全转移表并把命中标记沿 fail 链下传
void build_automaton() {
    int head = 0;
    int tail = 0;
    for (int c = 0; c < ALPHA; c++) {
        if (go[0][c] != 0) { // 根的孩子失配后回到根
            que[tail] = go[0][c];
            tail++;
        }
    }
    while (head < tail) {
        int v = que[head];
        head++;
        if (dead[fail[v]]) { // fail 链上的词尾说明当前后缀已命中，向下传递
            dead[v] = 1;
        }
        int f = fail[v]; // fail[v] 更浅，已处理完，它的转移表是完整的
        for (int c = 0; c < ALPHA; c++) {
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

// 统计长度恰为 m、且完全不含任何单词的串数（模 MOD）
int count_safe(int m) {
    for (int v = 0; v < node_cnt; v++) {
        dp[v] = 0;
    }
    dp[0] = 1; // 空串停在根
    for (int step = 1; step <= m; step++) {
        for (int v = 0; v < node_cnt; v++) {
            nxt[v] = 0;
        }
        for (int v = 0; v < node_cnt; v++) {
            if (dp[v] == 0) {
                continue;
            }
            for (int c = 0; c < ALPHA; c++) {
                int u = go[v][c];
                if (dead[u]) { // 落到死状态就已经命中，这条转移丢弃
                    continue;
                }
                nxt[u] += dp[v];
                if (nxt[u] >= MOD) {
                    nxt[u] -= MOD;
                }
            }
        }
        for (int v = 0; v < node_cnt; v++) {
            dp[v] = nxt[v];
        }
    }
    int sum = 0;
    for (int v = 0; v < node_cnt; v++) {
        sum += dp[v];
        if (sum >= MOD) {
            sum -= MOD;
        }
    }
    return sum;
}

// 快速幂求 base^exp mod MOD
int pow_mod(int base, int exp) {
    int result = 1;
    int b = base % MOD;
    int e = exp;
    while (e > 0) {
        if (e & 1) {
            result = result * b % MOD;
        }
        b = b * b % MOD;
        e >>= 1;
    }
    return result;
}

int main() {
    int n = 0;
    int m = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        int len = 0;
        while (word[len] != '\0') {
            len++;
        }
        insert_word(len);
    }
    build_automaton();

    int total = pow_mod(ALPHA, m); // 全部文章数 26^m
    int safe = count_safe(m);      // 不可读文章数
    int answer = (total - safe) % MOD;
    if (answer < 0) {
        answer += MOD;
    }
    printf("%d\n", answer);
    return 0;
}
