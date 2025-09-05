#include <iostream>
#include <vector>
#include <optional>
#include <chrono>
#include <fstream>
#define CAP_MAX 50


class setHashed {
private:
    enum State { EMPTY, FILLED, DELETED };

    struct Entry {
        int value;
        State state;

        Entry() : value(0), state(EMPTY) {}
    };

    std::vector<Entry> table;
    int capacity;
    int size;

    int hash(int x, int i) const {
        return (x + i) % capacity;
    }

public:
    setHashed() : capacity(CAP_MAX), size(0) {
        table.resize(capacity);
    }

    void add(int x) {
        for (int i = 0; i < capacity; ++i) {
            int idx = hash(x, i);
            if (table[idx].state == EMPTY || table[idx].state == DELETED) {
                table[idx].value = x;
                table[idx].state = FILLED;
                size++;
                return;
            }
            if (table[idx].state == FILLED && table[idx].value == x) return;
        }
    }

    void remove(int x) {
        for (int i = 0; i < capacity; ++i) {
            int idx = hash(x, i);
            if (table[idx].state == EMPTY) return;
            if (table[idx].state == FILLED && table[idx].value == x) {
                table[idx].state = DELETED;
                size--;
                return;
            }
        }
    }

    bool contains(int x) const {
        for (int i = 0; i < capacity; ++i) {
            int idx = hash(x, i);
            if (table[idx].state == EMPTY) return false;
            if (table[idx].state == FILLED && table[idx].value == x)
                return true;
        }
        return false;
    }

    setHashed sum(const setHashed& other) const {
        setHashed result;
        for (const auto& entry : table) {
            if (entry.state == FILLED) {
                result.add(entry.value);
            }
        }
        for (const auto& entry : other.table) {
            if (entry.state == FILLED) {
                result.add(entry.value);
            }
        }
        return result;
    }

    setHashed common(const setHashed& other) const {
        setHashed result;
        for (const auto& entry : table) {
            if (entry.state == FILLED && other.contains(entry.value))
                result.add(entry.value);
        }
        return result;
    }

    setHashed difference(const setHashed& other) const {
        setHashed result;
        for (const auto& entry : table) {
            if (entry.state == FILLED && !other.contains(entry.value))
                result.add(entry.value);
        }
        return result;
    }

    bool isEqual(const setHashed& other) const {
        for (const auto& entry : table) {
            if (entry.state == FILLED && !other.contains(entry.value))
                return false;
        }
        for (const auto& entry : other.table) {
            if (entry.state == FILLED && !contains(entry.value))
                return false;
        }
        return true;
    }

    void print() const {
        std::cout << "{ ";
        for (const auto& entry : table) {
            if (entry.state == FILLED)
                std::cout << entry.value << " ";
        }
        std::cout << "}\n";
    }
};

int randomInt() {
    return rand() % 100000;
}

void testAdd(int repeats, int seed, int n0, int n1) {
    std::ofstream file("add.txt");
    srand(seed);
    for (int n = n0; n <= n1; n++) {
        double totalTime = 0.0;
        for (int r = 0 ; r < repeats; ++r) {
            setHashed s;
            for (int i = 0; i < n; ++i)
                s.add(randomInt());

            auto start = std::chrono::high_resolution_clock::now();
            s.add(randomInt());
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

// Usuwanie
void testRemove(int repeats, int seed, int n0, int n1) {
    std::ofstream file("remove.txt");
    srand(seed);
    for (int n = n0; n <= n1; ++n) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
            setHashed s;
            for (int i = 0; i < n; ++i)
                s.add(randomInt());

            auto start = std::chrono::high_resolution_clock::now();
            s.remove(randomInt());
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

// Sprawdzanie przynależności
void testContains(int repeats, int seed, int n0, int n1) {
    std::ofstream file("contains.txt");
    srand(seed);
    for (int n = n0; n <= n1; ++n) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
            setHashed s;
            for (int i = 0; i < n; ++i)
                s.add(randomInt());

            auto start = std::chrono::high_resolution_clock::now();
            s.contains(randomInt());
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

// Suma zbiorów
void testSum(int repeats, int seed, int n0, int n1) {
    std::ofstream file("sum.txt");
    srand(seed);
    for (int n = n0; n <= n1; n=n+1) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
            setHashed A, B;
            for (int i = 0; i < n; ++i) {
                A.add(randomInt());
                B.add(randomInt());
            }

            auto start = std::chrono::high_resolution_clock::now();
            setHashed C = A.sum(B);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

// Różnica zbiorów
void testDifference(int repeats, int seed, int n0, int n1) {
    std::ofstream file("difference.txt");
    srand(seed);
    for (int n = n0; n <= n1; ++n) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
            setHashed A, B;
            for (int i = 0; i < n; ++i) {
                A.add(randomInt());
                B.add(randomInt());
            }

            auto start = std::chrono::high_resolution_clock::now();
            setHashed C = A.difference(B);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

// Część wspólna
void testCommon(int repeats, int seed, int n0, int n1) {
    std::ofstream file("common.txt");
    srand(seed);
    for (int n = n0; n <= n1; ++n) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
            setHashed A, B;
            for (int i = 0; i < n; ++i) {
                A.add(randomInt());
                B.add(randomInt());
            }

            auto start = std::chrono::high_resolution_clock::now();
            setHashed C = A.common(B);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

// Porównanie zbiorów
void testIsEqual(int repeats, int seed, int n0, int n1) {
    std::ofstream file("isEqual.txt");
    srand(seed);
    for (int n = n0; n <= n1; n=n+1) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
            setHashed A, B;
            for (int i = 0; i < n; ++i) {
                int val = randomInt();
                A.add(val);
                B.add(val);
            }

            auto start = std::chrono::high_resolution_clock::now();
            bool result = A.isEqual(B);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

int main() {
    setHashed set1;
    setHashed set2;

    set1.add(5);
    set1.add(10);
    set1.add(15);
    set1.add(20);

    set2.add(10);
    set2.add(15);
    set2.add(25);
    set2.add(30);

    std::cout << "Set1: ";
    set1.print();

    std::cout << "Set2: ";
    set2.print();

    std::cout << "Set1 contains 10? " << (set1.contains(10) ? "Yes" : "No") << "\n";
    std::cout << "Set2 contains 5? " << (set2.contains(5) ? "Yes" : "No") << "\n";

    set1.remove(10);
    std::cout << "Set1 after removing 10: ";
    set1.print();

    setHashed sumSet = set1.sum(set2);
    std::cout << "Sum of Set1 and Set2: ";
    sumSet.print();

    setHashed commonSet = set1.common(set2);
    std::cout << "Common elements of Set1 and Set2: ";
    commonSet.print();

    setHashed diffSet = set1.difference(set2);
    std::cout << "Difference (Set1 - Set2): ";
    diffSet.print();

    setHashed set3 = set1;
    std::cout << "Set1 equals Set3? " << (set1.isEqual(set3) ? "Yes" : "No") << "\n";
    std::cout << "Set1 equals Set2? " << (set1.isEqual(set2) ? "Yes" : "No") << "\n";

    //testAdd(15, 42, 1, 200);
    //testRemove(10, 42, 1, 200);
    //testContains(10, 42, 1, 200);
    testSum(10, 42, 1, 200);
    testDifference(10, 42, 1, 200);
    testCommon(10, 42, 1, 200);
    testIsEqual(10, 42, 1, 200);

    return 0;
}
