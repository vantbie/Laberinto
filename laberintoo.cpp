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
const string MURO = "⬛";
const string CAMINO = "  ";
const string RUTA = "🔹";
const string INICIO = "🟩";
const string FIN = "🟥";

// Direcciones
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// Generación del laberinto usando Backtracker

vector<vector<int>> generarLaberinto(int f, int c)
{
    int F = 2 * f + 1;
    int C = 2 * c + 1;

    vector<vector<int>> laberinto(F, vector<int>(C, 1)); // todo muros
    // semilla aleatoria
    mt19937 num_grande(time(0));

    // punto inicial
    int inicio_x = 1, inicio_y = 1;
    laberinto[inicio_x][inicio_y] = 0;

    stack<pair<int, int>> pila;
    pila.push({inicio_x, inicio_y});

    while (!pila.empty())
    {
        pair<int, int> corActual = pila.top();
        int x = corActual.first;
        int y = corActual.second;

        vector<int> direcciones = {0, 1, 2, 3};
        shuffle(direcciones.begin(), direcciones.end(), num_grande);

        bool mover = false;
        for (size_t i = 0; i < direcciones.size(); i++)
        {
            int dir = direcciones[i];

            int nx = x + 2 * dx[dir];
            int ny = y + 2 * dy[dir];
            if (nx > 0 && ny > 0 && nx < F - 1 && ny < C - 1 && laberinto[nx][ny] == 1)
            {

                // abrir muro intermedio
                laberinto[x + dx[dir]][y + dy[dir]] = 0;
                laberinto[nx][ny] = 0;
                pila.push({nx, ny});
                mover = true;
                break;
            }
        }
        if (!mover)
        {
            pila.pop();
        }
    }

    // Recorrer cada celda del laberinto
    for (int i = 1; i < F - 1; i++)
    {
        for (int j = 1; j < C - 1; j++)
        {

            // Si la celda es un muro
            if (laberinto[i][j] == 1)
            {

                // Verificar si a los lados hay caminos
                if (laberinto[i - 1][j] == 0 && laberinto[i + 1][j] == 0)
                {

                    // lanzar moneda
                    if (rand() % 2 == 0)
                    {
                        laberinto[i][j] = 0; // abrir muro
                    }
                }
            }
        }
    }
    return laberinto;
}

int validacion(void)
{
    int a;
    do
    {
        while (!(cin >> a)) // si la lectura falla
        {
            cin.clear();             // limpiar estado de error
            cin.ignore(10000, '\n'); // limpiar buffer
            cout << "Ingrese un valor numerico: ";
        }

        if (a <= 0 || a > 50)
        {
            cout << "Ingrese un valor dentro del limite  de 0 a 50 por favor: ";
        }
    } while (a <= 0 || a > 50);
    return a;
}

// Mostrar laberinto en consola
void mostrarLaberinto(vector<vector<int>> &laberinto)
{
    int F = laberinto.size();
    int C = laberinto[0].size();

    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (i == 1 && j == 1)
                cout << INICIO;
            else if (i == F - 2 && j == C - 2)
                cout << FIN;
            else if (laberinto[i][j] == 1)
                cout << MURO;
            else if (laberinto[i][j] == 2)
                cout << RUTA;
            else
                cout << CAMINO;
        }
        cout << "\n";
    }
}

// Resolver con BFS (ruta más corta)
bool resolverBFS(vector<vector<int>> &laberinto)
{

    int F = laberinto.size();
    int C = laberinto[0].size();

    pair<int, int> padre = {1, 1};
    pair<int, int> final = {F - 2, C - 2};

    queue<pair<int, int>> cola;
    vector<vector<bool>> corVisitadas(F, vector<bool>(C, false));
    vector<vector<pair<int, int>>> camino(F, vector<pair<int, int>>(C, {-1, -1}));

    cola.push(padre);
    corVisitadas[padre.first][padre.second] = true;

    while (!cola.empty())
    {
        pair<int, int> corActual = cola.front();
        cola.pop();
        int x = corActual.first;
        int y = corActual.second;

        if (make_pair(x, y) == final)
        {

            // reconstruir camino
            while (make_pair(x, y) != padre)
            {
                laberinto[x][y] = 2;
                int ax = camino[x][y].first;
                int ay = camino[x][y].second;
                x = ax;
                y = ay;
            }
            laberinto[padre.first][padre.second] = 2;
            return true;
        }

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && ny >= 0 && nx < F && ny < C && laberinto[nx][ny] == 0 && !corVisitadas[nx][ny])
            {
                corVisitadas[nx][ny] = true;
                camino[nx][ny] = {x, y};
                cola.push({nx, ny});
            }
        }
    }
    return false;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int F, C;
    cout << "Ingresa las filas para el laberinto: ";
    F = validacion();

    cout << "Ingresa las columnas para el laberinto: ";
    C = validacion();

    auto laberinto = generarLaberinto(F, C);

    cout << "🔹 Laberinto generado:\n";
    mostrarLaberinto(laberinto);

    cout << "\n🔹 Buscando la mejor ruta...\n\n";
    resolverBFS(laberinto);

    cout << "🔹 Solución encontrada:\n";
    mostrarLaberinto(laberinto);

    return 0;
}
