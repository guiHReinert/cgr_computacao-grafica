#include <GL/glut.h>
  
// A quadric object to rule them all
static GLUquadricObj *pObj = NULL;

// Rotation
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;

// Definition
static GLfloat slices = 32;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h)  
    {
    GLfloat fAspect;

    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    }  
  
  
// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

    // Configurating the quadric
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);
    gluQuadricNormals(pObj, GLU_SMOOTH);
    gluQuadricOrientation(pObj, GLU_OUTSIDE);
    // atexit(Cleanup);

}  
  
// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){

    (void)x; (void)y;

    if(key == GLUT_KEY_LEFT)    yRot -= 5.0f;  
    if(key == GLUT_KEY_RIGHT)   yRot += 5.0f;  
    if(key == GLUT_KEY_DOWN)    xRot -= 5.0f;
    if(key == GLUT_KEY_UP)      xRot += 5.0f;
    
    yRot = (GLfloat)((const int)yRot % 360);  
    xRot = (GLfloat)((const int)xRot % 100);

    // Refresh the Window  
    glutPostRedisplay();  
}

void DrawHead(GLfloat x, GLfloat y, GLfloat z){

    // Head: white
	glColor3f(1.0f, 1.0f, 1.0f);  

    glPushMatrix(); // save transform matrix state
        glTranslatef(x, y, z);
        glPushMatrix(); // save transform matrix state
            gluSphere(pObj, 0.25f, 32, 16);
        glPopMatrix();

        // Nose: orange
        glColor3f(1.0f, 0.4f, 0.51f);  
        glPushMatrix();
            glTranslatef(0, 0, 0.2);
            // Becomes a cone when base == 0 or top == 0
            gluCylinder(pObj, 0.05f, 0.0, 0.3, slices, 4);
        glPopMatrix();

        // Left eye: black
        glColor3f(0.0f, 0.0f, 0.0f);
        glPushMatrix();
            glTranslatef(-0.09f, 0.067, 0.21);
            gluSphere(pObj, 0.03f, slices, 6);
        glPopMatrix();

        // Right eye: black
        glPushMatrix();
            glTranslatef(0.09f, 0.067, 0.21);
            gluSphere(pObj, 0.03f, slices, 6);
        glPopMatrix();
    glPopMatrix(); // restore transform matrix state
}
  
void DrawHat(GLfloat x, GLfloat y, GLfloat z){

    // Hat: black
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glPushMatrix();
    glTranslatef(x, y, z);
        glRotatef(-90, 1, 0, 0);
        y = 0;

        // Hat brim
        gluCylinder(pObj, 0.25, 0.25, 0.1, slices, 4);
        // Close below
        glPushMatrix();
            glRotatef(180, 1, 0, 0);
            gluDisk(pObj, 0, 0.25, slices, 4);
        glPopMatrix();
        // Close above
        glPushMatrix();
            glTranslatef(0 ,0, 0.1);
            gluDisk(pObj, 0, 0.25, slices, 4);
        glPopMatrix();

        // Hat body
        glTranslatef(0, 0, 0.1);
        gluCylinder(pObj, 0.15, 0.15, 0.3, slices, 4);

        // Hat top
        glTranslatef(0, 0, 0.3);
        gluDisk(pObj, 0, 0.15, slices, 4);
    glPopMatrix();

}

void DrawBody(GLfloat x, GLfloat y, GLfloat z){

    glColor3f(1.0f, 1.0f, 1.0f);  
    glPushMatrix();
        glTranslatef(x, y, z);
        
        // Upper ball
        glPushMatrix();
            glTranslatef(0, 0.5, 0);
            gluSphere(pObj, 0.33f, 32, 16);
        glPopMatrix();

        // Lower ball
        gluSphere(pObj, 0.4f, 32, 16);

        // Buttons: black
        glColor3f(0.0f, 0.0f, 0.0f);
        // 1st button
        glPushMatrix();
            glTranslatef(0, 0.67, 0.27);
            gluSphere(pObj, 0.03f, slices, 6);
        glPopMatrix();
        // 2nd button
        glPushMatrix();
            glTranslatef(0, 0.55, 0.31);
            gluSphere(pObj, 0.03f, slices, 6);
        glPopMatrix();
        // 3rd button
        glPushMatrix();
            glTranslatef(0, 0.43, 0.31);
            gluSphere(pObj, 0.03f, slices, 6);
        glPopMatrix();

        // Scarf: green
        glColor3f(0, 1, 0);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glTranslatef(0, 0, 0.7);
            gluCylinder(pObj, 0.25, 0.2, 0.15, slices, 4);
        glPopMatrix();
    glPopMatrix();
}

void DrawArms(GLfloat x, GLfloat y, GLfloat z){

    // Arms: brown
    glColor3f(0.6, 0.3, 0);
    glPushMatrix();
        glTranslatef(x, y, z);

        // Left arm
        glPushMatrix();
            glTranslatef(0.25, 0, 0); 
            glRotatef(135, 0, 0, 1);  
            glRotatef(90, 1, 0, 0);    
            gluCylinder(pObj, 0.03, 0.01, 0.7, slices, 4);
        glPopMatrix();

        // Right arm:
        glPushMatrix();
            glTranslatef(-0.25, 0, 0);
            glRotatef(-30, 0, 0, 1);   
            glRotatef(90, 1, 0, 0);
            gluCylinder(pObj, 0.03, 0.01, 0.7, slices, 4);
        glPopMatrix();
        
        // Left hand
        glPushMatrix();
            glTranslatef(0.75, 0.5, 0);
            // Thumb
            glPushMatrix();
                glRotatef(90, 0, 0, 1);
                glRotatef(90, 0, 1, 0);
                gluCylinder(pObj, 0.01, 0, 0.2, slices, 4);
            glPopMatrix();
            // Middle finger
            glPushMatrix();
                glRotatef(45, 0, 0, 1);
                glRotatef(90, 0, 1, 0);
                gluCylinder(pObj, 0.01, 0, 0.2, slices, 4);
            glPopMatrix();
            // Last finger
            glPushMatrix();
                glRotatef(90, 0, 1, 0);
                gluCylinder(pObj, 0.01, 0, 0.2, slices, 4);
            glPopMatrix();
        glPopMatrix();

        // Right hand
        glPushMatrix();
            glTranslatef(-0.6, -0.6, 0);
            // Thumb
            glPushMatrix();
                glRotatef(315, 0, 0, 1);  
                glRotatef(45, 1, 0, 0);
                gluCylinder(pObj, 0.015, 0, 0.2, slices, 4);
            glPopMatrix();
            // Middle finger
            glPushMatrix();
                glRotatef(315, 0, 0, 1);  
                glRotatef(90, 1, 0, 0);    
                gluCylinder(pObj, 0.01, 0, 0.2, slices, 4);
            glPopMatrix();
            // Last finger
            glPushMatrix();
                glRotatef(45, 0, 0, 1);  
                glRotatef(45, 0, 1, 0);  
                glRotatef(180, 1, 0, 0);
                gluCylinder(pObj, 0.01, 0, 0.2, slices, 4);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

// Called to draw scene  
void RenderScene(void){  
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f,  0.0f);

	// Draw buneco
    DrawBody(   0,  0,      0);
    DrawArms(   0,  0.6,    0);
    DrawHead(   0,  1,      0);
    DrawHat(    0,  1.2,    0);

    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  
}    

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(750, 750);  
    glutCreateWindow("ALBJORN");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}
