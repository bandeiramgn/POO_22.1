#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <memory>
#include <math.h>

struct Point2D {
  double x;
  double y;

  Point2D(double x = 0.0, double y = 0.0) : x(x), y(y) {};

  std::string str() const {
    std::stringstream ss;
    ss << "(" << std::fixed << std::setprecision(2) << x << ", "
    << std::fixed << std::setprecision(2) << y << ")";
    return ss.str();
  }
};    

class Calc {
public:
  static double distance(Point2D pointA, Point2D pointB) {
    double dx = pointA.x - pointB.x;
    double dy = pointA.y - pointB.y;
    return std::sqrt(dx*dx + dy*dy);
  }
};

class Shape {
public:
  std::string name;
  
  Shape(std::string name = "") : name(name){};

  std::string getName() const { return name; }

  virtual bool inside(Point2D point) const = 0;
  virtual double getArea() const = 0;
  virtual double getPerimeter() const = 0;

  virtual std::string str() const {
    return name;
  }
};

class Circle : public Shape {
public:
  Point2D center;
  double radius;

  Circle(Point2D center, double radius) : Shape("Circ"), center(center), radius(radius) {
  };

  bool inside(Point2D point) const override {
    return Calc::distance(point, center) <= radius*radius;
  }

  double getArea() const override { 
    return M_PI * radius * radius;
  }

  double getPerimeter() const override {
    return 2 * M_PI * radius;
  }

  std::string str() const override {
    std::stringstream ss;
    ss << getName() << ": C=" << center.str() << ","
    << " R=" << std::fixed << std::setprecision(2) << radius;
    return ss.str();
  }
};

class Rectangle : public Shape {
public:
  Point2D p1;
  Point2D p2;

  Rectangle(Point2D p1, Point2D p2) : Shape("Rect"), p1(p1), p2(p2)  {};

  bool inside(Point2D point) const override {
    if ((point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x) &&
        point.y >= std::min(p1.y, p2.y) && point.y <= std::max(p1.y, p2.y)))
          return true;

    return false;
  }

  double getArea() const override {
    double width = p1.x - p2.x;
    double height = p1.y - p2.y;
    return width * height;
  }

  double getPerimeter() const override {
    double width = p1.x - p2.x;
    double height = p1.y - p2.y;
    return 2 * (width + height);
  }

  std::string str() const override {
    std::stringstream ss;
    ss << getName() << ": P1=" << p1.str() << " P2=" << p2.str();
    return ss.str();
  }
};

int main() {
  std::string line, cmd;
  std::vector<std::shared_ptr<Shape>> shapes;
  
  while(true) {
    try {
        std::getline(std::cin, line);
        std::cout << "$" << line << '\n';
        std::stringstream ss(line);
        //cria um vetor de strings a partir de line
        std::vector<std::string> ui(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>());
        std::string cmd = ui[0];
        
        if(cmd == "end"){
            break;
        } else if(cmd == "circle") {
            shapes.push_back(std::make_shared<Circle>(Point2D(std::stod(ui[1]), std::stod(ui[2])), std::stod(ui[3])));
        } else if(cmd == "rect") {
            shapes.push_back(std::make_shared<Rectangle>(Point2D(std::stod(ui[1]), std::stod(ui[2])), Point2D(std::stod(ui[3]), std::stod(ui[4]))));
        } else if(cmd == "show") {
            for (auto value : shapes)
              std::cout << value->str() << '\n';
        } else if(cmd == "info") {
          for (auto value : shapes) {
                std::cout << value->getName() << std::fixed << std::setprecision(2) << ": A=" << value->getArea()
                << std::fixed << std::setprecision(2) <<" P=" << value->getPerimeter() << '\n';
          }
        }else { 
            std::cout << "comando invalido " << "[" << cmd << "]\n";
        }
    } catch(std::string e){
      std::cout << e << std::endl;
    }
  }
  return 0;
}