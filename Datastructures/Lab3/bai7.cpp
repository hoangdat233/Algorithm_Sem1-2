#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct NodeList {
    int value;
    NodeList* next;
};

typedef Node* node;
typedef NodeList* nodeList;

node createStack() {
    return nullptr;
}

bool isEmpty(node top) {
    return top == nullptr;
}

void push(node& top, int data) {
    node newNode = new Node;  
    newNode->data = data;    
    newNode->next = top;   
    top = newNode;  
}

int top(node top) {
    if (!isEmpty(top)) {
        return top->data;  
    }
    return -1; 
}

void pop(node& top) {
    if (!isEmpty(top)) {
        node temp = top;   
        top = top->next;    
        delete temp;       
    }
}

void deleteStack(node& top) {
    while (!isEmpty(top)) {
        pop(top); 
    }
}

nodeList insert_Node(nodeList head, int value) {
    nodeList newNode = new NodeList;
    newNode->value = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        nodeList temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return head;
}

int get_index(nodeList head, int index) {
    nodeList temp = head;
    int count = 0;
    while (temp != nullptr) {
        if (count == index) {
            return temp->value;
        }
        count++;
        temp = temp->next;
    }
    return -1;  
}

long long largest_area(nodeList heightsHead, int n) {
    node st = createStack();  
    long long max_area = 0;
    int i = 0;
    
    nodeList cur_Node = heightsHead;
    int currentIndex = 0;
    while (i <= n) {
        int height = (i < n && cur_Node != nullptr) ? cur_Node->value : 0;
        while (!isEmpty(st) && (i == n || get_index(heightsHead, top(st)) > height)) {
            int h = get_index(heightsHead, top(st));
            pop(st);
            int width = isEmpty(st) ? i : (i - top(st) - 1);
            max_area = max(max_area, (long long)h * width);
        }
        if (i < n) {
            push(st, currentIndex);
        }
        ++i;
        ++currentIndex;
        if (cur_Node != nullptr) {
            cur_Node = cur_Node->next;
        }
    }

    deleteStack(st);  
    return max_area;
}

int main() {
    int N;
    cin >> N;
    nodeList heights = nullptr;
    for (int i = 0; i < N; ++i) {
        int h;
        cin >> h;
        heights = insert_Node(heights, h);
    }
    cout << largest_area(heights, N) << endl;
    while (heights != nullptr) {
        nodeList temp = heights;
        heights = heights->next;
        delete temp;
    }
    return 0;
}



