#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
    private:
        vector<list<int>> table;
    
        int hashFunction(int key) {
            return key % TABLE_SIZE;
        }

    public:
        HashTable() {
            table.resize(TABLE_SIZE);
        }

        void insert(int key) {
            int index = hashFunction(key);
            table[index].push_back(key);
        }

        // void remove(int key) {
        //     int index = hashFunction(key);
        //     table[index].remove(key);
        // }

        // bool search(int key) {
        //     int index = hashFunction(key);
        //     for (const auto& item : table[index]) {
        //         if (item == key) {
        //             return true;
        //         }
        //     }
        //     return false;
        // }

        void display() {
            for (int i = 0; i < TABLE_SIZE; i++) {
                cout << "Index " << i << ": ";
                for (int data : table[i]) {
                    cout << data << " -> ";
                }
                cout << "NULL" << endl;
            }
        }
};

int main() {
    HashTable ht;
    ht.insert(23);
    ht.insert(43);
    ht.insert(13);
    ht.insert(35);


    ht.display();

    return 0;
}