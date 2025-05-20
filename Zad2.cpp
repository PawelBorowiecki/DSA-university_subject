#include <iostream>
#include <string>

struct Artefact{
    std::string name;
    long m;
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    long t, n, energy{0};
    Artefact temp;
    std::cin >> t;
    for(int i = 0; i < t; i++){
        std::cin >> n;
        Artefact elements[n];
        long individualEnergies[n];
        for(int j = 0; j < n; j++){
            std::cin >> elements[j].name >> elements[j].m;
        }

        for(int j = 1, k; j < n; j++){
            if(elements[j].m < elements[j-1].m){
                temp = elements[j];
                for(k = j-1; (k >= 0) && (elements[k].m > temp.m); k--){
                    elements[k+1] = elements[k];
                }
                elements[k+1] = temp;
            }
        }

        for(int j = 0; j < n; j++){
            energy += elements[j].m;
            individualEnergies[j] = energy;
        }
        energy = 0;

        for(int j = 0; j < n; j++){
            energy += individualEnergies[j];
        }

        std::cout << energy << "\n";

        for(int j = 0; j < n; j++){
            std::cout << elements[j].name << " ";
        }
        std::cout << "\n";
        energy = 0;
    }

    return 0;
}