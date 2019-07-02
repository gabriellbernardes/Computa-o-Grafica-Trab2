#include "Curva.h"

Curva::Curva()
{
    for(int i = 0; i < 4; i++)
        Matriz.push_back(vector<float>(4));
    Matriz = Bspline();
    pista = new Pista();
}

vector<vector<float> > Curva::Interpoladora()
{
    vector<vector<float>> Matriz = {
        {-4.5, 13.5, -13.5, 4.5},
        {9, -22.5, 18, -4.5},
        {-5.5, 9, -4.5, 1},
        {1, 0, 0, 0}
    };

    return Matriz;
}

vector<vector<float> > Curva::Hermite()
{
    vector<vector<float>> Matriz = {
        {2, -2, 1, 1},
        {-3, 3, -2, -1},
        {0, 0, 1, 0},
        {1, 0, 0, 0}
    };

    return Matriz;
}

vector<vector<float> > Curva::Bezier()
{
    vector<vector<float>> Matriz = {
        {-1, 3, -3, 1},
        {3, -6, 3, 0},
        {-3, 3, 0, 0},
        {1, 0, 0, 0}
    };

    return Matriz;
}


vector<vector<float> > Curva::CatmullRom()
{
    vector<vector<float>> Matriz = {
        {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
        {2/2.0, -5/2.0, 4/2.0, -1/2.0},
        {-1/2.0, 0.0, 1/2.0, 0.0},
        {0.0, 2/2.0, 0.0, 0.0}
    };

    return Matriz;
}

vector<vector<float> > Curva::Bspline()
{
    vector<vector<float>> Matriz = {
        {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
        {3/6.0, -6/6.0, 3/6.0, 0},
        {-3/6.0, 0, 3/6.0, 0},
        {1/6.0, 4/6.0, 1/6.0, 0}
    };

    return Matriz;
}

Vetor3D Curva::pT(float u, const vector<Vetor3D>& points, int degree){

    Vetor3D P(0, 0, 0);
    double U[4];
    if(degree == 0)
        double U[4] = {pow(u, 3), pow(u, 2), u, 1};
    else if(degree == 1)
        double U[4] = {3*pow(u, 2), 2*u, 1, 0};
    else
        double U[4] = {6*u, 2, 0, 0};

    float M[4];

    for(int i = 0; i < 4; i++){
        M[i] = 0;
        for(int j = 0; j < 4; j++){
            M[i] += U[j] * Matriz[j][i];
        }
    }

    for(int i = 0; i<4; i++){
        P.x += M[i] * points[i].x;
        P.y += M[i] * points[i].y;
        P.z += M[i] * points[i].z;
    }

    return P;
}

void Curva::mudaMatriz(matriz M)
{
    switch (M) {
    case I:
        Matriz = Interpoladora();
        break;
    case H:
        Matriz = Hermite();
        break;
    case B:
        Matriz = Bezier();
        break;
    case CM:
        Matriz = CatmullRom();
        break;
    case BS:
        Matriz = Bspline();
        break;
    }
};

void Curva::desenhaCurva(const vector<Vetor3D> &pontosControle, float delta_u)
{
    vector<Vetor3D> pontos(4);
    for(int i = 0; i < pontosControle.size(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            pontos[j] = pontosControle[(i + j) % pontosControle.size()];
        }

        float dist = pontos[0].getDistance(pontos[3]);
        for(float u = 0; u <= 1; u += delta_u)
        {
            Vetor3D o = pT(u, pontos, 0);

            Vetor3D k = pT(u, pontos, 1) * (-1);
            k.normaliza();

            Vetor3D up = pT(u, pontos, 2);
            Vetor3D i = up ^ k;
            i.normaliza();

            Vetor3D j = k ^ i;

            double T[] = {
                i.x, j.x, k.x, o.x,
                i.y, j.y, k.y, o.y,
                i.z, j.z, k.z, o.z,
                0   , 0   , 0   , 1
            };

            glPushMatrix();
                glMultTransposeMatrixd(T);
                glScalef(1, 1, delta_u * dist);
                pista->desenha();
            glPopMatrix();
        }
    }
}

