#include <iostream>
using namespace std;

struct ElementCount {
    char element;
    int count;
    ElementCount* next;
};

struct Node {
    ElementCount* counts;
    Node* next;
};

void push(Node*& top_Node, ElementCount* counts) {
    Node* newNode = new Node;
    newNode->counts = counts;
    newNode->next = top_Node;
    top_Node = newNode;
}


ElementCount* pop(Node*& top_Node) {
    if (top_Node == nullptr) return nullptr;
    Node* temp = top_Node;
    ElementCount* counts = temp->counts;
    top_Node = top_Node->next;
    delete temp;
    return counts;
}

ElementCount* add_element(ElementCount* head, char element, int count) {
    ElementCount* newNode = new ElementCount{element, count, nullptr};
    if (!head) return newNode;

    ElementCount* cur = head;
    while (cur) {
        if (cur->element == element) {
            cur->count += count;
            delete newNode;
            return head;
        }
        if (!cur->next) break;
        cur = cur->next;
    }
    cur->next = newNode;
    return head;
}

ElementCount* mul_elements(ElementCount* head, int mul) {
    ElementCount* cur = head;
    while (cur) {
        cur->count *= mul;
        cur = cur->next;
    }
    return head;
}

ElementCount* merge_elements(ElementCount* parent, ElementCount* child) {
    ElementCount* cur = child;
    while (cur) {
        parent = add_element(parent, cur->element, cur->count);
        cur = cur->next;
    }
    return parent;
}

ElementCount* parse_fml() {
    Node* stackTop = nullptr;
    ElementCount* cur_cnts = nullptr;
    char ch;

    while (cin >> ch) {
        if (ch >= 'A' && ch <= 'Z') {
            int count = 0;
            while (cin.peek() >= '0' && cin.peek() <= '9') {
                char numChar;
                cin >> numChar;
                count = count * 10 + (numChar - '0');
            }
            count = (count == 0) ? 1 : count;
            cur_cnts = add_element(cur_cnts, ch, count);
        } else if (ch == '(') {
            push(stackTop, cur_cnts);
            cur_cnts = nullptr;
        } else if (ch == ')') {
            int mul = 0;
            while (cin.peek() >= '0' && cin.peek() <= '9') {
                char numChar;
                cin >> numChar;
                mul = mul * 10 + (numChar - '0');
            }
            mul = (mul == 0) ? 1 : mul;
            cur_cnts = mul_elements(cur_cnts, mul);
            ElementCount* parentCnt = pop(stackTop);
            cur_cnts = merge_elements(parentCnt, cur_cnts);
        }
    }
    return cur_cnts;
}

ElementCount* sortElements(ElementCount* head) {
    if (!head || !head->next) return head;
    ElementCount* sorted = nullptr;
    while (head) {
        ElementCount* node = head;
        head = head->next;
        if (!sorted || node->element < sorted->element) {
            node->next = sorted;
            sorted = node;
        } else {
            ElementCount* cur = sorted;
            while (cur->next && cur->next->element < node->element) {
                cur = cur->next;
            }
            node->next = cur->next;
            cur->next = node;
        }
    }
    return sorted;
}

int main() {
    ElementCount* res = parse_fml();
    res = sortElements(res);
    ElementCount* cur = res;
    while (cur) {
        cout << cur->element;
        if (cur->count > 1) {
            cout << cur->count;
        }
        cur = cur->next;
    }
    cout << endl;
    return 0;
}