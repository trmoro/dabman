#include "Dabman.h"

void Dabman::affichage()
{
    //On isole le model
    glPushMatrix();

    /////////////////Repère
    //axe x en rouge
    glBegin(GL_LINES);
        //glColor3f(1.0,0.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    	//glColor3f(0.0,1.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    	//glColor3f(0.0,0.0,1.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 0,1.0);
    glEnd();

    /////////////////////Dabman !
    //Couleur global
    glColor3f(m_r,m_g,m_b);

    //Tète
    glBindTexture(GL_TEXTURE_2D,m_tex_visage);
    glPushMatrix();
        sphere(100,150,1);
    glPopMatrix();

    //Texture du Corps
    glBindTexture(GL_TEXTURE_2D,m_tex_corps);

    //glDisable(GL_TEXTURE_2D);

    //Nez
    glPushMatrix();

        glRotatef(a_Nez.angle,a_Nez.axeX,a_Nez.axeY,a_Nez.axeZ);

        glRotatef(90,1,0,0); // Le nez se retrouve sur l'axe z
        glTranslatef(0,0.8,0);
        cylindre(20,0.1,0.5 + a_Nez.vF);

        glTranslatef(0,0.5 + a_Nez.vF,0);
        glutSolidSphere(0.1,30,20);

    glPopMatrix();

    //Bras (axe : x)
    glPushMatrix();

        //Bras gauche
        glPushMatrix();

            glRotatef(a_BrasGauche.angle,a_BrasGauche.axeX,a_BrasGauche.axeY,a_BrasGauche.axeZ);

            glRotatef(90,0,0,1);
            glTranslatef(0,0.9,0);
            cylindre(20,0.1,0.6);

            glTranslatef(0,0.6,0);

            //glColor3f(m_g,m_b,m_r);
                glutSolidSphere(0.15,30,20);
            //glColor3f(m_r,m_g,m_b);

            //L'avant Bras (enfin tu sais ce que je veux dire wesh)
            glPushMatrix();

                glRotatef(a_AvantBrasGauche.angle,a_AvantBrasGauche.axeX,a_AvantBrasGauche.axeY,a_AvantBrasGauche.axeZ);

                cylindre(20,0.1,0.7);

                glTranslatef(0,0.85,0);
                glBindTexture(GL_TEXTURE_2D,m_tex_gant);
                    glutSolidSphere(0.25,30,20);
                glBindTexture(GL_TEXTURE_2D,m_tex_corps);

            glPopMatrix();

        glPopMatrix();

        //Bras droit
        glPushMatrix();

            glRotatef(a_BrasDroit.angle,a_BrasDroit.axeX,a_BrasDroit.axeY,a_BrasDroit.axeZ);

            glRotatef(-90,0,0,1);
            glTranslatef(0,0.9,0);
            cylindre(20,0.1,0.6);

            glTranslatef(0,0.6,0);
            //glColor3f(m_g,m_b,m_r);
                glutSolidSphere(0.15,150,100);
            //glColor3f(m_r,m_g,m_b);

            //Avant-Bras Droit
            glPushMatrix();

                glRotatef(a_AvantBrasDroit.angle,a_AvantBrasDroit.axeX,a_AvantBrasDroit.axeY,a_AvantBrasDroit.axeZ);

                cylindre(20,0.1,0.7);

                glTranslatef(0,0.85,0);
                glBindTexture(GL_TEXTURE_2D,m_tex_gant);
                    glutSolidSphere(0.25,150,100);
                glBindTexture(GL_TEXTURE_2D,m_tex_corps);

            glPopMatrix();

        glPopMatrix();

    glPopMatrix();

    //Jambe (axe : y et x)
    glPushMatrix();

        //Jambe gauche
        glPushMatrix();

            glRotatef(a_CuisseGauche.angle,a_CuisseGauche.axeX,a_CuisseGauche.axeY,a_CuisseGauche.axeZ);

            glTranslatef(0.4,-1.5,0);
            cylindre(20,0.1,0.6);

            glTranslatef(0,-0.1,0);
            //glColor3f(m_g,m_b,m_r);
                glutSolidSphere(0.15,30,20);
            //glColor3f(m_r,m_g,m_b);

            //Mollet
            glPushMatrix();

                glRotatef(a_MolletGauche.angle,a_MolletGauche.axeX,a_MolletGauche.axeY,a_MolletGauche.axeZ);

                glTranslatef(0,-0.7,0);
                cylindre(20,0.1,0.6);

                glTranslatef(0,-0.1,0);
                //glColor3f(m_g,m_b,m_r);
                    glutSolidSphere(0.15,30,20);
                //glColor3f(m_r,m_g,m_b);

                //Pied
                glBindTexture(GL_TEXTURE_2D,m_tex_botte);
                glTranslatef(0,-0.1,-0.05);
                glPushMatrix();
                    glRotatef(90,1,0,0);
                    cylindre(20,0.15,0.5);

                    glTranslatef(0,0.5,0);
                    glutSolidSphere(0.15,30,20);
                glPopMatrix();
                glBindTexture(GL_TEXTURE_2D,m_tex_corps);

            glPopMatrix();


        glPopMatrix();

        //Jambe droite
        glPushMatrix();

            glRotatef(a_CuisseDroite.angle,a_CuisseDroite.axeX,a_CuisseDroite.axeY,a_CuisseDroite.axeZ);

            glTranslatef(-0.4,-1.5,0);
            cylindre(20,0.1,0.6);

            glTranslatef(0,-0.1,0);
            ////glColor3f(m_g,m_b,m_r);
                glutSolidSphere(0.15,30,20);
            ////glColor3f(m_r,m_g,m_b);

            //Mollet
            glPushMatrix();

                glRotatef(a_MolletDroit.angle,a_MolletDroit.axeX,a_MolletDroit.axeY,a_MolletDroit.axeZ);

                glTranslatef(0,-0.7,0);
                cylindre(20,0.1,0.6);

                glTranslatef(0,-0.1,0);
                ////glColor3f(m_g,m_b,m_r);
                    glutSolidSphere(0.15,30,20);
                ////glColor3f(m_r,m_g,m_b);

                //Pied
                glBindTexture(GL_TEXTURE_2D,m_tex_botte);
                glTranslatef(0,-0.1,-0.05);
                glPushMatrix();
                    glRotatef(90,1,0,0);
                    cylindre(20,0.15,0.5);

                    glTranslatef(0,0.5,0);
                    glutSolidSphere(0.15,30,20);
                glPopMatrix();
                glBindTexture(GL_TEXTURE_2D,0);

            glPopMatrix();

        glPopMatrix();

    glPopMatrix();

  //On le ramène
  glPopMatrix();
}

