#include <iostream>

using namespace std;
#include <Ufo.h>
#include <gui.h>
#include <vector>
#include <texturemanager.h>
#include <nave.h>

//-------------------picking------------------
int r,t;
Model3DS *nave2 = new Model3DS("../3DS/Moon.3DS");
Nave *nave = new Nave();
GLuint sunTexture = NULL;
GLuint erica = NULL;

GLuint starsTexture = NULL;
GLuint terraTexture = NULL;
vector<Vetor3D> pontosControle;
TextureManager *textureManager = new TextureManager();
//Pista *test = new Pista();
float discretizacao =0.05;
Curva *curva = new Curva();
Ufo *ufo = new Ufo();
CameraDistante *camerad = new CameraDistante();
int pontoSelecionado = 0;

void estrela(int x , int y, int z){

    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(0.2,0.2,.5);
    glBegin(GL_POLYGON);
         glNormal3f(0,0,1.1);
         glVertex3f(0,0,0);
         glVertex3f(2.2,0,0);
         glVertex3f(2,2,0);
     glEnd();
     glBegin(GL_POLYGON);
          glNormal3f(0,0,1.1);
          glVertex3f(0.5,1.4,0);
          glVertex3f(0.8,-.6,0);
          glVertex3f(2.8,1,0);
      glEnd();
     glPopMatrix();

}

void enfeite(){

    glPushMatrix();
        glTranslatef(1,5,0);
        glRotatef(180,1,0,0);

     nave->desenha();
     glPopMatrix();

}

void desenhaPontosDeControle(){
    //desenhando pontos de controle
    for (int i=0; i<pontosControle.size(); i++) {
        //definindo cor da selecao

        //desenhando (definindo nomes para o picking)
        Vetor3D p = pontosControle[i];


        glPushName(i+1); //não se deve definir name = 0!
                //Desenhando o ponto

               // GUI::drawSphere(p.x,p.y,p.z,0.3);
        glPushMatrix();

        //desenhando a terra
        if(sunTexture == NULL ){
            sunTexture = textureManager->LoadBitmap("../textures/sun.bmp");
        }




        glTranslatef(p.x,p.y,p.z);


        if (i == pontoSelecionado-1) {
           glRotatef(t+1,0,1,0);

        }

        //glPushMatrix();

            glScalef(.005,.005,.005);
            glDisable(GL_CULL_FACE);
            glEnable(GL_COLOR_MATERIAL);
            glEnable (GL_TEXTURE_2D);
            glBindTexture (GL_TEXTURE_2D, sunTexture);
            nave2->draw();
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_COLOR_MATERIAL);

        //glPopMatrix();



        glPopMatrix();

        glPopName();
    }
}

//picking
int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);

//de acordo com a implementacao original da funcao display
    //lembrar de nao inicializar a matriz de projecao, para nao ignorar a gluPickMatrix
    GUI::displayInit();
    //só precisa desenhar o que for selecionavel
    desenhaPontosDeControle();
//fim-de acordo com a implementacao original da funcao display

    //retornando o name do objeto (ponto de controle) mais proximo da camera (z minimo! *[matrizes de normalizacao da projecao])
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}
//-------------------picking------------------

//-------------------viewPorts------------------

bool viewports = false;
bool scissored = false;
void cenario();
Camera *gopro = new CameraDistante();
//visao de duas cameras (duas viewports), viewport auxiliar sobrepondo a principal
void viewPorts() {
    float width = glutGUI::width;
    float height = glutGUI::height;

    //viewport principal
    glViewport(0, 0, width, height);
        glLoadIdentity();
        gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
            cenario();

    //viewport auxiliar sobrepondo a principal
    if (!scissored) {
        //misturando com a principal
        glViewport(0, 3*height/4, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, 3*height/4, width/4, height/4);
    }
        glLoadIdentity();
        gluLookAt(gopro->e.x,gopro->e.y,gopro->e.z,
                  gopro->c.x,gopro->c.y,gopro->c.z,
                  gopro->u.x,gopro->u.y,gopro->u.z);
            cenario();
}
//-------------------viewPorts------------------



