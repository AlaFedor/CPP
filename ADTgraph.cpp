#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <chrono>
#include <list>

class Graph
{
private:
    std::unordered_map<int, std::string> vertex_values; // Wartości wierzchołków (string)
    std::unordered_map<int, int> vertex_index;          // Mapowanie wierzchołków na indeksy
    std::vector<std::vector<int>> adjacency_matrix;     // Macierz połączeń (int)
    int vertex_count = 0;                               // Liczba wierzchołków

    int getVertexIndex(int x) const
    {
        if (vertex_index.count(x))
            return vertex_index.at(x);
        else
            return -1;
    }

    int getVertexId(int index) const
    {
        for (const auto &pair : vertex_index)
        {
            if (pair.second == index)
            {
                return pair.first;  // Zwracamy identyfikator
            }
        }
        throw std::runtime_error("Indeks " + std::to_string(index) + " nie istnieje");
    }



public:
    bool adjacent(int x, int y) const
    {
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        if (i == -1 || j == -1)
            return false;
        return adjacency_matrix[i][j] != 0;
    }

    std::vector<int> neighbours(int x) const
    {
        std::vector<int> result;
        int i = getVertexIndex(x);
        if (i == -1) return result;
        for (int j = 0; j < vertex_count; ++j)
        {
            if (adjacency_matrix[i][j] != 0)
            {
                int v = getVertexId(j);
                result.push_back(v);
            }
        }
        return result;
    }

    void addVertex(int x)
    {
        if (vertex_index.count(x)) return;

        vertex_index[x] = vertex_count;
        vertex_values[x] = ""; // Domyślna wartość (pusty string)

        for (auto &row : adjacency_matrix)
        {
            row.push_back(0);
        }

        adjacency_matrix.push_back(std::vector<int>(vertex_count + 1, 0));
        ++vertex_count;
    }


    void removeVertex(int x)
    {
        int idx = getVertexIndex(x);
        if(idx == -1) return;

        adjacency_matrix.erase(adjacency_matrix.begin() + idx);
        for (auto &row : adjacency_matrix)
        {
            row.erase(row.begin() + idx);
        }

        vertex_index.erase(x);
        vertex_values.erase(x);

        for (auto &entry : vertex_index)
        {
            if (entry.second > idx) entry.second--;
        }

        --vertex_count;
    }


    void addEdge(int x, int y)
    {
        addVertex(x);
        addVertex(y);

        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        if(i==-1 || j==-1) return;

        adjacency_matrix[i][j] = 1;
    }

    void removeEdge(int x, int y)
    {
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        if(i==-1 || j==-1) return;
        adjacency_matrix[i][j] = 0;
    }

    std::string getVertexValue(int x) const
    {
        if(!vertex_values.count(x)){
            throw std::runtime_error("wierzcholek nie istnieje");
        }
        return vertex_values.at(x);
    }


    void setVertexValue(int x, const std::string &value)
    {
        vertex_values[x] = value;
    }

        int getEdgeValue(int x, int y) const
    {
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        if(i==-1 || j==-1) return -1;
        return adjacency_matrix[i][j];
    }

        void setEdgeValue(int x, int y, int value)
    {
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        if(i==-1 || j==-1) return;
        adjacency_matrix[i][j] = value;
    }

    void exportToDotFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (!file)
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file << "digraph G {\n";

        // Wierzchołki z etykietami
        for (const auto &pair : vertex_index)
        {
            int id = pair.first;
            std::string label = vertex_values.at(id);
            file << "    " << id << " [label=\"" << label << "\"];\n";
        }

        // Krawędzie
        for (int i = 0; i < vertex_count; ++i)
        {
            for (int j = 0; j < vertex_count; ++j)
            {
                if (adjacency_matrix[i][j] != 0)
                {
                    int from = getVertexId(i);
                    int to = getVertexId(j);
                    int value = adjacency_matrix[i][j];
                    file << "    " << from << " -> " << to << " [label=\"" << value << "\"];\n";
                }
            }
        }

        file << "}\n";
        file.close();
    }

    void topologicalSortUtil(int v, std::unordered_map<int, bool>& seen, std::list<int>& stack) {
        seen[v] = true;

        for (int neighbor : neighbours(v)) {
            if (!seen[neighbor]) {
                topologicalSortUtil( neighbor, seen, stack);
            }
        }

        stack.push_front(v);
    }

    std::list<int> topologicalSort() {
        std::unordered_map<int, bool> seen;
        std::list<int> stack;

        for (const auto& pair : vertex_index) {
            seen[pair.first] = false;
        }

        for (const auto& pair : vertex_index) {
            int vertexId = pair.first;
            if (!seen[vertexId]) {
                topologicalSortUtil(vertexId, seen, stack);
            }
        }

        return stack;
    }


};

void test(int repeats, int seed, int n0, int n1) {
    std::ofstream file("adjacent.txt");
    srand(seed);
    for (int n = n0; n <= n1; n++) {
        double totalTime = 0.0;
        for (int r = 0; r < repeats; ++r) {
             Graph graph;
            for (int i = 0; i < n; ++i) {
                graph.addVertex(i);
                if(i!=0){
                    graph.addEdge(i-1, i);
                }
            }
            auto start = std::chrono::high_resolution_clock::now();
            graph.adjacent(n, n-1);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration<double>(end - start).count();
        }
        file << n << " " << (totalTime / repeats) << "\n";
    }
}



int main()
{
    Graph graph;

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addVertex(6);
    graph.addVertex(7);
    graph.addVertex(8);
    graph.addVertex(9);

    graph.setVertexValue(1, "3/4 szklanki mleka");
    graph.setVertexValue(2, "1 jajko");
    graph.setVertexValue(3, "lyzka oleju");
    graph.setVertexValue(4, "pomieszaj");
    graph.setVertexValue(5, "podgrzej syrop");
    graph.setVertexValue(6, "nagrzej patelnie");
    graph.setVertexValue(7, "wylej ciasto na patelnie");
    graph.setVertexValue(8, "obroc gdy bedzie rumiany");
    graph.setVertexValue(9, "zjedz");

    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(4, 7);
    graph.addEdge(6, 7);
    graph.addEdge(7, 8);
    graph.addEdge(8, 9);
    graph.addEdge(5, 9);

    graph.neighbours(4);
    graph.exportToDotFile("graf.dot");

    std::list<int> sorted = graph.topologicalSort();
    
    for (int v : sorted) {
        std::cout << v << " ( " << graph.getVertexValue(v) << ")" << std::endl;
    }

    return 0;
}

