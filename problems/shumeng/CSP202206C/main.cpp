/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 一个角色允许的操作、资源类型和资源名称三张清单
struct Role {
    string name;                                  // 角色名称
    unordered_set<string> operations;             // 允许的操作清单
    unordered_set<string> object_types;           // 允许的资源类型清单
    unordered_set<string> object_names;           // 允许的资源名称清单（空表示任意名称）
};

int role_count, relation_count, query_count;
vector<Role> role;
unordered_map<string, int> role_id;               // 角色名称 -> 编号
unordered_map<string, vector<int> > object_roles; // "u:用户" 或 "g:用户组" -> 可获得的角色编号列表
vector<int> seen;                                 // 去重标记：值为最近一次查询的编号
int query_id;

// 读入一个角色并填入角色表
void read_role(int id) {
    int count;
    string value;
    cin >> role[id].name;
    role_id[role[id].name] = id;

    cin >> count; // 操作清单
    for (int i = 0; i < count; i++) {
        cin >> value;
        role[id].operations.insert(value);
    }
    cin >> count; // 资源类型清单
    for (int i = 0; i < count; i++) {
        cin >> value;
        role[id].object_types.insert(value);
    }
    cin >> count; // 资源名称清单
    for (int i = 0; i < count; i++) {
        cin >> value;
        role[id].object_names.insert(value);
    }
}

// 读入一条角色关联：把该角色关联到若干用户或用户组
void read_relation() {
    string name;
    int count;
    cin >> name >> count;
    int id = role_id[name];
    for (int i = 0; i < count; i++) {
        string type, value;
        cin >> type >> value; // type 为 u 或 g
        object_roles[type + ":" + value].push_back(id);
    }
}

// 加入一个授权对象（"u:xxx" 或 "g:xxx"）对应的角色，用 seen 去重
void collect_roles(const string &key, vector<int> &candidate) {
    vector<int> &list = object_roles[key];
    for (int i = 0; i < (int)list.size(); i++) {
        int id = list[i];
        if (seen[id] != query_id) {
            seen[id] = query_id;
            candidate.push_back(id);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> role_count >> relation_count >> query_count;
    role.resize(role_count);
    for (int i = 0; i < role_count; i++) read_role(i);
    for (int i = 0; i < relation_count; i++) read_relation();

    seen.assign(role_count, 0);
    query_id = 0;
    while (query_count--) {
        string user, operation, object_type, object_name;
        int group_count;
        cin >> user >> group_count;
        vector<string> group(group_count);
        for (int i = 0; i < group_count; i++) cin >> group[i];
        cin >> operation >> object_type >> object_name;
        query_id++;

        vector<int> candidate; // 本次查询涉及的所有角色编号（已去重）
        collect_roles("u:" + user, candidate);
        for (int i = 0; i < group_count; i++) collect_roles("g:" + group[i], candidate);

        // 任一角色允许该操作即输出 1
        bool allowed = false;
        for (int i = 0; i < (int)candidate.size() && !allowed; i++) {
            Role &current = role[candidate[i]];
            bool operation_ok = current.operations.count(operation)
                || current.operations.count("*");
            bool type_ok = current.object_types.count(object_type)
                || current.object_types.count("*");
            bool name_ok = current.object_names.empty()
                || current.object_names.count(object_name);
            if (operation_ok && type_ok && name_ok) allowed = true;
        }
        cout << (allowed ? 1 : 0) << '\n';
    }

    return 0;
}