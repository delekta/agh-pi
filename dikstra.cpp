// Dysponujemy mapą, na której uwidoczniono N miast i K połączeń między nimi. Napisz program, który na podstawie
// tej mapy znajdzie najkrótszą trasę między wyznaczonymi dwoma miastami.

#include <iostream>
#include <climits>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

const int INF = INT_MAX;

typedef struct Node {
    vector <pair<Node *, int>> neighbours;
    int val, dist;
} Node;

Node *newNode(int val) {
    Node *n = new Node;
    n->val = val;
    n->dist = INF;
    return n;
}

void addEdge(Node *u, Node *v, int w) {
    pair <Node *, int> u_edge(v, w);
    pair <Node *, int> v_edge(u, w);
    u->neighbours.push_back(u_edge);
    v->neighbours.push_back(v_edge);
}

auto cmp = [](Node *x, Node *y) { return x->dist > y->dist; };

bool relax(Node *u, Node *v, int weight) {
    if(v->dist > u->dist + weight)
    {
        v->dist = u->dist + weight;
        return true;
    }
    return false;
}

void dijkstra(Node **nodes, int n, Node *start) {
    priority_queue <Node *, vector<Node *>, decltype(cmp)> queue(cmp);


    start->dist = 0;

    for(int i = 0; i < n; i++)
        queue.push(nodes[i]);

    while(queue.empty() == false)
    {
        Node* vertex = queue.top();
        queue.pop();

        for(auto edge_v : vertex -> neighbours)
            if(relax(vertex, edge_v.first, edge_v.second))
                queue.push(vertex);
    }
}

int main() {
    int N, k, start, end;

    cin >> N >> k;
    cin >> start >> end;

    Node *nodes[N];
    for (int i = 0; i < N; i++) nodes[i] = newNode(i);

    for (int i = 0; i < k; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(nodes[u], nodes[v], w);
    }

    dijkstra(nodes, N, nodes[start]);
    cout << nodes[end]->dist << endl;

    for (int i=0; i<N; i++) delete nodes[i];
}

