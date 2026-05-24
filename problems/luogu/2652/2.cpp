#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100005;

struct Card {
    int suit;
    int num;

    // 重载小于号：优先按花色排，花色相同按数字排
    bool operator<(const Card& other) const {
        if (suit != other.suit) return suit < other.suit;
        return num < other.num;
    }
};

Card cards[N];
int n;

// 复用的临时容器，避免反复申请内存
vector<int> cur_nums;

// 核心计算函数 (对当前这一种花色进行处理)
int solve() {
    if (cur_nums.empty()) return 0;
    
    // 注意：因为外部 cards 已经排过序了，
    // 所以 push 进来的数字天然是有序的，不需要再 sort！
    
    // 1. 去重
    cur_nums.erase(unique(cur_nums.begin(), cur_nums.end()), cur_nums.end());
    
    int max_len = 0;
    
    // 2. 二分查找逻辑
    for (int i = 0; i < cur_nums.size(); i++) {
        int end_limit = cur_nums[i] + n - 1;
        
        // 找到第一个大于 end_limit 的位置
        auto it = upper_bound(cur_nums.begin(), cur_nums.end(), end_limit);
        
        int count = (it - cur_nums.begin()) - i;
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

    for (int i = 0; i < n; i++) {
        cin >> cards[i].suit >> cards[i].num;
    }

    // 1. 全局排序 (关键步骤)
    // 这样相同花色的牌会聚在一起，且内部有序
    sort(cards, cards + n);

    int max_keep = 0;

    // 2. 线性扫描，按花色分组处理
    for (int i = 0; i < n; ) {
        int j = i;
        
        // 找到当前花色的右边界 j (使得 cards[i...j-1] 是同一种花色)
        while (j < n && cards[j].suit == cards[i].suit) {
            j++;
        }
        
        // 此时 [i, j) 区间内全是同一种花色的牌
        
        // --- 提取数据 ---
        cur_nums.clear(); // 清空容器
        for (int k = i; k < j; k++) {
            cur_nums.push_back(cards[k].num);
        }
        
        // --- 处理这一组 ---
        max_keep = max(max_keep, solve());
        
        // --- 移动指针 ---
        i = j; //哪怕 j 越界也没关系，循环条件会终止
    }

    cout << n - max_keep << endl;

    return 0;
}
