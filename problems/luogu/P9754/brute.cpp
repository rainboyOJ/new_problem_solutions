/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:45
 * update_at: 2026-10-01 22:45
 */
// brute.cpp：小数据朴素模拟，与 main.cpp 逻辑相同但写法更紧凑，用来辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct MemberInfo {
    string type_name;
    string name;
    ll offset;
};

struct TypeInfo {
    string name;
    ll size;
    ll align;
    bool is_basic;
    vector<MemberInfo> members;
    map<string, ll> member_id;
};

struct ElementInfo {
    string type_name;
    string name;
    ll start;
};

vector<TypeInfo> types;
vector<ElementInfo> elements;
map<string, ll> type_id;
map<string, ll> element_id;
ll memory_end;

ll align_up(ll x, ll a) {
    if (x % a == 0) return x;
    return x + (a - x % a);
}

void add_basic_type(const string &name, ll size) {
    TypeInfo t;
    t.name = name;
    t.size = size;
    t.align = size;
    t.is_basic = true;
    type_id[name] = (ll)types.size();
    types.push_back(t);
}

vector<string> split_path(const string &s) {
    vector<string> result;
    string cur;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            result.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(s[i]);
        }
    }
    result.push_back(cur);
    return result;
}

bool find_addr_in_type(ll tid, ll base, ll addr, const string &path, string &answer) {
    if (types[tid].is_basic) {
        if (base <= addr && addr < base + types[tid].size) {
            answer = path;
            return true;
        }
        return false;
    }
    for (size_t i = 0; i < types[tid].members.size(); i++) {
        MemberInfo member = types[tid].members[i];
        ll child_tid = type_id[member.type_name];
        ll child_base = base + member.offset;
        if (child_base <= addr && addr < child_base + types[child_tid].size) {
            return find_addr_in_type(child_tid, child_base, addr, path + "." + member.name, answer);
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    add_basic_type("byte", 1);
    add_basic_type("short", 2);
    add_basic_type("int", 4);
    add_basic_type("long", 8);

    ll q;
    cin >> q;
    while (q--) {
        ll op;
        cin >> op;
        if (op == 1) {
            string name;
            ll k;
            cin >> name >> k;

            TypeInfo t;
            t.name = name;
            t.size = 0;
            t.align = 1;
            t.is_basic = false;

            ll cur = 0;
            for (ll i = 0; i < k; i++) {
                string type_name, member_name;
                cin >> type_name >> member_name;
                ll tid = type_id[type_name];
                cur = align_up(cur, types[tid].align);

                MemberInfo member;
                member.type_name = type_name;
                member.name = member_name;
                member.offset = cur;
                t.member_id[member_name] = (ll)t.members.size();
                t.members.push_back(member);

                cur += types[tid].size;
                t.align = max(t.align, types[tid].align);
            }

            t.size = align_up(cur, t.align);
            type_id[name] = (ll)types.size();
            types.push_back(t);
            cout << t.size << ' ' << t.align << '\n';
        } else if (op == 2) {
            string type_name, name;
            cin >> type_name >> name;
            ll tid = type_id[type_name];

            ElementInfo e;
            e.type_name = type_name;
            e.name = name;
            e.start = align_up(memory_end, types[tid].align);
            memory_end = e.start + types[tid].size;

            element_id[name] = (ll)elements.size();
            elements.push_back(e);
            cout << e.start << '\n';
        } else if (op == 3) {
            string path;
            cin >> path;
            vector<string> parts = split_path(path);

            ll eid = element_id[parts[0]];
            ll addr = elements[eid].start;
            string cur_type = elements[eid].type_name;
            for (size_t i = 1; i < parts.size(); i++) {
                ll tid = type_id[cur_type];
                ll mid = types[tid].member_id[parts[i]];
                MemberInfo member = types[tid].members[mid];
                addr += member.offset;
                cur_type = member.type_name;
            }
            cout << addr << '\n';
        } else {
            ll addr;
            cin >> addr;
            string answer;
            bool ok = false;
            for (size_t i = 0; i < elements.size(); i++) {
                ll tid = type_id[elements[i].type_name];
                ll l = elements[i].start;
                ll r = l + types[tid].size;
                if (l <= addr && addr < r) {
                    ok = find_addr_in_type(tid, l, addr, elements[i].name, answer);
                    break;
                }
            }
            if (ok) cout << answer << '\n';
            else cout << "ERR\n";
        }
    }

    return 0;
}
