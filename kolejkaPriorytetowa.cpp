#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

class priorityQueueBinary {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int removeMin() {
        if (heap.empty()) {
            cerr << "Kolejka jest pusta!" << endl;
            return -1;
        }
        int minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return minValue;
    }

};

void testRemoveMin(int repeats, int seed, int n0, int n1) {
    std::ofstream file("removeMin.txt");
    srand(seed);
    for (int n = n0; n <= n1; n++) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
            priorityQueueBinary Q;
            for (int i = 0; i < n; ++i) {
                Q.insert(rand()%10000);
            }
            auto start = std::chrono::high_resolution_clock::now();
            bool equal = Q.removeMin();
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}

int main() {

    priorityQueueBinary q;
    q.insert(20);
    q.insert(10);
    q.insert(5);
    q.insert(15);

    cout<< q.removeMin() <<endl;
    cout<< q.removeMin() <<endl;
    cout<< q.removeMin() <<endl;
    cout<< q.removeMin() <<endl;

    testRemoveMin(10, 42, 1, 200);

    return 0;
}
