#include <iostream>
#include <vector>

using namespace std;

/*bool limite(int x, int y, int F, int C){

    if ((x <= F && x > 0) && (y <= C && y > 0)){
        return true;            
    }
    else{
        return false;
    }
} */

void generarMtriz(int F, int C, vector<vector<int>> matriz){
    
    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cout << matriz[i][j];
        }
        cout << "/n";
    }
}

int main(){
    int F = 5, C = 5;
    int x = 5, y = 5;
    int matriz[F][C];

    /*bool estaLimite = limite(x, y, F, C);

    if (estaLimite)
    {
        cout << "Si esta en el limite";
    }else
    {
        cout << "No esta en el limite";
    }*/
    generarMtriz(F, C, matriz);
    
return 0;
}