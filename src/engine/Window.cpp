#include "Window.h"
#include "Assets.h"
#include <cstdio>

GLFWwindow *Window::window;
float Window::ratio;

bool Window::open(const std::string &name) {
    auto& c = Assets::VIEW_MODE_CONFIG;
    setRatio(c.resolution.x, c.resolution.y);
    if (!c.enabled) {
        return true;
    }
	
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(c.resolution.x, c.resolution.y, name.c_str(), NULL, NULL);
    if (window == NULL) {
        fprintf(
            stderr,
            "Failed to open GLFW window. If you have an Intel GPU, they are "
            "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.8f, 0.0f);
    return true;
}

void Window::framebufferSizeCallback(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
    setRatio(width, height);
}

void Window::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Window::swapBuffers() { glfwSwapBuffers(window); }

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

void Window::close() { glfwTerminate(); }

GLFWwindow *Window::getPtr() { return window; }

void Window::setRatio(int width, int height) {
    ratio = static_cast<float>(width) / height;
    printf("Ratio: %f\n", ratio);
}

float Window::getRatio() { return ratio; }
