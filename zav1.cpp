#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <exception>

using namespace std;

// Функція Variant
double Variant(double r, double k) {
    return 0.8973 * r + 0.1027 * k;
}

// Функція Qgn
double Qgn(double x, double y) {
    return log(1 + abs(x - y)) * (pow(sin(x), 2) + pow(cos(y), 2));
}

// Функція Qnk
double Qnk(double x, double y) {
    return Qgn(x, y - x) + Qgn(y, x - y);
}

// Функція Rnk
double Rnk(double x, double y) {
    return x * Qnk(x, y) + y * Qnk(y, x);
}

// Функція U
double U(double x) {
    return pow(sin(x), 2) - pow(cos(x), 2);
}

// Функція T
double T(double x) {
    return pow(x, 2) - x + 1;
}

// Функція Max
double Max(double x, double y, double z) {
    return max({ x, y, z });
}

// Функція RText
double RText(double x, double y, double z, string text) {
    if (text.empty()) {
        return x + y + z;
    }
    else {
        return x * y * z;
    }
}

// Функція CText
double CText(double x, double y, double z, double u, string text) {
    return Max(x, y, z) + u + text.length();
}

// Функція func
double func(double x, double y, double z) {
    return Rnk(x, y) + Rnk(y, z) * Rnk(x, y);
}

// Функція Gtext
double Gtext(string action) {
    if (action == "set") {
        return 1;
    }
    else if (action == "get") {
        return 2;
    }
    return 0;
}

// Функція для обчислення CText
double CText(double x, double y, double z, string text) {
    if (text.empty()) {
        return Gtext("set") + Gtext("get") - x * y;
    }
    else {
        return Gtext("set") + Gtext(text) + z;
    }
}

// Алгоритм 2: функція Rnk2
double Rnk2(double x, double y) {
    return x * Qnk(x, y) + y * Qnk(y, x) - 0.03 * Qnk(x, y) + 0.12 * Qnk(x, y) * y;
}

// Алгоритм 2: функція Qnk2
double Qnk2(double x, double y) {
    return 1.1 * Qgn(x, y - x) + 0.9 * Qgn(y, x - y) + Qnk(x, y);
}

// Алгоритм 2: функція U1
double U1(double x) {
    return 2 * pow(sin(x), 2);
}

// Алгоритм 2: функція U2
double U2(double x) {
    return pow(cos(x), 2);
}

// Алгоритм 2: функція U2 з двома аргументами
double U2(double x, double y) {
    return (U1(x) + y * T(y) - U2(y) * T(x)) / (U1(x) + T(x));
}

// Головна функція
int main() {
    // Ініціалізація змінних
    double x, y, z, r, k;
    string text;

    // Введення змінних
    cin >> x >> y >> z >> text;

    // Відкриття файлів
    ifstream dat1, dat2, dat3;

    // Обробка файлу dat1.dat
    try {
        dat1.open("dat1.dat");
        if (!dat1.is_open()) throw runtime_error("Could not open dat1.dat");

        double dat1_x, dat1_y;
        while (dat1 >> dat1_x >> dat1_y) {
            double temp = Rnk(dat1_x, dat1_y);
            cout << "Обробка з dat1.dat, Rnk: " << temp << endl;
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        // Виклик Алгоритму 2
        double i = 1;
        while (i <= 5) {
            double temp = Rnk2(x, y);
            cout << "Алгоритм 2, Rnk2: " << temp << endl;
            i++;
        }
    }

    // Обробка файлу dat2.dat
    try {
        dat2.open("dat2.dat");
        if (!dat2.is_open()) throw runtime_error("Could not open dat2.dat");

        double dat2_x, dat2_y, dat2_z;
        while (dat2 >> dat2_x >> dat2_y >> dat2_z) {
            double temp = func(dat2_x, dat2_y, dat2_z);
            cout << "Обробка з dat2.dat, func: " << temp << endl;
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        // Виклик Алгоритму 3
        double i = 1;
        while (i <= 10) {
            double temp = Rnk(x, y);
            cout << "Алгоритм 3, Rnk: " << temp << endl;
            i++;
        }
    }

    // Основні обчислення
    r = func(x, y, z);
    k = CText(Max(x, y, z), x + y + z, r, text);

    // Обчислення Variant(r, k)
    double result = Variant(r, k);

    // Виведення результату
    cout << "Result: " << result << endl;

    return 0;
}
