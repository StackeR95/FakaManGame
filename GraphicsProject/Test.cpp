// Include standard headers
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <linux/l2tp.h>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#define COIN "coin.wav"
#define CAR "car1.wav"
#define FAKA "fakanew.wav"
#define MAGNET "magnet.wav"
#define EHDA "ehda.wav"
#define MAFESH "mafeshfaka.wav"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>//rotation
#include <glm/gtx/norm.hpp>//rotation
using namespace glm;

//sound library


#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/text2D.hpp>
#include <vector>
#include <fstream>
using namespace std;
#include <algorithm>
#include <string>

#include    <GL/glut.h>
#include    <GL/glu.h>
#include    <GL/gl.h>
//Global Variables
// For All Objects
vector<vector<glm::vec3> >theVertices;
vector<vector<glm::vec2> >theUVS;
vector<vector<glm::vec3> >theNormals;

// Load the texture
vector<GLuint>TextureVector;
GLFWwindow* window;
bool NoKeyCallBack=false;
string PlayerName="";
//End Global


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)             // Resize And Initialize The GL Window
{
    if (height==0)                              // Prevent A Divide By Zero By
    {
        height=1;                           // Making Height Equal One
    }

    glViewport(0, 0, width, height);                    // Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
     glLoadIdentity();                           // Reset The Projection Matrix

     // Calculate The Aspect Ratio Of The Window
     gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

     glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
     glLoadIdentity();                           // Reset The Modelview Matrix
 }


void AttractCoins(vector<float> & xCoins,vector<float> &zCoins, vector<float> zRoads,vector<float> &yCoins,float xPlayer,float yPlayer,vector<float>zCars,float GameSpeed,float deltaTime)
{
if(zCoins.size()==0)
{
    return;
}
bool zRoadsEmpty = (zRoads.size() == 0);
bool zCarsEmpty = (zCars.size() == 0);
if(zRoadsEmpty && zCarsEmpty)
{
    vec3 direction=normalize(vec3(xPlayer-xCoins[0],yPlayer - yCoins[0],29.0-zCoins[0]));
    vec3 oldpos=vec3(xCoins[0],0,zCoins[0]);
    vec3 newpos=oldpos+direction*GameSpeed*deltaTime *vec3(2,2,2);
    xCoins[0]=newpos[0];
    yCoins[0]= newpos[1];
    zCoins[0]=newpos[2];
    return;
}
else if(zRoadsEmpty)
{
    if(zCoins[0] > zCars[0])
    {
        vec3 direction=normalize(vec3(xPlayer-xCoins[0],yPlayer - yCoins[0],29.0-zCoins[0]));
        vec3 oldpos=vec3(xCoins[0],0,zCoins[0]);
        vec3 newpos=oldpos+direction*GameSpeed*deltaTime *vec3(2,2,2);
        xCoins[0]=newpos[0];
        yCoins[0]= newpos[1];
        zCoins[0]=newpos[2];
    }
}
else if(zCarsEmpty)
{
    if(zCoins[0] > zRoads[0])
    {
        vec3 direction=normalize(vec3(xPlayer-xCoins[0],yPlayer - yCoins[0],29.0-zCoins[0]));
        vec3 oldpos=vec3(xCoins[0],0,zCoins[0]);
        vec3 newpos=oldpos+direction*GameSpeed*deltaTime *vec3(2,2,2);
        xCoins[0]=newpos[0];
        yCoins[0]= newpos[1];
        zCoins[0]=newpos[2];
    }
}
else if(zCoins[0] > zRoads[0] && zCoins[0] > zCars[0])
{
    vec3 direction=normalize(vec3(xPlayer-xCoins[0],yPlayer - yCoins[0],29.0-zCoins[0]));
    vec3 oldpos=vec3(xCoins[0],0,zCoins[0]);
    vec3 newpos=oldpos+direction*GameSpeed*deltaTime *vec3(2,2,2);
    xCoins[0]=newpos[0];
    yCoins[0]= newpos[1];
    zCoins[0]=newpos[2];
}

}
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    if(!NoKeyCallBack)
    {
    if (action != GLFW_RELEASE)
    {       // avoid double updates

    switch (key)
    {
        case GLFW_KEY_0: PlayerName=PlayerName+"0"; break;
        case GLFW_KEY_1: PlayerName=PlayerName+"1"; break;
        case GLFW_KEY_2: PlayerName=PlayerName+"2"; break;
        case GLFW_KEY_3: PlayerName=PlayerName+"3"; break;
        case GLFW_KEY_4: PlayerName=PlayerName+"4"; break;
        case GLFW_KEY_5: PlayerName=PlayerName+"5"; break;
        case GLFW_KEY_6: PlayerName=PlayerName+"6"; break;
        case GLFW_KEY_7: PlayerName=PlayerName+"7"; break;
        case GLFW_KEY_8: PlayerName=PlayerName+"8"; break;
        case GLFW_KEY_9: PlayerName=PlayerName+"9"; break;
        case GLFW_KEY_A: PlayerName=PlayerName+"A"; break;
        case GLFW_KEY_B: PlayerName=PlayerName+"B"; break;
        case GLFW_KEY_C: PlayerName=PlayerName+"C"; break;
        case GLFW_KEY_D: PlayerName=PlayerName+"D"; break;
        case GLFW_KEY_E: PlayerName=PlayerName+"E"; break;
        case GLFW_KEY_F: PlayerName=PlayerName+"F"; break;
        case GLFW_KEY_G: PlayerName=PlayerName+"G"; break;
        case GLFW_KEY_H: PlayerName=PlayerName+"H"; break;
        case GLFW_KEY_I: PlayerName=PlayerName+"I"; break;
        case GLFW_KEY_J: PlayerName=PlayerName+"J"; break;
        case GLFW_KEY_K: PlayerName=PlayerName+"K"; break;
        case GLFW_KEY_L: PlayerName=PlayerName+"L"; break;
        case GLFW_KEY_M: PlayerName=PlayerName+"M"; break;
        case GLFW_KEY_N: PlayerName=PlayerName+"N"; break;
        case GLFW_KEY_O: PlayerName=PlayerName+"O"; break;
        case GLFW_KEY_P: PlayerName=PlayerName+"P"; break;
        case GLFW_KEY_Q: PlayerName=PlayerName+"Q"; break;
        case GLFW_KEY_R: PlayerName=PlayerName+"R"; break;
        case GLFW_KEY_S: PlayerName=PlayerName+"S"; break;
        case GLFW_KEY_T: PlayerName=PlayerName+"T"; break;
        case GLFW_KEY_U: PlayerName=PlayerName+"U"; break;
        case GLFW_KEY_V: PlayerName=PlayerName+"V"; break;
        case GLFW_KEY_W: PlayerName=PlayerName+"W"; break;
        case GLFW_KEY_X: PlayerName=PlayerName+"X"; break;
        case GLFW_KEY_Y: PlayerName=PlayerName+"Y"; break;
        case GLFW_KEY_Z: PlayerName=PlayerName+"Z"; break;
        case GLFW_KEY_SPACE:PlayerName=PlayerName+' '; break;
        case GLFW_KEY_BACKSPACE: PlayerName=PlayerName.substr(0,PlayerName.size()-1); break;
            break;
        }
    }
    }
}

