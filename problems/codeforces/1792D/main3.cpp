/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 09:22
 * update_at: 2026-11-12 09:50
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 50000 + 50;
vector<int> a[maxn]; // 原排列序列
int pos_of[15];      // pos_of[val] 记录数字 val 在当前排列中的位置 (1-based)

// 静态字典树节点池：最多 50000 个长度为 10 的排列，总节点数不超过 500050
// 字符集固定为 1~10，按实际规模开辟固定大小 ch[MAX_NODES][11]
const int MAX_NODES = 500000 + 50;
int ch[MAX_NODES][11];
bool has_q[MAX_NODES]; // has_q[u] = true 表示节点 u 所代表的前缀至少存在于一个逆置换 q 中
int node_cnt = 0;      // 已经创建的节点个数，充当动态分配指针

int new_node() {
    node_cnt++;
    for (int d = 1; d <= 10; ++d) {
        ch[node_cnt][d] = 0;
    }
    has_q[node_cnt] = false;
    return node_cnt;
}

// 将原排列 a 插入前缀树
void insert_a(const vector<int>& p, int m) {
    int u = 0;
    for (int k = 1; k <= m; ++k) {
        int d = p[k - 1];
        if (!ch[u][d]) {
            ch[u][d] = new_node();
        }
        u = ch[u][d];
    }
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // 清空根节点与节点计数器
    node_cnt = 0;
    for (int d = 1; d <= 10; ++d) {
        ch[0][d] = 0;
    }
    has_q[0] = false;

    // 第一步：将所有原排列 a[i] 插入前缀树，建立待匹配的结构骨架
    for (int i = 0; i < n; ++i) {
        a[i].resize(m);
        for (int k = 0; k < m; ++k) {
            cin >> a[i][k];
        }
        insert_a(a[i], m);
    }

    // 第二步：让每个逆置换 q[j] 在树上漫游匹配，沿途激活节点 has_q[u] = true
    for (int j = 0; j < n; ++j) {
        for (int k = 1; k <= m; ++k) {
            pos_of[a[j][k - 1]] = k; // 计算逆置换
        }

        int u = 0;
        for (int k = 1; k <= m; ++k) {
            int d = pos_of[k];
            if (!ch[u][d]) break; // 无法继续匹配，直接截断
            u = ch[u][d];
            has_q[u] = true;     // 标记：该前缀已被某个逆置换成功覆盖
        }
    }

    // 第三步：每个 a[i] 顺着自己的前缀路径，查看最深能够保持在已激活状态的步数
    for (int i = 0; i < n; ++i) {
        int u = 0, max_lcp = 0;
        for (int k = 1; k <= m; ++k) {
            int d = a[i][k - 1];
            u = ch[u][d];
            if (!has_q[u]) break;
            max_lcp = k;
        }
        cout << max_lcp << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
