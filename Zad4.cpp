#include <iostream>

struct Pair{
    int f,l, occurenceCounter{0};
    Pair* left{nullptr};
    Pair* right{nullptr};
};

struct Survey{
    int y;
    Pair* results{nullptr};
    Survey* left{nullptr};
    Survey* right{nullptr};
};

Pair* insertToResultsTree(Pair* root, const Pair& data){
    if(root == nullptr){
        root = new Pair;
        root->f = data.f;
        root->l = data.l;
        (root->occurenceCounter)++;
    }else if((root->f == data.f && root->l > data.l) || root->f > data.f){
        root->left = insertToResultsTree(root->left, data);
    }else if((root->f == data.f && root->l < data.l) || root->f < data.f){
        root->right = insertToResultsTree(root->right, data);
    }else if(root->f == data.f && root->l == data.l){
        root->occurenceCounter++;
    }

    return root;
}

Survey* insertToSurveyTree(Survey* root, const Pair& data, const int& year){
    if(root == nullptr){
        root = new Survey;
        root->y = year;
        root->results = insertToResultsTree(root->results, data);      
    }else if(root->y == year){
        root->results = insertToResultsTree(root->results, data);
    }else if(year < root->y){
        root->left = insertToSurveyTree(root->left, data, year);
    }else{
        root->right = insertToSurveyTree(root->right, data, year);
    }

    return root;
}

void printResultsTreeInorder(Pair* root){
    if(root == nullptr){
        return;
    }
    printResultsTreeInorder(root->left);
    for(int i = 0; i < root->occurenceCounter; i++){
        std::cout << "(" << root->f << "," << root->l << ") ";
    }
    printResultsTreeInorder(root->right);
}

void printSurveyTreeInorder(Survey* root){
    if(root == nullptr){
        return;
    }
    printSurveyTreeInorder(root->left);
    std::cout << root->y << ": ";
    printResultsTreeInorder(root->results);
    std::cout << "\n";
    printSurveyTreeInorder(root->right);
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n, currentYear;
    bool wasAnyCorrectSurvey{false}, wasAnyIncorrectSurvey{false};
    Pair currentPair;
    Survey* root{nullptr};
    std::cin >> n;

    for(int i = 0; i < n; i++){
        std::cin >> currentYear >> currentPair.f >> currentPair.l;
        float v = float(currentPair.l) / 100 * currentPair.f;
        if((v >= 313.00f && v <= 350.00f) && (currentPair.f >= 20 && currentPair.f <= 20000)){
            if(currentPair.f <= 325 && currentPair.f >= 275){
                wasAnyCorrectSurvey = true;
            }else{
                wasAnyIncorrectSurvey = true;
            }
            root = insertToSurveyTree(root, currentPair, currentYear);
        }
    }   

    printSurveyTreeInorder(root);

    if(wasAnyCorrectSurvey && !wasAnyIncorrectSurvey){
        std::cout << "TAK\n";
    }else{
        std::cout << "NIE\n";
    }

    return 0;
}