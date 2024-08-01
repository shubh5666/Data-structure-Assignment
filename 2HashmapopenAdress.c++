#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

template<typename K, typename V>
class Entry {
public:
    K key;
    V value;
    bool isDeleted;
    
    Entry(K key, V value) : key(key), value(value), isDeleted(false) {}
};

template<typename K, typename V>
class HashMapOpenAddressing {
private:
    int size;
    int capacity;
    vector<Entry<K, V>*> data;

    int hash(const K& key) {
        return abs(hash<K>{}(key) % capacity);
    }

    void resize() {
        capacity *= 2;
        vector<Entry<K, V>*> oldData = data;
        data = vector<Entry<K, V>*>(capacity, nullptr);
        size = 0;
        for (auto entry : oldData) {
            if (entry != nullptr && !entry->isDeleted) {
                insert(entry->key, entry->value);
            }
            delete entry;
        }
    }

public:
    HashMapOpenAddressing() : size(0), capacity(10), data(10, nullptr) {}

    ~HashMapOpenAddressing() {
        for (auto entry : data) {
            delete entry;
        }
    }

    int getSize() {
        return size;
    }

    void insert(const K& key, const V& value) {
        if (size >= capacity / 2) {
            resize();
        }
        int index = hash(key);
        int initialIndex = index;
        while (data[index] != nullptr && data[index]->key != key) {
            index = (index + 1) % capacity;
            if (index == initialIndex) {
                resize();
                index = hash(key);
                initialIndex = index;
            }
        }
        if (data[index] == nullptr || data[index]->isDeleted) {
            data[index] = new Entry<K, V>(key, value);
            size++;
        } else {
            data[index]->value = value;
        }
    }

    V get(const K& key) {
        int index = hash(key);
        int initialIndex = index;
        while (data[index] != nullptr) {
            if (!data[index]->isDeleted && data[index]->key == key) {
                return data[index]->value;
            }
            index = (index + 1) % capacity;
            if (index == initialIndex) {
                break;
            }
        }
        throw runtime_error("Key not found");
    }

    void remove(const K& key) {
        int index = hash(key);
        int initialIndex = index;
        while (data[index] != nullptr) {
            if (!data[index]->isDeleted && data[index]->key == key) {
                data[index]->isDeleted = true;
                size--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == initialIndex) {
                break;
            }
        }
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            if (data[i] != nullptr && !data[i]->isDeleted) {
                cout << "Index " << i << ": " << data[i]->key << " " << data[i]->value << endl;
            }
        }
    }
};

int main() {
    HashMapOpenAddressing<string, int> map;
    map.insert("kfshdgkdf", 1);
    map.insert("2", 7);
    map.insert("3", 3);
    map.insert("1", 0);
    map.insert("shubh", 0);
    map.insert("cha", 0);
    map.insert("cha", 1);
    map.insert("ch", 0);
    map.insert("c", 0);
    map.display();

    try {
        int value = map.get("2");
        cout << "Value for key 2: " << value << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    cout << endl;
    map.remove("raj");
    cout << "Size of the map: " << map.getSize() << endl;
    map.display();

    return 0;
}