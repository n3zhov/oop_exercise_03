#include <iostream>
#include <vector>
#include <cmath>
/*
 * Ежов Н П М8О-207Б-19
 * Разработать классы согласно варианту задания,
 * классы должны наследоваться от базового класса Figure.
 * Фигуры являются фигурами вращения.
 * Все классы должны поддерживать набор общих методов:
 * - Вычисление геометрического центра фигуры
 * - Вывод в стандартный поток std::cout координат вершин фигуры
 * - Вычисление площади фигуры
 * Создать программу, которая позволяет:
 * - Вводить в стандартный поток std::cin фигуры
 * - Сохранять заданные фигуры в вектор std::vector<Figure*>
 * - Вызывать для всего массива общие функции
 * - Необходимо уметь вычислять общую площадь фигур в массиве.
 * - Удалять из массива фигуру по индексу
 * Трапеция, ромб, пятиугольник.
 */
const double PI = 3.141592653589;

class Cord {
protected:
    long double X, Y;
public:
    Cord() : X(0), Y(0) {};
    Cord(long double x, long double y) : X(x), Y(y) {};
    ~Cord() = default;;
    friend std::ostream & operator << (std::ostream & out, const Cord & crd);
};

class Figure {
public:
    virtual long double FigureSquare() = 0;
    virtual Cord FigureCenter() = 0;
    virtual void FigurePrint() = 0;
};

class Trapeze : public Figure {
private:
    /* Cords of left bottom corner, larger and smaller base, side */
    long double X, Y, A, B, C;
public:
    Trapeze(const long double & x, const long double & y, const long double & a, const long double & b, const long double & c);
    long double FigureSquare() override;
    Cord FigureCenter() override;
    void FigurePrint() override;
    friend std::ostream & operator << (std::ostream & out, const Trapeze & trapez);
};

class Rhomb : public Figure {
private:
    /* Cords of left bottom corner, and angle phi between sides*/
    double X, Y, A, PHI;
public:
    Rhomb(const double & x, const double & y, const double & a, const double & phi);
    long double FigureSquare() override;
    Cord FigureCenter() override;
    void FigurePrint() override;
    friend std::ostream & operator << (std::ostream & out, const Rhomb & trapez);
};

class Pentagon : public Figure {
private:
    /* Cords of left bottom corner, and size of side*/
    double X, Y, A;
public:
    Pentagon(const double & x, const double & y, const double & a);
    long double FigureSquare() override;
    Cord FigureCenter() override;
    void FigurePrint() override;
    friend std::ostream & operator << (std::ostream & out, const Pentagon & trapez);
};

long double TotalSquare(std::vector<Figure*> & figures) {
    long double res = 0.0;
    for (auto fig : figures) {
        res = res + fig->FigureSquare();
    }
    return res;
}

