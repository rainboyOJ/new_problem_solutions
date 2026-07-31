#include <cstring>
#include <iostream>

char val[][20] = { "Scissors", "Paper", "Rock" };

int n;
char str1[20];
char str2[20];

int main(){
    std::cin >> n;
    int i,j;
    for (i=1;i<=n;i++){
        std::cin >> str1;
        std::cin >> str2;
        int idx_1,idx_2;
        for (j=0;j<3;j++){
            if( strcmp(str1,val[j]) == 0)
                idx_1 = j;
            if( strcmp(str2,val[j]) == 0)
                idx_2 = j;
        }
        if( idx_1 == idx_2)
            std::cout << "Tie\n";
        //else if ( (idx_1 == 0 && idx_2 == 1) || (idx_1 == 1 && idx_2 == 2) || (idx_1 == 2 && idx_2 == 0))
        else if( (idx_1+1) % 3 == idx_2 )
            std::cout << "Player1\n";
        else
            std::cout << "Player2\n";

    }
    return 0;
}
