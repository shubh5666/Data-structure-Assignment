#include <bits/stdc++.h>
using namespace std;

template<typename K, typename V>
class Entry {
public:
    K key;
    V value;
    size_t hash;

    Entry(const K& key, const V& value) : key(key), value(value), hash(hash<K>{}(key)) {}
};

template<typename K, typename V>
class HashMap {
private:
    int size;
    int capacity;
    vector<vector<Entry<K, V>>> data;

public: 
    HashMap() : size(0), capacity(10), data(10) {}

    int getSize() {
        return size;
    }

    void insert(const K& key, const V& value) {
        Entry<K, V> entry(key, value);
        int index = abs(static_cast<int>(entry.hash % capacity));
        bool isUpdated = false;
        for (auto& e : data[index]) {
            if (e.key == key) {
                e.value = value;
                isUpdated = true;
                return;
            }
        }
        if (!isUpdated) {
            data[index].push_back(entry);
            size++;
        }
    }

    V* get(const K& key) {
        int index = abs(static_cast<int>(hash<K>{}(key) % capacity));
        for (auto& e : data[index]) {
            if (e.key == key) {
                return &e.value;
            }
        }
        return nullptr;
    }

    void remove(const K& key) {
        int index = abs(static_cast<int>(hash<K>{}(key) % capacity));
        auto& bucket = data[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                size--;
                return;
            }
        }
    }

    void display() {
        for (const auto& bucket : data) {
            for (const auto& e : bucket) {
                cout << e.key << " " << e.value << endl;
            }
        }
    }
};

int main() {
    HashMap<string, int> map;
    map.insert("1", 1);
    map.insert("2", 7);
    map.insert("3", 3);
    map.insert("1", 0);
    map.insert("shubham", 0);
    map.insert("chauhan", 0);
    map.insert("chauhan", 1);
    map.insert("ch", 0);
    map.insert("h", 0);
    map.display();

    int* value = map.get("2");
    if (value) {
        cout << *value << endl;
    }
    cout << endl;

    map.remove("shubham");
    cout << map.getSize() << endl;
    map.display();

    return 0;
}