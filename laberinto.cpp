#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>

using namespace std;

// Símbolos
const string MURO   = "⬛";
const string CAMINO = "  ";
const string RUTA   = "🔷";
const string INICIO  = "🟩";
const string FIN    = "🟥";

// Direcciones (N, S, E, O)
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// Generación del laberinto usando Recursive Backtracker

vector<vector<int>> generarLaberinto(int R, int C) {
    int H = 2 * R + 1;
    int W = 2 * C + 1;

    vector<vector<int>> grid(H, vector<int>(W, 1)); // todo muros

    // semilla aleatoria
    mt19937 rng(time(0));

    // punto inicial
    int sx = 1, sy = 1;
    grid[sx][sy] = 0;

    stack<pair<int,int>> st;
    st.push({sx, sy});

    while (!st.empty()) {
       pair<int, int> current = st.top();
        int x = current.first;
        int y = current.second;

        vector<int> dirs = {0, 1, 2, 3};
        shuffle(dirs.begin(), dirs.end(), rng);

        bool moved = false;
        for (int dir : dirs) {
            int nx = x + 2*dx[dir];
            int ny = y + 2*dy[dir];
            if (nx > 0 && ny > 0 && nx < H-1 && ny < W-1 && grid[nx][ny] == 1) {
                // abrir muro intermedio
                grid[x + dx[dir]][y + dy[dir]] = 0;
                grid[nx][ny] = 0;
                st.push({nx, ny});
                moved = true;
                break;
            }
        }
        if (!moved) st.pop();
    }

    // entrada y salida
    grid[1][1] = 0;
    grid[H-2][W-2] = 0;

    return grid;
}

// ---------------------------------------------------------
// Mostrar laberinto en consola
// ---------------------------------------------------------
void mostrarLaberinto(const vector<vector<int>>& grid) {
    int H = grid.size();
    int W = grid[0].size();

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == 1 && j == 1) cout << INICIO;
            else if (i == H-2 && j == W-2) cout << FIN;
            else if (grid[i][j] == 1) cout << MURO;
            else if (grid[i][j] == 2) cout << RUTA;
            else cout << CAMINO;
        }
        cout << "\n";
    }
}

// ---------------------------------------------------------
// Resolver con BFS (ruta más corta)
// ---------------------------------------------------------
bool resolverBFS(vector<vector<int>>& grid) {
    int H = grid.size();
    int W = grid[0].size();
    pair<int,int> start = {1,1};
    pair<int,int> goal  = {H-2, W-2};

    queue<pair<int,int>> q;
    vector<vector<bool>> vis(H, vector<bool>(W, false));
    vector<vector<pair<int,int>>> parent(H, vector<pair<int,int>>(W, {-1,-1}));

    q.push(start);
    vis[start.first][start.second] = true;

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;

        if (make_pair(x,y) == goal) {
            // reconstruir camino
            while (make_pair(x,y) != start) {
                grid[x][y] = 2;
                int px = parent[x][y].first;
                int py = parent[x][y].second;
                x = px; y = py;
            }
            grid[start.first][start.second] = 2;
            return true;
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && ny >= 0 && nx < H && ny < W &&
                grid[nx][ny] == 0 && !vis[nx][ny]) {
                vis[nx][ny] = true;
                parent[nx][ny] = {x,y};
                q.push({nx,ny});
            }
        }
    }
    return false;
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // para que los emojis se vean bien

    int R = 8, C = 12; // número de celdas (no incluye muros)
    auto grid = generarLaberinto(R, C);

    cout << "🔹 Laberinto generado:\n";
    mostrarLaberinto(grid);

    cout << "\n🔹 Resolviendo con BFS...\n\n";
    resolverBFS(grid);

    cout << "🔹 Solución encontrada:\n";
    mostrarLaberinto(grid);

    return 0;
}
