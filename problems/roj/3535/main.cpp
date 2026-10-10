/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
int cola[30], colb[30], colc[30];   // 每列三个字母（低位在前）
int val[30];      // 字母 -> 数字，-1 未定
bool used[30];
int ans[30];

// 给本列未定字母 letters 分配数字，验证等式 Σ coeff[l]*val[l] == rhs 后递归下一列
bool assign_letters(const vector<int>& letters, const int coeff[30], int idx, int rhs, int pos, int carry_in);

// 从最高位列 pos 向低位搜；carry_out 是本列出进位（最高位固定 0）
bool dfs(int pos, int carry_out) {
    if (pos < 0) {
        for (int i = 0; i < n; i++) ans[i] = val[i];
        return true;
    }
    int a = cola[pos], b = colb[pos], c = colc[pos];
    int va = val[a], vb = val[b], vc = val[c];
    int nco = n * carry_out;
    int lo = 0;
    int hi = (pos == 0) ? 0 : 1;

    // 三个字母都已定：等式必须对某个入进位成立
    if (va >= 0 && vb >= 0 && vc >= 0) {
        int base = va + vb - vc;
        for (int carry_in = lo; carry_in <= hi; carry_in++)
            if (base == nco - carry_in && dfs(pos - 1, carry_in)) return true;
        return false;
    }

    // 本列未定字母的系数；已定字母折进常数项 base
    int coeff[30];
    memset(coeff, 0, sizeof(coeff));
    bool appear[30] = {false};
    int base = 0;
    if (va < 0) { coeff[a] += 1; appear[a] = true; } else base += va;
    if (vb < 0) { coeff[b] += 1; appear[b] = true; } else base += vb;
    if (vc < 0) { coeff[c] -= 1; appear[c] = true; } else base -= vc;

    vector<int> letters;
    for (int l = 0; l < n; l++)
        if (appear[l]) letters.push_back(l);

    for (int carry_in = lo; carry_in <= hi; carry_in++) {
        int rhs = nco - carry_in - base;
        if (assign_letters(letters, coeff, 0, rhs, pos, carry_in)) return true;
    }
    return false;
}

bool assign_letters(const vector<int>& letters, const int coeff[30], int idx, int rhs, int pos, int carry_in) {
    if (idx == (int)letters.size()) {
        int got = 0;
        for (size_t li = 0; li < letters.size(); li++)
            got += coeff[letters[li]] * val[letters[li]];
        if (got == rhs) return dfs(pos - 1, carry_in);
        return false;
    }
    int l = letters[idx];
    for (int d = 0; d < n; d++) {
        if (used[d]) continue;
        used[d] = true;
        val[l] = d;
        if (assign_letters(letters, coeff, idx + 1, rhs, pos, carry_in)) return true;
        val[l] = -1;
        used[d] = false;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    reverse(s3.begin(), s3.end());
    for (int i = 0; i < n; i++) {
        cola[i] = s1[i] - 'A';
        colb[i] = s2[i] - 'A';
        colc[i] = s3[i] - 'A';
    }
    for (int i = 0; i < n; i++) { val[i] = -1; used[i] = false; }
    dfs(n - 1, 0);
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
