#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int n, m, k_val, mod;
int beat[20];
int tot = 0;
vector<string> ans;
map<string, int> vis;

void dfs(string s, int len) {
    if (vis[s] == 0) {
        vis[s] = 1;
        ans.push_back(s);
        tot++;
    } else {
        return;
    }
    if (len == n) return;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            string t = s;
            char c = '0';
            for (int j = 0; j < i; j++) {
                c = max(c, s[j]);
            }
            t[i] = c + 1;
            dfs(t, len + 1);
        }
    }
}

string S[120000];
map<string, int> ID;
int num = 0;
long long cnt[120000];

void init() {
    for (int i = 0; i < tot; i++) {
        string s = ans[i];
        char c = '0';
        for (int j = 0; j < n; j++) {
            if (s[j] == '0') {
                s[j] = c + 1;
                c++;
            } else {
                c = max(c, s[j]);
            }
        }
        c = '0';
        for (int j = 0; j < n; j++) {
            c = max(c, s[j]);
        }
        if (c >= '0' + k_val) {
            S[++num] = ans[i];
            ID[ans[i]] = num;
        }
    }

    for (int i = 1; i <= num; i++) {
        cnt[i] = 0;
        for (int j = 0; j < n; j++) {
            if (S[i][j] != '0') {
                cnt[i] |= (1 << j);
            }
        }
    }
}

long long C[550][550];
long long fact[550];

void init2() {
    fact[0] = 1;
    for (int i = 1; i <= 530; i++) fact[i] = fact[i - 1] * i % mod;
    C[0][0] = 1;
    for (int i = 1; i <= 530; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || i == 1) C[i][j] = 1;
            else {
                C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
                C[i][j] %= mod;
            }
        }
    }
}

void add(long long &x, long long y) {
    x = (x + y) % mod;
}

long long dp[17][120000];

void modify(string &s, int pos) {
    char c = '0';
    for (int i = 0; i < pos; i++) c = max(c, s[i]);
    s[pos] = c + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (!(cin >> n >> m >> k_val >> mod)) return 0;
    
    for (int i = 0; i < m; i++) cin >> beat[i];
    sort(beat, beat + m);
    
    string start_s = "";
    for (int i = 1; i <= n; i++) start_s += '0';
    
    dfs(start_s, 0);
    init();
    init2();
    
    dp[0][1] = 1; // Start with the first valid string in S, S[1] should be '00...0' if k <= 0 but actually start string might just be '00..0'.
                  // Wait, ID["00...0"] might not be 1. Let's find ID of "0...0".
    
    // According to std.cpp, dp[0][1]=1 starts assuming S[1] is the initial string.
    // Let's make sure ID["0...0"] is 1 or something.
    int init_id = ID[start_s];
    if (init_id == 0) { // Should not happen if k<=n, but maybe k limits it.
        // If k requires more, it still processes start_s, let's fix it by exactly following std.cpp:
        // Wait, the std.cpp just says dp[0][1]=1, and S is filled 1-indexed. S[1] might not be start_s if start_s is filtered out.
        // Actually, start_s (all zeros) has c='0' after filling? 
        // Let's look at init():
        // s=ans[i] ("000" for example)
        // c='0'; for j=0..n if s[j]=='0' s[j]=c+1, c++; => s becomes "123"
        // c='0'; for j=0..n c=max(c,s[j]) => c='3'
        // if c>='0'+k => '3'>='0'+k => include.
        // Since max possible is n, if k<=n, "000" ALWAYS becomes "123" and gives max 'n'. 
        // So ans[0] (which is "0...0") is ALWAYS included in S and will be S[1].
    }
    
    dp[0][1] = 1;
    
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= num; j++) {
            if (dp[i][j]) {
                add(dp[i + 1][j], dp[i][j]);
                string now = S[j];
                for (int l = 0; l < n; l++) {
                    if (now[l] == '0' && beat[i] >= (cnt[j] + (1 << l) + 1)) {
                        string nxt = now;
                        modify(nxt, l);
                        int next_id = ID[nxt];
                        if (next_id > 0) { // Just in case, it should be valid
                            long long ways = dp[i][j] * C[beat[i] - cnt[j] - 2][(1 << l) - 1] % mod;
                            ways = ways * fact[1 << l] % mod;
                            add(dp[i + 1][next_id], ways);
                        }
                    }
                }
            }
        }
    }
    
    long long ans_val = 0;
    for (int j = 1; j <= num; j++) {
        if (cnt[j] == ((1LL << n) - 1)) {
            add(ans_val, dp[m][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        ans_val = (ans_val * 2) % mod;
    }
    
    cout << ans_val << "\n";
    return 0;
}
