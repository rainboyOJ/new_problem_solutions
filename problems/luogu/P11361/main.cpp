#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Block {
    int left, right;
    int count_one;
};

int T, n;
string s1, s2, t1, t2;
Block block_a[MAXN], block_b[MAXN];
int cnt_a, cnt_b;

void build_blocks(const string &s, const string &t, Block block[], int &cnt, bool flip_bit) {
    cnt = 0;
    int i = 0;

    while (i < n) {
        if (t[i] == '0') {
            int value = s[i] - '0';
            if (flip_bit) {
                value ^= 1;
            }

            cnt++;
            block[cnt].left = i + 1;
            block[cnt].right = i + 1;
            block[cnt].count_one = value;
            i++;
        } else {
            int j = i;
            int count_one = 0;
            while (j < n && t[j] == '1') {
                int value = s[j] - '0';
                if (flip_bit) {
                    value ^= 1;
                }
                count_one += value;
                j++;
            }

            cnt++;
            block[cnt].left = i + 1;
            block[cnt].right = j;
            block[cnt].count_one = count_one;
            i = j;
        }
    }
}

int count_same_one(bool flip_bit) {
    build_blocks(s1, t1, block_a, cnt_a, flip_bit);
    build_blocks(s2, t2, block_b, cnt_b, flip_bit);

    int i = 1, j = 1;
    int rest_a = block_a[1].count_one;
    int rest_b = block_b[1].count_one;
    int ans = 0;

    while (i <= cnt_a && j <= cnt_b) {
        int left = max(block_a[i].left, block_b[j].left);
        int right = min(block_a[i].right, block_b[j].right);

        if (left <= right) {
            int len = right - left + 1;
            int take = min(len, min(rest_a, rest_b));
            ans += take;
            rest_a -= take;
            rest_b -= take;
        }

        if (block_a[i].right < block_b[j].right) {
            i++;
            if (i <= cnt_a) {
                rest_a = block_a[i].count_one;
            }
        } else if (block_a[i].right > block_b[j].right) {
            j++;
            if (j <= cnt_b) {
                rest_b = block_b[j].count_one;
            }
        } else {
            i++;
            j++;
            if (i <= cnt_a) {
                rest_a = block_a[i].count_one;
            }
            if (j <= cnt_b) {
                rest_b = block_b[j].count_one;
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        cin >> s1 >> s2 >> t1 >> t2;

        int same_one = count_same_one(false);
        int same_zero = count_same_one(true);

        cout << same_one + same_zero << '\n';
    }

    return 0;
}
