#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int TABLE_SIZE = 10;
const int PRIME = 7; 

struct Mahasiswa {
    string nim;
    string nama;
    bool isOccupied = false;
    bool isDeleted = false;
};

class HashTable {
private:
    vector<Mahasiswa> table;

    int hash1(string key) {
        long long hashVal = 0;
        for (char ch : key) {
            hashVal = (hashVal * 31 + ch) % TABLE_SIZE;
        }
        return hashVal % TABLE_SIZE;
    }

    int hash2(string key) {
        long long hashVal = 0;
        for (char ch : key) {
            hashVal = (hashVal * 31 + ch) % PRIME;
        }
        return PRIME - (hashVal % PRIME);
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    void insert(string nim, string nama) {
        int index = hash1(nim);
        int step = hash2(nim);
        int i = 0;

        while (i < TABLE_SIZE) {
            int newIndex = (index + i * step) % TABLE_SIZE;
            
            if (!table[newIndex].isOccupied || table[newIndex].isDeleted) {
                table[newIndex].nim = nim;
                table[newIndex].nama = nama;
                table[newIndex].isOccupied = true;
                table[newIndex].isDeleted = false;
                cout << "Sukses input " << nim << " di indeks " << newIndex << endl;
                return;
            }
            
            if (table[newIndex].isOccupied && !table[newIndex].isDeleted && table[newIndex].nim == nim) {
                table[newIndex].nama = nama;
                cout << "NIM " << nim << " ketemu, nama diupdate" << endl;
                return;
            }
            
            i++;
        }
        cout << "Gagal input, tabel udah penuh" << endl;
    }

    string search(string nim) {
        int index = hash1(nim);
        int step = hash2(nim);
        int i = 0;

        while (i < TABLE_SIZE) {
            int newIndex = (index + i * step) % TABLE_SIZE;
            
            if (!table[newIndex].isOccupied && !table[newIndex].isDeleted) {
                break;
            }
            
            if (table[newIndex].isOccupied && !table[newIndex].isDeleted && table[newIndex].nim == nim) {
                return table[newIndex].nama;
            }
            
            i++;
        }
        return "Ga ketemu";
    }

    void remove(string nim) {
        int index = hash1(nim);
        int step = hash2(nim);
        int i = 0;

        while (i < TABLE_SIZE) {
            int newIndex = (index + i * step) % TABLE_SIZE;
            
            if (!table[newIndex].isOccupied && !table[newIndex].isDeleted) {
                break;
            }
            
            if (table[newIndex].isOccupied && !table[newIndex].isDeleted && table[newIndex].nim == nim) {
                table[newIndex].isDeleted = true;
                cout << "NIM " << nim << " berhasil dihapus" << endl;
                return;
            }
            
            i++;
        }
        cout << "Gagal hapus, NIM " << nim << " ga ada" << endl;
    }

    void display() {
        cout << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Indeks " << i << ": ";
            if (table[i].isOccupied && !table[i].isDeleted) {
                cout << table[i].nim << " - " << table[i].nama;
            } else if (table[i].isDeleted) {
                cout << "Deleted";
            } else {
                cout << "Kosong";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    HashTable mhsTable;

    mhsTable.insert("230101", "Andi");
    mhsTable.insert("230102", "Budi");
    mhsTable.insert("230112", "Citra"); 
    mhsTable.insert("230104", "Dewi");
    mhsTable.display();

    string targetNIM = "230112";
    cout << "Cari NIM " << targetNIM << " : " << mhsTable.search(targetNIM) << endl;
    cout << "Cari NIM 230199 : " << mhsTable.search("230199") << endl;
    cout << endl;

    mhsTable.remove("230102");
    mhsTable.display();

    return 0;
}
