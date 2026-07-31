/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:56
 */
// brute.cpp：为每个元素显式收集祖先链后，按选择器从根向下匹配。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

string tag[MAXN], id[MAXN];
int parent[MAXN];

string to_lower_string(string value) {
    for (int i = 0; i < (int)value.size(); i++) {
        value[i] = (char)tolower((unsigned char)value[i]);
    }
    return value;
}

bool match_part(int node, const string &part) {
    if (part[0] == '#') return id[node] == part.substr(1);
    return tag[node] == part;
}

bool match_selector(int node, const vector<string> &parts) {
    vector<int> chain;
    for (int current = node; current != -1; current = parent[current]) {
        chain.push_back(current);
    }
    reverse(chain.begin(), chain.end());
    int need = 0;
    for (int i = 0; i < (int)chain.size() - 1 && need + 1 < (int)parts.size(); i++) {
        if (match_part(chain[i], parts[need])) {
            need++;
        }
    }
    return need + 1 == (int)parts.size() && match_part(node, parts.back());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string line;
    getline(cin, line);
    int last_at_depth[MAXN];
    fill(last_at_depth, last_at_depth + MAXN, -1);
    for (int i = 1; i <= n; i++) {
        getline(cin, line);
        int depth = 0;
        while (line[2 * depth] == '.') depth++;
        int start = 2 * depth;
        int space = (int)line.find(' ', start);
        tag[i] = to_lower_string(line.substr(start, space == -1 ? string::npos : space - start));
        if (space != -1) id[i] = line.substr(space + 2);
        parent[i] = depth == 0 ? -1 : last_at_depth[depth - 1];
        last_at_depth[depth] = i;
    }

    for (int query = 1; query <= m; query++) {
        getline(cin, line);
        stringstream input(line);
        vector<string> parts;
        string part;
        while (input >> part) {
            if (part[0] != '#') part = to_lower_string(part);
            parts.push_back(part);
        }
        vector<int> answer;
        for (int node = 1; node <= n; node++) {
            if (match_selector(node, parts)) answer.push_back(node);
        }
        cout << answer.size();
        for (int i = 0; i < (int)answer.size(); i++) cout << ' ' << answer[i];
        cout << '\n';
    }

    return 0;
}
