#ifndef UFO_H
#define UFO_H

#include<Curva.h>

class Ufo : public Objeto
{
public:
    Model3DS *modelo;
    float u;
    int p;
    int direcao;
    float velocidade;
    int r;

    Ufo();
    void desenha();
    void desenhaNaCurva(Curva &c, vector<Vetor3D> &pontosControle, Camera *camera);
    void mover();
    void mudaDirecao();
    void acelera();
    void desacelera();
};

#endif // UFO_H
