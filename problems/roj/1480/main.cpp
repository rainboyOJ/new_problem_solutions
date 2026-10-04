/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:34
 * update_at: 2026-10-05 03:34
 */
// 玄武密码（JSOI 2012）：把 M 段文字建成 trie（每段长度 <= 100），
// 母串每个起点从根同步逐层下走，走到哪个节点就给哪个节点打「出现过」标记 occ；
// 每段文字沿自身路径下走，答案 = 路径上最深的 occ 节点深度。
//
// 内存说明：sum|T| 可达 1e7，若用 ch[节点*4+字符] 孩子表要 160MB；
// 这里改用「大儿子-兄弟」表示法（son/bro/label 各一个数组），trie 只占 90MB。
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXSUM = 10000005; // sum|T| <= 1e7，M 段文字总字符数上限
const int MAXN = 10000005;   // 母串长度上限

// trie 的「大儿子-兄弟」表示：节点 0 是根，节点编号从 1 开始
int son[MAXSUM];     // son[u] = u 的第一个孩子节点编号，0 表示没有孩子
int bro[MAXSUM];     // bro[v] = v 的下一个兄弟节点编号，0 表示没有更多兄弟
char label[MAXSUM];  // label[v] = 从父节点走到 v 的那个字符（存 0~3 的编号）
bool occ[MAXSUM];    // occ[v] = str(v) 是否作为子串出现在母串中
int cnt_node = 1;    // 已用节点数（0 是根，1 号起是文字段节点）

char s[MAXN];          // 母串
char pool[MAXSUM + 5]; // 文字段字符池：M 段文字按读入顺序连续存放
ll start_id[100005];   // start_id[i] = 第 i 段文字在 pool 里的起始下标
int tlen[100005];      // tlen[i] = 第 i 段文字的长度

// 存活起点列表：pos[k] = 起点下标，node_id[k] = 该起点当前匹配到的 trie 节点
// 每扫一层就地压缩（只保留还能继续走的起点），所以各只需一份数组
int pos[MAXN];
int node_id[MAXN];

ll n, m;
ll pool_end = 0;   // 字符池当前已用到的位置（游标）
ll max_len = 0;    // 最长文字段长度 = trie 最大深度，扫描层数的天然上限

// 把方向字符映射成 0~3 的编号
int code(char c) {
    if (c == 'E') return 0;
    if (c == 'S') return 1;
    if (c == 'W') return 2;
    return 3; // 'N'
}

// 在 u 的孩子里找字符编号为 c 的孩子，没有返回 0
// 兄弟链最多 4 个节点（字符集大小为 4），扫描代价很小
int find_child(int u, int c) {
    for (int v = son[u]; v != 0; v = bro[v])
        if (label[v] == c) return v;
    return 0;
}

int main() {
    scanf("%lld %lld", &n, &m);
    scanf("%s", s);

    // 第一步：读入 M 段文字存进字符池，同时插入 trie（公共前缀只存一份）
    for (ll i = 1; i <= m; i++) {
        scanf("%s", pool + pool_end);
        start_id[i] = pool_end;
        tlen[i] = (ll)strlen(pool + pool_end);
        if (tlen[i] > max_len) max_len = tlen[i];
        pool_end += tlen[i];
        int cur = 0; // 从根出发沿路径插入
        for (ll j = 0; j < tlen[i]; j++) {
            int c = code(pool[start_id[i] + j]);
            int nxt = find_child(cur, c);
            if (nxt == 0) { // 没有这个孩子就新建，并挂到兄弟链头部
                nxt = cnt_node++;
                label[nxt] = c;
                bro[nxt] = son[cur];
                son[cur] = nxt;
            }
            cur = nxt;
        }
    }

    // 第二步：母串每个起点从根同步逐层下走，走到就打 occ 标记
    // 第 len 层处理的是「以 pos[k] 为左端点、长度为 len 的前缀」
    ll alive = 0; // 当前层存活的起点数
    for (ll i = 0; i < n; i++) { // 初始：所有起点都在根
        pos[alive] = i;
        node_id[alive] = 0;
        alive++;
    }
    // 文字段最长只有 100，所以任何匹配深度都不超过 max_len，层数到此封顶
    for (ll len = 1; len <= max_len; len++) {
        ll w = 0; // 下一层存活起点的写入位置（w <= 读下标，可以就地压缩）
        for (ll k = 0; k < alive; k++) {
            ll i = pos[k];
            if (i + len - 1 >= n) continue; // 窗口伸出母串，淘汰
            int nxt = find_child(node_id[k], code(s[i + len - 1]));
            if (nxt != 0) {
                occ[nxt] = true; // 该节点代表的串以 i 为左端点出现在母串中
                pos[w] = i;
                node_id[w] = nxt;
                w++;
            }
        }
        alive = w;
        if (alive == 0) break; // 没有任何起点还能匹配，提前结束
    }

    // 第三步：每段文字沿自身路径下走，取最深的 occ 节点深度
    // occ 沿路径前缀封闭，命中深度一定连续，最后一个命中就是答案
    for (ll i = 1; i <= m; i++) {
        int cur = 0; // 从根出发重走这一段的路径
        ll best = 0;
        for (ll j = 0; j < tlen[i]; j++) {
            cur = find_child(cur, code(pool[start_id[i] + j]));
            if (cur == 0) break; // 路径断了，后面的前缀一定不在 trie 里
            if (occ[cur]) best = j + 1;
        }
        printf("%lld\n", best);
    }
    return 0;
}
