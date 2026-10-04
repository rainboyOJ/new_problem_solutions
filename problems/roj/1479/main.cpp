/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:32
 * update_at: 2026-10-05 03:32
 */
#include <cstdio>
#include <cstring>

typedef long long ll;

// 单组数据最多 1e4 个查询词、每词不超过 50 字符，Trie 节点数不超过 5e5+1
const int MAXNODE = 500005;
// 文章长度上限
const int MAXM = 1000005;

// 链式前向星存 Trie 边：只保存真实存在的边，不建 26 叉的完整转移表
int head[MAXNODE];      // head[u]：节点 u 的第一条出边编号，-1 表示无出边
int edge_to[MAXNODE];   // edge_to[e]：第 e 条边指向的子节点
char edge_ch[MAXNODE];  // edge_ch[e]：第 e 条边上的字符
int edge_next[MAXNODE]; // edge_next[e]：同一起点的下一条出边编号
int edge_cnt;           // 已分配的边数

int fail_arr[MAXNODE];  // fail_arr[v]：v 的最长真后缀且同时是某个查询词前缀的节点
int word_cnt[MAXNODE];  // word_cnt[v]：以 v 结尾的查询词个数，重复词各计一次
int bfs_order[MAXNODE]; // bfs_order[]：BFS 出队序列，深度不减，用于逆序传播命中
char hit[MAXNODE];      // hit[v]：扫描文章时是否到达过状态 v，取值只有 0/1，用 char 省内存
int node_cnt;           // 当前 Trie 的节点数

char article[MAXM]; // 文章
char word[64];      // 单个查询词，长度不超过 50

// 在节点 u 的出边中查找字符 c 指向的子节点，找不到返回 -1
int find_child(int u, int c) {
    for (int e = head[u]; e != -1; e = edge_next[e]) {
        if (edge_ch[e] == c) {
            return edge_to[e];
        }
    }
    return -1;
}

// 新建一条从 u 到 v、边上字符为 c 的 Trie 边
void add_edge(int u, int v, int c) {
    edge_to[edge_cnt] = v;
    edge_ch[edge_cnt] = c;
    edge_next[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

// 初始化一个空节点并返回它的编号
int new_node() {
    int v = node_cnt;
    head[v] = -1;
    word_cnt[v] = 0;
    fail_arr[v] = 0;
    node_cnt++;
    return v;
}

// 把所有查询词插入 Trie：状态含义是“当前文本后缀中，是某个查询词前缀的最长者”
void insert_word() {
    int u = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        int c = word[i];
        int v = find_child(u, c);
        if (v == -1) {
            v = new_node();
            add_edge(u, v, c);
        }
        u = v;
    }
    word_cnt[u] += 1; // 内容相同的查询词要各算一次，所以累加而不是置 1
}

// BFS 按层求 fail：处理节点 u 的孩子 v（字符 c）时，
// 从 fail_arr[u] 出发沿 fail 链找第一个有 c 边的祖先 f，则 fail_arr[v] 就是 f 的 c 边指向的节点
void build_fail() {
    int qhead = 0;
    int qtail = 0;
    // 根的孩子没有更短的真后缀，fail 直接指向根
    for (int e = head[0]; e != -1; e = edge_next[e]) {
        int v = edge_to[e];
        fail_arr[v] = 0;
        bfs_order[qtail] = v;
        qtail++;
    }
    while (qhead < qtail) {
        int u = bfs_order[qhead];
        qhead++;
        for (int e = head[u]; e != -1; e = edge_next[e]) {
            int v = edge_to[e];
            int c = edge_ch[e];
            int f = fail_arr[u];
            int found = find_child(f, c);
            while (f != 0 && found == -1) {
                f = fail_arr[f];
                found = find_child(f, c);
            }
            fail_arr[v] = (found == -1 ? 0 : found);
            bfs_order[qtail] = v;
            qtail++;
        }
    }
}

// 扫描文章标出到达过的状态，再按 BFS 逆序把命中沿 fail 边向上传播，最后统计词尾节点的命中
int scan_article() {
    memset(hit, 0, node_cnt); // 只清理本组数据实际用到的节点范围
    int u = 0;
    for (int i = 0; article[i] != '\0'; i++) {
        int c = article[i];
        int found = find_child(u, c);
        while (u != 0 && found == -1) { // Trie 上没有对应边就沿 fail 链回退
            u = fail_arr[u];
            found = find_child(u, c);
        }
        if (found != -1) {
            u = found;
        }
        hit[u] = 1;
    }

    // 到达状态 v 说明 v 的整条 fail 祖先链上的查询词都以当前文本为后缀出现过；
    // 逆 BFS 序保证处理 v 时它的 fail 祖先还没被传播，可以把命中继续往上传
    for (int i = node_cnt - 2; i >= 0; i--) {
        int v = bfs_order[i];
        if (hit[v]) {
            hit[fail_arr[v]] = 1;
        }
    }

    int ans = 0;
    for (int v = 1; v < node_cnt; v++) {
        if (hit[v]) {
            ans += word_cnt[v];
        }
    }
    return ans;
}

int main() {
    ll T;
    scanf("%lld", &T);
    while (T--) {
        ll n;
        scanf("%lld", &n);
        edge_cnt = 0;
        node_cnt = 0;
        new_node(); // 根节点编号为 0
        for (ll i = 0; i < n; i++) {
            scanf("%s", word);
            insert_word();
        }
        scanf("%s", article);
        build_fail();
        printf("%d\n", scan_article());
    }
    return 0;
}
