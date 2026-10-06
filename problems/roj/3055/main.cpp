/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:40
 * update_at: 2026-10-06 11:42
 */
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

typedef long long ll;

// Trie：sons[node][c] 表示节点 node 沿字符 c 走到的子节点编号，0 表示不存在
const int MAXNODE = 400005; // 每组最多 n*11 个字符，节点数不超过总字符数
int sons[MAXNODE][11];      // 子节点表：0~9 为数字，10 为哨兵 '$'
int node_cnt;               // 当前已用节点数（含根 0）

// 每组数据开始前清空 Trie（只清实际用到的部分）
void trie_init() {
    node_cnt = 1; // 根节点编号 0
    memset(sons[0], 0, sizeof(sons[0]));
}

// 插入号码 s（末尾隐含哨兵 '$'），途中检测前缀冲突；有冲突返回 false
bool trie_insert(const string &s) {
    int node = 0;
    int len = s.size(); // 先存成 int，避免和有符号下标比较出问题
    for (int i = 0; i <= len; i++) {
        int c = (i == len) ? 10 : s[i] - '0'; // 末尾多走一步：哨兵 '$' 用编号 10
        bool has_son = false; // 节点 node 是否已有任何子节点
        for (int k = 0; k < 11; k++)
            if (sons[node][k]) has_son = true;
        if (c == 10 && has_son) return false; // 结尾仍有后继：当前号码是更早号码的前缀
        if (sons[node][c] == 0) { // 惰性建点（含哨兵位）
            sons[node][c] = node_cnt;
            memset(sons[node_cnt], 0, sizeof(sons[node_cnt]));
            node_cnt++;
        } else if (sons[sons[node][c]][10] != 0) {
            // 下一个节点已有哨兵：有号码在这位终止，它是当前号码的前缀
            return false;
        }
        node = sons[node][c];
    }
    return true;
}

int t = 0, n = 0;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> t;
    while (t--) {
        cin >> n;
        trie_init();
        bool ok = true; // 兼容 = 任意两个号码互不为前缀
        for (int i = 1; i <= n; i++) {
            cin >> s;
            if (ok && !trie_insert(s)) ok = false; // 已判 NO 也要读完剩余输入
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
