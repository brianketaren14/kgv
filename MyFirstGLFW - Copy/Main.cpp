#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Util.h"
#include <math.h>

float color1[] = { 1.0f,1.0f,1.0f,1.0f};
float color2[] = { 1.0f,0.0f,0.0f,1.0f};
unsigned int program;
GLint color1Loc, color2Loc, scaleloc;
float r=1;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    { 
        for (int i = 0; i < 4; i++) 
        {
            color1[i] = (rand()*1.0f)/RAND_MAX;
            color2[i] = (rand()*1.0f)/RAND_MAX;
        }
        //std::cout << color1[0] << " " << color1[1] << " " << color1[2] << " " << color1[3] << std::endl;
        //std::cout << color2[0] << " " << color2[1] << " " << color2[2] << " " << color2[3] << std::endl;
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);

    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        if (r < 1.8) 
        {
            r+=0.02;
        }
        else if(r>=2){
            r += 0;
        }
        std::cout << r << endl;
        glUniform1f(scaleloc, r);
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        if (r > 0.2)
        {
            r -= 0.02;
        }
        else if( r <=0){
            r -= 0;
        }
        std::cout << r << endl;
        glUniform1f(scaleloc, r);
    }
    
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, keyCallback);


    GLenum err = glewInit();

    // vertex
    float vertices[] = {
        0,0, // 0
        0.6,-0.3, // 1
        0.3,-0.6, // 2
        -0.3,-0.6, // 3
        -0.6,-0.3, // 4
        -0.6,0.3, // 5
        -0.3,0.6, // 6
        0.3,0.6, // 7
        0.6,0.3 // 8
    };
    // index untuk gambar 
    unsigned int indexArr[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,1
    };

    // uniform adalah sebuah variabel yang dikirimkan dari cpu ke gpu


    // untuk vertex nya
    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    // buffer tempat penyimpanan sementara
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // untuk mengikat(bind) vertexBuffer ke gl_array_buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * 2, vertices, GL_STATIC_DRAW); // jumlah vertex yng di deklarasikan

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    // untuk  index buffernya
    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // untuk mengikat indexBUffer ke gl_element_array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 27, indexArr, GL_STATIC_DRAW); // jumlah index yg di deklarasikan

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");
    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);


    glUseProgram(program);
    scaleloc = glGetUniformLocation(program, "scale");
    glUniform1f(scaleloc, r);

    color1Loc = glGetUniformLocation(program, "color1");
    glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);

    color2Loc = glGetUniformLocation(program, "color2");
    glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES,0,6);

        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, nullptr); // jenis yng mau digambar, berapa banyak indexnya yang digambar, jenis tipe data index nya

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}