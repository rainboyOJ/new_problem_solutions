/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
string tag[MAXN], id[MAXN]; // 每个元素的小写标签与 id 属性
int parent[MAXN];           // 每个元素的父元素行号，根元素为 -1

// 标签统一转小写，id 保持原样。
string to_lower_string(string value) {
    for (int i = 0; i < (int)value.size(); i++) {
        value[i] = (char)tolower((unsigned char)value[i]);
    }
    return value;
}

// 判断节点 node 是否匹配选择器的一段：'#' 开头是 id 选择器，否则是标签选择器。
bool match_part(int node, const string &part) {
    if (part[0] == '#') {
        return id[node] == part.substr(1);
    }
    return tag[node] == part;
}

// 判断节点 node 是否被整个后代选择器选中，从最后一段向根贪心匹配。
bool match_selector(int node, const vector<string> &parts) {
    int last = (int)parts.size() - 1;
    if (!match_part(node, parts[last])) {
        return false;
    }

    node = parent[node];
    for (int index = last - 1; index >= 0; index--) {
        // 沿祖先链向上找最近一段能匹配的祖先。
        while (node != -1 && !match_part(node, parts[index])) {
            node = parent[node];
        }
        if (node == -1) {
            return false;
        }
        node = parent[node];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    string line;
    getline(cin, line);

    int last_at_depth[MAXN]; // 每个缩进深度最后出现的元素行号
    fill(last_at_depth, last_at_depth + MAXN, -1);

    // 读入文档：缩进层级决定父子关系。
    for (int i = 1; i <= n; i++) {
        getline(cin, line);
        int depth = 0;
        while (line[2 * depth] == '.') {
            depth++;
        }
        int start = 2 * depth;
        int space = (int)line.find(' ', start);
        if (space == -1) {
            tag[i] = to_lower_string(line.substr(start));
        } else {
            tag[i] = to_lower_string(line.substr(start, space - start));
            id[i] = line.substr(space + 2);
        }
        parent[i] = depth == 0 ? -1 : last_at_depth[depth - 1];
        last_at_depth[depth] = i;
    }

    for (int query = 1; query <= m; query++) {
        getline(cin, line);
        stringstream input(line);
        vector<string> parts;
        string part;
        while (input >> part) {
            if (part[0] != '#') {
                part = to_lower_string(part);
            }
            parts.push_back(part);
        }

        // 枚举每个元素作为匹配的最后一段。
        vector<int> answer;
        for (int node = 1; node <= n; node++) {
            if (match_selector(node, parts)) {
                answer.push_back(node);
            }
        }
        cout << answer.size();
        for (int i = 0; i < (int)answer.size(); i++) {
            cout << ' ' << answer[i];
        }
        cout << '\n';
    }

    return 0;
}