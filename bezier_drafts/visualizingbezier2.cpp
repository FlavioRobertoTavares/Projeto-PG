#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Define a simple 3D point structure
struct Point3D {
    double x, y, z;
};

// Function to project 3D point to 2D
sf::Vector2f project(const Point3D& point, float scale, sf::Vector2f offset) {
    return sf::Vector2f(point.x * scale + offset.x, point.y * scale + offset.y);
}

// Function to draw a Bézier curve using SFML
void drawBezierCurve(sf::RenderWindow& window, const std::vector<Point3D>& controlPoints, int evaluationsNumber) {
    std::vector<sf::Vertex> vertices;
    for (int i = 0; i <= evaluationsNumber; ++i) {
        double t = i / static_cast<double>(evaluationsNumber);
        Point3D p = cubicBezier(controlPoints, t);
        vertices.push_back(sf::Vertex(project(p, 100, { 400, 300 }), sf::Color::Red));
    }
    window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
}

// Function to draw a Bézier surface using SFML
void drawBezierSurface(sf::RenderWindow& window, const std::vector<std::vector<Point3D>>& curves, int evaluationsNumber) {
    for (int i = 0; i <= evaluationsNumber; ++i) {
        double v = i / static_cast<double>(evaluationsNumber);
        std::vector<sf::Vertex> rowVertices;
        for (int j = 0; j <= evaluationsNumber; ++j) {
            double u = j / static_cast<double>(evaluationsNumber);
            Point3D p = bezierSurface(curves, u, v);
            rowVertices.push_back(sf::Vertex(project(p, 100, { 400, 300 }), sf::Color::Green));
        }
        window.draw(&rowVertices[0], rowVertices.size(), sf::LineStrip);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "3D Bézier Curves and Surfaces");

    // Example control points for Bézier curve
    std::vector<Point3D> curveControlPoints = {
        {0, 0, 0},
        {1, 2, 1},
        {2, 2, -1},
        {3, 0, 0}
    };

    // Example control points for Bézier surface
    std::vector<std::vector<Point3D>> surfaceControlPoints = {
        { {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0} },
        { {0, 1, 0}, {1, 1, 1}, {2, 1, 1}, {3, 1, 0} },
        { {0, 2, 0}, {1, 2, 1}, {2, 2, 1}, {3, 2, 0} },
        { {0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0} }
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Draw Bézier curve
        drawBezierCurve(window, curveControlPoints, 100);

        // Draw Bézier surface
        drawBezierSurface(window, surfaceControlPoints, 10);

        window.display();
    }

    return 0;
}