int main() {
    double x = 0.0, y = 0.0, a = -1.0, b = -1.0, c = -1.0, phi = 0.0;
    std::vector<Figure*> vec;

    /* Input trapeze */
    std::cout << "Input trapeze as follows: x y a b c" << std::endl;
    std::cout << "x, y is a left bottom corner cords" << std::endl;
    std::cout << "a, b and c are larger, smaller base and side" << std::endl;
    std::cin >> x >> y >> a >> b >> c;
    Trapeze * trapeze = NULL;
    try {
        trapeze = new Trapeze(x, y, a, b, c);
    } catch (std::invalid_argument & ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    x = 0.0, y = 0.0, a = -1.0, b = -1.0, c = -1.0;
    vec.push_back(trapeze);

    /* Input rhomb */
    std::cout << "Input square as follows: x y a phi (as degrees)" << std::endl;
    std::cout << "x, y is a left bottom corner cords" << std::endl;
    std::cout << "phi is angle between sides" << std::endl;
    std::cin >> x >> y >> a >> phi;
    Rhomb* rhomb = NULL;
    try {
        rhomb = new Rhomb(x, y, a, phi);
    } catch (std::invalid_argument & ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    x = 0.0, y = 0.0, a = -1.0;
    vec.push_back(rhomb);

    /* Input pentagon */
    std::cout << "Input rectangle as follows: x y a" << std::endl;
    std::cout << "x, y is a left bottom corner cords" << std::endl;
    std::cout << "a is size of side" << std::endl;
    std::cin >> x >> y >> a;
    Pentagon * pentagon = NULL;
    try {
        pentagon = new Pentagon(x, y, a);
    } catch (std::invalid_argument & ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    x = 0.0, y = 0.0, a = -1.0, b = -1.0;
    vec.push_back(pentagon);


    for (auto fig : vec) {
        fig->FigurePrint();
        std::cout << "Center of figure is " << fig->FigureCenter() << std::endl;
        std::cout << "Square of figure is " << fig->FigureSquare() << std::endl;
    }
    std::cout << "Total square: " << TotalSquare(vec) << std::endl;
    int i = 0;
    std::cout << "Input index to remove figure" << std::endl;
    std::cin >> i;
    for (auto fig = vec.begin(); fig != vec.end() and i > 0; ++fig) {
        --i;
        if (i == 0) {
            vec.erase(fig);
        }
    }
    for (auto fig : vec) {
        fig->FigurePrint();
        std::cout << "Center of figure is " << fig->FigureCenter() << std::endl;
        std::cout << "Square of figure is " << fig->FigureSquare() << std::endl;
    }
    std::cout << "Total square after erase: " << TotalSquare(vec) << std::endl;
    return 0;
}

std::ostream & operator << (std::ostream & out, const Cord & crd) {
    out << "(" << crd.X << ", " << crd.Y << ")";
    return out;
}

Trapeze::Trapeze(const long double & x, const long double & y, const long double & a, const long double & b,
                 const long double & c) : X(x), Y(y), A(a), B(b), C(c) {
    if (A < 0.0 or B < 0.0 or C < 0.0) {
        throw std::invalid_argument("Invalid trapeze parameters!");
    }
    if (B > A) {
        std::swap(A, B);
    }
}

Rhomb::Rhomb(const double & x, const double & y, const double & a, const double & phi) : X(x), Y(y), A(a), PHI(phi) {
    if (phi >= 180 || A <= 0) {
        throw std::invalid_argument("Invalid rhomb parameters!");
    }
}

Pentagon::Pentagon(const double & x, const double & y, const double & a) : X(x), Y(y), A(a) {
    if (A <= 0){
        throw std::invalid_argument("Invalid pentagon parameters!");
    }
}

long double Trapeze::FigureSquare() {
    long double diff = (A - B) / 2.0;
    long double height = std::sqrt(C * C - diff * diff);
    return height * (A + B) / 2.0;
}

Cord Trapeze::FigureCenter() {
    long double diff = (A - B) / 2.0;
    long double height = std::sqrt(C * C - diff * diff);
    return Cord(X + A / 2.0, Y + height / 2.0);
}

void Trapeze::FigurePrint() {
    std::cout << *this << std::endl;
}

std::ostream & operator << (std::ostream & out, const Trapeze & trapeze) {
    long double diff = (trapeze.A - trapeze.B) / 2.0;
    long double height = std::sqrt(trapeze.C * trapeze.C - diff * diff);
    out << "Trapeze verticies: [";
    out << Cord(trapeze.X, trapeze.Y) << ", ";
    out << Cord(trapeze.X + diff, trapeze.Y + height) << ", ";
    out << Cord(trapeze.X + trapeze.A - diff, trapeze.Y + height) << ", ";
    out << Cord(trapeze.X + trapeze.A, trapeze.Y);
    out << "]";
    return out;
}


long double Rhomb::FigureSquare() {
    long double S = A*A*sin(PHI*PI/180);
    return S;
}

Cord Rhomb::FigureCenter() {
    double X1, Y1;
    X1 = X + A * cos(PHI *PI/180);
    Y1 = Y + A * sin(PHI * PI/180);
    X1 += A;
    return Cord((X+X1)/2.0, (Y+Y1)/2.0);
}

void Rhomb::FigurePrint() {
    std::cout << *this << std::endl;
}

std::ostream & operator << (std::ostream & out, const Rhomb & rhomb) {
    double X1, Y1;
    X1 = rhomb.X + rhomb.A * cos(rhomb.PHI *PI/180);
    Y1 = rhomb.Y + rhomb.A * sin(rhomb.PHI * PI/180);
    out << "Rhomb coordinates: [";
    out << Cord(rhomb.X, rhomb.Y) << ", ";
    out << Cord(X1, Y1) << ", ";
    X1 += rhomb.A;
    out << Cord(X1, Y1) << ", ";
    X1 = rhomb.X + rhomb.A;
    Y1 = rhomb.Y;
    out << "]";
    out << Cord(X1, Y1) << ", ";
    return out;
}


long double Pentagon::FigureSquare() {
    long double S = A*A*5/4*tan(PI/5);
    return S;
}

Cord Pentagon::FigureCenter() {
    double X1, Y1;
    X1 = (X + A)/2.0;
    Y1 = Y + (A/2*tan(54*PI/180));
    return Cord(X1, Y1);
}

void Pentagon::FigurePrint() {
    std::cout << *this << std::endl;
}

std::ostream & operator << (std::ostream & out, const Pentagon & pentagon) {
    double X1, Y1;
    X1 = pentagon.X - pentagon.A * cos(72 *PI/180);
    Y1 = pentagon.Y + pentagon.A * sin(72 * PI/180);
    out << "pentagon coordinates: [";
    out << Cord(pentagon.X, pentagon.Y) << ", ";
    out << Cord(X1, Y1) << ", ";
    X1 = X1 + pentagon.A * cos(36*PI/180);
    Y1 = Y1 + pentagon.A * sin(36*PI/180);
    out << Cord(X1, Y1) << ", ";
    X1 = X1 + pentagon.A * cos(36*PI/180);
    Y1 = Y1 - pentagon.A * sin(36*PI/180);
    out << Cord(X1, Y1) << ", ";
    Y1 = pentagon.Y;
    X1 = pentagon.X + pentagon.A;
    out << Cord(X1, Y1) << ", ";
    return out;
}