bool LoadObjectsGame(const char *ObjPath,const char * TexturePath)
{
    vector<vec3> vertices;
    vector<vec2> uvs;
    vector<vec3> normals; // Won't be used at the moment.
    GLuint Texture;
    bool res = loadOBJ(ObjPath, vertices, uvs, normals);
    theVertices.push_back(vertices);
    theUVS.push_back(uvs);
    theNormals.push_back(normals);
    Texture=loadBMP_custom(TexturePath);
    TextureVector.push_back(Texture);
return res;
}

bool DetectCarCollision ( vector <float> &xCars , vector <float> &zCars , float xPlayer , float zPlayer)
{
    for (int i = 0 ; i < xCars.size() ; i ++ )
    {
        if ( xPlayer >= xCars[i]-1.6 && xPlayer <= xCars[i]+1.6 &&( zPlayer>=zCars[i]-3.7  && zPlayer<=zCars[i]+1.5))
                     {

                          // xCars.erase(xCars.begin()+ i );
                         //  zCars.erase(zCars.begin()+ i );

                           return true;
                     }
    }
return false ;

}

bool DetectMagnetCollision ( vector <float> &xMagnets , vector <float> &zMagnets , float xPlayer , float zPlayer, float yPlayer)
{
    for (int i = 0 ; i < xMagnets.size() ; i ++ )
    {

        if ( xPlayer >= xMagnets[i]-1.6 && xPlayer <= xMagnets[i]+1.6 &&( zPlayer>=zMagnets[i]-3.7  && zPlayer<=zMagnets[i]) && yPlayer <= 3.0f)
                     {

                           xMagnets.erase(xMagnets.begin()+ i );
                           zMagnets.erase(zMagnets.begin()+ i );
                           return true;
                     }
    }
return false ;

}

bool DetectCoinCollision ( vector <float> &xCoins , vector <float> &zCoins , float xPlayer , float zPlayer ,float yPlayer,int & Score , vector<float> & yCoins)
{
    for (int i = 0 ; i < xCoins.size() ; i ++ )
    {
        if ( xPlayer >= xCoins[i]-1&& xPlayer <= xCoins[i]+1 &&( zPlayer>=zCoins[i]-2  && zPlayer<=zCoins[i]-0.5) && yPlayer <2 +yCoins[i] )
        {
                            Score++;
                            xCoins.erase(xCoins.begin()+ i );
                            zCoins.erase(zCoins.begin()+ i );
                            yCoins.erase(yCoins.begin() + i);
                            return true;
        }

    }
return false ;

}

