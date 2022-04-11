// UTS_Octagonal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Util.h"
#include <math.h>

//pewarnaan setiap segitiga
float color1[] = { 1.0, 0.0, 0.0, 1.0 };
float color2[] = { 0.0, 1.0, 0.0, 1.0 };
float color3[] = { 0.0, 0.0, 1.0, 1.0 };
float color4[] = { 0.160, 1, 0.921, 1.0 };
float color5[] = { 1, 0.925, 0.160, 1.0 };
float color6[] = { 0.698, 0.160, 1, 1.0 };
float color7[] = { 1, 0.160, 0.941, 1.0 };
float color8[] = { 0.847, 0.619, 0.231, 1.0 };

float currentTime = 0.0f;
float a, b = 0.0f;

unsigned int program;
GLint color1Loc, color2Loc, color3Loc, color4Loc, color5Loc, color6Loc, color7Loc, color8Loc, scaleloc;
float r = 0.5;

void octagonVertices(float r, float vertices[9][2]) {
    for (int i = 0; i < 8; i++) {
        // 1, 2, 3, ..., 8
        // 0, 1,
        vertices[i + 1][0] = r * cos(2 * M_PI * i / 8); // 0,1,2,3,4,5,6,7
        vertices[i + 1][1] = r * sin(2 * M_PI * i / 8);
    }

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   //tombol c untuk random color
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        for (int i = 0; i < 4; i++)
        {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
            color3[i] = (rand() * 1.0f) / RAND_MAX;
            color4[i] = (rand() * 1.0f) / RAND_MAX;
            color5[i] = (rand() * 1.0f) / RAND_MAX;
            color6[i] = (rand() * 1.0f) / RAND_MAX;
            color7[i] = (rand() * 1.0f) / RAND_MAX;
            color8[i] = (rand() * 1.0f) / RAND_MAX;

        }

        /*std::cout << color1[0] << " " << color1[1] << " " << color1[2] << " " << color1[3] << std::endl;
        std::cout << color2[0] << " " << color2[1] << " " << color2[2] << " " << color2[3] << std::endl;
        std::cout << color3[0] << " " << color3[1] << " " << color3[2] << " " << color3[3] << std::endl;
        std::cout << color4[0] << " " << color4[1] << " " << color4[2] << " " << color4[3] << std::endl;
        std::cout << color5[0] << " " << color5[1] << " " << color5[2] << " " << color5[3] << std::endl;
        std::cout << color6[0] << " " << color6[1] << " " << color6[2] << " " << color6[3] << std::endl;
        std::cout << color7[0] << " " << color7[1] << " " << color7[2] << " " << color7[3] << std::endl;
        std::cout << color8[0] << " " << color8[1] << " " << color8[2] << " " << color8[3] << std::endl;
        */

        //mengirim nilai ke color loc
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
        glUniform4f(color4Loc, color4[0], color4[1], color4[2], color4[3]);
        glUniform4f(color5Loc, color5[0], color5[1], color5[2], color5[3]);
        glUniform4f(color6Loc, color6[0], color6[1], color6[2], color6[3]);
        glUniform4f(color7Loc, color7[0], color7[1], color7[2], color7[3]);
        glUniform4f(color8Loc, color8[0], color8[1], color8[2], color8[3]);

    }
    // scaling / merubah ukuran octagon
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        if (r < 1.8)
        {
            r += 0.02;
        }
        else if (r >= 2) {
            r += 0;
        }
        //std::cout << r << endl;
        glUniform1f(scaleloc, r);
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        if (r > 0.2)
        {
            r -= 0.02;
        }
        else if (r <= 0) {
            r -= 0;
        }
        //std::cout << r << endl;
        glUniform1f(scaleloc, r);
    }

}

int main(void) //main program
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Projek UTS KGV", NULL, NULL);
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
    float vertices[9][2] = {
        {0,0 }, // 0
    };

    octagonVertices(1, vertices);

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

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

    //memasukkan nilai dari random generate
    glUseProgram(program);
    scaleloc = glGetUniformLocation(program, "scale");
    glUniform1f(scaleloc, r);

    color1Loc = glGetUniformLocation(program, "color1");
    glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);

    color2Loc = glGetUniformLocation(program, "color2");
    glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);

    color3Loc = glGetUniformLocation(program, "color3");
    glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);

    color4Loc = glGetUniformLocation(program, "color4");
    glUniform4f(color4Loc, color4[0], color4[1], color4[2], color4[3]);

    color5Loc = glGetUniformLocation(program, "color5");
    glUniform4f(color5Loc, color5[0], color5[1], color5[2], color5[3]);

    color6Loc = glGetUniformLocation(program, "color6");
    glUniform4f(color6Loc, color6[0], color6[1], color6[2], color6[3]);

    color7Loc = glGetUniformLocation(program, "color7");
    glUniform4f(color7Loc, color7[0], color7[1], color7[2], color7[3]);

    color8Loc = glGetUniformLocation(program, "color8");
    glUniform4f(color8Loc, color8[0], color8[1], color8[2], color8[3]);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime() / 0.5f;

        a = (float)sin(currentTime) * (RAND_MAX);
        b = (float)cos(currentTime) * (RAND_MAX);
        
        glUniform4f(color1Loc, color1[0] * a, color1[1] * b, color1[2], color1[3] * a);
        glUniform4f(color2Loc, color2[0] * a, color2[1] * a, color2[2], color2[3] * b);
        glUniform4f(color3Loc, color3[0] * a, color3[1] * b, color3[2], color3[3] * a);

        glUniform4f(color4Loc, color4[0] * b, color4[1] * a, color4[2], color4[3] * b);
        glUniform4f(color5Loc, color5[0] * b, color5[1] * b, color5[2], color5[3] * a);
        glUniform4f(color6Loc, color6[0] * b, color6[1] * a, color6[2], color6[3] * b);

        glUniform4f(color7Loc, color7[0] * a, color7[1] * b, color7[2], color7[3] * a);
        glUniform4f(color8Loc, color8[0] * b, color8[1] * a, color8[2], color8[3] * b);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES,0,6);

        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, nullptr); // jenis yang mau digambar, berapa banyak indexnya yang digambar, jenis tipe data index nya

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
