#include <iostream>

int m,n;
int map[200][200];

bool is_ok(){
    int i,j;
    for (i=1;i<=n;i++){
        int cnt=0;
        for (j=1;j<=n;j++){
            if( map[i][j]) cnt++;
        }
        if( cnt % 2 != 0)
            return 0;
    }

    for (j=1;j<=n;j++){
        int cnt=0;
        for (i=1;i<=n;i++){
            if( map[i][j]) cnt++;
        }
        if( cnt % 2 != 0)
            return 0;

    }

    return 1;
}
int main(){
    std::cin >> n;
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            std::cin >> map[i][j];
        }
    }

    if( is_ok()){
        std::cout << "OK";
        return 0;
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            map[i][j] = !map[i][j];
            if( is_ok()){
                std::cout << i << " " << j << "\n";
                return 0;
            }
            map[i][j] = !map[i][j];
        }
    }
    std::cout << "Corrupt";

    return 0;
}
