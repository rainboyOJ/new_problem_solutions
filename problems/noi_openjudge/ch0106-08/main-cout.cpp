#include <iostream>

int n,na,nb;
int a[105],b[105];

int main(){
    std::cin >> n >> na >> nb;
    int i,j;
    for (i=1;i<=na;i++){
        std::cin >> a[i];
    }

    int idx = 1;
    for(i=na+1;i<=n;i++){
        a[i] = a[idx];
        idx++;
    }
    for (i=1;i<=nb;i++){
        std::cin >> b[i];
    }

    idx = 1;
    for(i=nb+1;i<=n;i++){
        b[i] = b[idx];
        idx++;
    }
    int win_a = 0,win_b =0;
    for(i=1;i<=n;i++){
        if( (a[i] == 0 && b[i] == 2) || (a[i] == 2 && b[i] == 5) || (a[i] == 5 && b[i] == 0 ))
            win_a++;
        else if( (b[i] == 0 && a[i] == 2) || (b[i] == 2 && a[i] == 5) || (b[i] == 5 && a[i] == 0 ))
            win_b++;
    }
    if( win_a == win_b)
        std::cout << "draw";
    else if( win_a > win_b)
        std::cout << "A";
    else 
        std::cout << "B";
    return 0;
}
