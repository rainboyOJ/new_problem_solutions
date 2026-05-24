#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 定义结构体存储节目的开始和结束时间
struct Show {
    int start;
    int end;
};

// 比较函数：按结束时间从小到大排序
// 如果结束时间相同，怎么排都可以，这里默认按结束时间升序
bool compareShows(const Show &a, const Show &b) {
    return a.end < b.end;
}

int main() {
    int n;
    // 循环处理每个测试实例，直到 n=0
    while (cin >> n && n != 0) {
        vector<Show> shows(n);
        for (int i = 0; i < n; i++) {
            cin >> shows[i].start >> shows[i].end;
        }

        // 1. 贪心策略的核心：按结束时间排序
        sort(shows.begin(), shows.end(), compareShows);

        // 2. 选择第一个结束最早的节目
        int count = 1;
        int last_end = shows[0].end;

        // 3. 遍历剩下的节目
        for (int i = 1; i < n; i++) {
            // 如果当前节目的开始时间 >= 上一个节目的结束时间
            if (shows[i].start >= last_end) {
                count++;
                last_end = shows[i].end; // 更新结束时间
            }
        }

        cout << count << endl;
    }
    return 0;
}
