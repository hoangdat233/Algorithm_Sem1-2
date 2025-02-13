#include <iostream>

struct Node {
    int data;
    Node* next;
};

typedef Node* node;

node createNode(int x){
    node temp = new Node(); 
    temp->data = x;  
    temp->next = nullptr; 
    return temp;
}

bool isEmpty(node a){
    return a == nullptr;
}

void push(node& a, int x){
    node temp = createNode(x);
    if(a == nullptr){
        a = temp;
    } else {
        temp->next = a;
        a = temp;
    }
}
void pop(node& a){
    if(isEmpty(a)){
        return;
    }
    node temp = a;
    a = a->next;
    delete temp;
}

int gettop(node a){
    if(isEmpty(a)){
        return -1;
    }
    return a->data;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    unsigned int n;
    std :: cin >> n;
    char operato;
    int x;
    node a = nullptr;
    for(unsigned int i = 1; i <= n; i++){
        std :: cin >> operato;
        if(operato == '+'){
            std :: cin >> x;
            push(a, x);
        } else {
            std :: cout << gettop(a) << "\n";
            pop(a);
        } 
    }
    while(!isEmpty(a)){
        pop(a);
    }
    return 0;
}
