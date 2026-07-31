#include <iostream>

/* 对差值进行记数 ,a[1] = 1*/
int cnt[3005] = {0};

int main(){
    int n;
    std::cin >> n;
    int i;
    int a,b;
    std::cin >> a;
    for (i=2;i<=n;i++){
        std::cin >> b;
        int cha = b - a;
        if( cha < 0)
            cha = -cha;
        cnt[cha]++;
        a = b;
    }

    for(i=1;i<=n-1;i++){
        if( cnt[i] != 1){
            std::cout << "Not jolly";
            return 0;
        }
    }
    std::cout << "Jolly";
    return 0;
}
