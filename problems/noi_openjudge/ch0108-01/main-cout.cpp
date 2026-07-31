#include <iostream>

int a[10][10];

int main(){
    int i,j;

    for (i=1;i<=5;i++){
        for (j=1;j<=5;j++){
            std::cin >> a[i][j];
        }
    }
    int t1,t2;
    std::cin >> t1 >> t2;
    for (i=1;i<=5;i++){
        int t;
        t = a[t1][i];
        a[t1][i] = a[t2][i];
        a[t2][i] = t;
    }

    for (i=1;i<=5;i++){
        for (j=1;j<=5;j++){
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
