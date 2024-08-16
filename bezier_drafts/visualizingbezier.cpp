#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

// Define a simple 3D point structure
struct Point3D {
    float x, y, z;
};

// Function to compute Bernstein polynomial basis
float bernstein(int n, int i, float t) {
    float binomialCoeff = 1;
    for (int k = 0; k < i; ++k) binomialCoeff *= (n - k) / float(k + 1);
    return binomialCoeff * pow(t, i) * pow(1 - t, n - i);
}

// Function to compute a cubic Bézier curve point
Point3D cubicBezier(const std::vector<Point3D>& controlPoints, float t) {
    Point3D p;
    p.x = 0;
    p.y = 0;
    p.z = 0;

    for (int i = 0; i < 4; ++i) {
        float b = bernstein(3, i, t);
        p.x += b * controlPoints[i].x;
        p.y += b * controlPoints[i].y;
        p.z += b * controlPoints[i].z;
    }
    return p;
}

// Function to compute the Bézier curve points
std::vector<Point3D> computeBezierCurve(const std::vector<Point3D>& controlPoints, int evaluationsNumber) {
    std::vector<Point3D> bezierPoints;
    for (int i = 0; i <= evaluationsNumber; ++i) {
        float t = i / static_cast<float>(evaluationsNumber);
        bezierPoints.push_back(cubicBezier(controlPoints, t));
    }
    return bezierPoints;
}

// Function to draw a Bézier curve using OpenGL
void drawBezierCurve(const std::vector<Point3D>& points) {
    glBegin(GL_LINE_STRIP);
    for (const auto& p : points) {
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Bézier Curves", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    std::vector<Point3D> curveControlPoints = {
        {0, 0, 0},
        {1, 2, 1},
        {2, 2, -1},
        {3, 0, 0}
    };

    int evaluationsNumber = 100;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);

        // Compute and draw Bézier curve
        std::vector<Point3D> curvePoints = computeBezierCurve(curveControlPoints, evaluationsNumber);
        drawBezierCurve(curvePoints);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
