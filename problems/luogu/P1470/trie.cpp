#include <bits/stdc++.h>
using namespace std;

// ============ 倒序 Trie ============
// 需求：给定字符串 S 和位置 i，快速找出"以 S[i] 结尾、且在词集 P 中"的所有后缀。
// 普通 Trie 从根出发表示"前缀"，无法直接回答"后缀"；把每个词反着插入，
// 再让 S 从后往前走，就能从根一路判断后缀是不是词。
struct Trie {
    struct Node {
        array<int, 26> ch{};    // ch[c] 子节点编号，0 为空（根也是 0）
        int end = 0;            // 以该节点结尾的完整词个数
    };

    vector<Node> tree;          // tree[0] 为根

    Trie() { tree.push_back(Node()); }

    // 倒着插入：把 s 反串放进 Trie。例如 "AB" 存成根->B->A
    void insert(const string &s) {
        int u = 0;
        for (int i = (int)s.size() - 1; i >= 0; i--) {
            int c = s[i] - 'A';
            if (tree[u].ch[c] == 0) {       // 无子节点则新建
                tree[u].ch[c] = (int)tree.size();
                tree.push_back(Node());
            }
            u = tree[u].ch[c];
        }
        tree[u].end++;          // 走到词尾，标记为一个完整词
    }
};

// ============ 主程序 ============
// 思路：dp[i] 表示前缀 S[0..i) 能否由词集 P 完整拆开。
// 转移：枚举最后一个词 w，要求 S 以 i 结尾的后缀 == w，且 dp[i-|w|] 为真。
// 词长 <= 10，所以从 i 往回最多试 10 个长度。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入词集 P：以单独一行 "." 结束（"." 之前可能有多行）
    Trie trie;
    string word;
    while (cin >> word && word != ".") {
        trie.insert(word);
    }

    // 读入 S：每 76 个字符一行，必须拼成完整串
    string S, line;
    while (cin >> line) S += line;

    int n = (int)S.size();
    vector<char> dp(n + 1, false);
    dp[0] = true;               // 空前缀可拆
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        // 从 i 往前，在倒序 Trie 上连续走，len 是当前后缀长度
        int u = 0;
        for (int len = 1; len <= 10 && i - len >= 0; len++) {
            int c = S[i - len] - 'A';
            // 走不动了：不可能有更长的反串前缀，直接剪枝
            if (trie.tree[u].ch[c] == 0) break;
            u = trie.tree[u].ch[c];

            // 当前后缀 S[i-len..i) 是一个完整词，且前面部分能拆开
            if (trie.tree[u].end && dp[i - len]) {
                dp[i] = true;
                break;          // 找到一个拆法即可
            }
        }
        if (dp[i]) ans = i;     // dp 不单调，取所有可达位置的最大值
    }

    cout << ans << '\n';
    return 0;
}
