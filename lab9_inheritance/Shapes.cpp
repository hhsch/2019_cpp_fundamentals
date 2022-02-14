#include <string>
#include <iostream>
#include "Shapes.h"

void Shape2D::ShowArea() const {
  std::cout << "The area of the " << GetName2D();
  std::cout << " is : " << Area() << std::endl;
}

bool Shape2D::operator>(const Shape2D &rhs) const {
  return ( Area() > rhs.Area() );
}

bool Shape2D::operator<(const Shape2D &rhs) const {
  return ( Area() < rhs.Area() );
}

bool Shape2D::operator==(const Shape2D &rhs) const {
  return ( Area() == rhs.Area() );
}

void Shape3D::ShowVolume() const {
  std::cout << "The volume of the " << GetName3D();
  std::cout << " is : " << Volume() << std::endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const {
  return ( Volume() > rhs.Volume() );
}

bool Shape3D::operator<(const Shape3D &rhs) const {
  return ( Volume() < rhs.Volume() );
}

bool Shape3D::operator==(const Shape3D &rhs) const {
  return ( Volume() == rhs.Volume() );
}

Square::Square() {
  side = 0;
}

Square::Square(float _side) {
  side = _side;
}

void Square::Scale(float scaleFactor) {
  side *= scaleFactor;
}

void Square::Display() const {
  ShowArea();
  std::cout << "Length of a side: " << side << std::endl;
}

float Square::Area() const {
  return side * side;
}

std::string Square::GetName2D() const {
  return "Square";
}

Rectangle::Rectangle() {
  width = 0;
  height = 0;
}

Rectangle::Rectangle(float _width, float _height) {
  width = _width;
  height = _height;
}

void Rectangle::Scale(float scaleFactor) {
  width *= scaleFactor;
  height *= scaleFactor;
}

void Rectangle::Display() const {
  ShowArea();
  std::cout << "Length: " << width << std::endl;
  std::cout << "Width: " << height << std::endl;
}

float Rectangle::Area() const {
  return width * height;
}

std::string Rectangle::GetName2D() const {
  return "Rectangle";
}

Triangle::Triangle() {
  base = 0;
  height = 0;
}

Triangle::Triangle(float _base, float _height) {
  base = _base;
  height = _height;
}

void Triangle::Scale(float scaleFactor) {
  base *= scaleFactor;
  height *= scaleFactor;
}

void Triangle::Display() const {
  ShowArea();
  std::cout << "Base: " << base << std::endl;
  std::cout << "Height: " << height << std::endl;
}

float Triangle::Area() const {
  return base * height / 2;
}

std::string Triangle::GetName2D() const {
  return "Triangle";
}

Circle::Circle() {
  radius = 0;
}

Circle::Circle(float _radius) {
  radius = _radius;
}

void Circle::Scale(float scaleFactor) {
  radius *= scaleFactor;
}

void Circle::Display() const {
  ShowArea();
  std::cout << "Radius: " << radius << std::endl;
}

float Circle::Area() const {
  return PI * radius * radius;
}

std::string Circle::GetName2D() const {
  return "Circle";
}

Ellipse::Ellipse() {
  major = 0;
  minor = 0;
}

Ellipse::Ellipse(float _major, float _minor) {
  major = _major;
  minor = _minor;
}

void Ellipse::Scale(float scaleFactor) {
  major *= scaleFactor;
  minor *= scaleFactor;
}

void Ellipse::Display() const {
  ShowArea();
  std::cout << "Length of semi-major axis: " << major << std::endl;
  std::cout << "Length of semi-minor axis: " << minor << std::endl;
}

float Ellipse::Area() const {
  return PI * major * minor;
}

std::string Ellipse::GetName2D() const {
  return "Ellipse";
}

Trapezoid::Trapezoid() {
  top = 0;
  bottom = 0;
  height = 0;
}

Trapezoid::Trapezoid(float _top, float _bottom, float _height) {
  top = _top;
  bottom = _bottom;
  height = _height;
}

void Trapezoid::Scale(float scaleFactor) {
  top *= scaleFactor;
  bottom *= scaleFactor;
  height *= scaleFactor;
}

void Trapezoid::Display() const {
  ShowArea();
  std::cout << "Length of side A: " << top << std::endl;
  std::cout << "Length of side B: " << bottom << std::endl;
  std::cout << "Height: " << height << std::endl;
}

float Trapezoid::Area() const {
  return (top + bottom) * height / 2;
}

std::string Trapezoid::GetName2D() const {
  return "Trapezoid";
}

Sector::Sector() {
  radius = 0;
  angle = 0;
}

Sector::Sector(float _radius, float _degree) {
  radius = _radius;
  angle = _degree * PI / 180;
}

void Sector::Scale(float scaleFactor) {
  radius *= scaleFactor;
  angle *= scaleFactor;
}

void Sector::Display() const {
  ShowArea();
  std::cout << "Radius: " << radius << std::endl;
  std::cout << "Angle in radians: " << angle << std::endl;
  std::cout << "Angle in degrees: " << angle * 180 / PI << std::endl;
}

float Sector::Area() const {
  return radius * radius * angle / 2;
}

std::string Sector::GetName2D() const {
  return "Sector";
}

TriangularPyramid::TriangularPyramid() {
  height = 0;
}

TriangularPyramid::TriangularPyramid(float _height, float triLength, float triHeight) {
  base = Triangle(triLength, triHeight);
  height = _height;
}

void TriangularPyramid::Scale(float scaleFactor) {
  base.Scale(scaleFactor);
  height *= scaleFactor;
}

void TriangularPyramid::Display() const {
  ShowVolume();
  std::cout << "The height is: " << height << std::endl;
  base.Display();
}

float TriangularPyramid::Volume() const {
  return base.Area() * height / 3;
}

std::string TriangularPyramid::GetName3D() const {
  return "Triangular Pyramid";
}

RectangularPyramid::RectangularPyramid() {
  height = 0;
}

RectangularPyramid::RectangularPyramid(float _height, float rectLength, float rectWidth) {
  base = Rectangle(rectLength, rectWidth);
  height = _height;
}

void RectangularPyramid::Scale(float scaleFactor) {
  base.Scale(scaleFactor);
  height *= scaleFactor;
}

void RectangularPyramid::Display() const {
  ShowVolume();
  std::cout << "The height is: " << height << std::endl;
  base.Display();
}

float RectangularPyramid::Volume() const {
  return base.Area() * height / 3;
}

std::string RectangularPyramid::GetName3D() const {
  return "Rectangular Pyramid";
}

Cylinder::Cylinder() {
  height = 0;
}

Cylinder::Cylinder(float _height, float circRadius) {
  base = Circle(circRadius);
  height = _height;
}

void Cylinder::Scale(float scaleFactor) {
  base.Scale(scaleFactor);
  height *= scaleFactor;
}

void Cylinder::Display() const {
  ShowVolume();
  std::cout << "The height is: " << height << std::endl;
  base.Display();
}

float Cylinder::Volume() const {
  return base.Area() * height;
}

std::string Cylinder::GetName3D() const {
  return "Cylinder";
}

Sphere::Sphere() {
  radius = 0;
}

Sphere::Sphere(float _radius) {
  base = Circle(_radius);
  radius = _radius;
}

void Sphere::Scale(float scaleFactor) {
  base.Scale(scaleFactor);
  radius *= scaleFactor;
}

void Sphere::Display() const {
  ShowVolume();
  base.Display();
}

float Sphere::Volume() const {
  return base.Area() * radius * 4 / 3;
}

std::string Sphere::GetName3D() const {
  return "Sphere";
}