bool DetectRoadCollision (float zPlayer ,float yPlayer, vector<float> &zRoads,vector<float> &xRoads,float xPlayer)
{
    for (int i = 0 ; i < zRoads.size() ; i ++ )
    {
        if (zPlayer>=zRoads[i]-2  && zPlayer<=zRoads[i]-0.15 && yPlayer <= 2.3 && xPlayer>xRoads[i]-5.3 && xPlayer<xRoads[i]+5.3  )
        {
                           // zRoads.erase(zRoads.begin()+ i );
                            return true;
        }

    }
return false ;

}

bool MovePlayer(float &xPlayer,float &yPlayer,float &PlayerSpeed,float &angle,bool & jump,bool &jumpUp,float & jumpAngle,float  deltaTime)
{
    // Move the Player

    if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS)
    {

        if(xPlayer - PlayerSpeed * deltaTime > - 6.0f)
        xPlayer  -= PlayerSpeed * deltaTime;
        if (angle < 0.3)
            angle+= PlayerSpeed* deltaTime /10;

    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS)
    {
        if(xPlayer + PlayerSpeed * deltaTime < 6.0f)
             xPlayer += PlayerSpeed* deltaTime;
        if (angle > -0.3)
            angle-=PlayerSpeed* deltaTime /10;

     }
    else // no left or right is pressed
    {
        if (angle < 0.05 && angle > -0.05 )
            angle = 0 ;
        else
        {
        if ( angle>0 )
        {
            angle-= PlayerSpeed* deltaTime /10;
        }
        else
        {
            angle+= PlayerSpeed* deltaTime /10;

        }
        }
    }

    if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){

       // yPlayer  -= 0.1 ;
        jump = 1 ; // new wello
    }
    else if (glfwGetKey( window,GLFW_KEY_DOWN) == GLFW_PRESS){
            // yPlayer += 0.1;
         }

    if (jump == 1 )
    {

        if (jumpUp == 1)
        {
            if (jumpAngle < 0.3)
                jumpAngle+= PlayerSpeed* deltaTime /5;
            if (yPlayer < 3.5 )
            yPlayer += PlayerSpeed* deltaTime ;
            else
                jumpUp = 0 ;
        }
        else
        {

            if (jumpAngle > -0.3 && yPlayer > 1.5)
                jumpAngle-= PlayerSpeed* deltaTime /2;
            else if (jumpAngle < 0 )
                jumpAngle+= PlayerSpeed* deltaTime /2;

            if(yPlayer >0.1)
               yPlayer -= PlayerSpeed* deltaTime;

            else
            {
                jumpAngle = 0 ;
                jump = 0 ;
                jumpUp = 1 ;
            }
        }

    }

}


