// main.cpp：模拟结构体类型定义、元素定义、路径访问和地址反查。
#include <bits/stdc++.h>
using namespace std;

struct MemberInfo {
    string type_name;
    string name;
    long long offset;
};

struct TypeInfo {
    string name;
    long long size;
    long long align;
    bool is_basic;
    vector<MemberInfo> members;
    map<string, int> member_id;
};

struct ElementInfo {
    string type_name;
    string name;
    long long start;
};

vector<TypeInfo> types;
vector<ElementInfo> elements;
map<string, int> type_id;
map<string, int> element_id;
long long memory_end;

long long align_up(long long x, long long a) {
    if (x % a == 0) {
        return x;
    }
    return x + (a - x % a);
}

void add_basic_type(const string &name, long long size) {
    TypeInfo t;
    t.name = name;
    t.size = size;
    t.align = size;
    t.is_basic = true;
    type_id[name] = (int)types.size();
    types.push_back(t);
}

vector<string> split_path(const string &s) {
    vector<string> result;
    string cur;
    for (int i = 0; i < (int)s.size(); i++) {
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

void define_struct_type() {
    string name;
    int k;
    cin >> name >> k;

    TypeInfo t;
    t.name = name;
    t.size = 0;
    t.align = 1;
    t.is_basic = false;

    long long cur = 0;
    for (int i = 0; i < k; i++) {
        string type_name, member_name;
        cin >> type_name >> member_name;
        int tid = type_id[type_name];

        cur = align_up(cur, types[tid].align);

        MemberInfo member;
        member.type_name = type_name;
        member.name = member_name;
        member.offset = cur;
        t.member_id[member_name] = (int)t.members.size();
        t.members.push_back(member);

        cur += types[tid].size;
        t.align = max(t.align, types[tid].align);
    }

    t.size = align_up(cur, t.align);
    type_id[name] = (int)types.size();
    types.push_back(t);

    cout << t.size << ' ' << t.align << '\n';
}

void define_element() {
    string type_name, name;
    cin >> type_name >> name;
    int tid = type_id[type_name];

    ElementInfo e;
    e.type_name = type_name;
    e.name = name;
    e.start = align_up(memory_end, types[tid].align);
    memory_end = e.start + types[tid].size;

    element_id[name] = (int)elements.size();
    elements.push_back(e);

    cout << e.start << '\n';
}

void query_path() {
    string path;
    cin >> path;
    vector<string> parts = split_path(path);

    int eid = element_id[parts[0]];
    long long addr = elements[eid].start;
    string cur_type = elements[eid].type_name;

    for (int i = 1; i < (int)parts.size(); i++) {
        int tid = type_id[cur_type];
        int mid = types[tid].member_id[parts[i]];
        MemberInfo member = types[tid].members[mid];
        addr += member.offset;
        cur_type = member.type_name;
    }

    cout << addr << '\n';
}

bool find_addr_in_type(int tid, long long base, long long addr, const string &path, string &answer) {
    if (types[tid].is_basic) {
        if (base <= addr && addr < base + types[tid].size) {
            answer = path;
            return true;
        }
        return false;
    }

    for (int i = 0; i < (int)types[tid].members.size(); i++) {
        MemberInfo member = types[tid].members[i];
        int child_tid = type_id[member.type_name];
        long long child_base = base + member.offset;
        long long child_end = child_base + types[child_tid].size;
        if (child_base <= addr && addr < child_end) {
            return find_addr_in_type(child_tid, child_base, addr, path + "." + member.name, answer);
        }
    }
    return false;
}

void query_address() {
    long long addr;
    cin >> addr;

    string answer;
    for (int i = 0; i < (int)elements.size(); i++) {
        int tid = type_id[elements[i].type_name];
        long long l = elements[i].start;
        long long r = l + types[tid].size;
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

    add_basic_type("byte", 1);
    add_basic_type("short", 2);
    add_basic_type("int", 4);
    add_basic_type("long", 8);

    int q;
    cin >> q;
    while (q--) {
        int op;
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
