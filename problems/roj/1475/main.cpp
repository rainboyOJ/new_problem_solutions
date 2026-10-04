/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:21
 * update_at: 2026-10-05 03:21
 */
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXNODE = 205;    // 字典树节点上限：20 个单词，每个单词长度不超过 10
const int MAXLEN = 1000005; // 单篇文章长度上限 1 MB

int trie_next[MAXNODE][26]; // trie_next[u][c]：节点 u 沿字符 c 走到的子节点，0 表示没有该分支
int is_end[MAXNODE];        // is_end[u] = 1 表示节点 u 是某个单词的结尾
char reach[MAXLEN];         // reach[i] = 1 表示文章长度为 i 的前缀可以被字典完整拆分
char text[MAXLEN];          // 当前处理的文章

ll n, m;
int node_cnt = 0;     // 0 号节点是字典树的根
int max_word_len = 0; // 字典中最长单词的长度，用来限制匹配步数和剪枝

// 把单词 w 插入字典树。
void insert_word(const char *w) {
    int u = 0;
    for (int i = 0; w[i] != '\0'; i++) {
        int c = w[i] - 'a';
        if (trie_next[u][c] == 0) {
            node_cnt++;
            trie_next[u][c] = node_cnt;
        }
        u = trie_next[u][c];
    }
    is_end[u] = 1;
}

// 计算当前文章能被字典理解的最长前缀长度。
int longest_prefix() {
    int len = strlen(text);
    for (int i = 0; i <= len; i++) {
        reach[i] = 0;
    }
    reach[0] = 1; // 空前缀天然可以被理解

    int last_reach = 0; // 最近一个可达前缀的位置
    int ans = 0;
    for (int i = 0; i <= len; i++) {
        if (reach[i] == 0) {
            // 连续超过最长单词长度都没有可达位置，后面任何位置都不可能可达，直接结束
            if (i - last_reach > max_word_len) {
                break;
            }
            continue;
        }

        last_reach = i;
        ans = i;

        // 从位置 i 出发沿字典树匹配，最多前进 max_word_len 步
        int u = 0;
        for (int j = i; j < len && j < i + max_word_len; j++) {
            int c = text[j] - 'a';
            if (trie_next[u][c] == 0) {
                break;
            }
            u = trie_next[u][c];
            if (is_end[u]) {
                reach[j + 1] = 1;
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    char word[16]; // 单词长度不超过 10
    for (ll i = 1; i <= n; i++) {
        cin >> word;
        int wlen = strlen(word);
        if (wlen > max_word_len) {
            max_word_len = wlen;
        }
        insert_word(word);
    }

    for (ll i = 1; i <= m; i++) {
        cin >> text; // text 已按 1 MB 上限开足
        cout << longest_prefix() << "\n";
    }

    return 0;
}
