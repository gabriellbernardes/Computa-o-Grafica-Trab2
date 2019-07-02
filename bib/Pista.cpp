#include "Pista.h"

Pista::Pista()
{

}

void Pista::desenha()
{

       Objeto::desenha();

       glPushMatrix();
            GUI::setColor(0, 0, 1);
            glBegin(GL_QUADS);
                glNormal3f(0, -1, 0);
                glVertex3f(-0.5, 0, -0.5);
                glVertex3f(0.5, 0, -0.5);
                glVertex3f(0.5, 0, 0.5);
                glVertex3f(-0.5, 0, 0.5);
            glEnd();


            GUI::setColor(1, 1, 1);
            glBegin(GL_QUADS);
                glNormal3f(0, 1, 0);
                glVertex3f(-0.5, 0, -0.5);
                glVertex3f(-0.5, 0, 0.5);
                glVertex3f(0.5, 0, 0.5);
                glVertex3f(0.5, 0, -0.5);
            glEnd();
        glPopMatrix();
}

