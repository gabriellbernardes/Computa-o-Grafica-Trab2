#include "Ufo.h"

Ufo::Ufo()
{
    modelo = new Model3DS("../3DS/UFO.3DS");
    u = 0.0;
    p = 0;
    direcao = 1;
    velocidade = 0.01;
}

void Ufo::desenha()
{
    glPushMatrix();
        Objeto::desenha();

            glTranslatef(0, 0.5, 0);
            glRotatef(r+=4,0,1,0);
            r%=360;
            glRotatef(100, 1, 0, 0);
//        GUI::drawOrigin(0.5);
        glScalef(0.03, 0.03, 0.03);
        modelo->draw();
        glTranslatef(0, 0, 0);
    glPopMatrix();
}

void Ufo::desenhaNaCurva(Curva &curva,  vector<Vetor3D> &pontosControle, Camera *camera)
{
    int n = pontosControle.size();
    if(p <= -n || p >= n)
        p = 0;
    vector<Vetor3D> pontos(4);
    for(int j = 0; j < 4; j++)
    {
        pontos[j] = pontosControle[(p + j) % pontosControle.size()];
    }

    Vetor3D o = curva.pT(u, pontos, 0);

    Vetor3D k = curva.pT(u, pontos, 1) * (-1);
    k.normaliza();

    Vetor3D up = curva.pT(u, pontos, 2);
    Vetor3D i = up ^ k;
    i.normaliza();

    Vetor3D j = k ^ i;

    double T[] = {i.x, j.x, k.x, o.x,i.y, j.y, k.y, o.y, i.z, j.z, k.z, o.z, 0, 0, 0 , 1};

    glPushMatrix();
        glMultTransposeMatrixd(T);
        this->desenha();
    glPopMatrix();

    glLineWidth(100);
    glBegin(GL_LINES);
        GUI::setColor((float)(rand())/(float)(RAND_MAX)*1.0,(float)(rand())/(float)(RAND_MAX)*1.0,(float)(rand())/(float)(RAND_MAX)*1.0);
        glVertex3f(o.x, o.y, o.z);
        glVertex3f(0, 0, 0);
    glEnd();

    glEnable(GL_CULL_FACE);

    //Vetor3D desloc = j*(-.5) + k*5;
      camera->c = o -j;
      camera->u = j * (-1);
      camera->e = (k - j)*3 + o;


}

void Ufo::mover()
{
    u += velocidade * (direcao);
    if(u >= 1){
        u = 0.0;
        p++;
    }
    if(u < 0) {
        u = 0.99;
        p--;
    }
}

void Ufo::acelera(){

    if(velocidade<1){
        velocidade+=0.001;
    }
}
void Ufo::desacelera(){

    if(velocidade>0){
        velocidade-=0.001;
    }
}

void Ufo::mudaDirecao()
{
    direcao = -direcao;
}

