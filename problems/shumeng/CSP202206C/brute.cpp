/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:45
 */
// brute.cpp：按同一授权规则直接执行查询判定。
#include <bits/stdc++.h>
using namespace std;

struct Role {
    string name;
    unordered_set<string> operations, object_types, object_names;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int role_count, relation_count, query_count;
    cin >> role_count >> relation_count >> query_count;
    vector<Role> role(role_count);
    unordered_map<string, int> role_id;
    for (int i = 0; i < role_count; i++) {
        int count;
        cin >> role[i].name;
        role_id[role[i].name] = i;
        cin >> count;
        for (int j = 0; j < count; j++) {
            string value;
            cin >> value;
            role[i].operations.insert(value);
        }
        cin >> count;
        for (int j = 0; j < count; j++) {
            string value;
            cin >> value;
            role[i].object_types.insert(value);
        }
        cin >> count;
        for (int j = 0; j < count; j++) {
            string value;
            cin >> value;
            role[i].object_names.insert(value);
        }
    }

    unordered_map<string, vector<int> > object_roles;
    for (int i = 0; i < relation_count; i++) {
        string name;
        int count;
        cin >> name >> count;
        int id = role_id[name];
        for (int j = 0; j < count; j++) {
            string type, value;
            cin >> type >> value;
            object_roles[type + ":" + value].push_back(id);
        }
    }

    vector<int> seen(role_count, 0);
    int query_id = 0;
    while (query_count--) {
        string user, operation, object_type, object_name;
        int group_count;
        cin >> user >> group_count;
        vector<string> group(group_count);
        for (int i = 0; i < group_count; i++) cin >> group[i];
        cin >> operation >> object_type >> object_name;
        query_id++;
        vector<int> candidate;
        string user_key = "u:" + user;
        for (int i = 0; i < (int)object_roles[user_key].size(); i++) {
            int id = object_roles[user_key][i];
            if (seen[id] != query_id) seen[id] = query_id, candidate.push_back(id);
        }
        for (int i = 0; i < group_count; i++) {
            string key = "g:" + group[i];
            for (int j = 0; j < (int)object_roles[key].size(); j++) {
                int id = object_roles[key][j];
                if (seen[id] != query_id) seen[id] = query_id, candidate.push_back(id);
            }
        }
        bool allowed = false;
        for (int i = 0; i < (int)candidate.size() && !allowed; i++) {
            Role &current = role[candidate[i]];
            bool operation_ok = current.operations.count(operation) || current.operations.count("*");
            bool type_ok = current.object_types.count(object_type) || current.object_types.count("*");
            bool name_ok = current.object_names.empty() || current.object_names.count(object_name);
            if (operation_ok && type_ok && name_ok) allowed = true;
        }
        cout << (allowed ? 1 : 0) << '\n';
    }

    return 0;
}
