#include <iostream>

const int n = 35;
int garden[n][n];

void findMinCostTrack(const int& n, const int& column, int& currentCost, int& minCost, bool* rowsStates, int* selectedRows, int* finalTrack){
    if(column == n || currentCost > minCost){
        if(currentCost < minCost){
            minCost = currentCost;
            for(int i = 0; i < n; i++){
                finalTrack[i] = selectedRows[i];
            }
        }
        return;
    }

    for(int i = 0; i < n; i++){
        if(!rowsStates[i]){
            rowsStates[i] = true;
            selectedRows[column] = i;
            currentCost += garden[i][column];
            findMinCostTrack(n, column + 1, currentCost, minCost, rowsStates, selectedRows, finalTrack);
            rowsStates[i] = false;
            currentCost -= garden[i][column];
        }
        
    }
}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int a, currentCost{0}, minCost{1001};
    std::cin >> a;
    bool rowsStates[a];
    int selectedRows[a];
    int finalTrack[a];

    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            std::cin >> garden[i][j];
        }
        rowsStates[i] = false;
    }

    findMinCostTrack(a, 0, currentCost, minCost, rowsStates, selectedRows, finalTrack);

    for(int i = 0; i < a; i++){
        std::cout << finalTrack[i] << " ";
    }

    return 0;
}