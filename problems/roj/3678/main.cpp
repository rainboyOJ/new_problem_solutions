#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Member {
    string type;
    string name;
    long long offset;
};

struct Type {
    long long size;
    long long align;
    vector<Member> members;
    map<string, int> name_to_index;
};

struct Variable {
    string type;
    string name;
    long long addr;
};

map<string, Type> types;
vector<Variable> vars;
map<string, int> var_name_to_index;

vector<string> split(const string& s, char delim) {
    vector<string> res;
    string item;
    for (char c : s) {
        if (c == delim) {
            res.push_back(item);
            item = "";
        } else {
            item += c;
        }
    }
    res.push_back(item);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    types["byte"] = {1, 1, {}, {}};
    types["short"] = {2, 2, {}, {}};
    types["int"] = {4, 4, {}, {}};
    types["long"] = {8, 8, {}, {}};

    int n;
    if (!(cin >> n)) return 0;

    while (n--) {
        int op;
        cin >> op;
        if (op == 1) {
            string name;
            int k;
            cin >> name >> k;
            Type t;
            t.align = 0;
            long long current_offset = 0;
            for (int i = 0; i < k; ++i) {
                string type_name, member_name;
                cin >> type_name >> member_name;
                Type& member_type = types[type_name];
                t.align = max(t.align, member_type.align);
                current_offset = (current_offset + member_type.align - 1) / member_type.align * member_type.align;
                t.members.push_back({type_name, member_name, current_offset});
                t.name_to_index[member_name] = i;
                current_offset += member_type.size;
            }
            t.size = (current_offset + t.align - 1) / t.align * t.align;
            types[name] = t;
            cout << t.size << " " << t.align << "\n";
        } else if (op == 2) {
            string type_name, var_name;
            cin >> type_name >> var_name;
            Type& t = types[type_name];
            long long start_addr = 0;
            if (!vars.empty()) {
                Variable& last_var = vars.back();
                Type& last_type = types[last_var.type];
                long long next_avail = last_var.addr + last_type.size;
                start_addr = (next_avail + t.align - 1) / t.align * t.align;
            }
            vars.push_back({type_name, var_name, start_addr});
            var_name_to_index[var_name] = (int)vars.size() - 1;
            cout << start_addr << "\n";
        } else if (op == 3) {
            string path;
            cin >> path;
            vector<string> parts = split(path, '.');
            int var_idx = var_name_to_index[parts[0]];
            long long ans = vars[var_idx].addr;
            string curr_type = vars[var_idx].type;
            for (size_t i = 1; i < parts.size(); ++i) {
                Type& t = types[curr_type];
                int member_idx = t.name_to_index[parts[i]];
                ans += t.members[member_idx].offset;
                curr_type = t.members[member_idx].type;
            }
            cout << ans << "\n";
        } else if (op == 4) {
            long long addr;
            cin >> addr;
            int found_var_idx = -1;
            for (int i = 0; i < (int)vars.size(); ++i) {
                if (addr >= vars[i].addr && addr < vars[i].addr + types[vars[i].type].size) {
                    found_var_idx = i;
                    break;
                }
            }
            if (found_var_idx == -1) {
                cout << "ERR\n";
                continue;
            }
            string res = vars[found_var_idx].name;
            string curr_type = vars[found_var_idx].type;
            long long rem_addr = addr - vars[found_var_idx].addr;
            bool ok = true;
            while (types[curr_type].members.size() > 0) {
                Type& t = types[curr_type];
                int found_member_idx = -1;
                for (int i = (int)t.members.size() - 1; i >= 0; --i) {
                    if (rem_addr >= t.members[i].offset) {
                        found_member_idx = i;
                        break;
                    }
                }
                if (found_member_idx == -1) {
                    ok = false;
                    break;
                }
                Member& m = t.members[found_member_idx];
                if (rem_addr < m.offset + types[m.type].size) {
                    res += "." + m.name;
                    rem_addr -= m.offset;
                    curr_type = m.type;
                } else {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                cout << res << "\n";
            } else {
                cout << "ERR\n";
            }
        }
    }
    return 0;
}
