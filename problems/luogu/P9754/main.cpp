/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:45
 * update_at: 2026-10-01 22:45
 */
// main.cpp：模拟结构体类型定义、元素定义、路径访问和地址反查。
// 核心思路：按定义顺序计算偏移量和对齐，维护类型表和元素表，支持四种操作。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 成员信息：类型名、名称、在结构体内的偏移量。
struct MemberInfo {
    string type_name;
    string name;
    ll offset;
};

// 类型信息：名称、大小、对齐要求、是否基本类型、成员列表。
struct TypeInfo {
    string name;
    ll size;
    ll align;
    bool is_basic;
    vector<MemberInfo> members;
    map<string, ll> member_id; // 成员名 -> 在 members 中的下标
};

// 元素信息：类型名、名称、起始地址。
struct ElementInfo {
    string type_name;
    string name;
    ll start;
};

vector<TypeInfo> types;
vector<ElementInfo> elements;
map<string, ll> type_id;    // 类型名 -> 在 types 中的下标
map<string, ll> element_id; // 元素名 -> 在 elements 中的下标
ll memory_end;              // 当前已分配内存的末尾地址

// 向上对齐到 a 的整数倍。
ll align_up(ll x, ll a) {
    if (x % a == 0) {
        return x;
    }
    return x + (a - x % a);
}

// 注册一个基本类型。
void add_basic_type(const string &name, ll size) {
    TypeInfo t;
    t.name = name;
    t.size = size;
    t.align = size;
    t.is_basic = true;
    type_id[name] = (ll)types.size();
    types.push_back(t);
}

// 把 "a.b.c" 形式的路径按 '.' 拆分成列表。
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

// 操作 1：定义结构体类型，输出大小和对齐要求。
void define_struct_type() {
    string name;
    ll k;
    cin >> name >> k;

    TypeInfo t;
    t.name = name;
    t.size = 0;
    t.align = 1;
    t.is_basic = false;

    ll cur = 0; // 当前偏移量
    for (ll i = 0; i < k; i++) {
        string type_name, member_name;
        cin >> type_name >> member_name;
        ll tid = type_id[type_name];

        cur = align_up(cur, types[tid].align); // 对齐到成员类型的对齐要求

        MemberInfo member;
        member.type_name = type_name;
        member.name = member_name;
        member.offset = cur;
        t.member_id[member_name] = (ll)t.members.size();
        t.members.push_back(member);

        cur += types[tid].size;
        t.align = max(t.align, types[tid].align);
    }

    t.size = align_up(cur, t.align); // 结构体大小对齐到自身对齐要求
    type_id[name] = (ll)types.size();
    types.push_back(t);

    cout << t.size << ' ' << t.align << '\n';
}

// 操作 2：定义元素，输出起始地址。
void define_element() {
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
}

// 操作 3：按路径访问元素，输出最内层成员的起始地址。
void query_path() {
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
}

// 在类型 tid 的内存范围内递归查找 addr，找到则把路径写入 answer。
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
        ll child_end = child_base + types[child_tid].size;
        if (child_base <= addr && addr < child_end) {
            return find_addr_in_type(child_tid, child_base, addr, path + "." + member.name, answer);
        }
    }
    return false;
}

// 操作 4：按地址反查基本类型元素，找不到输出 ERR。
void query_address() {
    ll addr;
    cin >> addr;

    string answer;
    for (size_t i = 0; i < elements.size(); i++) {
        ll tid = type_id[elements[i].type_name];
        ll l = elements[i].start;
        ll r = l + types[tid].size;
        if (l <= addr && addr < r) {
            if (find_addr_in_type(tid, l, addr, elements[i].name, answer)) {
                cout << answer << '\n';
            } else {
                cout << "ERR\n";
            }
            return;
        }
    }

    cout << "ERR\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 注册四种基本类型。
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
            define_struct_type();
        } else if (op == 2) {
            define_element();
        } else if (op == 3) {
            query_path();
        } else {
            query_address();
        }
    }

    return 0;
}