int main( void )
{

    //initialising the sound engine
    ALuint buffer, source,buffer2,source2,buffer3,source3,state,Magnet,Ehda,Mafesh;
    ALuint buffer4,buffer5,buffer6;
    bool lose = true;


        // Initialize the environment
        alutInit(0, NULL);

        // Capture errors
        alGetError();

        // Load pcm data into buffer
        buffer = alutCreateBufferFromFile(COIN);
        buffer2 = alutCreateBufferFromFile(CAR);
        buffer3 = alutCreateBufferFromFile(FAKA);
        buffer4 = alutCreateBufferFromFile(MAGNET);
        buffer5 = alutCreateBufferFromFile(MAFESH);
        buffer6 = alutCreateBufferFromFile(EHDA);


        // Create sound source (use buffer to fill source)
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcef(source, AL_GAIN, 0.2f);
        alGenSources(1, &source2);
        alSourcei(source2, AL_BUFFER, buffer2);
        //alSourcef(source2, AL_GAIN, 12.0f);

        alGenSources(1, &source3);
        alSourcei(source3, AL_BUFFER, buffer3);
        alSourcei(source3, AL_LOOPING, AL_TRUE);
        alSourcef(source3, AL_GAIN, 0.25f);


        alGenSources(1, &Magnet);
        alSourcei(Magnet, AL_BUFFER, buffer4);
        alGenSources(1,&Mafesh);
        alSourcei(Mafesh, AL_BUFFER, buffer5);
        alGenSources(1, &Ehda);
        alSourcei(Ehda, AL_BUFFER, buffer6);





    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 790, "Faka Man", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }



    // Ensure we can capture the escape key being pressed below



    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

    // Get a handle for our buffers
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
    GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");






    // Read our .obj file


    // Load 1st Object + It's Texture.. Player
    LoadObjectsGame("./Skate/NewSkateDola.obj","./Skate/TwoText.bmp");

    // Load 2nd Object + It's Texture ... Sky
     LoadObjectsGame("./Sky/BigSky.obj","./Sky/SKYDOME.bmp");

    //Load 3rd Object .. Road
     LoadObjectsGame("./Road/Road.obj","./Road/DRD.bmp");

   //Load 4th Object// Coins
     LoadObjectsGame("./Coins/CoinNew.obj","./Coins/CoinNew.bmp");

    //Load 5th Object // car
     LoadObjectsGame("./Car/BigCar.obj","./Car/CarTexture.bmp");


    //Load 6th Object // FirstMenu
     LoadObjectsGame("./FirstMenu/FirstMenuNew3.obj","./FirstMenu/MafeeshFaka.bmp");

    //Load 7th object // Magnet
    LoadObjectsGame("./Magnet/MagnetNew.obj","./Magnet/magnet.bmp");

    //Load 8th Object // RoadBlock
    LoadObjectsGame("./RoadBlock/RoadBlock.obj","./RoadBlock/RoadBlockText.bmp");

    // End Loading Objects



    // Load it into a VBO

    vector<glm::vec3>AllData;
   for(int i=0;i<theVertices.size();i++)
   {
       for(int j=0;j<theVertices[i].size();j++)
       {
            AllData.push_back(theVertices[i][j]);
       }
   }
   vector<glm::vec2>AllDataUVS;
   for(int i=0;i<theUVS.size();i++)
   {
       for(int j=0;j<theUVS[i].size();j++)
       {
            AllDataUVS.push_back(theUVS[i][j]);
       }
   }
   vector<glm::vec3>AllDataNormals;
   for(int i=0;i<theNormals.size();i++)
   {
       for(int j=0;j<theNormals[i].size();j++)
       {
            AllDataNormals.push_back(theNormals[i][j]);
       }
   }

   int theVerticesSize = 0 ;
   int theUVSSize = 0 ;
   int theNormalsSize=0;

   for (int i = 0 ; i < theVertices.size() ; i++)
   {
       theVerticesSize += theVertices[i].size() ;
       theUVSSize += theUVS [i].size();
       theNormalsSize+=theNormals[i].size();
   }

   vector<int> StartIndex;
   int Counter = 0;
   for (int i = 0; i < theVertices.size(); i++)
   {
       StartIndex.push_back(Counter);
       Counter+=theVertices[i].size();
   }
    StartIndex.push_back(Counter);
    GLuint vertexbuffer;


    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, theVerticesSize * sizeof(glm::vec3), &AllData[0], GL_STATIC_DRAW); // &vertices[0]

    GLuint uvbuffer;

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, theUVSSize * sizeof(glm::vec2), &AllDataUVS[0], GL_STATIC_DRAW);

    GLuint normalbuffer;

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, theNormalsSize * sizeof(glm::vec3), &AllDataNormals[0], GL_STATIC_DRAW);


    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    initText2D( "Holstein.DDS" );

