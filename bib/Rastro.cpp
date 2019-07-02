#include "Rastro.h".h"

Rastro::Rastro()
{

}

void Rastro::desenha()
{
    glPushMatrix();
        Objeto::desenha();
        GUI::setColor(1, 1, 0);
        glBegin(GL_POLYGON);
            glNormal3f(0, -1, 0);
            glVertex3f(0, 1, 0);
            glVertex3f(-1, 0, 0);
            glVertex3f(1, 0, 0);
        glEnd();
        GUI::setColor(0, 0, 0);

    glPopMatrix();
}
