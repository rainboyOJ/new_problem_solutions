#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100005;

// 存储原始输入的牌，方便后续处理
struct CardInput {
    int suit, num;
};
vector<CardInput> inputs;

// 离散化数组：存储所有出现过的花色
vector<int> all_suits;

// 核心容器：piles[i] 存储第 i 种花色下的所有数字
// 此时 i 的范围是 0 ~ N，不再是 10^9
vector<int> piles[N]; 

int n;

// --- 离散化辅助函数 ---
// 传入原始花色，返回离散化后的 ID (0, 1, 2...)
int get_suit_id(int original_suit) {
    // lower_bound 查找第一个 >= x 的位置
    return lower_bound(all_suits.begin(), all_suits.end(), original_suit) - all_suits.begin();
}

// --- 核心逻辑 (和之前一样) ---
int solve_suit(vector<int>& v) {
    if (v.empty()) return 0;
    
    // 1. 排序
    sort(v.begin(), v.end());
    // 2. 去重
    v.erase(unique(v.begin(), v.end()), v.end());
    
    int max_len = 0;
    
    // 3. 遍历 + upper_bound
    for (int i = 0; i < v.size(); i++) {
        // 目标：找到以 v[i] 为起点，数值在 [v[i], v[i] + n - 1] 范围内的最远位置
        // 注意：这里 v[i] + n - 1 可能会超过 int 范围，但这题 max val 是 10^9，加 10^5 不会爆 int
        int end_limit = v[i] + n - 1;
        
        // 找第一个 大于 end_limit 的位置
        auto it = upper_bound(v.begin(), v.end(), end_limit);
        
        int count = (it - v.begin()) - i;
        max_len = max(max_len, count);
    }
    
    return max_len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n)) return 0;
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    // 1. 读入数据并收集花色
    inputs.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> inputs[i].suit >> inputs[i].num;
        all_suits.push_back(inputs[i].suit);
    }

    // 2. 离散化处理 (Sort + Unique)
    sort(all_suits.begin(), all_suits.end());
    all_suits.erase(unique(all_suits.begin(), all_suits.end()), all_suits.end());

    // 3. 数据分发 (使用离散化后的 ID)
    for (int i = 0; i < n; i++) {
        // 将原始花色转为小整数 ID
        int id = get_suit_id(inputs[i].suit);
        // 放入对应的桶
        piles[id].push_back(inputs[i].num);
    }

    // 4. 计算答案
    int max_keep = 0;
    // all_suits.size() 就是实际有多少种不同的花色
    for (int i = 0; i < all_suits.size(); i++) {
        max_keep = max(max_keep, solve_suit(piles[i]));
    }

    cout << n - max_keep << endl;

    return 0;
}
