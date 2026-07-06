// main.cpp：用路径上的未匹配左括号栈，线性统计每个节点对应字符串中的合法括号子串数。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

struct Event {
    int type; // 0 表示进入节点，1 表示离开节点并恢复栈
    int u;
};

int n;
char bracket_char[MAXN];
int parent_node[MAXN];
int head[MAXN], to[MAXN], nxt[MAXN], edge_cnt;

long long end_count[MAXN];   // end_count[u]：根到 u 的字符串中，以 u 结尾的合法括号子串数量
long long total_count[MAXN]; // total_count[u]：根到 u 的字符串中所有合法括号子串数量

int action_type[MAXN];       // 1：进入时压入左括号；2：进入时弹出了一个左括号
int matched_open[MAXN];      // 当前右括号匹配到的左括号节点
vector<int> open_stack;      // 当前根到节点路径上尚未匹配的左括号节点

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void enter_node(int u, long long &answer) {
    action_type[u] = 0;
    matched_open[u] = 0;
    end_count[u] = 0;

    if (bracket_char[u] == '(') {
        open_stack.push_back(u);
        action_type[u] = 1;
    } else if (!open_stack.empty()) {
        int left_node = open_stack.back();
        open_stack.pop_back();

        matched_open[u] = left_node;
        action_type[u] = 2;

        // 形成一对 ( ... ) 后，可以接在 left_node 父亲处结尾的合法串后面。
        end_count[u] = end_count[parent_node[left_node]] + 1;
    }

    total_count[u] = total_count[parent_node[u]] + end_count[u];
    answer ^= 1LL * u * total_count[u];
}

void leave_node(int u) {
    if (action_type[u] == 1) {
        open_stack.pop_back();
    } else if (action_type[u] == 2) {
        open_stack.push_back(matched_open[u]);
    }
}

long long solve() {
    long long answer = 0;

    vector<Event> events;
    events.push_back({0, 1});

    while (!events.empty()) {
        Event cur = events.back();
        events.pop_back();

        int u = cur.u;
        if (cur.type == 0) {
            enter_node(u, answer);

            events.push_back({1, u});
            for (int e = head[u]; e != 0; e = nxt[e]) {
                events.push_back({0, to[e]});
            }
        } else {
            leave_node(u);
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string s;
    cin >> s;
    for (int i = 1; i <= n; i++) {
        bracket_char[i] = s[i - 1];
    }

    for (int i = 2; i <= n; i++) {
        cin >> parent_node[i];
        add_edge(parent_node[i], i);
    }

    cout << solve() << '\n';
    return 0;
}
