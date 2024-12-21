// KruskalMST.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class KruskalMST {
private:
    struct Edge {
        int src, dest, weight;
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    };

    struct DisjointSet {
        vector<int> parent, rank;
        
        DisjointSet(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++)
                parent[i] = i;
        }

        int find(int u) {
            if (parent[u] != u)
                parent[u] = find(parent[u]);
            return parent[u];
        }

        void unite(int u, int v) {
            int pu = find(u), pv = find(v);
            if (rank[pu] > rank[pv])
                parent[pv] = pu;
            else if (rank[pu] < rank[pv])
                parent[pu] = pv;
            else {
                parent[pv] = pu;
                rank[pu]++;
            }
        }
    };

    int V;
    vector<Edge> edges;

public:
    KruskalMST(int vertices) : V(vertices) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    vector<Edge> findMST() {
        sort(edges.begin(), edges.end(), 
             [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

        vector<Edge> result;
        DisjointSet ds(V);

        for (const Edge& edge : edges) {
            int u = edge.src;
            int v = edge.dest;

            int set_u = ds.find(u);
            int set_v = ds.find(v);

            if (set_u != set_v) {
                result.push_back(edge);
                ds.unite(u, v);
            }
        }

        return result;
    }

    void printMST(const vector<Edge>& mst) {
        cout << "Minimum Spanning Tree edges:\n";
        int totalWeight = 0;
        for (const Edge& edge : mst) {
            cout << edge.src << " -- " << edge.dest << " : " << edge.weight << endl;
            totalWeight += edge.weight;
        }
        cout << "Total MST weight: " << totalWeight << endl;
    }
};

int main() {
    int V = 4;  // Number of vertices
    KruskalMST kruskal(V);
    
    // Adding edges to the graph
    kruskal.addEdge(0, 1, 10);
    kruskal.addEdge(0, 2, 6);
    kruskal.addEdge(0, 3, 5);
    kruskal.addEdge(1, 3, 15);
    kruskal.addEdge(2, 3, 4);

    vector<KruskalMST::Edge> mst = kruskal.findMST();
    kruskal.printMST(mst);

    return 0;
}