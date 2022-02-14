#pragma once

#include <string>

#define PI 3.14159f

class Shape {
public:
  virtual void Scale(float scaleFactor) = 0;
  virtual void Display() const = 0;
  virtual ~Shape() {};
};

class Shape2D : virtual public Shape {
public:
  virtual float Area() const = 0;
  void ShowArea() const;
  virtual std::string GetName2D() const = 0;
  bool operator>(const Shape2D &rhs) const;
  bool operator<(const Shape2D &rhs) const;
  bool operator==(const Shape2D &rhs) const;
  virtual ~Shape2D() {};
};

class Shape3D : virtual public Shape {
public:
  virtual float Volume() const = 0;
  void ShowVolume() const;
  virtual std::string GetName3D() const = 0;
  bool operator>(const Shape3D &rhs) const;
  bool operator<(const Shape3D &rhs) const;
  bool operator==(const Shape3D &rhs) const;
  virtual ~Shape3D() {};
};
  
class Square : public Shape2D {
public:
  Square();
  Square(float);
  void Scale(float scaleFactor);
  void Display() const;
  float Area() const;
  std::string GetName2D() const;

private:
  float side;
};

class Rectangle : public Shape2D {
public:
  Rectangle();
  Rectangle(float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Area() const;
  std::string GetName2D() const;

private:
  float width;
  float height;
};

class Triangle : public Shape2D {
public:
  Triangle();
  Triangle(float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Area() const;
  std::string GetName2D() const;

private:
  float base;
  float height;
};

class Circle : public Shape2D {
public:
  Circle();
  Circle(float);
  void Scale(float scaleFactor);
  void Display() const;
  float Area() const;
  std::string GetName2D() const;

private:
  float radius;
};

class Ellipse : public Shape2D {
public:
  Ellipse();
  Ellipse(float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Area() const;
  std::string GetName2D() const;

private:
  float major;
  float minor;
};

class Trapezoid : public Shape2D {
public:
  Trapezoid();
  Trapezoid(float, float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Area() const;
  std::string GetName2D() const;

private:
  float top;
  float bottom;
  float height;
};

class Sector : public Shape2D {
public:
  Sector();
  Sector(float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Area() const;
  std::string GetName2D() const;

private:
  float radius;
  float angle;
};

class TriangularPyramid : public Shape3D, private Triangle {
public:
  TriangularPyramid();
  TriangularPyramid(float, float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Volume() const;
  std::string GetName3D() const;

private:
  Triangle base;
  float height;
};

class RectangularPyramid : public Shape3D, private Rectangle {
public:
  RectangularPyramid();
  RectangularPyramid(float, float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Volume() const;
  std::string GetName3D() const;

private:
  Rectangle base;
  float height;
};

class Cylinder : public Shape3D, private Circle {
public:
  Cylinder();
  Cylinder(float, float);
  void Scale(float scaleFactor);
  void Display() const;
  float Volume() const;
  std::string GetName3D() const;

private:
  Circle base;
  float height;
};

class Sphere : public Shape3D, private Circle {
public:
  Sphere();
  Sphere(float);
  void Scale(float scaleFactor);
  void Display() const;
  float Volume() const;
  std::string GetName3D() const;

private:
  Circle base;
  float radius;
};
