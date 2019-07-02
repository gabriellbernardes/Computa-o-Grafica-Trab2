#include "nave.h"

Nave::Nave()
{

    modelo = new Model3DS("../3DS/arma2.3DS");
    //modelo2 = new Model3DS("../3ds/arma3.3DS");

}

void Nave::desenha()
{
      Objeto::desenha();
    glPushMatrix();

         glPushMatrix();

             glScalef(0.05,0.05,0.05);
             modelo->draw();


        glPopMatrix();



    glPopMatrix();
}
