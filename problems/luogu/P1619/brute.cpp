// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string s;

string extract_digits(const string &src) {
    string digits;
    for (char ch : src) {
        if (ch >= '0' && ch <= '9') {
            digits += ch;
        }
    }
    return digits;
}

string normalize_number_string(const string &digits) {
    int pos = 0;
    while (pos < (int) digits.size() && digits[pos] == '0') {
        pos++;
    }
    if (pos == (int) digits.size()) {
        return "0";
    }
    return digits.substr(pos);
}

bool is_too_large(const string &num) {
    const string LIMIT = "40000000";
    if ((int) num.size() > (int) LIMIT.size()) {
        return true;
    }
    if ((int) num.size() < (int) LIMIT.size()) {
        return false;
    }
    return num > LIMIT;
}

int string_to_int(const string &num) {
    int value = 0;
    for (char ch : num) {
        value = value * 10 + (ch - '0');
    }
    return value;
}

// 朴素素性判断：从 2 一直试到 n-1，只适合小数据对拍。
bool is_prime_bruteforce(int n) {
    if (n <= 1) {
        return false;
    }
    for (int d = 2; d < n; d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

string factorize_to_string(int n) {
    int x = n;
    string res = to_string(n) + "=";
    bool first = true;

    for (int p = 2; p <= x; p++) {
        if (x % p != 0) {
            continue;
        }
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        if (!first) {
            res += "*";
        }
        first = false;
        res += to_string(p) + "^" + to_string(cnt);
    }

    return res;
}

bool solve_one(const string &line) {
    string digits = extract_digits(line);
    if (digits.empty()) {
        return false;
    }

    string num = normalize_number_string(digits);

    if (is_too_large(num)) {
        cout << "Prime? No!\n";
        cout << "The number is too large!\n\n";
        return true;
    }

    int value = string_to_int(num);
    if (is_prime_bruteforce(value)) {
        cout << "Prime? Yes!\n\n";
        return true;
    }

    cout << "Prime? No!\n";
    if (value > 1) {
        cout << factorize_to_string(value) << '\n';
    }
    cout << '\n';
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "Enter the number=\n";
        if (!getline(cin, s)) {
            break;
        }
        if (!solve_one(s)) {
            break;
        }
    }

    return 0;
}
