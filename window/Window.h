//
// Created by niklas on 10.07.25.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <thread>

#include <GLFW/glfw3.h>

class Window;

typedef struct KeyCallback {
    Window &window;
    const int key;
    const int scancode;
    const int action;
    const int mods;
} KeyCallback;

class Window {
public:
    static void updateEvents();

    void eventThreadLoop() const;

    void startEventThread(const int *keepAlive) const;

    Window(int width, int height, const std::string &title);
    ~Window();
    void close() const;
    [[nodiscard]] bool should_close() const;
    [[nodiscard]] bool is_key_pressed(int key) const;
    void updateBuffers() const;

    void setWidth(int width);
    void setHeight(int height);
    void setTitle(const std::string &title);
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] float getAspectRatio() const;
    GLFWwindow *window;

    void writeToFile(const std::string &filename) const;


private:
    static int instance_count;
    static void errorCallback(int error, const char* description);
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    std::string title;
    int width, height;
    std::thread eventThread;
    int keepEventThreadRunning;
    const void (*renderFunc)();
};

#endif //WINDOW_H
