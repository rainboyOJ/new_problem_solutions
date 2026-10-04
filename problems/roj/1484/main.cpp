/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:52
 * update_at: 2026-10-05 03:52
 */
// AC 自动机 + 拓扑判环：是否存在无限长的安全 01 串。

#include <cstdio>
#include <string>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 30005 + 5; // 病毒串总长不超过 3e4，Trie 节点数不超过总长 + 1

int n;
int ch[MAXN][2];  // 补全后的转移表：ch[v][b] = 节点 v 读入位 b 后到达的节点
int fail_[MAXN];  // fail 指针：指向"最长且同时是某病毒串前缀"的真后缀
bool danger[MAXN];// danger[v] = 从根到 v 的串是否含有病毒串作子串
bool seen[MAXN];  // 从根沿安全边 BFS 时是否访问过
int indeg[MAXN];  // 可达安全子图中每个节点的入度
int tot = 1;      // Trie 节点数，0 是根，1 号起为真实节点（先占一个空位）

// 把一个病毒串插进 Trie
void insert_str(const string &s) {
    int v = 0;
    for (size_t i = 0; i < s.size(); i++) {
        int b = s[i] - '0';
        if (ch[v][b] == 0) { // 0 号保留为根，0 表示尚无此边
            ch[v][b] = ++tot;
        }
        v = ch[v][b];
    }
    danger[v] = true; // 病毒串结尾标记为危险
}

// BFS 建 fail 指针，同时补全转移表、沿 fail 链传播危险标记
void build_fail() {
    queue<int> q;
    for (int b = 0; b < 2; b++) {
        if (ch[0][b] != 0) {
            // 根的孩子 fail 指向根，缺省值 0 已正确，直接入队
            q.push(ch[0][b]);
        }
        // 根的缺失边 ch[0][b] == 0 恰好指回自己，无需处理
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int b = 0; b < 2; b++) {
            int w = ch[v][b];
            if (w == 0) {
                // 缺失边：抄 fail[v] 的同位边，补成完整转移图
                ch[v][b] = ch[fail_[v]][b];
            } else {
                fail_[w] = ch[fail_[v]][b];
                // 危险沿 fail 链传播：w 的后缀里有病毒串结尾则 w 也危险
                danger[w] = danger[w] || danger[fail_[w]];
                q.push(w);
            }
        }
    }
}

// 判断是否存在无限长安全串：可达安全子图有环输出 true
bool solve() {
    // 从根出发，只沿两端都安全的边 BFS，统计可达安全节点和入度
    queue<int> q;
    seen[0] = true;
    q.push(0);
    int total = 1; // 可达安全节点数
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int b = 0; b < 2; b++) {
            int w = ch[v][b];
            if (danger[w]) continue; // 走过去会踩雷，删掉这条边
            indeg[w]++;
            if (!seen[w]) {
                seen[w] = true;
                total++;
                q.push(w);
            }
        }
    }

    // Kahn 拓扑排序：入度归零的点出队并回删出边；环上节点入度永不归零
    int removed = 0;
    for (int v = 0; v <= tot; v++) {
        if (seen[v] && indeg[v] == 0) q.push(v);
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        removed++;
        for (int b = 0; b < 2; b++) {
            int w = ch[v][b];
            if (danger[w]) continue;
            indeg[w]--;
            if (indeg[w] == 0) q.push(w);
        }
    }
    return removed != total; // 删不光所有可达安全节点则必有环
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        static char buf[MAXN];
        scanf("%s", buf);
        insert_str(string(buf));
    }
    build_fail();
    printf(solve() ? "TAK\n" : "NIE\n");
    return 0;
}
