/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 20:09
 * update_at: 2026-10-08 20:09
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef long long ll;

// 并查集底层：人名 -> 代表元。代表元沿父亲方向上溯，
// 根（代表元就是自己）即该家族最早的那位祖先。
// 用 map<string,string> 代替数组，等价于把字符串名字当作下标。
map<string, string> parent_map;

// 返回 name 的最早祖先，并把沿途节点直接挂到祖先后（路径压缩）。
string find_root(const string &name) {
    auto it = parent_map.find(name);
    if (it == parent_map.end()) {   // 第一次出现的人，自己就是家族根
        parent_map[name] = name;
        return name;
    }
    if (it->second == name) {       // 已经指向自己，说明是根
        return name;
    }
    parent_map[name] = find_root(it->second);
    return parent_map[name];
}

// 把 child 所在家族整体接到 father 所在家族之下
void add_son(const string &child, const string &father) {
    string child_root = find_root(child);
    string father_root = find_root(father);
    if (child_root != father_root) {
        parent_map[child_root] = father_root;
    }
}

// 单组数据：顺序执行指令直到 '$'
void solve() {
    string str;
    string current_father;      // 最近一个 '#name' 声明的父亲，随后的 '+name' 都挂在他下面
    while (cin >> str) {
        if (str == "$") {
            break;
        }
        char op = str[0];
        string name = str.substr(1);

        if (op == '#') {
            current_father = name;
            if (parent_map.find(name) == parent_map.end()) {
                parent_map[name] = name;    // 新名字先自立为根，日后被 '+name' 认领时会改指
            }
        } else if (op == '+') {
            add_son(name, current_father);
        } else if (op == '?') {
            cout << name << " " << find_root(name) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
