#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6+5;
int ans;
int n;

struct people {
    int ship;
    int country;
} ;
int p_cnt;
people p[maxn];
int ship_time[maxn];
int ship_peo_start_pos[maxn]; //记录 ship i的人起始的位置 在 p[maxn]
int ship_peo_end_pos[maxn]; //记录 ship i的人终点的位置 在 p[maxn]


int pre = 1; //上一次的合法的船的范围的起始的id

int bucket[maxn];

void init() {
    cin >> n;
    
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        cin >> t;
        ship_time[i] = t;
        int m;
        std::cin >> m;
        for(int j = 1;j <= m ;++j ) // j: 1->m
        {
            p_cnt++;
            if( j == 1) {
                ship_peo_start_pos[i] = p_cnt;
            }
            if( j == m) {
                ship_peo_end_pos[i] = p_cnt;
            }
            cin >> p[p_cnt].country;
            p[p_cnt].ship = i;
        }
    }
}

int find_start_id(int pre,int now) {
    int end_time = ship_time[now];
    int start_time = ship_time[now] - 86400;

    for(int i = pre ; 1 ;i ++) {
        if( ship_time[i] > start_time) {
            return i;
        }
    }
    return 0;
}

// 写个注释给自己看,
void del_peo_on_ship(int s,int e) {

    for(int i = ship_peo_start_pos[s];i <= ship_peo_end_pos[e] ;++i ) // i: s->e
    {
        int country = p[i].country;
        bucket[country]--;
        if( bucket[country] == 0) {
            ans --;
        }
    }
}

void add_peo_on_ship(int ship) {
    for(int i = ship_peo_start_pos[ship] ;i <= ship_peo_end_pos[ship];i++) {
        int country = p[i].country;
        if( bucket[country] == 0) {
            ans++;
        }
        bucket[country]++;
    }
}



int main() {
    init();

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        // work

        //1 找到 合法的起始的新的 ship id
        int new_pre_id = find_start_id(pre,i);
        // std::cout << new_pre_id << "\n";

        //2. del 
        if( new_pre_id-1 >= pre)
            del_peo_on_ship(pre,new_pre_id-1);

        //3. add new people on ship i
        add_peo_on_ship(i);

        cout << ans << endl;

        // 
        // for(int i =1;i<=5;i++) {
        //     cout << bucket[i] << " ";
        // }
        // std::cout  << "-------\n";
        // std::cout  << "\n";
        // std::cout  << "\n";

        //4 . out ans
        pre = new_pre_id;
        
    }
    

    return 0;
}

