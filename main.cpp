#include <iostream>
#include <math.h>

#include <time.h>

#include <jpeglib.h>
#include <jerror.h>

#include "GL/glut.h"

#include "Dabman.h"

#define PI  3.14159265358979323846f

//Model
Dabman* gwendal;

//Camera
float angleU;
float angleV;
float angleRayon = 5;

//Lumière
bool LumiereON = true;

//Taille de la fenêtre
float widthScreen = 500;
float heightScreen = 500;

//Texture
#define I_W 256
#define I_H 256
unsigned char td_visage[I_W*I_H*3];
unsigned char td_corps[I_W*I_H*3];
unsigned char td_botte[I_W*I_H*3];
unsigned char td_gant[I_W*I_H*3];

//Couleur Incrémentée
unsigned int incColor = 0;


//Affichage
void affichage()
{
    //Nettoie les buffers
    if(LumiereON)
        glClearColor(0.89f,0.9f,0.91f,1);
    else
        glClearColor(0.01f,0.02f,0.03f,1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Rotation de la caméra
    gluPerspective(60,widthScreen/heightScreen,0.5,1000);

    float cX = angleRayon * cos(angleU) * cos(angleV);
    float cY = angleRayon * sin(angleV);
    float cZ = angleRayon * sin(angleU) * cos(angleV);

    gluLookAt(cX,cY,cZ, 0,0,0 ,0,1,0);

    //gluLookAt(-5,5,-5, 0,0,0 ,0,1,0);

    ///Variable des lumières

    //Pour L1 (Lumière Mobile)
    GLfloat l1Pos[3] = {cX,cY,cZ};
    GLfloat l1Dir[3] = {-cX,-cY,-cZ};

    GLfloat l1Amb[3] =  {0,0,0};
    GLfloat l1Diffuse[3] =  {0.6,0.6,0.6};
    GLfloat l1Specu[3] =  {0,0,0};

    GLfloat l1Shineness[] =  {0.0};

    //Pour L2 (Lumière Fixe)
    GLfloat l2Pos[3] = {50,50,50};

    GLfloat l2Amb[3] =  {0.4,0.4,0.4};
    GLfloat l2Diffuse[3] =  {0.85,0.8,0.8};
    GLfloat l2Specu[3] =  {1,1,1};

    GLfloat l2Shineness[] =  {100.0};

    //Affichage

    ///Pour L1
    if(incColor % 2 == 0)
    {
        //glClearColor(abs(cX / angleRayon) * 3,abs(cY / angleRayon) * 3,abs(cZ / angleRayon) * 3,1.0);
        l1Specu[0] =  cX / angleRayon;
        l1Specu[1] =  cY / angleRayon;
        l1Specu[2] =  cZ / angleRayon;

    }
    else
    {
        l1Specu[0] =  cZ / angleRayon;
        l1Specu[1] =  cX / angleRayon;
        l1Specu[2] =  cY / angleRayon;

    }

    ///Applique Lumière

    //L1 Light 0
    if(!LumiereON)
    {
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glLightfv(GL_LIGHT0,GL_POSITION,l1Pos);

        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,l1Amb);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,l1Diffuse);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,l1Specu);

        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l1Dir);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2);

        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,l1Shineness);

    }
    //L2 : Lumière Ambiante (Light 1)
    else
    {
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT0);

        //N'étant pas la lumière par défaut, il faut définir tous les paramètres
        glLightfv(GL_LIGHT1,GL_POSITION,l2Pos);
        glLightfv(GL_LIGHT1, GL_AMBIENT,l2Amb);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,l2Diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR,l2Specu);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,1.5f);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5f);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2f);


        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,l2Amb);

        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,l2Amb);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,l2Diffuse);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,l2Specu);

        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,l2Shineness);
    }



    ///Animation
    gwendal->setColor(1,1,1);

    gwendal->a_BrasGauche.angle+= 5;
    gwendal->a_BrasGauche.axeY = 1;

    gwendal->a_AvantBrasGauche.angle+= 5;
    gwendal->a_AvantBrasGauche.axeZ = 1;

    gwendal->a_BrasDroit.angle+= 5;
    gwendal->a_BrasDroit.axeY = 1;

    gwendal->a_AvantBrasDroit.angle+= 5;
    gwendal->a_AvantBrasDroit.axeZ = 1;

    gwendal->a_CuisseGauche.angle+= 5;
    gwendal->a_CuisseGauche.axeZ = 1;

    gwendal->a_MolletGauche.angle+= 5;
    gwendal->a_MolletGauche.axeZ = 1;

    gwendal->a_CuisseDroite.angle+= 5;
    gwendal->a_CuisseDroite.axeZ = 1;

    gwendal->a_MolletDroit.angle+= 5;
    gwendal->a_MolletDroit.axeZ = 1;
    //

    gwendal->affichage();

    glFlush();


    //On echange les buffers
    glutSwapBuffers();
}

