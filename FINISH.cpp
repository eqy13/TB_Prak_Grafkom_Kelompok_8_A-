// ---------------------------------- library
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
// ---------------------------------- global variabel
const float PI = 3.14159265f;
const float MOVE_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.002f;
float cameraPosX = 5.0f, cameraPosY = 0.0f, cameraPosZ = 25.0f;
float cameraYaw = 0.0f, cameraPitch = -25.0f;
int lastMouseX = 0, lastMouseY = 0;
bool mouseActive = false;
bool keys[256] = {false};
int windowWidth = 1200, windowHeight = 800;
bool lightingEnabled = true;
int lightMode = 1;
bool isDirectional = false;
bool isSpotlight = false;
float spotCutoff = 45.0f;
float spotExponent = 2.0f;
float linearAttenuation = 0.0f;
bool isShiny = true;
bool hidden = false;
float engsel = 0.0f;
bool buka = false;
float PagerGeser = 0.0f;

GLUquadric *quad = gluNewQuadric();
//------------------------------------------------------------ eqy dan maul dan zahra ----------------------------------------------------------//
// ---------------------------------- fungsi pencahayaan
void initLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {0.5f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void updateLightingLogic() {
    if (!lightingEnabled)
    {
        glDisable(GL_LIGHTING);
        return;
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat globalAmbient[] = {0,0,0,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    
	// PAGI 
    GLfloat pagi_ambient[]  = {0.30f, 0.28f, 0.25f, 1.0f};
    GLfloat pagi_diffuse[]  = {0.50f, 0.48f, 0.45f, 1.0f};
    GLfloat pagi_specular[] = {0.15f, 0.15f, 0.15f, 1.0f};

    // SIANG 
    GLfloat siang_ambient[]  = {0.40f, 0.40f, 0.40f, 1.0f};
    GLfloat siang_diffuse[]  = {0.85f, 0.85f, 0.85f, 1.0f};
    GLfloat siang_specular[] = {0.30f, 0.30f, 0.30f, 1.0f};

    // SENJA 
    GLfloat senja_ambient[]  = {0.25f, 0.18f, 0.12f, 1.0f};
    GLfloat senja_diffuse[]  = {0.70f, 0.35f, 0.15f, 1.0f};
    GLfloat senja_specular[] = {0.20f, 0.15f, 0.10f, 1.0f};

    // MALAM 
	GLfloat malam_ambient[]  = {0.15f, 0.16f, 0.22f, 1.0f};
	GLfloat malam_diffuse[]  = {0.30f, 0.32f, 0.45f, 1.0f};
	GLfloat malam_specular[] = {0.12f, 0.12f, 0.15f, 1.0f};

    if (lightMode == 1)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT,  pagi_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  pagi_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, pagi_specular);
    }
    else if (lightMode == 2)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, siang_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, siang_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, siang_specular);
    }
    else if (lightMode == 3)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, senja_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, senja_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, senja_specular);
    }
    else if (lightMode == 4)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, malam_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, malam_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, malam_specular);
    }
    GLfloat w_component = isDirectional ? 0.0f : 1.0f;
    GLfloat light_pos[] = {0.0f, 0.50f, 0.0f, w_component};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    if (isSpotlight)
    {
        GLfloat spotDir[] = {0.0f, -1.0f, 0.0f};
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
    }
    else
    {
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
    }
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
    if (isShiny)
    {
        GLfloat mat_spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    }
    else
    {
        GLfloat mat_spec[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    }
}

