#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Shape {
protected:
    double x;
    double y;
public:
    Shape() :x(0), y(0) {}
    Shape(double x, double y) :x(x), y(y) {}
    virtual void Show() const {
        cout << "???" << "\nKordinati: (" << x<<" , "<<y<<")" << endl;
    }
    virtual void Save(ofstream& zap) const {
        zap << "??? " << "\nKordinati: " << x << " , " << y << endl;
    }
    virtual void Load(ifstream& print) {
        print >> x >> y ;
    }
    virtual ~Shape() {}
};
class Square:public Shape {
    double a;
public:
    Square() :Shape(0, 0), a(0) {}
    Square(double x, double y, double a) :Shape(x, y),a(a) {}
    virtual void Show() const {
        cout << "Square \nKordinati: (" << x << " , " << y << ")\nStorona: "<<a << endl;
    }
    virtual void Save(ofstream& zap) const {
        zap << "Square\n" << x << " " << y << " " << a << endl;
    }
    virtual void Load(ifstream& print) {
        Shape::Load(print);
        print >>a;
    }
};
class Rectangle :public Shape {
    double a;
    double b;
public:
    Rectangle() :Shape(0, 0), a(0),b(0) {}
    Rectangle(double x, double y, double a, double b) :Shape(x, y), a(a),b(b) {}
    virtual void Show() const {
        cout << "Rectangle \nKordinati: (" << x << " , " << y << ")\nStoroni: " << a<<" , "<<b  << endl;
    }
    virtual void Save(ofstream& zap) const {
        zap << "Rectangle\n" << x << " " << y << " " << a << " " << b << endl;
    }
    virtual void Load(ifstream& print) {
        Shape::Load(print);
        print >> a>>b;
    }
};
class Circle :public Shape {
    double R;
public:
    Circle() :Shape(0, 0), R(0) {}
    Circle(double x, double y, double R) :Shape(x, y), R(R) {}
    virtual void Show() const {
        cout << "Circle \nKordinati: (" << x << " , " << y << ")\nRadius: " << R<< endl;
    }
    virtual void Save(ofstream& zap) const {
        zap << "Circle\n" << x << " " << y << " " << R << endl;
    }
    virtual void Load(ifstream& print) {
        Shape::Load(print);
        print >> R;
    }
};
class Ellipse :public Shape {
    double a;
    double b;
public:
    Ellipse() :Shape(0, 0), a(0), b(0) {}
    Ellipse(double x, double y, double a, double b) :Shape(x, y), a(a), b(b) {}
    virtual void Show() const {
        cout << "Ellipse \nKordinati: (" << x << " , " << y << ")\nStoroni: " << a << " , " << b << endl;
    }
    virtual void Save(ofstream& zap) const {
        zap << "Ellipse\n" << x << " " << y << " " << a << " " << b << endl;
    }
    virtual void Load(ifstream& print) {
        Shape::Load(print);
        print >>  a >> b;
    }
};
int main()
{
    Shape* figures[4];
    figures[0] = new Square(5, -9,4);
    figures[1] = new Rectangle(6.5, 12, 8,4.3);
    figures[2] = new Circle(7, -2.6, 3);
    figures[3] = new Ellipse(3, 5.2, 7, 2);


    ofstream outFile("figures.txt");
    if (outFile.is_open()) {
        for (auto figure : figures) {
            figure->Save(outFile);
        }
        outFile.close();
    }
    else {
        cout << "Error opening file for writing!" << endl;
        return 1;  
    }
    Shape* figures2[4] = { nullptr, nullptr, nullptr, nullptr };
    ifstream inFile("figures.txt");
    if (!inFile.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return 1; 
    }
    string type;
    int count = 0;
    while(getline(inFile, type) && count < 4) {
        if (type == "Square") {
            figures2[count] = new Square();
        }
        if (type == "Rectangle") {
            figures2[count] = new Rectangle();
        }
        if (type == "Circle") {
            figures2[count] = new Circle();
        }
        if (type=="Ellipse") {
            figures2[count] = new Ellipse();
        }
        if (figures2[count]) {
            figures2[count]->Load(inFile); 
            count++;
        }
        
    }
    inFile.close();

    for (int i = 0; i < count; i++) {
        if (figures2[i] != nullptr) {
            figures2[i]->Show();
        }
    }
    for (int i = 0; i < 4; i++) {
        delete figures[i];
    }
}