//Clavier
void clavier(unsigned char touche,int x,int y)
{
    //Incrémentation par le clavier
    switch (touche)
    {
     case 'z':
        if(angleRayon > 0.05f)
            angleRayon -= 0.05f;
       break;
     case 'Z':
        angleRayon += 0.05f;
        break;
     case 'c':
      incColor++;
      break;
     case 'C':
      angleV += 0.05f;
      angleU += 0.05f;
      incColor++;
      break;
     case 'l':
      LumiereON = false;
      break;
    case 'L':
      LumiereON = true;
      break;
    }

   glutPostRedisplay();
}

//Fleche Clavier
void fleche(int key, int x,int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
      angleV += 0.05f;
      break;
    case GLUT_KEY_DOWN:
      angleV -= 0.05f;
      break;
     case GLUT_KEY_LEFT:
      angleU += 0.05f;
      break;
     case GLUT_KEY_RIGHT:
      angleU -= 0.05f;
      break;
    }

   glutPostRedisplay();
}

//Reshape (Source : TP1)
void reshape(int x,int y)
{
  widthScreen = x;
  heightScreen = y;
  glutPostRedisplay();

  glViewport(0,0,x,y);

}

//Source : TP3
void loadJpegImage(char *fichier, unsigned char* image)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *file;
  unsigned char *ligne;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
#ifdef __WIN32
  if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
  if ((file = fopen(fichier,"rb")) == 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#endif
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  /*
  if ((cinfo.image_width!=256)||(cinfo.image_height!=256)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
    exit(1);
  }*/
  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=image;

  //Lis l'image ligne par ligne
  while (cinfo.output_scanline<cinfo.output_height)
    {

      ligne=image+3*I_W*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }


  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
}

//Main
int main(int argc,char **argv)
{
    std::cout << "Hello world!" << std::endl;

    srand(time(NULL));

 /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(widthScreen,heightScreen);
  glutCreateWindow("Dabman");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  //Création des textures
  GLuint visage,corps,botte,gant;

  loadJpegImage("texture/texCorps.jpg",td_corps);
  loadJpegImage("texture/texVisage.jpg",td_visage);
  loadJpegImage("texture/texBotte.jpg",td_botte);
  loadJpegImage("texture/texGant.jpg",td_gant);

  glGenTextures(1, &corps);
  glBindTexture(GL_TEXTURE_2D,corps);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,I_W,I_H,0,GL_RGB,GL_UNSIGNED_BYTE,td_corps);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D,0);

  glGenTextures(1, &visage);
  glBindTexture(GL_TEXTURE_2D,visage);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,I_W,I_H,0,GL_RGB,GL_UNSIGNED_BYTE,td_visage);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D,0);

  glGenTextures(1, &botte);
  glBindTexture(GL_TEXTURE_2D,botte);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,I_W,I_H,0,GL_RGB,GL_UNSIGNED_BYTE,td_botte);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D,0);

  glGenTextures(1, &gant);
  glBindTexture(GL_TEXTURE_2D,gant);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,I_W,I_H,0,GL_RGB,GL_UNSIGNED_BYTE,td_gant);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D,0);

  //Naissance de Gwendal
  gwendal = new Dabman();
  gwendal->setTexture(corps,visage,botte,gant);


  /* enregistrement des fonctions de rappel*/
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutSpecialFunc(fleche);
  glutReshapeFunc(reshape);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}
