#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, artefactsCounter{0};
    std::cin >> n;
    std::vector<std::vector<int>> city(n, std::vector<int>(n));
    std::vector<std::vector<int>> artefacts(n, std::vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cin >> city[i][j];
        }
    }

    artefacts[0][0] = city[0][0];

    for(int k = 1; k < n; k++){
        for(int i = 0; i <= k; i++){
            if(i == k){
                artefacts[i][k] = std::max(artefacts[i][k-1], artefacts[i-1][k]) + city[i][k];
            }else if(i-1 < 0){
                artefacts[i][k] = artefacts[i][k-1] + city[i][k];
                artefacts[k][i] = artefacts[k-1][i] + city[k][i];
            }else{
                artefacts[i][k] = std::max(artefacts[i-1][k], artefacts[i][k-1]) + city[i][k];
                artefacts[k][i] = std::max(artefacts[k-1][i], artefacts[k][i-1]) + city[k][i];
            }
        }
    }

    artefactsCounter += artefacts[n-1][n-1];
    city[n-1][n-1] = 0;
    city[0][0] = 0;

    for(int k = 0, i = n-1, j = n-1; k < 2*(n-1); k++){
        city[i][j] = 0;
        if(i-1 < 0){
            j--;
        }else if(j-1 < 0){
            i--;
        }else if(artefacts[i-1][j] < artefacts[i][j-1]){
            j--;
        }else{
            i--;
        }    
    }

    artefacts[0][0] = city[0][0];

    for(int k = 1; k < n; k++){
        for(int i = 0; i <= k; i++){
            if(i == k){
                artefacts[i][k] = std::max(artefacts[i][k-1], artefacts[i-1][k]) + city[i][k];
            }else if(i-1 < 0){
                artefacts[i][k] = artefacts[i][k-1] + city[i][k];
                artefacts[k][i] = artefacts[k-1][i] + city[k][i];
            }else{
                artefacts[i][k] = std::max(artefacts[i-1][k], artefacts[i][k-1]) + city[i][k];
                artefacts[k][i] = std::max(artefacts[k-1][i], artefacts[k][i-1]) + city[k][i];
            }
        }
    }

    artefactsCounter += artefacts[n-1][n-1];

    std::cout << artefactsCounter;


    return 0;
}