#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int ans;
int n;

struct people {
    int ship;
    int country;
} ;
int p_cnt;
people p[maxn];
int ship_time[maxn];

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
            cin >> p[p_cnt].country;
            p[p_cnt].ship = i;
        }
    }
}

int find_start_ship(int ship_id) {
    int end_time = ship_time[ship_id];
    int start_time = end_time - 86400;

    int ret = ship_id;
    for(int i = ship_id ;i >=1;i--) {
        if( ship_time[i]  > start_time  )
        {
            ret = i;
        }
        else break;
    }
    return ret;
}

int count_country(int start_id,int end_id) {
    int cnt = 0;

    memset(bucket,0,sizeof(bucket) );

    for(int i = 1;i <= p_cnt ;++i ) // i: 1->p_cnt
    {
        if(   p[i].ship < start_id  ) continue;
        else if( p[i].ship > end_id) break;
        else {
            bucket[ p[i].country ]++;
        }
    }

    for(int i = 1;i <= 1000 ;++i ) // i: 1->1000
    {
        if( bucket[i] ) cnt++;
    }

    return cnt;
}


int main (int argc, char *argv[]) {
    init();
    // work
    // step1 : 扫描 每个船
    for(int i =1;i<=n;i++) {

        ans = 0;

        //
        int start_ship = find_start_ship(i);
        ans = count_country(start_ship,i);
        cout << ans << endl;
    }
    
    return 0;
}