void cenario() {
    GUI::setLight(1,20,30,15,true,false);
    GUI::setLight(2,-15,20,5,true,false);
    GUI::setLight(3,-25,40,5,true,false);
    GUI::setLight(0,15,15,0,true,false,false,false,false);

    GUI::drawOrigin(0.5);

    //GUI::setColor(1,0,0);
    //GUI::drawFloor();
    GUI::setColor(0,0,0);
    glPushMatrix();
    glTranslatef(0,-3,0);
    Desenha::drawGrid( 10, 0, 10, 1 );
    glPopMatrix();
//    test->desenha();
    desenhaPontosDeControle();
    ufo->desenhaNaCurva(*curva, pontosControle, gopro);
    ufo->mover();
    //discretizacao = .01; //distancia entre os rastros
    curva->desenhaCurva(pontosControle,discretizacao);
   // sol(5,5,5,10);

    if(starsTexture == NULL){
           starsTexture = textureManager->LoadBitmap("../textures/stars_milky_way.bmp");
    }
       //Desenhando fundo estrelado
       glPushMatrix();
           glDisable(GL_CULL_FACE);
           glEnable(GL_COLOR_MATERIAL);
           glEnable (GL_TEXTURE_2D);
           glBindTexture (GL_TEXTURE_2D, starsTexture);
           GUI::drawSphere(0, 0, 0, 100);
           glDisable(GL_TEXTURE_2D);
           glDisable(GL_COLOR_MATERIAL);
       glPopMatrix();


        //desenhando a terra
        if(terraTexture == NULL){
            terraTexture = textureManager->LoadBitmap("../textures/terra.bmp");
        }

        glPushMatrix();
            glRotatef(r+=1,0,1,0);
            glRotatef(t+=2,1,0,1);
            r%=360;
            t%=360;

            glDisable(GL_CULL_FACE);
            glEnable(GL_COLOR_MATERIAL);
            glEnable (GL_TEXTURE_2D);
            glBindTexture (GL_TEXTURE_2D, terraTexture);
            GUI::drawSphere(0, 0, 0, 2);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_COLOR_MATERIAL);

        glPopMatrix();

        //desenhando a terra
        if(erica == NULL){
            erica = textureManager->LoadBitmap("../textures/moon.bmp");
        }

        glPushMatrix();
            glRotatef(r,0,1,0);
           // glRotatef(t,1,0,0);
            glRotatef(t,0,0,1);
            r%=360;
            t%=360;

            glDisable(GL_CULL_FACE);
            glEnable(GL_COLOR_MATERIAL);
            glEnable (GL_TEXTURE_2D);
            glBindTexture (GL_TEXTURE_2D, erica);
            GUI::drawSphere(3, 3, 3, 1);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_COLOR_MATERIAL);

        glPopMatrix();

//        glPushMatrix();
//            glTranslatef(4,2,4);
//            glRotatef(r,0,1,0);
//            glRotatef(t,1,0,1);

//            nave->desenha();
//            glPopMatrix();;

}


void desenha() {
    GUI::displayInit();

    if (!viewports) {
        cenario();
    } else {
        viewPorts();
    }

    //transladando ponto selecionado atraves do picking
    //if (pontoSelecionado > 0 and pontoSelecionado <= objetos.size()) {
    if (pontoSelecionado!=0) {
        pontosControle[pontoSelecionado-1].x += glutGUI::dtx;
        pontosControle[pontoSelecionado-1].y += glutGUI::dty;
        pontosControle[pontoSelecionado-1].z += glutGUI::dtz;
    }

    GUI::displayEnd();
}

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        //transPontos = glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'v':
        viewports = !viewports;
        break;
    case 's':
        scissored = !scissored;
        break;
    case '.':
        ufo->acelera();
        break;
    case ',':
        ufo->desacelera();
        break;
    case ';':
        ufo->mudaDirecao();
        break;
    case 'p':
        pontosControle.push_back(Vetor3D(0,5,0));
        break;
    case 'P':
        pontosControle.erase(pontosControle.begin()+pontoSelecionado-1);
        break;
    case '1':
        curva->mudaMatriz(I);
        break;
    case '2':
        curva->mudaMatriz(H);
        break;
    case '3':
        curva->mudaMatriz(B);
        break;
    case '4':
        curva->mudaMatriz(CM);
        break;
    case '5':
        curva->mudaMatriz(BS);
        break;
    case 'a':
        if(discretizacao<1){
            discretizacao+=.01;
        }
        break;
    case 'A':
        if(discretizacao>0.001){
            discretizacao-=.01;
            if(discretizacao<0.001){
                discretizacao=0.001;
            }
        }
        break;
    case 'e':
        glutGUI::cam = gopro;
        break;
    case 'E':
        glutGUI::cam = camerad;
        break;

    default:
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick;
                glutGUI::lbpressed = false;
            }
        }
    }
}

void mapeamento()
{
    cout << "Teclas mapeadas:" << endl;
    cout << "\t'1': Interpoladora" << endl;
    cout << "\t'2': Hermite" << endl;
    cout << "\t'3': Bezier" << endl;
    cout << "\t'4': Catmull-Rom" << endl;
    cout << "\t'5': BSpline" << endl;
    cout << "'a'|'A' para diminuir/aumentar a discretização" << endl;
    cout << "';' para mudar direção" << endl;
    cout << "'.' para aumentar a velocidade" << endl;
    cout << "',' para adiminuir a velocidade" << endl;
    cout << "'E/e' para mudar a visão" << endl;
    cout << "'v' para exibir viewport" << endl;
    cout << "'Q' para mudar a visão quando exibindo o viewport" << endl;
    cout << "'s' para alternar o recorte" << endl;
    }

int main()
{
    cout << "Hello World!" << endl;



    pontosControle.push_back(Vetor3D(0,6,0));
    pontosControle.push_back(Vetor3D(7,5,-10));
    pontosControle.push_back(Vetor3D(9,0,0));
   pontosControle.push_back(Vetor3D(7,-5,10));
    pontosControle.push_back(Vetor3D(0,-6,0));
    pontosControle.push_back(Vetor3D(-7,-5,-10));
    pontosControle.push_back(Vetor3D(-9,0,0));
    pontosControle.push_back(Vetor3D(-7,5,10));



    mapeamento();
    GUI gui = GUI(800,600,desenha,teclado,mouse);

}



