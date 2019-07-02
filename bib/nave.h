#ifndef NAVE_H
#define NAVE_H

#include <Objeto.h>

class Nave : public Objeto
{

public:
    Model3DS *modelo;
    //Model3DS *modelo2;
    Nave();
    void desenha();
};

#endif // NAVE_H