// --------------------------------------------------------- fungsi objek dan tampilan -------------------------------------------------\\
\\============================================================================= eqy ====================================================//
void drawRumah() {

    //--------------------------------------------------------------------- tembok depan ------------------------------------------------\\
    //atas
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.0225f, -0.512f, 4.0f);
    glScalef(12.883f, 1.0f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //kiri
    glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(-1.8f, -1.986025f, 4.0f);
	glScalef(1.0f, 8.8268f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
    //bawah
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-1.05f, -3.83505f, 4.0f);
    glScalef(6.0f, 3.5f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    //kanan
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, -2.56005f, 4.0f);
    glScalef(1.0f, 12.6537f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- kusen jendela ------------------------------------------------\\
    //atas kusen
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(-0.9f, -0.695f, 4.0f);
    glScalef(5.0f, 0.22f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    //tengah kusen
    glColor3f(0.55f, 0.27f, 0.07f);
	glPushMatrix();
	glTranslatef(-0.9f, -1.985f, 4.0f);
	glScalef(0.22f, 8.40f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
    //kanan kusen
	glColor3f(0.55f, 0.27f, 0.07f);
	glPushMatrix();
	glTranslatef(-0.183f, -1.985f, 4.0f);
	glScalef(0.22f, 8.40f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
    //kiri kusen
    glColor3f(0.55f, 0.27f, 0.07f);
	glPushMatrix();
	glTranslatef(-1.617f, -1.985f, 4.0f);
	glScalef(0.22f, 8.40f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
    //bawah kusen
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(-0.9f, -3.27505f, 4.0f);
    glScalef(5.0f, 0.22f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    
	//---------------------------------------------------------------------garis tengah jendela  ------------------------------------------------\\
	//atas
	glPushMatrix();
	glTranslatef(-0.9f, -1.581f, 4.0f);
	glScalef(4.58f, 0.10f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	//tengah
	glPushMatrix();
	glTranslatef(-0.9f, -2.389f, 4.0f);
	glScalef(4.58f, 0.10f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	//----------------------------------------pinggiran tapi yang ditengah, untuk jendela juga sii ini ge --------------------------------------\\
	//atas kusen
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(-0.9f, -0.728f, 4.0f);
    glScalef(5.0f, 0.22f, 0.16f);
    glutSolidCube(0.3);
    glPopMatrix();
    //tengah kusen kiri
    glColor3f(0.55f, 0.27f, 0.07f);
	glPushMatrix();
	glTranslatef(-0.95f, -1.985f, 4.0f);
	glScalef(0.16f, 8.40f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	//tengah kusen kanan
    glColor3f(0.55f, 0.27f, 0.07f);
	glPushMatrix();
	glTranslatef(-0.85f, -1.985f, 4.0f);
	glScalef(0.22f, 8.40f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
    //kanan kusen
	glColor3f(0.55f, 0.27f, 0.07f);
	glPushMatrix();
	glTranslatef(-0.25f, -1.985f, 4.0f);
	glScalef(0.22f, 8.40f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
    //kiri kusen
    glColor3f(0.55f, 0.27f, 0.07f);
	glPushMatrix();
	glTranslatef(-1.56f, -1.985f, 4.0f);
	glScalef(0.22f, 8.40f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
    //bawah kusen
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(-0.9f, -3.24205f, 4.0f);
    glScalef(5.0f, 0.22f, 0.16f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- bagean kiri  ------------------------------------------------\\
    //tembok kiri
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-2.1f, -2.680f, 1.8f);
	glScalef(1.0f, 15.46f, 28.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //tembok tengah
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(2.36f, -1.986f, 1.81f);
	glScalef(3.0f, 19.827f, 28.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //tembok belakang
    glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(1.875f, -2.680f, -2.33f);
	glScalef(25.53f, 18.5f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	//----------------------------------------------------------------------lantai depan --------------------------------------------
	glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(1.875f, -4.66005f, 1.8f);
    glScalef(25.53f, 2.0f, 28.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- tangga niii ------------------------------------------------\\
    //1
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.15f, -4.78f, 6.15f);
    glScalef(14.0f, 1.2f, 2.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    //2
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.15f, -4.87f, 6.6f);
    glScalef(14.0f, 0.6f, 2.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- pintu ------------------------------------------------
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(1.86f, -2.514f, 4.0f);
    glRotatef(-engsel, 0, 1, 0);
    glTranslatef(-0.81f, 0.0f, 0.0f);
    glScalef(5.4f, 11.7068f, 0.1f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- alas jalan  ------------------------------------------------
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.15f, -4.97f,  12.9f);
    glScalef(14.0f, 0.4f, 40.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    
    
    //-------------------------------------------------------------------- kusen pintu ------------------------------------------------\\
    //kiri
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(0.2f, -2.511f, 4.0f);
    glScalef(0.35f, 12.3268f, 0.5);
    glutSolidCube(0.3);
    glPopMatrix();
    //kanan
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(1.85f, -2.511f, 4.0f);
    glScalef(0.35f, 12.3268f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    //atas
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(1.05f, -0.710f, 4.0f);
    glScalef(5.5f, 0.32f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    //bawah
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(1.05f, -4.31505f, 4.0f);
    glScalef(5.5f, 0.3f, 0.5);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- atap ------------------------------------------------\\
    //atap kiri
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.02f, -0.137f, 2.245f);
    glScalef(17.0f, 1.5f, 31.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    //atap kiri atas
	glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.02f, 0.0f, 2.335f);
    glScalef(17.6f, 0.8f, 31.6f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- BAGEAN KANAN INI MA ------------------------------------------------\\
    //tembok kanan
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(5.93f, -1.986f, 1.8f);
    glScalef(1.5f, 19.827f, 28.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //tembok belakang ornamen
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(3.4325f, -1.986f, 5.85f);
    glScalef(4.15f, 19.827f, 1.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //tembok depan atas
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(4.2575f, 0.313f, 5.85f);
    glScalef(9.65f, 4.5f, 1.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //tembok depan bawah
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(4.2575f, -4.36f, 5.851f);
    glScalef(9.65f, 4.0f, 1.0f);
    glutSolidCube(0.3);
    glPopMatrix();
	

	//-------------------------------------------------------------------- tembok untuk tanaman  ------------------------------------------------
	//kiri
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(4.1575f, -4.6f, 6.3f);
    glScalef(0.5f, 2.5f, 2.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //kanan
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(6.1f, -4.6f, 6.3f);
    glScalef(0.5f, 2.5f, 2.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //depan
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(5.12875f, -4.6f, 6.525f);
    glScalef(6.0f, 2.5f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //tanah ini teh
    glColor3f(0.45f, 0.30f, 0.18f);
    glPushMatrix();
    glTranslatef(5.12875f, -4.45f, 6.2f);
    glScalef(6.0f, 1.0f, 1.8f);
    glutSolidCube(0.3);
    glPopMatrix();

	//-------------------------------------------------------------------- atap kanan ------------------------------------------------\\
	//kiri
	glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(1.16f, 0.8f, 1.81f);
    glScalef(5.0f, 5.0f, 28.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    //atas
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(3.455f, 0.8f, 1.81f);
    glScalef(18.0f, 5.0f, 28.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    //pelapis atap
	glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(3.3f, 1.67f, 2.0f);
    glScalef(20.6f, 0.8f, 28.6f);
    glutSolidCube(0.3);
    glPopMatrix();


    //--------------------------------------------------------------------- ornamen penghias ------------------------------------------------//
    for (int i=0; i < 9; i++){
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(2.85f + i * 0.14, -2.3f, 6.0f);
    glScalef(0.35f, 18.0f, 0.5f);
    glutSolidCube(0.3);
    glPopMatrix();
	}
    //--------------------------------------------------------------------- kusen jendela kanan ------------------------------------------------\\
    // kiri
	glPushMatrix();
	glTranslatef(4.088f, -2.0525f, 5.85f);
	glScalef(0.22f, 11.05f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// tengah
	glPushMatrix();
	glTranslatef(4.88f, -2.0525f, 5.85f);
	glScalef(0.22f, 11.05f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// kanan
	glPushMatrix();
	glTranslatef(5.672f, -2.0525f, 5.85f);
	glScalef(0.22f, 11.05f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// atas
	glPushMatrix();
	glTranslatef(4.88f, -0.395f, 5.85f);
	glScalef(5.5f, 0.22f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// bawah
	glPushMatrix();
	glTranslatef(4.88f, -3.71f, 5.85f);
	glScalef(5.5f, 0.22f, 0.5f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	//--------------------------------------------------------------------- garis tengah jendela ------------------------------------------------\\
	//atas
	glPushMatrix();
	glTranslatef(4.88f, -1.197f, 5.85f);
	glScalef(5.5f, 0.10f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	//tengah
	glPushMatrix();
	glTranslatef(4.88f, -1.999f, 5.85f);
	glScalef(5.5f, 0.10f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	//bawah
    glPushMatrix();
	glTranslatef(4.88f, -2.800f, 5.85f);
	glScalef(5.5f, 0.10f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	//----------------------------------- pinggiran tapi yang ditengah, untuk jendela juga sii ini ge  ---------------------------------\\
	// kiri
	glPushMatrix();
	glTranslatef(4.15f, -2.0525f, 5.85f);
	glScalef(0.22f, 11.05f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// tengah kiri
	glPushMatrix();
	glTranslatef(4.83f, -2.0525f, 5.85f);
	glScalef(0.22f, 11.05f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// tengah kanan
	glPushMatrix();
	glTranslatef(4.93f, -2.0525f, 5.85f);
	glScalef(0.22f, 11.05f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// kanan
	glPushMatrix();
	glTranslatef(5.62f, -2.0525f, 5.85f);
	glScalef(0.22f, 11.05f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// atas
	glPushMatrix();
	glTranslatef(4.88f, -0.45f, 5.85f);
	glScalef(5.5f, 0.22f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
	
	// bawah
	glPushMatrix();
	glTranslatef(4.88f, -3.65f, 5.85f);
	glScalef(5.5f, 0.22f, 0.16f);
	glutSolidCube(0.3);
	glPopMatrix();
}
////------------------------------------------------------------------------------------ ini tanaman -----------------------------------------------------------//
void drawFlower() {
	
    // ===== Kelopak =====
    glColor3f(1.0f, 0.85f, 0.2f); // pink
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotatef(i * 45.0f, 0, 0, 1);
        glTranslatef(0.0f, 0.7f, 0.0f);
        glPushMatrix();
   		glScalef(0.3f, 0.6f, 0.2f);
    	glutSolidSphere(1.0, 20, 20);
    	glPopMatrix();
        glPopMatrix();
    }

    // ===== Putik =====
    glColor3f(0.45f, 0.25f, 0.1f); 
    glutSolidSphere(0.2, 20, 20);

    // ===== Batang =====
    GLUquadric* quad = gluNewQuadric();
    glColor3f(0.0f, 0.6f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -5.0f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.05, 0.05, 5.0, 20, 20);
    glPopMatrix();
    
   // ===== Daun kiri =====
  	glColor3f(0.0f, 0.7f, 0.0f);
    glPushMatrix();
    glTranslatef(0.25f, -1.8f, 0.0f); // posisi di batang
    glRotatef(30, 0, 0, 1);           // miring alami
    glScalef(0.4f, 0.15f, 0.05f);     // pipih kayak daun
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // ===== Daun kanan =====
    glColor3f(0.0f, 0.7f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.25f, -2.6f, 0.0f);
    glRotatef(-30, 0, 0, 1);
    glScalef(0.4f, 0.15f, 0.05f);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

//----------------------------------------------------------------------- ini jendela --------------------------------------------------//
void drawJendela(){
	//---------------------------------------------------------------------bagian kaca jendela kanan ------------------------------------------------\\
	//jendela kiri
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.5f, 1.0f, 0.3f);
    glPushMatrix();
    glTranslatef(4.49f, -2.05f, 5.85f);
    glScalef(2.05f, 11.05f, 0.15f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //jendela kanan
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.5f, 1.0f, 0.3f);
    glPushMatrix();
    glTranslatef(5.275f, -2.05f, 5.85f);
    glScalef(2.05f, 11.05f, 0.15f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //--------------------------------------------------------------------- Jendela kiri ------------------------------------------------\\
    //jendela kiri
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.5f, 1.0f, 0.3f);
    glPushMatrix();
    glTranslatef(-1.25f, -1.985f, 4.0f);
    glScalef(2.05f, 8.40f, 0.15f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    //jendela kanan
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.5f, 1.0f, 0.3f);
    glPushMatrix();
    glTranslatef(-0.55f, -1.985f, 4.0f);
    glScalef(2.05f, 8.40f, 0.15f);
    glutSolidCube(0.3);
    glPopMatrix();
}
//-------------------------------------------------------------- ini benteng tembok ----------------------------------------------------//
void drawBenteng() {

    glColor3f(0.85f, 0.85f, 0.85f);

    // kiri
    glPushMatrix();
    glTranslatef(-3.84f, -3.2f, 7.4f);   
    glScalef(0.6f, 12.0f, 80.0f);       
    glutSolidCube(0.3f);
    glPopMatrix();

    // kanan
    glPushMatrix();
    glTranslatef(9.84f, -3.2f, 7.4f);    
    glScalef(0.6f, 12.0f, 80.0f);
    glutSolidCube(0.3f);
    glPopMatrix();

    // bwlakang
    glPushMatrix();
    glTranslatef(3.0f, -3.2f, -4.5f);   
    glScalef(45.0f, 12.0f, 0.6f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //depan
    glPushMatrix();
    glTranslatef(6.5f, -3.2f, 19.32f);   
    glScalef(22.0f, 12.0f, 0.6f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //depan kicik
    glPushMatrix();
    glTranslatef(-3.4f, -3.2f, 19.32f);   
    glScalef(2.5f, 12.0f, 0.6f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //-------------------------------------------------------------- bata deket pager ------------------------------------------//
    //kanan
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(2.9f, -3.1f, 19.32f);   
    glScalef(2.0f, 12.5f, 2.0f);
    glutSolidCube(0.3f);
    glPopMatrix();
    //kiri
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(-2.7f, -3.1f, 19.32f);   
    glScalef(2.0f, 12.5f, 2.0f);
    glutSolidCube(0.3f);
    glPopMatrix();
}
//---------------------------------------------------------------- lampu -----------------------------------------------------------//
void drawLampu(float x, float y, float z, bool nyala){
    GLfloat emitOn[]  = {1,1,1,1};
    GLfloat emitOff[] = {0,0,0,1};

    // cantolan
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(x, y, z - 0.3f);
    glScalef(0.3f, 0.3f, 0.8f);
    glutSolidCube(0.3f);
    glPopMatrix();

    // tengah
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0f, 1.5f, 1.0f);
    glutSolidCube(0.3f);
    glPopMatrix();

    // atas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,0.5f);
    glPushMatrix();
    glTranslatef(x, y + 0.3f, z);
    glScalef(1.0f, 0.5f, 1.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, nyala ? emitOn : emitOff);
    glutSolidCube(0.3f);
    glMaterialfv(GL_FRONT, GL_EMISSION, emitOff);
    glPopMatrix();

    // bawah
    glPushMatrix();
    glTranslatef(x, y - 0.3f, z);
    glScalef(1.0f, 0.5f, 1.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, nyala ? emitOn : emitOff);
    glutSolidCube(0.3f);
    glMaterialfv(GL_FRONT, GL_EMISSION, emitOff);
    glPopMatrix();
}
//----------------------------------- lampu 
void drawLampuMawl(float x, float y, float z, bool nyala){
    GLfloat emitOn[]  = {1,1,1,1};
    GLfloat emitOff[] = {0,0,0,1};

    // tengah
    glPushMatrix();
    glColor3f(0,0,0);
	glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.07, 0.07, 0.1, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
    glPopMatrix();

    // atas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,0.5f);
    glPushMatrix();
    glTranslatef(x, y + 0.1f, z);
   	glRotatef(-90, 1, 0, 0);
    glMaterialfv(GL_FRONT, GL_EMISSION, nyala ? emitOn : emitOff);
	gluCylinder(quad, 0.07, 0.1, 0.2, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
    glMaterialfv(GL_FRONT, GL_EMISSION, emitOff);
    glPopMatrix();

    // bawah
    glPushMatrix();
    glTranslatef(x, y - 0.2f, z);
   	glRotatef(-90, 1, 0, 0);
    glMaterialfv(GL_FRONT, GL_EMISSION, nyala ? emitOn : emitOff);
	gluCylinder(quad, 0.1, 0.07, 0.2, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
    glMaterialfv(GL_FRONT, GL_EMISSION, emitOff);
    glPopMatrix();
}
//---------------------------------------------------------------- lampu Taman -----------------------------------------------------------//
void drawLamMan(float x, float y, float z, bool nyala){
    GLfloat emitOn[]  = {1,1,1,1};
    GLfloat emitOff[] = {0,0,0,1};

    //lampu kecil
	glColor3f(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(x, y + 1.135f, z);
    glScalef(0.2f, 0.6f, 0.2f); //panjang kiri kanan, tinggi atasbawah, lebar depan belakang
    glutSolidCube(0.4f);
    glPopMatrix();
    
    // Lampu
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,0.5f);
    glPushMatrix();
    glTranslatef(x, y + 1.135f, z);
    glMaterialfv(GL_FRONT, GL_EMISSION, nyala ? emitOn : emitOff);
    glScalef(0.4f, 0.5f, 0.4f); //panjang kiri kanan, tinggi atasbawah, lebar depan belakang
    glutSolidCube(0.6f);
    glMaterialfv(GL_FRONT, GL_EMISSION, emitOff);
    glPopMatrix(); 
    
    //atas bawah
	for (int i=0; i<2; i++){
 	glColor3f(0.24, 0.15, 0.13);
 	glPushMatrix();
    glTranslatef(x, -3.5 + i * 0.3f, z);
    glScalef(0.5f, 0.05f, 0.5f); //panjang kiri kanan, tinggi atasbawah, lebar depan belakang
    glutSolidCube(0.7f);
 	glPopMatrix();
	//kecil
	glPushMatrix();
    glTranslatef(x, -3.185 + i * 0.02f, z);
    glScalef(0.5f, 0.05f, 0.5f); //panjang kiri kanan, tinggi atasbawah, lebar depan belakang
    glutSolidCube(0.6f + i * -0.3f);
 	glPopMatrix(); }  
	
	//garis 
	for (int i=0; i<7; i++){
 	glColor3f(0.24, 0.15, 0.13);
 	//strip
 	glPushMatrix();
    glTranslatef(x, -3.5 + i * 0.05f, z);
    glScalef(0.41f, 0.03f, 0.41f); //panjang kiri kanan, tinggi atasbawah, lebar depan belakang
    glutSolidCube(0.7f);
	glPopMatrix();}
	
	//Gagang
    glPushMatrix();
    glColor3f(0,0,0);
	glTranslatef(x, -4.25, z);
    glScalef(0.3f, 3.5f, 0.3f); //panjang kiri kanan, tinggi atasbawah, lebar depan belakang
    glutSolidCube(0.5f);
    glPopMatrix();	
}
//---------------------------------------------------------------- Looping lampu -----------------------------------------------------------//
void drawLoopingLampu(){
    bool lampuNyala = (lightMode == 3 || lightMode == 4);

    // gerbang kanan
    drawLampu( 2.9f, -2.3f, 20.0f, lampuNyala);

    // gerbang kiri
    drawLampu(-2.7f, -2.3f, 20.0f, lampuNyala);

    // depan rumah kanan
    drawLampu( 2.35f, -1.8f, 6.4f, lampuNyala);

	// depan rumah kiri
    drawLampu( -2.1f, -1.8f, 6.4f, lampuNyala);

    // gazebo pagar
    drawLampuMawl(3.35f, -3.0f, 15.0, lampuNyala);//kirikanan, atasbawah, depanbelakang
    
    // gazebo rumah
	drawLampuMawl(3.35f, -3.0f, 18.0f, lampuNyala);//kirikanan, atasbawah, depanbelakang
	
	// taman gazebo
	drawLamMan(3.5f, -4.5f, 14.0f, lampuNyala);//kirikanan, atasbawah, depanbelakang
}

//---------------------------------------------------------------- zahra dan maul ---------------------------------------------------------//
//---------------------------------------------------------------- Cahaya lampu -----------------------------------------------------------//
void CahayaLampu(GLenum LIGHT, float x, float y, float z, float e, float q, float w, float bray){
	GLfloat pos[]  = { x, y, z, 1.0f };
	GLfloat dir[]  = { e, q, w };
	
	GLfloat diff[] = { bray, bray, bray, 1.0f };
	GLfloat spec[] = { bray * 0.5f, bray * 0.5f, bray * 0.5f, 1.0f };
	
	glEnable(LIGHT);                      
    glLightfv(LIGHT, GL_POSITION, pos);
    glLightfv(LIGHT, GL_SPOT_DIRECTION, dir);

    glLightf (LIGHT, GL_SPOT_CUTOFF, 12.0f);
    glLightf (LIGHT, GL_SPOT_EXPONENT, 15.0f);

    glLightfv(LIGHT, GL_DIFFUSE, diff);
    glLightfv(LIGHT, GL_SPECULAR, spec);

    glLightf(LIGHT, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(LIGHT, GL_LINEAR_ATTENUATION,   0.25f);
    glLightf(LIGHT, GL_QUADRATIC_ATTENUATION,0.15f);
}
//-------------------------------------------------------------- ini benteng tembok ----------------------------------------------------//
void drawPagar(){
	//bawah
	glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.1f, -4.93f, 19.32f);   
    glScalef(17.0f, 0.5f, 0.16f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //atas
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.1f, -1.5f, 19.32f);   
    glScalef(17.0f, 0.5f, 0.16f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //kiri
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(-2.35f, -3.25f, 19.32f);   
    glScalef(0.5f, 11.7f, 0.16f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //kanan
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(2.55f, -3.25f, 19.32f);   
    glScalef(0.5f, 11.7f, 0.16f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //tengah
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, -3.25f, 19.32f);   
    glScalef(0.5f, 11.7f, 0.16f);
    glutSolidCube(0.3f);
    glPopMatrix();
    
    //pagernya
   for (int i=0; i < 33; i++){
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.1f, -1.65f + i * -0.1, 19.32f);   
    glScalef(17.0f, 0.22f, 0.16f);
    glutSolidCube(0.3f);
    glPopMatrix();
	}
}

//============================================================ maulida ================================================================//
//----------------------------------- Gazebo 
void drawGazebo(){
//// alas biasa
// glPushMatrix();
// glColor3f(1.0, 0.0, 0.0);
// glTranslatef(5.25, -4.66005f, 16.5f); //kirikanan, atasbawah, depanbelakang
// glRotatef(180, 1, 0, 0);
// glScalef(4.49f, 0.009f, 3.8f); // panjang, tinggi, lebar
// glutSolidCube(0.80f);
// glPopMatrix();

//--------------------------------alas kayu 
for (int i=0; i < 35; i++){
 glColor3f(0.24, 0.15, 0.13);
 glPushMatrix();
 glTranslatef(7.0f + i * -0.1, -4.66005f, 15.0f);   
 glRotatef(-90, 0, 0, 1);
 gluCylinder(quad, 0.07, 0.07, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); }
//fitur anyam
//for (int i=0; i < 15; i++){
// glColor3f(1.0, 1.0, 0.4);
// glPushMatrix();
// glTranslatef(7.0f, -4.66005f, 18.0f + i * -0.2);   
// glRotatef(-90, 0, 1, 0);
// gluCylinder(quad, 0.07, 0.07, 3.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
// glPopMatrix(); }
 
//--------------------------------atas
 glPushMatrix();
 glColor3f(0.24, 0.15, 0.13);
 glTranslatef(5.25, -2.0f, 16.5f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 2.5, 0.0, 1.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
  
//--------------------------------sisi pagar utama
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(3.5f, -5.0f, 18.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.1, 0.1, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//pengaman pagar utama
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(3.5f, -4.66005f, 15.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 0, 0, 1);
 gluCylinder(quad, 0.07, 0.07, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); 
 
//--------------------------------sisi jalan
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(3.5f, -5.0f, 15.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.1, 0.1, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
   
//--------------------------------sisi pohon
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -5.0f, 18.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.1, 0.1, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//pengaman pohon
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -4.66005f, 15.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 0, 0, 1);
 gluCylinder(quad, 0.07, 0.07, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//pengaman pager pohon
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -4.16005f, 15.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 0, 0, 1);
 gluCylinder(quad, 0.03, 0.03, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); 
 //pagar kayu 
for (int i=0; i < 43; i++){
 glColor3f(0.19, 0.31, 0.15);
 glPushMatrix();
 glTranslatef(7.0f, -4.66005f, 18.0f + i * -0.07);   
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.03, 0.03, 0.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); }
 
//pengaman tembok
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -4.66005f, 18.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 0, 1, 0);
 gluCylinder(quad, 0.07, 0.07, 3.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//pengaman pager tembok
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -4.16005f, 18.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 0, 1, 0);
 gluCylinder(quad, 0.03, 0.03, 3.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
 //pagar kayu 
for (int i=0; i < 50; i++){
 glColor3f(0.19, 0.31, 0.15);
 glPushMatrix();
 glTranslatef(7.0f + i * -0.07, -4.66005f, 18.0f);   
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.03, 0.03, 0.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); } 
  
//--------------------------------sisi rumah
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -5.0f, 15.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.1, 0.1, 3.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); 
//pengaman rumah
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -4.66005f, 15.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 0, 1, 0);
 gluCylinder(quad, 0.07, 0.07, 3.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//pengaman pagar rumah
 glPushMatrix();
 glColor3f(0.19, 0.31, 0.15);
 glTranslatef(7.0f, -4.16005f, 15.0f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 0, 1, 0);
 gluCylinder(quad, 0.03, 0.03, 3.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//pagar kayu 
for (int i=0; i < 50; i++){
 glColor3f(0.19, 0.31, 0.15);
 glPushMatrix();
 glTranslatef(7.0f + i * -0.07, -4.66005f, 15.0f);   
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.03, 0.03, 0.5, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); }
}
//----------------------------------- Meja 
void drawMejoy() {
//bawah
 glColor3f(0.19f, 0.31f, 0.15f);
 glPushMatrix();
 glTranslatef(5.25, -4.66005f, 16.5f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.5, 0.6, 0.2, 40, 40);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//tengah
 glColor3f(1.0f, 1.0f, 1.0f);
 glPushMatrix();
 glTranslatef(5.25, -4.46005f, 16.5f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.6, 0.6, 0.005, 40, 40);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//atas
 glColor3f(0.64f, 0.75f, 0.44f);
 glPushMatrix();
 glTranslatef(5.25, -4.45505f, 16.5f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.0, 0.6, 0.0, 40, 40);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//taplak
 glColor3f(0.0f, 0.0f, 0.0f);
 glPushMatrix();
 glTranslatef(5.25, -4.455f, 16.5f); //kirikanan, atasbawah, depanbelakang
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.0, 0.55, 0.0, 10, 10);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
}
//----------------------------------- Teko 
void drawTeko() {
 glColor3f(1.10f, 0.2f, 0.5f);
 glPushMatrix();
 glTranslatef(5.5, -4.34f, 16.5f);
 glRotatef(180, 0, 1, 0); //derajat, x, y, z
 glutSolidTeapot(0.15);
 glPopMatrix();
}
//----------------------------------- Gantungan Baju 
void drawGantungan(){
//atas
for (int i=0; i < 2; i++){
 glColor3f(0.24, 0.15, 0.13);
 glPushMatrix();
 glTranslatef(6.3f + i * 2.0, -4.1f, 4.89f);   
 glRotatef(-90, 0, 0, 1);
 gluCylinder(quad, 0.04, 0.04, 1.2, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); }
 
//buat baju
for (int i=0; i < 6; i++){
 glColor3f(0.24, 0.15, 0.13);
 glPushMatrix();
 glTranslatef(6.3f, -4.1f, 4.99f + i * 0.2);   
 glRotatef(90, 0, 1, 0);
 gluCylinder(quad, 0.04, 0.04, 2.0, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); }
 
//depan 
for (int i=0; i < 2; i++){ 
 glColor3f(0.24, 0.15, 0.13);
 glPushMatrix();
 glTranslatef(6.3f + i * 2.0 , -4.1f, 4.99f);   
 glRotatef(45, 1, 0, 0);
 gluCylinder(quad, 0.04, 0.04, 1.23, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); }
//belakang
for (int i=0; i < 2; i++){  
 glColor3f(0.24, 0.15, 0.13);
 glPushMatrix();
 glTranslatef(6.3f + i * 2.0, -4.1f, 5.99f);   
 glRotatef(135, 1, 0, 0);
 gluCylinder(quad, 0.04, 0.04, 1.23, 30, 30);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); }
}
//----------------------------------- Piring 
void drawPiring(){
  glColor3f(1.5f, 1.0f, 1.0f);
//piring cokelat
 glPushMatrix();
 glTranslatef(5.0, -4.4549f, 16.5f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.15, 0.0, 0.0, 6, 6); //bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//teko 
 glPushMatrix();
 glTranslatef(5.5, -4.4549f, 16.5f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.17, 0.0, 0.0, 6, 6); //bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//piring donat
 glPushMatrix();
 glTranslatef(5.13, -4.4549f, 16.27f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.15, 0.0, 0.0, 6, 6); //bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//piring apel
 glPushMatrix();
 glTranslatef(5.13, -4.4549f, 16.73f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.15, 0.0, 0.0, 6, 6); //bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//piring mug
 glPushMatrix();
 glTranslatef(5.37, -4.4549f, 16.27f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.15, 0.0, 0.0, 6, 6); //bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
//piring gatau2
 glPushMatrix();
 glTranslatef(5.37, -4.4549f, 16.73f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.15, 0.0, 0.0, 6, 6); //bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
}
//----------------------------------- Gelas
void drawMug() {
//rumah
 glColor3f(0.2f, 1.0f, 1.0f);   //pinkeu cangkir
 glPushMatrix();
 glTranslatef(5.37, -4.35f, 16.27f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.05, 0.03, 0.1, 32, 32);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
 //atas cangkir
 glColor3f(1.0f, 1.0f, 1.0f);//isinya milku
 glPushMatrix();
 glTranslatef(5.37, -4.35f, 16.27f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.0, 0.05, 0.0, 32, 32);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
 
//tembok 
 glColor3f(0.2f, 1.0f, 1.0f);   //pinkeu cangkir
 glPushMatrix();
 glTranslatef(5.37, -4.35f, 16.73f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.05, 0.03, 0.1, 32, 32);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
 //atas cangkir
 glColor3f(1.0f, 1.0f, 1.0f);//isinya milku
 glPushMatrix();
 glTranslatef(5.37, -4.35f, 16.73);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 gluCylinder(quad, 0.0, 0.05, 0.0, 32, 32);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
}
//----------------------------------- Donat
void drawDonat() {
//1
 glColor3f(1.10f, 0.2f, 0.5f); //stroberi
 glPushMatrix();
 glTranslatef(5.125, -4.42f, 16.21f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.027, 0.027, 20, 20);
 glPopMatrix(); 
//2
 glColor3f(0.70f, 0.4f, 0.7f); //taro
 glPushMatrix();
 glTranslatef(5.125, -4.42f, 16.34f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.027, 0.027, 20, 20);
 glPopMatrix(); 
//3
 glColor3f(1.6f, 1.4f, 0.7f); //tramisu
 glPushMatrix();
 glTranslatef(5.075, -4.42f, 16.275f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.027, 0.027, 20, 20);
 glPopMatrix(); 
//4
 glColor3f(0.55f, 0.27f, 0.07f); //coklat
 glPushMatrix();
 glTranslatef(5.175, -4.42f, 16.275f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.027, 0.027, 20, 20);
 glPopMatrix(); 
//5
 glColor3f(0.40f, 1.10f, 0.70f); //chocomint
 glPushMatrix();
 glTranslatef(5.125, -4.38f, 16.275f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.027, 0.027, 20, 20);
 glPopMatrix();    
}
//----------------------------------- Apel 
void drawApel(){
//awal
 glPushMatrix();
 glColor3f(1.0f, 0.0f, 0.0f); //merah
 glTranslatef(5.07f, -4.42f, 16.73f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.028, 0.028, 50, 50);
 glPopMatrix(); 
 
 glPushMatrix();
 glColor3f(0.0, 1.0, 0.0);
 glTranslatef(5.07f, -4.42f, 16.73f);
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.005, 0.001, 0.04, 10, 10);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix();
 
//tembok 
 glPushMatrix();
 glColor3f(0.0f, 1.0f, 0.0f); //hijau
 glTranslatef(5.17f, -4.42f, 16.68f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.028, 0.028, 50, 50);
 glPopMatrix(); 
 
 glPushMatrix();
 glColor3f(0.0, 1.0, 0.0);
 glTranslatef(5.17f, -4.42f, 16.68f);
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.005, 0.001, 0.04, 10, 10);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); 
 
//belkang
 glPushMatrix();
 glColor3f(1.0f, 1.0f, 0.0f); //kuning
 glTranslatef(5.17f, -4.42f, 16.78f);//kirikanan, atasbawah, depanbelakang
 glRotatef(90, 1, 0, 0);
 glutSolidTorus(0.028, 0.028, 50, 50);
 glPopMatrix(); 
 
 glPushMatrix();
 glColor3f(0.0, 1.0, 0.0);
 glTranslatef(5.17f, -4.42f, 16.78f);
 glRotatef(-90, 1, 0, 0);
 gluCylinder(quad, 0.005, 0.001, 0.04, 10, 10);//bawah, atas, tinggi, vertikal, horizontal
 glPopMatrix(); 
}

//============================================================ zahra ================================================================//
// ===== AIR MANCUR =====
float airOffset = 0.0f;
// ================= BATA BAWAH (SILINDER) =================
void drawBataBawah() {


    glPushMatrix();
    glColor3f(0.3f, 0.6f, 0.9f);
    glTranslatef(6.0f, -4.95f, 11.0f); 
    glRotatef(-90, 1, 0, 0);            // biar berdiri
    glutSolidCylinder(2.3, 0.7, 30, 10); // radius, tinggi
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(6.0f, -4.95f, 11.0f);
    glRotatef(-90, 1, 0, 0);            // biar berdiri
    gluCylinder(quad, 2.35, 2.35, 1.0, 30, 10); // radius, tinggi
    glPopMatrix();
}

/* ================= SILINDER ================= */
void cylinder(float r, float h) {
    int slices = 20;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float a = 2.0f * 3.14159f * i / slices;
        glVertex3f(cos(a) * r, 0, sin(a) * r);
        glVertex3f(cos(a) * r, h, sin(a) * r);
    }
    glEnd();
}

/* ================= DAGING SEGITIGA ================= */
void dagingSegitiga() {
    glBegin(GL_TRIANGLES);
    // depan
    glVertex3f(0, 0.1f, 0.05f);
    glVertex3f(-0.1f, -0.1f, 0.05f);
    glVertex3f(0.1f, -0.1f, 0.05f);
    // belakang
    glVertex3f(0, 0.1f, -0.05f);
    glVertex3f(0.1f, -0.1f, -0.05f);
    glVertex3f(-0.1f, -0.1f, -0.05f);
    glEnd();
}

/* ================= SATU SATE ================= */
void satuSate() {
    // tusuk sate
    glColor3f(0.8f, 0.6f, 0.3f);
    cylinder(0.03f, 1.6f);

    // potongan daging (acak bentuk)
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(0, 0.3f + i * 0.25f, 0);
        glColor3f(0.6f, 0.3f, 0.15f);

        if (i == 0) {
            glutSolidSphere(0.1, 16, 16);          // bulat
        }
        else if (i == 1) {
            glutSolidCube(0.18);                  // kotak
        }
        else if (i == 2) {
            glScalef(1.2f, 0.8f, 1.0f);            // oval
            glutSolidSphere(0.1, 16, 16);
        }
        else if (i == 3) {
            dagingSegitiga();                     // segitiga
        }
        else {
            glScalef(0.8f, 1.2f, 1.0f);            // bentuk tak beraturan
            glutSolidCube(0.18);
        }

        glPopMatrix();
    }
}

/* ================= 5 SATE ================= */
void drawSate5() {
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef((i - 2) * 0.45f, 0, 0);
        satuSate();
        glPopMatrix();
    }
}


/* ================= BATANG (SILINDER) ================= */
void drawcylinder(float r, float h) {
    int slices = 24;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float a = 2.0f * 3.14159f * i / slices;
        glVertex3f(cos(a) * r, 0, sin(a) * r);
        glVertex3f(cos(a) * r, h, sin(a) * r);
    }
    glEnd();
}

/* ================= POHON ================= */
void drawTree() {
    // batang utama
    glColor3f(0.55f, 0.27f, 0.07f);
    drawcylinder(0.15f, 2.0f);

    // cabang kiri
    glPushMatrix();
    glTranslatef(0, 1.6f, 0);
    glRotatef(-35, 0, 0, 1);
    drawcylinder(0.08f, 0.6f);

    glTranslatef(0, 1.6f, 0);
    glScalef(0.35f, 0.35f, 0.35f);   // ukuran daun
    glColor3f(0.2f, 0.8f, 0.3f);
    glutSolidDodecahedron();
    glPopMatrix();

    // cabang kanan
    glPushMatrix();
    glTranslatef(0, 1.6f, 0);
    glRotatef(35, 0, 0, 1);
    glColor3f(0.55f, 0.27f, 0.07f);
    drawcylinder(0.08f, 0.6f);

    glTranslatef(0, 1.6f, 0);
    glScalef(0.35f, 0.35f, 0.35f);
    glColor3f(0.2f, 0.7f, 0.3f);
    glutSolidDodecahedron();
    glPopMatrix();

    // daun atas
    glPushMatrix();
    glTranslatef(0, 2.8f, 0);
    glScalef(0.55f, 0.55f, 0.55f);
    glColor3f(0.2f, 0.9f, 0.3f);
    glutSolidDodecahedron();
    glPopMatrix();
}


/* ================= KUBUS 3D ================= */
void kubus(float x, float y, float z) {
    glBegin(GL_QUADS);

    // Depan
    glVertex3f(-x, -y,  z);
    glVertex3f( x, -y,  z);
    glVertex3f( x,  y,  z);
    glVertex3f(-x,  y,  z);

    // Belakang
    glVertex3f(-x, -y, -z);
    glVertex3f(-x,  y, -z);
    glVertex3f( x,  y, -z);
    glVertex3f( x, -y, -z);

    // Kiri
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y,  z);
    glVertex3f(-x,  y,  z);
    glVertex3f(-x,  y, -z);

    // Kanan
    glVertex3f( x, -y, -z);
    glVertex3f( x,  y, -z);
    glVertex3f( x,  y,  z);
    glVertex3f( x, -y,  z);

    // Atas
    glVertex3f(-x,  y, -z);
    glVertex3f(-x,  y,  z);
    glVertex3f( x,  y,  z);
    glVertex3f( x,  y, -z);

    // Bawah
    glVertex3f(-x, -y, -z);
    glVertex3f( x, -y, -z);
    glVertex3f( x, -y,  z);
    glVertex3f(-x, -y,  z);

    glEnd();
}

/* ================= PEMANGGANG SATE 3D ================= */
void pemanggang3D() {

    /* ===== BADAN PEMANGGANG ===== */
    glColor3f(0.15, 0.15, 0.15);
    glPushMatrix();
        glTranslatef(0, 0.6, 0);
        kubus(1.6, 0.25, 0.6);
    glPopMatrix();

    /* ===== KAKI ===== */
    glColor3f(0.1, 0.1, 0.1);

    float kakiX[4] = {-1.4, 1.4, -1.4, 1.4};
    float kakiZ[4] = {-0.5, -0.5, 0.5, 0.5};

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
            glTranslatef(kakiX[i], -0.4, kakiZ[i]);
            kubus(0.08, 0.9, 0.08);
        glPopMatrix();
    }

    /* ===== RAK BAWAH ===== */
    glColor3f(0.4, 0.4, 0.4);
    glPushMatrix();
        glTranslatef(0, -0.2, 0);
        kubus(1.2, 0.05, 0.4);
    glPopMatrix();

    /* ===== KISI ATAS ===== */
    glColor3f(0.7, 0.7, 0.7);
    for (float x = -1.3; x <= 1.3; x += 0.25) {
        glPushMatrix();
            glTranslatef(x, 0.9, 0);
            kubus(0.02, 0.02, 0.55);
        glPopMatrix();
    }
}
float awanX = -5.0f;

void drawAwan() {
    glColor3f(1.0f, 1.0f, 1.0f); //warna putih

    glPushMatrix();
    glTranslatef(awanX, 2.0f, 0.0f);

    //posisi awan
    glutSolidSphere(1.0, 30, 30); //tengah

    glPushMatrix(); 
    glTranslatef(-1.2f, 0.3f, 0.0f); //dikiri
    glutSolidSphere(0.8, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2f, 0.4f, 0.0f); //kanan
    glutSolidSphere(0.8, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f); //atas
    glutSolidSphere(0.7, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, 0.2f, -0.8f); //belakang
    glutSolidSphere(0.7, 30, 30);
    glPopMatrix();

    glPopMatrix();
}

//====Yusrina Fauiyyah====Bagian Patung====//
void drawPatung() {
    // ==========================================
    // BAGIAN 1: SETUP POSISI & CAHAYA (GLOW)
    // ==========================================
    
    glPushMatrix();
    
    // 1. Posisikan Patung di koordinat yang Anda minta
    glTranslatef(6.0f, -3.95f, 11.0f); 

    // 2. [BARU] Tambahkan Cahaya Biru di Tengah Patung (GL_LIGHT1)
    // Posisi lampu relatif terhadap pusat patung (tepat di atas mangkuk besar)
    GLfloat light_pos[] = { 0.0f, 1.5f, 0.0f, 1.0f }; 
    GLfloat light_color[] = { 0.0f, 0.8f, 1.0f, 1.0f }; // Warna Cyan/Biru Terang
    
    glEnable(GL_LIGHT1); // Aktifkan lampu nomor 1
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color);
    
    // [PENTING] Attenuation: Agar cahaya tidak menyebar ke seluruh map (fokus di patung)
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f); 
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.05f);

    // ==========================================
    // BAGIAN 2: STRUKTUR BATU
    // ==========================================
    
    GLfloat mat_ambient[] = { 0.3f, 0.3f, 0.35f, 1.0f };
    GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.65f, 1.0f };
    GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f }; 
    GLfloat mat_shininess[] = { 10.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(0.5f, 0.5f, 0.55f); 

    GLUquadricObj *q = gluNewQuadric();

    // --- 1. Tiang Dasar ---
    glPushMatrix();
        glRotatef(-90, 1, 0, 0); 
        gluCylinder(q, 0.6, 0.5, 0.8, 20, 10);
    glPopMatrix();

    // --- 2. Mangkuk Besar (Bawah) ---
    glPushMatrix();
        glTranslatef(0.0f, 0.8f, 0.0f); 
        glRotatef(-90, 1, 0, 0); 
        glutSolidCylinder(1.2, 0.15, 20, 5); 
        glutSolidTorus(0.15, 0.9, 20, 20);   

        // [AIR MENGGENANG - KOLAM BAWAH]
        glPushMatrix();
             glDisable(GL_LIGHTING); // Matikan lighting agar air terlihat menyala (neon)
             glColor3f(0.2f, 0.6f, 1.0f); // Biru terang
             glTranslatef(0.0f, 0.0f, 0.16f); 
             gluDisk(q, 0.0, 0.9, 32, 1);     
             glEnable(GL_LIGHTING);
        glPopMatrix();
    glPopMatrix();

    // --- 3. Tiang Tengah ---
    glPushMatrix();
        glTranslatef(0.0f, 0.8f, 0.0f); 
        glRotatef(-90, 1, 0, 0);
        gluCylinder(q, 0.4, 0.3, 0.8, 20, 10);
    glPopMatrix();

    // --- 4. Mangkuk Kecil (Atas) ---
    glPushMatrix();
        glTranslatef(0.0f, 1.6f, 0.0f); 
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.8, 0.1, 20, 5); 
        glutSolidTorus(0.1, 0.6, 20, 20);   

        // [AIR MENGGENANG - KOLAM ATAS]
        glPushMatrix();
             glDisable(GL_LIGHTING);
             glColor3f(0.2f, 0.6f, 1.0f);
             glTranslatef(0.0f, 0.0f, 0.11f);
             gluDisk(q, 0.0, 0.6, 32, 1);
             glEnable(GL_LIGHTING);
        glPopMatrix();
    glPopMatrix();

    // --- 5. Pancuran Atas & Bola ---
    glPushMatrix();
        glTranslatef(0.0f, 1.7f, 0.0f); 
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.3, 0.5, 15, 10); 
    glPopMatrix();
    
    // Bola Puncak
    glPushMatrix();
        glTranslatef(0.0f, 2.2f, 0.0f); 
        glutSolidSphere(0.1, 10, 10); 
    glPopMatrix();


    // ==========================================
    // BAGIAN 3: ANIMASI SEMBURAN AIR
    // ==========================================
    
    // Matikan lighting saat menggambar garis air
    // Ini teknik agar garis air terlihat seperti cahaya/laser (Self-Luminous)
    glDisable(GL_LIGHTING); 
    glEnable(GL_BLEND);     
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4f(0.7f, 0.95f, 1.0f, 0.8f); // Putih kebiruan (Sangat Terang)
    glLineWidth(2.0f);

    int jumlahPancuran = 12; 
    
    // LOOP 1: Pancuran Atas (Parabola)
    for (int i = 0; i < jumlahPancuran; i++) {
        float theta = i * (2.0f * PI / jumlahPancuran);
        
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= 15; j++) {
            float t = j / 15.0f; 
            float t_anim = t - airOffset; 
            if (t_anim < 0.0f) t_anim += 1.0f;
            
            float currentRadius = t_anim * 0.5f; 
            float x = cos(theta) * currentRadius;
            float z = sin(theta) * currentRadius;
            float y = 2.2f - (t_anim * t_anim * 2.5f); 

            if(y < -1.65f) break; 
            glVertex3f(x, y, z);
        }
        glEnd();
    }

    // LOOP 2: Tetesan Atas ke Bawah
    glBegin(GL_LINES);
    for(int i=0; i<jumlahPancuran; i++) {
        float theta = i * (2.0f * PI / jumlahPancuran) + airOffset; 
        float r = 0.65f; 
        glVertex3f(cos(theta)*r, 1.6f, sin(theta)*r);
        glVertex3f(cos(theta)*r, 0.9f, sin(theta)*r); 
    }
    glEnd();

    // LOOP 3: Tetesan Bawah ke Dasar (Air mengalir sampai bawah)
    glBegin(GL_LINES);
    for(int i=0; i<jumlahPancuran; i++) {
        float theta = i * (2.0f * PI / jumlahPancuran) - (airOffset * 0.5f);
        float r = 1.0f; 
        // Dari bibir mangkuk besar (y=0.9) ke Lantai (y=0.0 relatif terhadap patung)
        glVertex3f(cos(theta)*r, 0.9f, sin(theta)*r);
        glVertex3f(cos(theta)*r, 0.0f, sin(theta)*r); 
    }
    glEnd();

    // ==========================================
    // RESTORE KONDISI
    // ==========================================
    glDisable(GL_BLEND);
    glDisable(GL_LIGHT1);  // Matikan lampu patung agar tidak mengganggu objek lain
    glEnable(GL_LIGHTING); // Hidupkan kembali lighting global
    gluDeleteQuadric(q);

    glPopMatrix(); // Restore Matrix Utama
}

void updateAir() {
    airOffset += 0.02f;     // kecepatan air

    if (airOffset > 1.0f)  // reset looping
        airOffset = 0.0f;
}

void timer(int value) {
    // 1. Panggil logika update air (agar variabel airOffset bertambah)
    updateAir(); 

    // 2. Minta layar digambar ulang (refresh tampilan)
    glutPostRedisplay();

    // 3. Panggil timer ini lagi dalam 16 milidetik (Looping)
    glutTimerFunc(16, timer, 0);
}


// ---------------------------------- kartesius
void drawCartecius(){
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	
	glVertex3f(-30.0, 0.0, 0.0);
	glVertex3f(30.0, 0.0, 0.0);
	
	glVertex3f(0.0, -30.0, 0.0);
	glVertex3f(0.0, 30.0, 0.0);
	
	glVertex3f(0.0, 0.0, -30.0);
	glVertex3f(0.0, 0.0, 30.0);
	glEnd();
}
void hiddenCarte() {
	if (hidden)
	{
		drawCartecius();
	}
}
// ---------------------------------- pencahayaan
void drawLightSource() {
    if (!lightingEnabled)
        return;

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(-1.0f, 10.0f, 0.0f);

    if (lightMode == 1)       // pagi
        glColor3f(1.0f, 0.95f, 0.7f);
    else if (lightMode == 2)  // siang
        glColor3f(1.0f, 1.0f, 1.0f);
    else if (lightMode == 3)  // senja
        glColor3f(1.0f, 0.45f, 0.1f);
	else if (lightMode == 4)  // malam
        glColor3f(0.95f, 0.95f, 1.0f); 
   
        
    if (isSpotlight)
        glutWireSphere(0.6, 10, 10);
    else
        glutSolidSphere(0.45, 20, 20);

    glPopMatrix();
    if (lightingEnabled)
        glEnable(GL_LIGHTING);
}

// //=====Yusrina Fauziyyah======Bagian Bunga==========================//
// Fungsi pembantu untuk menggambar satu helai kelopak yang cantik
void drawKelopak() {
    glPushMatrix();
    // Warna kelopak merah gradasi (merah tua ke merah muda via lighting)
    glColor3f(0.9f, 0.05f, 0.2f); // Merah Mawar Deep
    
    // Bentuk kelopak: Bola yang dipipihkan dan dilonjongkan
    glScalef(0.3f, 1.0f, 0.1f); 
    glutSolidSphere(0.5, 15, 15);
    glPopMatrix();
}

void drawMawar() {
    float scale = 0.8f; 
    glPushMatrix();
    glScalef(scale, scale, scale);

    // ==========================================
    // 1. BAGIAN BAWAH (SEPAL / KELOPAK HIJAU)
    // ==========================================
    glColor3f(0.2f, 0.6f, 0.1f); // Hijau Segar
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(72.0f * i, 0.0f, 1.0f, 0.0f); // Putar 72 derajat (360/5)
        glRotatef(45.0f, 1.0f, 0.0f, 0.0f);     // Miringkan keluar
        glTranslatef(0.0f, -0.1f, 0.1f);
        glScalef(0.15f, 0.5f, 0.05f);           // Pipih panjang
        glutSolidSphere(0.3, 10, 10);
        glPopMatrix();
    }

    // ==========================================
    // 2. BAGIAN TENGAH (PUTIK / SARI BUNGA)
    // ==========================================
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.0f); // Kuning Emas
    glutSolidSphere(0.1, 10, 10); // Bola kecil di pusat
    glPopMatrix();

    // ==========================================
    // 3. LAPISAN KELOPAK (MAHKOTA BUNGA)
    // ==========================================
    
    // --- LAPIS 1: KUNCUP DALAM (Berdiri tegak melindungi putik) ---
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(120.0f * i, 0.0f, 1.0f, 0.0f); // 3 Kelopak
        glRotatef(20.0f, 1.0f, 0.0f, 0.0f);      // Sedikit miring (masih kuncup)
        glTranslatef(0.0f, 0.1f, 0.05f);         // Geser sedikit dari pusat
        drawKelopak(); // Panggil fungsi kelopak
        glPopMatrix();
    }

    // --- LAPIS 2: MEKAR SETENGAH (Lebih miring) ---
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(72.0f * i + 35.0f, 0.0f, 1.0f, 0.0f); // Offset sudut biar selang-seling
        glRotatef(45.0f, 1.0f, 0.0f, 0.0f);      // Miring 45 derajat
        glTranslatef(0.0f, 0.15f, 0.1f);
        drawKelopak();
        glPopMatrix();
    }

    // --- LAPIS 3: MEKAR PENUH (Kelopak Luar) ---
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glRotatef(60.0f * i, 0.0f, 1.0f, 0.0f); 
        glRotatef(70.0f, 1.0f, 0.0f, 0.0f);      // Miring banget (hampir tidur)
        glTranslatef(0.0f, 0.2f, 0.15f);
        
        // Kelopak luar kita buat lebih lebar sedikit
        glPushMatrix();
        glScalef(1.2f, 1.0f, 1.0f); 
        drawKelopak();
        glPopMatrix();
        
        glPopMatrix();
    }

    glPopMatrix();
}

// Fungsi helper: Menggambar mawar tapi ada batangnya biar nancep di tanah
void drawBungaDenganBatang(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // 1. Gambar Batang (Stalk)
    glColor3f(0.1f, 0.6f, 0.1f); // Hijau
    glPushMatrix();
        glRotatef(-90, 1, 0, 0); // Biar silinder berdiri tegak
        // (radius bawah, radius atas, tinggi, slices, stacks)
        glutSolidCone(0.05f, 0.6f, 10, 10); 
    glPopMatrix();

    // 2. Gambar Kepala Mawar (Panggil fungsi mawar yang sudah ada)
    // Geser ke atas sedikit (y + 0.5) agar pas di ujung batang
    glTranslatef(0.0f, 0.5f, 0.0f);
    
    // Kita random sedikit rotasinya biar gak kaku kayak tentara
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f); 
    
    drawMawar(); // Memanggil fungsi mawar yang sebelumnya dibuat

    glPopMatrix();
}

//======Yusrina Fauziyyah=======Bagian Kucing===============//
void drawKakiKucing(GLUquadricObj *q) {
    glPushMatrix();
    // Paha (Silinder)
    glRotatef(90, 1, 0, 0); // Putar agar silinder menghadap ke bawah
    gluCylinder(q, 0.1, 0.08, 0.4, 10, 5); 
    
    // Telapak Kaki (Bola di ujung bawah)
    glTranslatef(0.0f, 0.0f, 0.4f);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
}

void drawKucing() {
    GLUquadricObj *q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);

    // --- DEFINISI WARNA KUCING PUTIH ---
    GLfloat warnaPutihBersih[] = { 0.95f, 0.95f, 0.95f }; 
    GLfloat warnaHidungPink[] = { 1.0f, 0.6f, 0.7f }; 
    GLfloat warnaMataBiru[] = { 0.2f, 0.6f, 1.0f }; 

    // Set material default ke PUTIH
    glMaterialfv(GL_FRONT, GL_DIFFUSE, warnaPutihBersih);
    glColor3fv(warnaPutihBersih); 

    glPushMatrix();
    
    // ========================================================
    // PENGATURAN POSISI & ROTASI (UPDATE DISINI)
    // ========================================================
    
    // 1. POSISI: Halaman Depan (Z=12), Sebelah Kiri (X=-6)
    // Y = -4.8f agar kaki menapak pas di atas tanah (Tanah = -5.0f)
    glTranslatef(-1.0f, -3.9f, 5.0f); 
    
    // 2. ROTASI: Menghadap serong ke Kanan (Melihat ke Air Mancur di tengah)
    // Rotasi 30 derajat di sumbu Y
    glRotatef(-90, 0, 1, 0); 
    
    // 3. SKALA: Anak Kucing (Kecil)
    glScalef(0.7f, 0.7f, 0.7f); 

    // ========================================================
    // 1. BADAN (TORSO)
    // ========================================================
    glPushMatrix();
        glScalef(1.2f, 0.9f, 1.0f); 
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    // ========================================================
    // 2. KEPALA & WAJAH
    // ========================================================
    glPushMatrix();
        glTranslatef(0.5f, 0.3f, 0.0f); // Kepala ada di sisi +X badan
        glutSolidSphere(0.4, 20, 20);

        // --- Telinga ---
        for(int i=-1; i<=1; i+=2) { 
            glPushMatrix();
            glTranslatef(0.15f, 0.35f, 0.2f * i); 
            glRotatef(-25 * i, 0, 0, 1); 
            glRotatef(-90, 1, 0, 0); 
            glutSolidCone(0.12, 0.3, 10, 5);
            glPopMatrix();
        }

        // --- Mata ---
        glMaterialfv(GL_FRONT, GL_DIFFUSE, warnaMataBiru);
        glColor3fv(warnaMataBiru);
        for(int i=-1; i<=1; i+=2) {
            glPushMatrix();
            glTranslatef(0.32f, 0.1f, 0.15f * i); 
            glutSolidSphere(0.06, 8, 8); 
            glPopMatrix();
        }

        // --- Hidung ---
        glMaterialfv(GL_FRONT, GL_DIFFUSE, warnaHidungPink);
        glColor3fv(warnaHidungPink);
        glPushMatrix();
            glTranslatef(0.38f, 0.0f, 0.0f); 
            glutSolidSphere(0.04, 8, 8);
        glPopMatrix();
        
        // --- Mulut ---
        glMaterialfv(GL_FRONT, GL_DIFFUSE, warnaPutihBersih);
        glColor3fv(warnaPutihBersih);
        glPushMatrix();
            glTranslatef(0.35f, -0.08f, 0.0f); 
            glutSolidSphere(0.08, 8, 8);
        glPopMatrix();

    glPopMatrix(); 

    // ========================================================
    // 3. KAKI-KAKI
    // ========================================================
    glMaterialfv(GL_FRONT, GL_DIFFUSE, warnaPutihBersih);
    glColor3fv(warnaPutihBersih);

    float offsetX = 0.3f; 
    float offsetZ = 0.25f; 
    float offsetY = -0.25f; 

    glPushMatrix(); glTranslatef(offsetX, offsetY, -offsetZ); drawKakiKucing(q); glPopMatrix();
    glPushMatrix(); glTranslatef(offsetX, offsetY, offsetZ); drawKakiKucing(q); glPopMatrix();
    glPushMatrix(); glTranslatef(-offsetX, offsetY, -offsetZ); drawKakiKucing(q); glPopMatrix();
    glPushMatrix(); glTranslatef(-offsetX, offsetY, offsetZ); drawKakiKucing(q); glPopMatrix();

    // ========================================================
    // 4. EKOR
    // ========================================================
    glPushMatrix();
        glTranslatef(-0.5f, 0.1f, 0.0f); 
        glRotatef(60, 0, 0, 1); 

        for(int i=0; i<5; i++) {
            gluCylinder(q, 0.07, 0.06, 0.25, 8, 2); 
            glTranslatef(0.0f, 0.0f, 0.23f); 
            glRotatef(10, 0, 1, 0); 
        }
        glutSolidSphere(0.06, 8, 8);
    glPopMatrix();

    glPopMatrix(); 
    gluDeleteQuadric(q);
}

// ---------------------------------- tanah
void drawFloor() {
    // ==========================================
    // 1. GAMBAR TANAH (RUMPUT)
    // ==========================================
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // Warna Hijau Rumput
    glNormal3f(0.0f, 1.0f, 0.0f); // Normal menghadap ke atas (untuk cahaya)
    glVertex3f(-50.0f, -5.0f, -50.0f);
    glVertex3f(-50.0f, -5.0f, 50.0f);
    glVertex3f(50.0f, -5.0f, 50.0f);
    glVertex3f(50.0f, -5.0f, -50.0f);
    glEnd();

    // ==========================================
    // 2. GAMBAR BUNGA DI TANAH (DEKAT TEMBOK)
    // ==========================================
    
    // Pastikan lighting nyala untuk bunganya
    if (lightingEnabled) glEnable(GL_LIGHTING);

    // Koordinat tembok kiri ada di sktr X = -3.8, jadi bunga di -3.2 (agak masuk)
    float xKiri = -3.2f; 
    
    // Koordinat tembok kanan ada di sktr X = 9.8, jadi bunga di 9.2 (agak masuk)
    float xKanan = 9.2f;
    
    // Posisi Y lantai adalah -5.0f
    float yLantai = -5.0f;

    // Loop dari depan (Z=0) sampai belakang (Z=18)
    // Jarak antar bunga 1.5 meter
    for (float z = 2.0f; z <= 18.0f; z += 1.5f) {
        
        // --- Baris Kiri ---
        drawBungaDenganBatang(xKiri, yLantai, z);
        
        // --- Baris Kanan ---
        drawBungaDenganBatang(xKanan, yLantai, z);
    }

    // ==========================================
    // 3. GRID (OPSIONAL / DIBIARKAN MATI)
    // ==========================================
    glDisable(GL_LIGHTING);
    // Kode grid yang lama biarkan saja di sini jika ingin dipakai nanti
    
    // Kembalikan kondisi lighting
    if (lightingEnabled)
        glEnable(GL_LIGHTING);
}

//------------------------------------------------------------ eqy ----------------------------------------------------------//
// ---------------------------------- fungsi kontrol kamera dan input
void updateCamera() {
    float yawRad = cameraYaw * PI / 180.0f;
    float pitchRad = cameraPitch * PI / 180.0f;
    float forwardX = sin(yawRad) ;
    float forwardY = sin(pitchRad);
    float forwardZ = -cos(yawRad) ;
    float rightX = sin(yawRad + PI / 2);
    float rightZ = -cos(yawRad + PI / 2);

    if (keys['w'] || keys['W'])
    {
        cameraPosX += forwardX * MOVE_SPEED;
        cameraPosY += forwardY * MOVE_SPEED;
        cameraPosZ += forwardZ * MOVE_SPEED;
    }
    if (keys['s'] || keys['S'])
    {
        cameraPosX -= forwardX * MOVE_SPEED;
        cameraPosY -= forwardY * MOVE_SPEED;
        cameraPosZ -= forwardZ * MOVE_SPEED;
    }
    if (keys['a'] || keys['A'])
    {
        cameraPosX -= rightX * MOVE_SPEED;
        cameraPosZ -= rightZ * MOVE_SPEED;
    }
    if (keys['d'] || keys['D'])
    {
        cameraPosX += rightX * MOVE_SPEED;
        cameraPosZ += rightZ * MOVE_SPEED;
    }
    if (keys[' '])
        cameraPosY += MOVE_SPEED;
    if (keys[GLUT_KEY_CTRL_L] || keys[GLUT_KEY_CTRL_R])
        cameraPosY -= MOVE_SPEED;
}
// ---------------------------------- fungsi utama GLUT
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)windowWidth / windowHeight, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float yawRad = cameraYaw * PI / 180.0f;
    float pitchRad = cameraPitch * PI / 180.0f;
    float lookX = cameraPosX + sin(yawRad) * cos(pitchRad);
    float lookY = cameraPosY + sin(pitchRad);
    float lookZ = cameraPosZ - cos(yawRad) * cos(pitchRad);

    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, lookX, lookY, lookZ, 0.0f,
              1.0f, 0.0f);


//------------------------------------------------------------ eqy dan maul dan zahra ----------------------------------------------------------//
glDisable(GL_LIGHT1);
glDisable(GL_LIGHT2);
glDisable(GL_LIGHT3);
glDisable(GL_LIGHT4);
glDisable(GL_LIGHT5);
glDisable(GL_LIGHT6);
glDisable(GL_LIGHT7);
if (lightMode == 3 ){
	float I = 3.0f;
	CahayaLampu(GL_LIGHT1,   2.35f,  1.5f, 6.4f,   0.0f,   -1.0f, 0.0f, I); // depan rumah kanan
	CahayaLampu(GL_LIGHT3,  -2.1f,   1.5f, 6.4f,   0.0f,   -1.0f, 0.0f, I); // depan rumah kiri
    CahayaLampu(GL_LIGHT2,   2.9f,   2.0f, 20.0f,  0.0f,   -1.0f, 0.0f, I); // kanan gerbang
    CahayaLampu(GL_LIGHT4,  -2.7f,   2.0f, 20.0f,  0.0f,   -1.0f, 0.0f, I); // kiri gerbang
    CahayaLampu(GL_LIGHT5,   3.35f, -2.0f, 15.0f,  0.0f,   -1.0f, 0.0f, I); // kiri gajebo
    CahayaLampu(GL_LIGHT6,   3.35f, -2.0f, 18.0f,  0.0f,   -1.0f, 0.0f, I); // kanan gajebo
    CahayaLampu(GL_LIGHT7,   3.5f,  -3.5f, 14.0f,  0.0f,   -1.0f, 0.0f, I); // tengah tengah
}
else if (lightMode == 4 ){
	float I = 5.0f;
	CahayaLampu(GL_LIGHT1,   2.35f,  1.5f, 6.4f,   0.0f,   -1.0f, 0.0f, I); // depan rumah kanan
	CahayaLampu(GL_LIGHT3,  -2.1f,   1.5f, 6.4f,   0.0f,   -1.0f, 0.0f, I); // depan rumah kiri
    CahayaLampu(GL_LIGHT2,   2.9f,   2.0f, 20.0f,  0.0f,   -1.0f, 0.0f, I); // kanan gerbang
    CahayaLampu(GL_LIGHT4,  -2.7f,   2.0f, 20.0f,  0.0f,   -1.0f, 0.0f, I); // kiri gerbang
    CahayaLampu(GL_LIGHT5,   3.35f, -2.0f, 15.0f,  0.0f,   -1.0f, 0.0f, I); // kiri gajebo
    CahayaLampu(GL_LIGHT6,   3.35f, -2.0f, 18.0f,  0.0f,   -1.0f, 0.0f, I); // kanan gajebo
    CahayaLampu(GL_LIGHT7,   3.5f,  -3.5f, 14.0f,  0.0f,   -1.0f, 0.0f, I); // tengah tengah
}


    updateLightingLogic();
    drawFloor(); //lantai
  
    drawBenteng();
	drawRumah();
	hiddenCarte();
	
for (int i = 0; i < 4; i++){

	glPushMatrix();
	glTranslated(4.3f + i * 0.5, -3.5f, 6.2f);
	glScalef(0.2f, 0.2f, 0.2f);
	drawFlower();
	glPopMatrix();
}
	
	glPushMatrix();  
	glTranslatef( PagerGeser, 0.0f, 0.0f); 
	drawPagar();
	glPopMatrix();

   	drawGazebo();
   	drawMejoy();
   	drawPiring();
	drawTeko();
	drawMug();
	drawDonat();
	drawApel();
	
	glPushMatrix();
	glTranslatef(1.5f , 0.0f, 12.25f); 
	glRotatef(90, 0, 1, 0);
	drawGantungan();
	glPopMatrix();

	drawBataBawah();
	drawPatung();

	glPushMatrix();

        // posisi dasar pemanggang
        glTranslatef(6.0f, -4.66f, 14.0f);

        // naik ke atas pemanggang (kisi)
        glTranslatef(0.0f, 0.50f, 0.35f);

        // samakan skala dengan pemanggang
        glScalef(0.4f, 0.4f, 0.4f);

        // arah sate sejajar pemanggang
        glRotatef(-90, 1, 0, 0);

        drawSate5();

    glPopMatrix();

	glPushMatrix();
        glTranslatef(6.0f, -4.66f, 14.0f);
        glScalef(0.5f, 0.5f, 0.5f); // biar proporsional
        pemanggang3D();
    glPopMatrix();
	
	 glPushMatrix();
        glTranslatef(8.0f, -5.0f, 17.0f);
        glScalef(1.2f, 2.0f, 1.2f); // opsional, biar agak besar
        glRotatef(90, 0, 1, 0);
        drawTree();
    glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, 5.0f, 0.0f);
    drawAwan();
    glPopMatrix();
    
  	drawKucing();
    drawLightSource();
    drawLoopingLampu();
	drawJendela();
    
    
	glutSwapBuffers();
}
// ---------------------------------- fungsi kontrol kamera dan input
void keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == 27)
        exit(0);
    if (key == '1')
    {
        lightMode = 1;
    }
    if (key == '2')
    {
        lightMode = 2;
    }
    if (key == '3')
    {
        lightMode = 3;
    }
    if (key == '4')
    {
        lightMode = 4;
    }
    if (key == 'c' || key == 'C')
	{
    	hidden = !hidden;
	}
	 if (key == 'e' || key == 'E') {
        buka = !buka;
    }
    if (key == 'b') {
		PagerGeser += 0.1f; 
		if(PagerGeser > 5.0)
			PagerGeser = 5.0;
		}
	
    if (key == 'v') {
    	PagerGeser -= 0.1f;
    	if (PagerGeser < 0.0)
    		PagerGeser = 0.0;
    	}

//	if (key == 'v' && PagerGeser < 90.0f)
//	    PagerGeser += 2.0f;
//	
//	if (key == 'b' && PagerGeser > 0.0f)
//	    PagerGeser -= 2.0f;
}

void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void specialKey(int key, int x, int y) {
    if (key == GLUT_KEY_CTRL_L || key == GLUT_KEY_CTRL_R)
    {
        keys[key] = true;
    }
}

void specialKeyUp(int key, int x, int y) {
    if (key == GLUT_KEY_CTRL_L || key == GLUT_KEY_CTRL_R)
    {
        keys[key] = false;
    }
}
// ---------------------------------- fungsi kontrol kamera dan input
void mouseMotion(int x, int y) {
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    if (x == centerX && y == centerY)
        return;
    float deltaX = (x - centerX) * MOUSE_SENSITIVITY * 50.0f;
    float deltaY = (centerY - y) * MOUSE_SENSITIVITY * 50.0f;
    cameraYaw += deltaX;
    cameraPitch += deltaY;
    if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;
    if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;
    glutWarpPointer(centerX, centerY);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseActive = true;
        glutSetCursor(GLUT_CURSOR_NONE);
        glutWarpPointer(windowWidth / 2, windowHeight / 2);
        lastMouseX = windowWidth / 2;
        lastMouseY = windowHeight / 2;
    }
}

void idle() {
    updateCamera();
    if (buka && engsel < 90.0f)
        engsel += 0.5f;
    if (!buka && engsel > 0.0f)
        engsel -= 0.5f;

//    glutPostRedisplay();

    glutPostRedisplay();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tugas BADAG");
    glutFullScreen();

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    initLighting();
	
	glutTimerFunc(0, timer, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKey);
    glutSpecialUpFunc(specialKeyUp);
    glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    

    glutMainLoop();
    return 0;
}


