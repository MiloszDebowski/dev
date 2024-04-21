#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(vertexColor, 1.0);\n"
"}\0";

GLfloat cubeVertices[] = {
    // Przód
    -0.5f, -0.5f, 0.5f,  0.2f, 0.9f, 1.0f,
    0.5f, -0.5f, 0.5f,   0.0f, 0.2f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.4f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

    // Ty³
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.3f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

    // Lewa œciana
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.7f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.3f, 1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,

    // Prawa œciana
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.7f, 0.0f, 2.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.4f,
    0.5f, -0.5f, 0.5f,   0.9f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,

    // Górna œciana
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,

    // Dolna œciana
    -0.5f, -0.5f, 0.5f,  0.5f, 0.2f, 1.0f,
    0.5f, -0.5f, 0.5f,   0.1f, 0.8f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.9f, 0.9f, 1.0f,
    0.5f, -0.5f, -0.5f,  3.0f, 5.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f
};

int main()
{
    // Inicjalizacja GLFW
    if (!glfwInit())
    {
        std::cerr << "Nie uda³o siê zainicjowaæ GLFW" << std::endl;
        return -1;
    }

    // Utworzenie okna GLFW
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Cube3D", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Nie uda³o siê utworzyæ okna GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Ustawienie okna GLFW jako bie¿¹cego kontekstu OpenGL
    glfwMakeContextCurrent(window);

    // Inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Nie uda³o siê zainicjowaæ GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Ustawienie rozmiaru widoku
    glViewport(0, 0, windowWidth, windowHeight);

    // W³¹czenie testowania g³êbi
    glEnable(GL_DEPTH_TEST);

    // Kompilacja i ³¹czenie shaderów
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint status;
    GLchar error_message[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, error_message);
        std::cout << "B³¹d (Shader wierzcho³ków): " << error_message << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, error_message);
        std::cout << "B³¹d (Shader fragmentów): " << error_message << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, error_message);
        std::cout << "B³¹d (Program shaderów): " << error_message << std::endl;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Dane wierzcho³ków
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // Zmienne kamery i transformacji
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 2.5f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float pitch = 0.0f;
    float yaw = -90.0f;
    float sensitivity = 0.1f;
    float cameraSpeed = 0.03f;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);


    // G³ówna pêtla
    while (!glfwWindowShouldClose(window))
    {
        // Przetwarzanie wejœcia
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPosition += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPosition -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        static float previousX = static_cast<float>(windowWidth) / 2.0f;
        static float previousY = static_cast<float>(windowHeight) / 2.0f;
        float xdifference = xpos - previousX;
        float ydifference = previousY - ypos;
        previousX = xpos;
        previousY = ypos;
        xdifference *= sensitivity;
        ydifference *= sensitivity;
        yaw += xdifference;
        pitch += ydifference;
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 cameraFrontNew;
        cameraFrontNew.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFrontNew.y = sin(glm::radians(pitch));
        cameraFrontNew.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(cameraFrontNew);

        view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        // Wyczyszczenie buforów koloru i g³êbi
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // U¿ycie programu shaderów
        glUseProgram(shaderProgram);

        // Ustawienie uniformów
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Powi¹zanie VAO i narysowanie szeœcianu
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Zamiana buforów przednich i tylnych
        glfwSwapBuffers(window);

        // Oczekiwanie na zdarzenia
        glfwPollEvents();
    }

    // Wyczyszczenie zasobów
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Zakoñczenie GLFW
    glfwTerminate();

    return 0;
}
