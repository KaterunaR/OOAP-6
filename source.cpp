#include <iostream>
#include <memory>
#include <cmath>
using namespace std;

#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class GeometricShape {
public:
    virtual double area() const = 0; 
    virtual void displayColor() const = 0; 
    virtual void printCenterCoordinates() const = 0; 
    virtual ~GeometricShape() = default;
};


class Circle : public GeometricShape {
private:
    double radius;
    string color;

public:
    Circle(double r, const string& c) : radius(r), color(c) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    void displayColor() const override {
        cout << "Color: " << color << endl;
    }

    void printCenterCoordinates() const override {
        cout << "Center coordinates of the circumscribed circle: (0, 0)" << endl;
    }
};


class Rectangle : public GeometricShape {
private:
    double width, height;
    string color;

public:
    Rectangle(double w, double h, const string& c) : width(w), height(h), color(c) {}

    double area() const override {
        return width * height;
    }

    void displayColor() const override {
        cout << "Color: " << color << endl;
    }

    void printCenterCoordinates() const override {
        cout << "Center coordinates of the circumscribed circle: ("
            << width / 2 << ", " << height / 2 << ")" << endl;
    }
};


class Triangle : public GeometricShape {
private:
    double base, height;
    string color;

public:
    Triangle(double b, double h, const string& c) : base(b), height(h), color(c) {}

    double area() const override {
        return 0.5 * base * height;
    }

    void displayColor() const override {
        cout << "Color: " << color << endl;
    }

    void printCenterCoordinates() const override {
        cout << "Center coordinates of the circumscribed circle: ("
            << base / 2 << ", " << height / 2 << ")" << endl;
    }
};

// Фабричний метод для створення фігур
class ShapeFactory {
public:
    virtual shared_ptr<GeometricShape> createShape() const = 0;
    virtual ~ShapeFactory() = default;
};

// Фабрика для створення кола
class CircleFactory : public ShapeFactory {
private:
    double radius;
    string color;

public:
    CircleFactory(double r, const string& c) : radius(r), color(c) {}

    shared_ptr<GeometricShape> createShape() const override {
        return make_shared<Circle>(radius, color);
    }
};

// Фабрика для створення прямокутника
class RectangleFactory : public ShapeFactory {
private:
    double width, height;
    string color;

public:
    RectangleFactory(double w, double h, const string& c) : width(w), height(h), color(c) {}

    shared_ptr<GeometricShape> createShape() const override {
        return make_shared<Rectangle>(width, height, color);
    }
};

// Фабрика для створення трикутника
class TriangleFactory : public ShapeFactory {
private:
    double base, height;
    string color;

public:
    TriangleFactory(double b, double h, const string& c) : base(b), height(h), color(c) {}

    shared_ptr<GeometricShape> createShape() const override {
        return make_shared<Triangle>(base, height, color);
    }
};

// Функція для вибору фігури і її прорисовки
void drawShape(const ShapeFactory& factory) {
    auto shape = factory.createShape();
    shape->displayColor();
    cout << "Area: " << shape->area() << endl;
    shape->printCenterCoordinates();
}

int main() {
    int choice;
    cout << "Select a shape to draw:\n";
    cout << "1. Circle\n2. Rectangle\n3. Triangle\n";
    cin >> choice;

    if (choice == 1) {
        CircleFactory circleFactory(5.0, "Red");
        drawShape(circleFactory);
    }
    else if (choice == 2) {
        RectangleFactory rectangleFactory(4.0, 6.0, "Blue");
        drawShape(rectangleFactory);
    }
    else if (choice == 3) {
        TriangleFactory triangleFactory(3.0, 4.0, "Green");
        drawShape(triangleFactory);
    }
    else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
