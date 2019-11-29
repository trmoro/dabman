#pragma once //Inclut une seul fois dans le compilateur

#include <iostream>

#include <math.h>
#define PI  3.14159265358979323846f

#include "GL/glut.h"

struct Animation
{
    int angle;
    int axeX;
    int axeY;
    int axeZ;

    float vF; //valeur flotante
};

class Dabman
{
public:
    void affichage();

    void setTexture(GLuint corps, GLuint visage,GLuint botte, GLuint gant);

    void setColor(float r, float g, float b);

    Animation a_Nez;

    Animation a_BrasGauche;
    Animation a_AvantBrasGauche;

    Animation a_BrasDroit;
    Animation a_AvantBrasDroit;

    Animation a_CuisseGauche;
    Animation a_MolletGauche;

    Animation a_CuisseDroite;
    Animation a_MolletDroit;

private:
    void cylindre(unsigned int n, float rayon, float hauteur);
    void cercle(unsigned int n, float rayon);

    void pointSphere(float rayon, float u, float v);
    void sphere(unsigned int nM, unsigned int nP, float rayon);

    float m_r;
    float m_g;
    float m_b;

    GLuint m_tex_corps;
    GLuint m_tex_visage;
    GLuint m_tex_botte;
    GLuint m_tex_gant;
};
