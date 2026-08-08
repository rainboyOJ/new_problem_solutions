#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 200005;
const int ALPHA = 26;

int trie[MAXLEN][ALPHA];
int fail_link[MAXLEN];
int word_len[MAXLEN]; // 若当前状态结尾匹配某个单词，记录这个单词长度。
int node_cnt;

string s;
int n;
string word;
char answer_stack[MAXLEN];
int state_stack[MAXLEN];
int top_pos;

void insert_word(const string &text) {
    int p = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        int c = text[i] - 'a';
        if (trie[p][c] == 0) {
            node_cnt++;
            trie[p][c] = node_cnt;
        }
        p = trie[p][c];
    }
    word_len[p] = (int)text.size();
}

void build_ac() {
    queue<int> que;
    for (int c = 0; c < ALPHA; c++) {
        int v = trie[0][c];
        if (v != 0) {
            que.push(v);
        }
    }

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int c = 0; c < ALPHA; c++) {
            int v = trie[u][c];
            if (v != 0) {
                fail_link[v] = trie[fail_link[u]][c];
                que.push(v);
            } else {
                trie[u][c] = trie[fail_link[u]][c];
            }
        }

        // 题目保证单词互不为子串，正常不会需要继承；保留可增强健壮性。
        if (word_len[u] == 0 && word_len[fail_link[u]] != 0) {
            word_len[u] = word_len[fail_link[u]];
        }
    }
}

void read_input() {
    cin >> s;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> word;
        insert_word(word);
    }
}

void solve() {
    build_ac();

    top_pos = 0;
    state_stack[0] = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        int next_state = trie[state_stack[top_pos]][c];

        top_pos++;
        answer_stack[top_pos] = s[i];
        state_stack[top_pos] = next_state;

        if (word_len[next_state] > 0) {
            top_pos -= word_len[next_state];
        }
    }

    for (int i = 1; i <= top_pos; i++) {
        cout << answer_stack[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
