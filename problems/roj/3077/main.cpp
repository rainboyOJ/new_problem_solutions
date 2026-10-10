#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int n;
string s1, s2, s3;
int val[26];
bool used[26];
int order[26];
int order_cnt = 0;

bool check() {
    int carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        int v1 = val[s1[i] - 'A'];
        int v2 = val[s2[i] - 'A'];
        int v3 = val[s3[i] - 'A'];
        if (v1 != -1 && v2 != -1 && v3 != -1) {
            if (carry != -1) {
                int sum = v1 + v2 + carry;
                if (sum % n != v3) return false;
                carry = sum / n;
            } else {
                if ((v1 + v2) % n != v3 && (v1 + v2 + 1) % n != v3) {
                    return false;
                }
            }
        } else {
            carry = -1;
            if (v1 != -1 && v2 != -1) {
                int t1 = (v1 + v2) % n;
                int t2 = (v1 + v2 + 1) % n;
                if (used[t1] && used[t2]) {
                    return false;
                }
            } else if (v1 != -1 && v3 != -1) {
                int t1 = (v3 - v1 + n) % n;
                int t2 = (v3 - v1 - 1 + n) % n;
                if (used[t1] && used[t2]) {
                    return false;
                }
            } else if (v2 != -1 && v3 != -1) {
                int t1 = (v3 - v2 + n) % n;
                int t2 = (v3 - v2 - 1 + n) % n;
                if (used[t1] && used[t2]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 模拟完整加法验证，严格校验所有进位
bool verify() {
    int carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        int v1 = val[s1[i] - 'A'];
        int v2 = val[s2[i] - 'A'];
        int v3 = val[s3[i] - 'A'];
        int sum = v1 + v2 + carry;
        if (sum % n != v3) return false;
        carry = sum / n;
    }
    return carry == 0;
}

bool dfs(int u) {
    if (u == n) {
        return verify();
    }
    if (!check()) return false;
    
    int c = order[u];
    for (int i = n - 1; i >= 0; --i) {
        if (!used[i]) {
            val[c] = i;
            used[i] = true;
            if (dfs(u + 1)) return true;
            used[i] = false;
            val[c] = -1;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    cin >> s1 >> s2 >> s3;

    for (int i = 0; i < n; ++i) {
        val[i] = -1;
        used[i] = false;
    }

    bool vis_order[26] = {false};
    for (int i = n - 1; i >= 0; --i) {
        if (!vis_order[s1[i] - 'A']) {
            vis_order[s1[i] - 'A'] = true;
            order[order_cnt++] = s1[i] - 'A';
        }
        if (!vis_order[s2[i] - 'A']) {
            vis_order[s2[i] - 'A'] = true;
            order[order_cnt++] = s2[i] - 'A';
        }
        if (!vis_order[s3[i] - 'A']) {
            vis_order[s3[i] - 'A'] = true;
            order[order_cnt++] = s3[i] - 'A';
        }
    }

    dfs(0);

    for (int i = 0; i < n; ++i) {
        cout << val[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}