int FirstMenuCases=0;
int width,height;
FirstMenu:
    do{

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glUseProgram(programID);
              //  computeMatricesFromInputs();

                glfwGetWindowSize(window,&width, &height);
                ReSizeGLScene(width,height);
                 mat4 ProjectionMatrix = glm::perspective(1.74f, 4.0f / 3.0f, 0.1f, 100.0f);//110.0f
                 mat4  ViewMatrix = glm::lookAt(vec3(9,-0.5f,41),glm::vec3(9,-0.5f,0),glm::vec3(0,1,0));
                 mat4 ModelMatrix = glm::mat4(1.0);
                // mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
                 mat4 FirstMenuTranslate = translate (mat4() , vec3(0.0f,0.0f,0.0f )) ;
                 mat4 FirstMenuRotate = eulerAngleYXZ ( 0.0f , 0.0f , 0.0f) ;
                 mat4 FirstMenuScale = scale(mat4(),vec3(1.0f,1.0f,1.0f));
                 mat4 FirstMenuModelMatrix =FirstMenuTranslate *FirstMenuRotate*FirstMenuScale ;
                 mat4 FirstMenuMVP = ProjectionMatrix * ViewMatrix * FirstMenuModelMatrix;

                 // cout<<getViewMatrix();
                 glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &FirstMenuMVP[0][0]);
                 glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
                 glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
              //  Matrix4fv(MatrixID, 1, GL_FALSE, &FirstMenuMVPGLFWwindow* window;[0][0]);
                 // 1rst attribute buffer : vertic1es
                 glEnableVertexAttribArray(vertexPosition_modelspaceID);
                 glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                 glVertexAttribPointer(
                     vertexPosition_modelspaceID,  // The attribute we want to configure
                     3,                            // size
                     GL_FLOAT,                     // type
                     GL_FALSE,                     // normalized?
                     0,                            // stride
                     (void*)0                      // array buffer offset
                 );

                 // 2nd attribute buffer : UVs
                 glEnableVertexAttribArray(vertexUVID);
                 glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
                 glVertexAttribPointer(
                     vertexUVID,                   // The attribute we want to configure
                     2,                            // size : U+V => 2
                     GL_FLOAT,                     // type
                     GL_FALSE,                     // normalized?
                     0,                            // stride
                     (void*)0                      // array buffer offset
                 );
                 glEnableVertexAttribArray(vertexNormal_modelspaceID);
                 glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
                 glVertexAttribPointer(
                     vertexNormal_modelspaceID,    // The attribute we want to configure
                     3,                            // size
                     GL_FLOAT,                     // type
                     GL_FALSE,                     // normalized?
                     0,                            // stride
                     (void*)0                      // array buffer offset
                 );

                glBindTexture(GL_TEXTURE_2D, TextureVector[5]);
                glDrawArrays(GL_TRIANGLES, StartIndex[5], theVertices[5].size());
                glDisableVertexAttribArray(vertexPosition_modelspaceID);
                glDisableVertexAttribArray(vertexUVID);
                glDisableVertexAttribArray(vertexNormal_modelspaceID);
                glfwSwapBuffers(window);
                glfwPollEvents();
                if(glfwGetKey(window,GLFW_KEY_1))
                {
                    FirstMenuCases=1;
                    break;
                }
                if(glfwGetKey(window,GLFW_KEY_2))
                {
                    FirstMenuCases=2;
                    break;
                }
                if(glfwGetKey(window,GLFW_KEY_3))
                {
                    FirstMenuCases=3;
                    break;
                }
                if(glfwGetKey(window,GLFW_KEY_4))
                {
                    FirstMenuCases=4;
                    break;
                }
    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS);

