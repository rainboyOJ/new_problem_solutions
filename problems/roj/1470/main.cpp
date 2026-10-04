/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:59
 * update_at: 2026-10-05 02:59
 */

// Censoring：屏蔽词建 AC 自动机，逐字符扫描，命中词尾就按长度整段弹出。
// 关键观察：屏蔽词互不为子串 => 删除只会发生在保留串末尾，
// 且同一结尾位置至多一个屏蔽词，所以一次从左到右扫描即可完成全部删除。

#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 100005; // 屏蔽词总长 <= 1e5，trie 节点数不超过总长 + 1
const int ALPHA = 26;

typedef long long ll;

int ch[MAXNODE][ALPHA]; // trie 图转移表：ch[u][c] = 读到字符 c 后到达的节点
int fail_[MAXNODE];     // fail 指针，指向当前节点最长真后缀对应的节点
int end_[MAXNODE];      // end_[v] > 0 表示节点 v 结尾的屏蔽词长度
int tot = 1;            // 节点计数，0 号是根，1 号留给第一个新节点

char s[MAXNODE];    // 主串 S
char buf[MAXNODE];  // 读入屏蔽词用的缓冲区
char kept[MAXNODE]; // 栈：保存删除后保留下来的字符
int sta[MAXNODE];   // 平行状态栈：sta[i] = 保留前 i 个字符时的自动机节点
int top = 0;        // 栈中字符个数（即当前保留串长度）
int cur = 0;        // 当前保留串对应的自动机节点

// 把一个屏蔽词插入 trie。
void insert_word(const char *w) {
    int u = 0;
    for (int i = 0; w[i] != '\0'; i++) {
        int c = w[i] - 'a';
        if (ch[u][c] == 0) {
            ch[u][c] = tot++;
        }
        u = ch[u][c];
    }
    end_[u] = strlen(w); // 屏蔽词互不为子串 => 每个节点至多结尾一个词
}

// BFS 建 fail 指针，同时把缺边补全成 fail 转移（trie 图），
// 并把词尾长度沿 fail 链传播到所有后缀节点上。
void build_automaton() {
    queue<int> q;
    for (int c = 0; c < ALPHA; c++) {
        if (ch[0][c] != 0) {
            fail_[ch[0][c]] = 0; // 第一层的 fail 都是根
            q.push(ch[0][c]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int c = 0; c < ALPHA; c++) {
            int v = ch[u][c];
            if (v != 0) {
                // 真孩子：定 fail，并继承 fail 链上的词尾长度
                fail_[v] = ch[fail_[u]][c];
                end_[v] = max(end_[v], end_[fail_[v]]);
                q.push(v);
            }
            else {
                // 补全成 trie 图：缺边改指向 fail 的同边，扫描时免跳 fail
                ch[u][c] = ch[fail_[u]][c];
            }
        }
    }
}

// 逐字符扫描主串：命中屏蔽词就按词长整段弹出，状态恢复为栈顶记录值。
void solve() {
    sta[0] = 0; // 空串对应根节点
    int len = strlen(s + 1);
    for (int i = 1; i <= len; i++) {
        cur = ch[cur][s[i] - 'a']; // trie 图上一步转移，自带 fail 语义
        top++;
        kept[top] = s[i];
        sta[top] = cur;
        if (end_[cur] != 0) {
            // 栈顶拼出了屏蔽词：连当前字符一起弹出 end_[cur] 个，
            // 状态回到删除后串的状态，拼接处的匹配由自动机自动接上
            top -= end_[cur];
            cur = sta[top];
        }
    }
    kept[top + 1] = '\0';
    cout << kept + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> (s + 1); // 主串从下标 1 开始存，与栈下标对应
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (buf + 1);
        insert_word(buf + 1);
    }
    build_automaton();
    solve();

    return 0;
}
