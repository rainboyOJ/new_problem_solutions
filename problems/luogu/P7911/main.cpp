#include <bits/stdc++.h>
using namespace std;

int n;
map<string, int> server_id;

bool parse_token(const string &s, int &pos, int limit, char delim) {
    int n = (int) s.size();
    if (pos >= n || s[pos] < '0' || s[pos] > '9') {
        return false;
    }

    int start = pos;
    long long value = 0;
    while (pos < n && s[pos] >= '0' && s[pos] <= '9') {
        value = value * 10 + (s[pos] - '0');
        pos++;
    }

    if (pos - start > 1 && s[start] == '0') {
        return false;
    }
    if (value > limit) {
        return false;
    }
    if (pos >= n || s[pos] != delim) {
        return false;
    }

    pos++;
    return true;
}

bool parse_last_token(const string &s, int &pos, int limit) {
    int n = (int) s.size();
    if (pos >= n || s[pos] < '0' || s[pos] > '9') {
        return false;
    }

    int start = pos;
    long long value = 0;
    while (pos < n && s[pos] >= '0' && s[pos] <= '9') {
        value = value * 10 + (s[pos] - '0');
        pos++;
    }

    if (pos - start > 1 && s[start] == '0') {
        return false;
    }
    if (value > limit) {
        return false;
    }
    return pos == n;
}

bool valid_address(const string &s) {
    int pos = 0;
    if (!parse_token(s, pos, 255, '.')) return false;
    if (!parse_token(s, pos, 255, '.')) return false;
    if (!parse_token(s, pos, 255, '.')) return false;
    if (!parse_token(s, pos, 255, ':')) return false;
    if (!parse_last_token(s, pos, 65535)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string type, addr;
        cin >> type >> addr;

        if (!valid_address(addr)) {
            cout << "ERR\n";
            continue;
        }

        if (type == "Server") {
            if (server_id.count(addr)) {
                cout << "FAIL\n";
            }
            else {
                server_id[addr] = i;
                cout << "OK\n";
            }
        }
        else {
            if (server_id.count(addr)) {
                cout << server_id[addr] << '\n';
            }
            else {
                cout << "FAIL\n";
            }
        }
    }

    return 0;
}