//Set color
void Dabman::setColor(float r, float g, float b)
{
    m_r = r;
    m_g = g;
    m_b = b;
}

//Cylindre
void Dabman::cylindre(unsigned int n, float rayon, float hauteur)
{
    //Cercle inférueur
    glPushMatrix();
        glNormal3f(0,-1,0);
        cercle(n,rayon);
    glPopMatrix();

    //Cercle supérieur
    glPushMatrix();
        glNormal3f(0,1,0);
        glTranslatef(0,hauteur,0);
        cercle(n,rayon);
    glPopMatrix();

    //Le tour du cylindre
    glBegin(GL_QUADS);
    for(unsigned int i = 0; i <= n; i++)
    {
        glNormal3f(cos(2*PI*i/n),0,sin(2*PI*i/n));
        glVertex3f(cos(2*PI*i/n)*rayon,0,sin(2*PI*i/n)*rayon);
        glVertex3f(cos(2*PI*i/n)*rayon,hauteur,sin(2*PI*i/n)*rayon);

        glNormal3f(cos(2*PI*(i+1)/n),0,sin(2*PI*(i+1)/n));
        glVertex3f(cos(2*PI*(i+1)/n)*rayon,hauteur,sin(2*PI*(i+1)/n)*rayon);
        glVertex3f(cos(2*PI*(i+1)/n)*rayon,0,sin(2*PI*(i+1)/n)*rayon);
    }
    glEnd();
}

//Cercle
void Dabman::cercle(unsigned int n, float rayon)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    for(unsigned int i = 0; i <= n; i++)
        glVertex3f(cos(2*PI*i/n)*rayon,0,sin(2*PI*i/n)*rayon);
    glEnd();
}

//Point d'une Sphère
void Dabman::pointSphere(float rayon, float u, float v)
{
    glVertex3f(rayon*cos(u)*cos(v),rayon*sin(v),rayon*sin(u)*cos(v) );
    glNormal3f(cos(u)*cos(v),sin(v),sin(u)*cos(v) );
}


//Sphère
void Dabman::sphere(unsigned int nM, unsigned int nP, float rayon)
{
      glBegin(GL_QUADS);

      for(unsigned int m = 0; m < nM; m++)
      {
            for(unsigned int p = 0; p < nP; p++)
            {
                glTexCoord2f( ( (float) m / (float) nM ), ( (float) p / (float) nP ) );
                pointSphere(rayon, ( (float) m / (float) nM ) * 2*PI, ( (float) p / (float) nP ) * PI  - (PI/2) );

                glTexCoord2f( ( (float) (m+1) / (float) nM ), ( (float) p / (float) nP ) );
                pointSphere(rayon, ( (float) (m+1) / (float) nM ) * 2*PI, ( (float) p / (float) nP ) * PI  - (PI/2) );

                glTexCoord2f( ( (float) (m+1) / (float) nM ), ( (float) (p+1) / (float) nP ) );
                pointSphere(rayon, ( (float) (m+1) / (float) nM ) * 2*PI, ( (float) (p+1) / (float) nP ) * PI  - (PI/2) );

                glTexCoord2f( ( (float) m / (float) nM ), ( (float) (p+1) / (float) nP ) );
                pointSphere(rayon, ( (float) m / (float) nM ) * 2*PI, ( (float) (p+1) / (float) nP ) * PI  - (PI/2) );
            }
      }

      glEnd();
}

//Set Texture
void Dabman::setTexture(GLuint corps, GLuint visage,GLuint botte, GLuint gant)
{
    m_tex_corps = corps;
    m_tex_visage = visage;
    m_tex_botte = botte;
    m_tex_gant = gant;
}
