#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const ull BASE1 = 131;
const ull BASE2 = 13331;

struct HashKey {
    ull h1, h2;

    bool operator==(const HashKey &other) const {
        return h1 == other.h1 && h2 == other.h2;
    }

    bool operator<(const HashKey &other) const {
        if (h1 != other.h1) {
            return h1 < other.h1;
        }
        return h2 < other.h2;
    }
};

struct KeyHasher {
    size_t operator()(const HashKey &key) const {
        ull x = key.h1 * 1000003ULL;
        ull y = key.h2 * 1000033ULL;
        return (size_t)(x ^ (y << 1) ^ (y >> 3));
    }
};

int total_s, total_t, n, m;
vector<string> s_list, t_list;
vector<ull> pow1_base, pow2_base;

int char_value(char ch) {
    return (unsigned char)ch + 1;
}

void build_pow(int max_len) {
    pow1_base.assign(max_len + 1, 0);
    pow2_base.assign(max_len + 1, 0);
    pow1_base[0] = 1;
    pow2_base[0] = 1;
    for (int i = 1; i <= max_len; i++) {
        pow1_base[i] = pow1_base[i - 1] * BASE1;
        pow2_base[i] = pow2_base[i - 1] * BASE2;
    }
}

void build_prefix_hash(const string &s, vector<ull> &h1, vector<ull> &h2) {
    int len = (int)s.size();
    h1.assign(len + 1, 0);
    h2.assign(len + 1, 0);
    for (int i = 0; i < len; i++) {
        h1[i + 1] = h1[i] * BASE1 + char_value(s[i]);
        h2[i + 1] = h2[i] * BASE2 + char_value(s[i]);
    }
}

HashKey get_sub_hash(const vector<ull> &h1, const vector<ull> &h2, int l, int len) {
    HashKey res;
    res.h1 = h1[l + len] - h1[l] * pow1_base[len];
    res.h2 = h2[l + len] - h2[l] * pow2_base[len];
    return res;
}

HashKey hash_whole_string(const string &s) {
    ull h1 = 0, h2 = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        h1 = h1 * BASE1 + char_value(s[i]);
        h2 = h2 * BASE2 + char_value(s[i]);
    }
    return {h1, h2};
}

vector<int> prefix_function(const string &pat) {
    int len = (int)pat.size();
    vector<int> pi(len, 0);
    for (int i = 1; i < len; i++) {
        int j = pi[i - 1];
        while (j > 0 && pat[i] != pat[j]) {
            j = pi[j - 1];
        }
        if (pat[i] == pat[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

// 在 text 中寻找 pattern 的所有出现位置。
vector<int> kmp_match(const string &text, const string &pattern) {
    vector<int> result;
    if (pattern.empty()) {
        return result;
    }
    vector<int> pi = prefix_function(pattern);
    int j = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == (int)pattern.size()) {
            result.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> total_s >> total_t >> n >> m;
    s_list.resize(total_s);
    t_list.resize(total_t);
    for (int i = 0; i < total_s; i++) {
        cin >> s_list[i];
    }
    for (int i = 0; i < total_t; i++) {
        cin >> t_list[i];
    }

    int half = (n + m) / 2;
    int max_len = max(max(n, m), half * 2);
    build_pow(max_len);

    long long answer = 0;

    if (n >= m) {
        int d = n - half;

        unordered_map<HashKey, int, KeyHasher> t_count;
        t_count.reserve(total_t * 2 + 1);
        for (int i = 0; i < total_t; i++) {
            t_count[hash_whole_string(t_list[i])]++;
        }

        for (int i = 0; i < total_s; i++) {
            const string &a = s_list[i];
            string p = a.substr(0, half);
            string q = a.substr(half, d);
            string text = p + p;

            vector<ull> h1, h2;
            build_prefix_hash(text, h1, h2);

            vector<HashKey> cand;
            if (d == 0) {
                cand.reserve(half);
                for (int st = 0; st < half; st++) {
                    cand.push_back(get_sub_hash(h1, h2, st, m));
                }
            }
            else {
                vector<int> pos = kmp_match(text, q);
                cand.reserve(pos.size());
                for (int idx = 0; idx < (int)pos.size(); idx++) {
                    int st = pos[idx];
                    if (st < half) {
                        cand.push_back(get_sub_hash(h1, h2, st + d, m));
                    }
                }
            }

            sort(cand.begin(), cand.end());
            cand.erase(unique(cand.begin(), cand.end()), cand.end());
            for (int j = 0; j < (int)cand.size(); j++) {
                unordered_map<HashKey, int, KeyHasher>::iterator it = t_count.find(cand[j]);
                if (it != t_count.end()) {
                    answer += it->second;
                }
            }
        }
    }
    else {
        int e = half - n;

        unordered_map<HashKey, int, KeyHasher> s_count;
        s_count.reserve(total_s * 2 + 1);
        for (int i = 0; i < total_s; i++) {
            s_count[hash_whole_string(s_list[i])]++;
        }

        for (int i = 0; i < total_t; i++) {
            const string &b = t_list[i];
            string x = b.substr(0, e);
            string y = b.substr(e, half);
            string text = y + y;

            vector<ull> h1, h2;
            build_prefix_hash(text, h1, h2);

            vector<HashKey> cand;
            if (e == 0) {
                cand.reserve(half);
                for (int st = 0; st < half; st++) {
                    cand.push_back(get_sub_hash(h1, h2, st, n));
                }
            }
            else {
                vector<int> pos = kmp_match(text, x);
                cand.reserve(pos.size());
                for (int idx = 0; idx < (int)pos.size(); idx++) {
                    int st = pos[idx];
                    if (st >= n && st < n + half) {
                        cand.push_back(get_sub_hash(h1, h2, st - n, n));
                    }
                }
            }

            sort(cand.begin(), cand.end());
            cand.erase(unique(cand.begin(), cand.end()), cand.end());
            for (int j = 0; j < (int)cand.size(); j++) {
                unordered_map<HashKey, int, KeyHasher>::iterator it = s_count.find(cand[j]);
                if (it != s_count.end()) {
                    answer += it->second;
                }
            }
        }
    }

    cout << answer << '\n';

    return 0;
}
