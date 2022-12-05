#include <iostream>
#include <iomanip>
#include <set>
#include <list>
#include <queue>
using namespace std;

class Graph {
private:
    int** G;
    int numVertex;
public:
    Graph(int numVertex)
    {
        this->numVertex = numVertex;
        G = new int* [numVertex];
        for (int i = 0; i < numVertex; i++) {
            G[i] = new int[numVertex];
            for (int j = 0; j < numVertex; j++)
                G[i][j] = 0;
        }
    }
    ~Graph() {
        for (int i = 0; i < numVertex; i++)
            delete[] G[i];
        delete[] G;
    }
    void addEdge(int i, int j, int w, int u) 
    {
        u==0 ? G[i][j]=w : u==1 ? G[j][i] = w : G[i][j] = G[j][i] = w;
    }
    void toString() {
        for (int i = 0; i < numVertex; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertex; j++) {
                cout << setw(5) << G[i][j] << " ";
            }
            cout << endl;
        }
    }

    void Dijkstra(int st);
    void shortestPath(int st);

    void infograph();
};

void Graph::Dijkstra(int st)
{
    int* distance = new int[numVertex];
    bool* visited = new bool[numVertex];
    int count, index;

    for (int i = 0; i < numVertex; i++)
        distance[i] = INT_MAX, visited[i] = false;

    distance[st] = 0;

    for (count = 0; count < numVertex - 1; count++)
    {
        int min = INT_MAX;
        for (int i = 0; i < numVertex; i++)
            if (!visited[i] && distance[i] <= min)
            {
                min = distance[i]; index = i;
            }

        int u = index;
        visited[u] = true;
        for (int i = 0; i < numVertex; i++)
            if (!visited[i] && G[u][i] && distance[u] != INT_MAX && distance[u] + G[u][i] < distance[i])
                distance[i] = distance[u] + G[u][i];
    }

    cout << "Стоимость пути из начальной вершины до остальных:\t\n";
    for (int i = 0; i < numVertex; i++)
        if (distance[i] != INT_MAX)
            cout << st << " > " << i << " = " << distance[i] << endl;
        else
            cout << st << " > " << i << " = " << "маршрут недоступен" << endl;

    delete[] distance;
    delete[] visited;
}

void Graph::shortestPath(int st)
{
    int* dist = new int[numVertex];
    int* visit = new int[numVertex];

    for (int i = 0; i < numVertex; i++)
        visit[i] = false, dist[i] = INT_MAX;

    dist[st] = 0;
    visit[st] = true;

    queue<int>q;
    q.push(st);

    while (!q.empty()) {
        int t = q.front(); 
        q.pop(); 
        for (int i = 0; i < numVertex; i++) {
            if (!visit[i] && G[t][i] && G[t][i] + dist[t] < dist[i])
            { // Ставим условия заходим только если вершина не посещена, с этой вершиной есть ребро, расстояние между вершинами меньше чем уже существует
                dist[i] = G[t][i] + dist[t];
                q.push(i);
            }
        }
    }
    cout << "Стоимость пути из начальной вершины до остальных:\t\n";
    for (int i = 0; i < numVertex; i++)
        if (dist[i] != INT_MAX)
            cout << st << " > " << i << " = " << dist[i] << endl;
        else
            cout << st << " > " << i << " = " << "маршрут недоступен" << endl;

    delete[] dist;
    delete[] visit;
}

void Graph::infograph()
{
    int* ext= new int[numVertex];;
    set <int> center, pereph;
    int rad = INT_MAX, diam;
    int **d= new int* [numVertex];
    for (int i = 0; i < numVertex; i++) 
        d[i] = new int[numVertex];

    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < numVertex; k++) {
        for (int j = 0; j < numVertex; j++) {
            for (int i = 0; i < numVertex; i++) {
                d[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }

    // Нахождение эксцентриситета
    for (int i = 0; i < numVertex; i++) {
        for (int j = 0; j < numVertex; j++) {
            ext[i] = max(ext[i], d[i][j]);
        }
    }

    for (int i = 0; i < numVertex; i++) {
        if (min(rad, ext[i])>0) {
            rad = min(rad, ext[i]);
        }
        diam = max(diam, ext[i]);
    }

    for (int i = 0; i < numVertex; i++) {
        if (ext[i] == rad) {
            center.insert(i);
        }
    }

    for (int i = 0; i < numVertex; i++) {
        if (ext[i] == diam) {
            pereph.insert(i);
        }
    }

    cout << endl << "Диаметр: " << diam << endl << "Радиус: " << rad << endl;

    cout << endl << "множества периферийных вершин: ";
    for (int i : pereph)
        cout << i<<" ";
    cout << endl << "множества центральных вершин: ";
    for (int i : center)
        cout << i<<" ";

    for (int i = 0; i < numVertex; i++)
        delete[] d[i];
    delete[] d;
    delete[]ext;
}

int main(int argc, char* argv[])
{
    setlocale(0,"");
    srand(time(0));
    int z = 7;
    Graph c(z);

    cout << argv[0]<<endl;
    //int k, b; cin >> b >> k;

    if (argv[argc-2]=="1" && argv[argc-1]=="1") {
    //if (b == 1 && k == 1) {
        for (int i = 0; i < z; i++)
        {
            for (int j = i + 1; j < z; j++)
            {
                if (0 < (rand() % 3)) {
                    c.addEdge(i, j, 1, 3);
                }
            }
        }
    }
    if (argv[argc-2]=="1" && argv[argc-1]=="2") {
    //if (b == 1 && k == 2) {
        for (int i = 0; i < z; i++)
        {
            for (int j = i + 1; j < z; j++)
            {
                if (0 < (rand() % 3)) {
                    c.addEdge(i, j, 1, rand() % 3);
                }
            }
        }
    }

    if (argv[argc-2]=="2" && argv[argc-1]=="1") {
    //if (b==2 && k==1) {
        for (int i = 0; i < z; i++)
        {
            for (int j = i + 1; j < z; j++)
            {
                if (0<(rand() % 3)) {
                    c.addEdge(i, j, rand() % 50, 3);
                }
            }
        }
    }
    if (argv[argc-2]=="2" && argv[argc-1] == "2") {
        //if (b==2 && k==2) {
        for (int i = 0; i < z; i++)
        {
            for (int j = i + 1; j < z; j++)
            {
                if (0<(rand() % 3)) {
                    c.addEdge(i, j, rand() % 50, rand()%3);
                }
            }
        }
    }

    cout << "Матрица смежности: \n";
    c.toString();

    cout << endl; c.infograph(); cout << endl;

    int start;
    cout << endl << "Стартовая вершина > "; cin >> start;
    c.Dijkstra(start);
    cout << endl;
    c.shortestPath(start);

    return 0;
}

