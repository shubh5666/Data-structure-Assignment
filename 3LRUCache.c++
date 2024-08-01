#include <iostream>
#include <unordered_map>

using namespace std;

class DLL {
public:
    class Node {
    public:
        int val;
        Node* next;
        Node* prev;
        int key;
        Node(int key, int val) : val(val), next(nullptr), prev(nullptr), key(key) {}
    };

    Node* head;
    Node* tail;

    DLL() : head(nullptr), tail(nullptr) {}

    void append(Node* node) {
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void moveToEnd(Node* node) {
        if (node == nullptr || head == nullptr || node == tail) {
            return;
        }
        if (node == head) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else {
            node->prev->next = node->next;
            if (node->next != nullptr) {
                node->next->prev = node->prev;
            }
        }
        node->next = nullptr;
        node->prev = tail;
        if (tail != nullptr) {
            tail->next = node;
        }
        tail = node;
        if (head == nullptr) {
            head = node;
        }
    }

    void deleteHead() {
        if (head == nullptr) {
            return;
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
    }
};

class LRUCache {
private:
    DLL dll;
   unordered_map<int, DLL::Node*> map;
    int cap;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) {
            return -1;
        }
        DLL::Node* node = it->second;
        dll.moveToEnd(node);
        return node->val;
    }

    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            DLL::Node* node = it->second;
            node->val = value;
            dll.moveToEnd(node);
        } else {
            if (map.size() >= cap) {
                DLL::Node* nodeToRemove = dll.head;
                dll.deleteHead();
                map.erase(nodeToRemove->key);
            }
            DLL::Node* node = new DLL::Node(key, value);
            dll.append(node);
            map[key] = node;
        }
    }

    ~LRUCache() {
        DLL::Node* current = dll.head;
        while (current != nullptr) {
            DLL::Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
   cout << cache.get(1) <<endl; 
    cache.put(3, 3);  
   cout << cache.get(2) <<endl;  
    cache.put(4, 4);  
   cout << cache.get(1) <<endl;  
   cout << cache.get(3) <<endl;  
   cout << cache.get(4) <<endl;  
    return 0;
}