ifstream infile("HighScore.txt");
    switch(FirstMenuCases)
    {
    case 1:
              break;
    case 2:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        char text[256];

        while(!glfwGetKey(window,GLFW_KEY_ENTER)== GLFW_PRESS)
        {
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           sprintf(text,"Enter Your Name :");
           printText2D(text,0,400,25);
            glfwSetKeyCallback( window, keyCallback);
            sprintf(text,"%s",PlayerName.c_str());
            printText2D(text,450,400,25);
            glDisableVertexAttribArray(vertexPosition_modelspaceID);
            glDisableVertexAttribArray(vertexUVID);
            glDisableVertexAttribArray(vertexNormal_modelspaceID);
            glfwSwapBuffers(window);
            glfwPollEvents();

        }
        NoKeyCallBack=true;

        break;
    case 3:
        do
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        sprintf(text,"High Score : ");
        printText2D(text,0,400,25);

        int highscore;
        infile >> highscore;
        sprintf(text,"%d",highscore);
        printText2D(text,320,400,25);
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexUVID);
        glDisableVertexAttribArray(vertexNormal_modelspaceID);
        glfwSwapBuffers(window);
        glfwPollEvents();
        }
        while(!glfwGetKey(window,GLFW_KEY_ENTER)==GLFW_PRESS);
        FirstMenuCases=0;
        goto FirstMenu;
        break;
       case 4:
        // Cleanup VBO and shader
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &uvbuffer);
        glDeleteBuffers(1, &normalbuffer);
        glDeleteProgram(programID);
        glDeleteTextures(1, &TextureID);
           cleanupText2D();
        // Close OpenGL window and terminate GLFW
        glfwTerminate();
        // Clean up sources and buffers
            alDeleteSources(1, &source);
            alDeleteBuffers(1, &buffer);
            alDeleteSources(1, &source2);
            alDeleteBuffers(1, &buffer2);

            // Exit everything

            alutExit();
            return 0;

        break;


       default: break;
    }
 infile.close();

    //Declare Variables
    BeginOfGame:
    alGetSourcei(source3,AL_SOURCE_STATE,(ALint*)&state);
    if(state != AL_PLAYING)
        alSourcePlay(source3);
    int ScoreGame=0;
    char text[256];
    float angle =0 ;


     float xPlayer = 0.0f;
     float zPlayer = 30.0f ;
     float yPlayer = 0.0f ;
     vector <float> xCoins ;
     vector <float> zCoins ;
     vector <float> yCoins ;
     vector <float> xCars ;
     vector <float> zCars ;
     vector <float> xMagnets;
     vector <float> zMagnets;
     vector <float> zRoads;
     vector <float> xRoads;

     double lastFrameTime = glfwGetTime();
     float seconds=0;
     srand(time(0));

     float dist=70.0f;

     float street1=0.0f;
     float street2=-dist;

     float GameSpeed = 30 ;
     float PlayerSpeed = 10 ;


     float jumpAngle =0 ;
     float yAngle = 0 ;
     float CoinAngle =0 ;
     bool jump = 0 ;
     bool jumpUp = 1 ;
     bool attract = 0;
     bool isOnTheGround = false ;
     bool CollisionHappened = false  ;

     float ycoin =0 ;

     float TimeForMagnet = 10.0f;
    bool ExitGameLost=false;

    do{

        glfwGetWindowSize(window,&width, &height);
        ReSizeGLScene(width,height);
        PlayerSpeed = 0.2/0.3 * GameSpeed ;


        if(PlayerSpeed>15)
        {
            PlayerSpeed=15;
        }
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double currentTime = glfwGetTime();
        float deltaTime = (float)(currentTime - lastFrameTime);
        CoinAngle += 3.14 * deltaTime ;
        if ( CoinAngle > 3.14 *2)
        CoinAngle = CoinAngle - 3.14 *2 ;
        lastFrameTime = currentTime;
        seconds+=deltaTime;
        TimeForMagnet-=deltaTime;
        if(TimeForMagnet <= 0.0f)
        {
            attract=false;
        }
        for(int i = 0; i < xCoins.size(); i++)
        {
            zCoins[i]+=GameSpeed * deltaTime;
            if (zCoins[i] > 35)
            {
                zCoins.erase(zCoins.begin()+i);
                xCoins.erase(xCoins.begin()+i);
                yCoins.erase(yCoins.begin()+i);

                i-- ;
            }
        }
        for(int i = 0; i < xCars.size(); i++)
        {
            zCars[i]+=GameSpeed* deltaTime;
            if (zCars[i] > 35)
            {
                zCars.erase(zCars.begin()+i);
                xCars.erase(xCars.begin()+i);
                i-- ;
            }
        }

        for(int i = 0; i < zMagnets.size(); i++)
        {
            zMagnets[i]+=GameSpeed* deltaTime;
            if (zMagnets[i] > 35)
            {
                zMagnets.erase(zMagnets.begin()+i);
                xMagnets.erase(xMagnets.begin()+i);
                i-- ;
            }
        }

        for(int i = 0; i < zRoads.size(); i++)
        {
            zRoads[i]+=GameSpeed* deltaTime;
            if (zRoads[i] > 35)
            {
                zRoads.erase(zRoads.begin()+i);
                xRoads.erase(xRoads.begin()+i);
                i-- ;
            }
        }

        if(street1 >= dist)
        {
            street1=-dist;
            street2=0.0f;
        }
        else if(street2 >= dist)
        {
            street2=-dist;
            street1=0.0f;
        }

        street1+=GameSpeed*deltaTime;
        street2+=GameSpeed*deltaTime;
       // cout << deltaTime << endl ;

        if(seconds>=15.0 / GameSpeed )
        {
            seconds=0.0f;
            int randomval1 = rand() % 150;
            float randomval2 = ((float)rand())/RAND_MAX * 10.0f - 5.0f;
            if(randomval1 <= 60)
            {
                xCoins.push_back(randomval2);
                zCoins.push_back(-20.0f);
                yCoins.push_back (0);
            }
            else if (randomval1 <= 120)
            {
                xCars.push_back(randomval2);
                zCars.push_back(-20.0f);

            }
            else if(randomval1 <= 144)
            {
                zRoads.push_back(-20.0f);
                if (randomval1 < 128)
                    xRoads.push_back(2.5); // put on the right
                else if (randomval1 > 136)
                    xRoads.push_back(-2.5); // put on the left
                else
                    xRoads.push_back(0);
            }
           else
            {

                xMagnets.push_back(randomval2);
                zMagnets.push_back(-20.0f);
            }
        }


        // Use our shader
        glUseProgram(programID);

        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();

         mat4  ProjectionMatrix = glm::perspective(1.74f, 4.0f / 3.0f, 0.1f, 100.0f);//110.0f
         mat4  ViewMatrix =glm::lookAt(vec3(0,5,35),glm::vec3(0,0,0),glm::vec3(0,1,0));
         mat4 ModelMatrix = glm::mat4(1.0);
         mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;



        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

        glm::vec3 lightPos = glm::vec3(0,22,0.12);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
               // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        MovePlayer(xPlayer,yPlayer,PlayerSpeed,angle,jump,jumpUp,jumpAngle,deltaTime);



        // 1rst attribute buffer : vertic1es
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            vertexPosition_modelspaceID,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(vertexUVID);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            vertexUVID,                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );
        glEnableVertexAttribArray(vertexNormal_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            vertexNormal_modelspaceID,    // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );


        if (!CollisionHappened)
           yAngle = angle*3/2 ;


        mat4 PlayerTranslate = translate (mat4() , vec3(xPlayer , yPlayer , zPlayer  )) ;
        mat4 PlayerRotate = eulerAngleYXZ ( yAngle , jumpAngle , angle /2) ;
        mat4 PlayerScale = scale(mat4(),vec3(0.4f,0.4f,0.4f));
        mat4 PlayerModelMatrix =PlayerTranslate *PlayerRotate*PlayerScale ;
        mat4 PlayerMVP = ProjectionMatrix * ViewMatrix * PlayerModelMatrix;


        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &PlayerMVP[0][0]);
         glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &PlayerModelMatrix[0][0]);
        glBindTexture(GL_TEXTURE_2D, TextureVector[0]);
        glDrawArrays(GL_TRIANGLES,StartIndex[0] , theVertices[0].size());
        // Draw the triangles !


        int vIndex = theVertices[0].size() ;


        for(int i = 0; i < xCoins.size(); i++)
        {
           // if (attract && zCoins[i] >10)
              //  ycoin = yPlayer ; // to jump with the player
            //else
              //  ycoin = 0.0f ;
            glm ::mat4 Translate = translate (mat4() , vec3(xCoins[i] , yCoins[i]+0.2 , zCoins[i] )) ;
            mat4 Rotate = eulerAngleYXZ ( -CoinAngle ,0.0f  , 0.0f) ;
            glm::mat4 ModelMatrix =Translate * Rotate  ;

            glm:: mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
             glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
            glBindTexture(GL_TEXTURE_2D, TextureVector[3]);
            glDrawArrays(GL_TRIANGLES,StartIndex[3] , theVertices[3].size());
        }
        for(int i = 0; i < xCars.size(); i++)
        {
            glm ::mat4 Translate = translate (mat4() , vec3(xCars[i] , 0.0f , zCars[i] )) ;
            glm ::mat4 Scale = scale (mat4() , vec3(1.0f,1.5f,1.0f )) ;
            glm::mat4 ModelMatrix =Translate*Scale ;
            glm:: mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
             glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
            glBindTexture(GL_TEXTURE_2D, TextureVector[4]);
            glDrawArrays(GL_TRIANGLES,StartIndex[4] , theVertices[4].size());
        }

        for(int i = 0; i < xMagnets.size(); i++)
        {
            glm ::mat4 Translate = translate (mat4() , vec3(xMagnets[i] , 0.0f , zMagnets[i] )) ;
            glm ::mat4 Scale = scale (mat4() , vec3(0.5f,0.5f,0.5f )) ;
            glm::mat4 ModelMatrix =Translate*Scale ;
            glm:: mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
             glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
            glBindTexture(GL_TEXTURE_2D, TextureVector[6]);
            glDrawArrays(GL_TRIANGLES,StartIndex[6] , theVertices[6].size());
        }

        for(int i = 0; i < zRoads.size(); i++)
        {
            glm ::mat4 Translate = translate (mat4() , vec3(xRoads[i] , 0.0f , zRoads[i] )) ;
            glm ::mat4 Scale = scale (mat4() , vec3(1.0f,1.0f,1.0f )) ;
            glm::mat4 ModelMatrix =Translate*Scale ;
            glm:: mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
             glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
            glBindTexture(GL_TEXTURE_2D, TextureVector[7]);
            glDrawArrays(GL_TRIANGLES,StartIndex[7] , theVertices[7].size());
        }

        for ( int i = 1 ; i < 3 ; i ++)
        {
            if(i==2)
            {
                glm::mat4 ModelMatrix=translate(mat4(),vec3(0.0f,0.0f,street1));
                glm::mat4 MVP =ProjectionMatrix*ViewMatrix*ModelMatrix;
                glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
                 glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
                glBindTexture(GL_TEXTURE_2D, TextureVector[i]);
                glDrawArrays(GL_TRIANGLES,vIndex , theVertices[i].size());
                ModelMatrix=translate(mat4(),vec3(0.0f,0.0f,street2));
                MVP =ProjectionMatrix*ViewMatrix*ModelMatrix;
                glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
                 glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
                glBindTexture(GL_TEXTURE_2D, TextureVector[i]);
                glDrawArrays(GL_TRIANGLES,vIndex , theVertices[i].size());
            }

            else
           {
                glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
                 glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
                glBindTexture(GL_TEXTURE_2D, TextureVector[i]);
                glDrawArrays(GL_TRIANGLES,vIndex , theVertices[i].size());
            }

            vIndex += theVertices[i].size() ;
    }

         if(DetectCarCollision(xCars,zCars,xPlayer,28.0f ) || DetectRoadCollision(28.0f,yPlayer,zRoads,xRoads,xPlayer))
         {
             if(lose)
             {
                 alSourcePlay(source2);
                 lose = false;
             }
             GameSpeed = 0 ;
             CollisionHappened = true ;


         }
         if(GameSpeed+0.01f <= 50 &&  !CollisionHappened)
         {
             GameSpeed += 0.01f ;
         }

         if (CollisionHappened)
         {
           //  jumpAngle = + 3.14/2 ;
            if (yPlayer < 0.7)
            {
             if (angle < 3.14 && yAngle >= 3.14/2)
                 angle += 0.2 ;
             if (yAngle <3.14/2)
                 yAngle += 0.2 ;
           //  angle = +3.14 ;
             if (angle > 3.14)
             {
                 isOnTheGround = true ;
                 CollisionHappened = false ;


             }
            // yAngle = 3.14 / 2  ;
             yPlayer = 0.5 ;
            }
            else
            {

                if (angle > -3.14 )
                    angle -= 0.2 ;
                if (yAngle <3.14/2)
                    yAngle += 0.2 ;
              //  angle = +3.14 ;
                if (angle < -3.14)
                {
                    isOnTheGround = true ;
                    CollisionHappened = false ;
                }
                if(DetectCarCollision(xCars, zCars ,xPlayer , 28.0f))
                {
                    if (yPlayer < 3)
                    {
                        yPlayer += 0.1 ;
                        zPlayer -= 0.4 ;
                     }
                }
                else if (yPlayer > 0.8)
                {
                    yPlayer -= 0.1 ;
                    zPlayer -= 0.4 ;
                 }
                jumpAngle = 0 ;
               // yAngle = 3.14 / 2  ;
               // yPlayer = 1 ;
             //   yAngle = 3.14/ 2 ;
              //  angle = -3.14 ;
            }
         }


        if(isOnTheGround)
        {
            sprintf(text,"Game Over" );
            printText2D(text, 150,390,60);


            ifstream infile("HighScore.txt");
            int highscore;
            infile >> highscore;

            if(ScoreGame > highscore)
            {
                highscore = ScoreGame;
            }

            infile.close();

            ofstream outfile("HighScore.txt");
            outfile << highscore;
            outfile.close();

            while(!(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS))
            {
                if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
                {
                ExitGameLost=true;
                break;
                }
                sprintf(text,"Your Score :" );
                printText2D(text, 150,300,30);
                sprintf(text,"%d",ScoreGame);
                printText2D(text, 550,300,30);
                sprintf(text,"High Score :" );
                printText2D(text, 150,270,30);
                sprintf(text,"%d",highscore);
                printText2D(text, 550,270,30);
                sprintf(text,"Press Space To Play Again !!" );
                printText2D(text, 150,250,21);
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            if(!ExitGameLost)
            {
                isOnTheGround = false ;
                lose = true;
                 goto BeginOfGame;
            }
        }

        if(attract)
        {
            AttractCoins(xCoins,zCoins,zRoads,yCoins,xPlayer,yPlayer,zCars,GameSpeed,deltaTime);
        }

        if(DetectCoinCollision(xCoins,zCoins,xPlayer,28.0f,  yPlayer,ScoreGame , yCoins))
        {
            alSourcePlay(source);
            if(ScoreGame % 20 == 0)
                alSourcePlay(Mafesh);
            if(ScoreGame % 20 == 10)
                alSourcePlay(Ehda);
        }

        if(DetectMagnetCollision(xMagnets,zMagnets,xPlayer,28.0f,yPlayer))
        {
            attract=true;
            alSourcePlay(Magnet);
            TimeForMagnet = 10.0f;
        }
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexUVID);
        glDisableVertexAttribArray(vertexNormal_modelspaceID);




        sprintf(text,"%s",PlayerName.c_str() );

        printText2D(text, 0, 0,22);
        sprintf(text,"Score %d",ScoreGame);
        printText2D(text, 0, 580 ,22);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        if(ExitGameLost)
        {
            break;
        }

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( window,GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );




    ifstream infile2("HighScore.txt");
    int highscore;
    infile2 >> highscore;

    if(ScoreGame > highscore)
    {
        highscore = ScoreGame;
    }

    infile2.close();

    ofstream outfile("HighScore.txt");
    outfile << highscore;
    outfile.close();




    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);
       cleanupText2D();
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    // Clean up sources and buffers
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
        alDeleteSources(1, &source2);
        alDeleteBuffers(1, &buffer2);
        alDeleteBuffers(1,&buffer3);
        alDeleteSources(1,&source3);
        alDeleteBuffers(1,&buffer4);
        alDeleteSources(1,&Magnet);
        alDeleteBuffers(1,&buffer5);
        alDeleteSources(1,&Mafesh);
        alDeleteBuffers(1,&buffer6);
        alDeleteSources(1,&Ehda);




        // Exit everything
        alutExit();

    return 0;
}

