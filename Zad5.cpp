#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

struct Vertex{
    int id;
    bool isStable{false};
    std::vector<int> neighboursId;
};

struct Pair{
    int vertexId;
    bool isStable{false};
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, m, s, currentVertexId, neighbourVertexId;
    short t;
    Vertex currentVertex, neighbourVertex;
    Pair currentPair;
    std::cin >> t;

    for(int i = 0; i < t; i++){
        std::cin >> n >> m >> s;
        std::vector<Vertex> vertices(n);
        std::vector<bool> visited(2*n, false);
        std::vector<int> predecessorsId(2*n, -1);
        std::vector<int> reversedOutput;
        std::queue<Pair> queue;
        bool isLoop{false};

        for(int j = 0; j < n; j++){
            vertices[j].id = j;
        }

        for(int j = 0; j < m; j++){
            std::cin >> currentVertexId >> neighbourVertexId;
            vertices[currentVertexId].neighboursId.resize(vertices[currentVertexId].neighboursId.size()+1, neighbourVertexId);
        }

        for(int j = 0; j < n; j++){
            std::sort(vertices[j].neighboursId.begin(), vertices[j].neighboursId.end());
        }

        visited[s] = true;
        currentPair.vertexId = s;
        currentPair.isStable = true;
        queue.push(currentPair);

        while(!queue.empty()){
            currentPair = queue.front();
            currentVertex = vertices[currentPair.vertexId];
            currentVertex.isStable = currentPair.isStable;
            if(currentVertex.isStable && currentVertex.neighboursId.empty()){
                break;
            }

            for(int j = 0; j < currentVertex.neighboursId.size(); j++){
                neighbourVertex = vertices[currentVertex.neighboursId[j]];
                neighbourVertex.isStable = !(currentVertex.isStable);

                if(neighbourVertex.isStable && !(visited[neighbourVertex.id])){
                    visited[neighbourVertex.id] = true;
                    predecessorsId[neighbourVertex.id] = currentVertex.id;
                    currentPair.vertexId = neighbourVertex.id;
                    currentPair.isStable = neighbourVertex.isStable;
                    queue.push(currentPair);
                }else if(!neighbourVertex.isStable && !(visited[neighbourVertex.id + n])){
                    visited[neighbourVertex.id + n] = true;
                    predecessorsId[neighbourVertex.id + n] = currentVertex.id;
                    currentPair.vertexId = neighbourVertex.id;
                    currentPair.isStable = neighbourVertex.isStable;
                    queue.push(currentPair);
                }else if(neighbourVertex.isStable && visited[neighbourVertex.id] || !neighbourVertex.isStable && visited[neighbourVertex.id + n]){
                    isLoop = true;
                }
            }
            
            queue.pop();
        }
        
        if(currentVertex.isStable){
            std::cout << "TAK\n";

            for(int j = currentVertex.id; predecessorsId[j] != -1;){
                if(visited[j] && currentVertex.isStable){
                    reversedOutput.resize(reversedOutput.size() + 1, currentVertex.id);
                    currentVertex = vertices[predecessorsId[currentVertex.id]];
                    currentVertex.isStable = false;
                    j = currentVertex.id + n;
                }else if(visited[j] && !currentVertex.isStable){
                    reversedOutput.resize(reversedOutput.size() + 1, currentVertex.id);
                    currentVertex = vertices[predecessorsId[currentVertex.id + n]];
                    currentVertex.isStable = true;
                    j = currentVertex.id;
                }
            }

            reversedOutput.resize(reversedOutput.size() + 1, s);

            for(int j = reversedOutput.size() - 1; j >= 0; j--){
                std::cout << reversedOutput[j] << " ";
            }
            std::cout << "\n";
        }else if(isLoop){
            std::cout << "PETLA\n";
        }else{
            std::cout << "NIE\n";
        }
    }

    return 0;
}