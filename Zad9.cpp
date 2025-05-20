#include <iostream>
#include <cmath>
#include <iomanip>

struct Bucket{
    bool isFilled{false};
    float min, max;
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, filledBucketsSize{0};
    float maxPostPosition, minPostPosition, averageDistance, maxArch{0.0f};
    std::cin >> n;
    float postsPositions[n];
    Bucket buckets[n];

    for(int i = 0; i < n; i++){
        std::cin >> postsPositions[i];
        if(i == 0){
            maxPostPosition = postsPositions[i];
            minPostPosition = postsPositions[i];
        }else{
            if(maxPostPosition < postsPositions[i]){
                maxPostPosition = postsPositions[i];
            }else if(minPostPosition > postsPositions[i]){
                minPostPosition = postsPositions[i];
            }
        }
    }

    averageDistance = (maxPostPosition - minPostPosition) / (float)(n - 1);

    for(int i = 0, bucketIndex; i < n; i++){
        bucketIndex = (int)(std::floor((postsPositions[i] - minPostPosition) / averageDistance));                
        if(!buckets[bucketIndex].isFilled){
            buckets[bucketIndex].isFilled = true;
            buckets[bucketIndex].max = postsPositions[i];
            buckets[bucketIndex].min = postsPositions[i];
            filledBucketsSize++;
        }else{
            if(postsPositions[i] > buckets[bucketIndex].max){
                buckets[bucketIndex].max = postsPositions[i];
            }else if(postsPositions[i] < buckets[bucketIndex].min){
                buckets[bucketIndex].min = postsPositions[i];
            } 
        }                   
    }

    Bucket filledBuckets[filledBucketsSize];

    for(int i = 0, j = 0; i < n; i++){
        if(buckets[i].isFilled){
            filledBuckets[j] = buckets[i];
            j++;
        }            
    }

    for(int i = 1; i < filledBucketsSize; i++){
        if(filledBuckets[i].min - filledBuckets[i-1].max > maxArch){
            maxArch = filledBuckets[i].min - filledBuckets[i-1].max;
        }       
    }

    std::cout << std::setprecision(4) << std::fixed << maxArch << std::endl;

    return 0;
}