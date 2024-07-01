#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <exception>

using namespace std;

// Function declarations
double Variant(double r, double k);
double Qgn(double x, double y);
double Qnk(double x, double y);
double Rnk(double x, double y);
double U(double x);
double T(double x);
double Max(double x, double y, double z);
double RText(double x, double y, double z, string text);
double CText(double x, double y, double z, double u, string text);
double func(double x, double y, double z);
double Gtext(string action);
double CText(double x, double y, double z, string text);
double Rnk2(double x, double y);
double Qnk2(double x, double y);
double U1(double x);
double U2(double x);
double U2(double x, double y);

// Custom exception classes
class ErrorRange {
    string str = "ErrorRange";
public:
    double rd;
    ErrorRange(double d) : rd(d) { }
    void Message() const {
        cout << "ErrorRange: current x is " << rd << " but -10 < x < 10" << endl;
    }
};

class ErrorNoFile {
    string str = "ErrorNoFile";
public:
    ErrorNoFile(string s) : str(s) { }
    void Message() const {
        cout << "ErrorNoFile: " << str << endl;
    }
};

class ErrorKrl {
    string str = "ErrorKrl";
protected:
    double x;
public:
    ErrorKrl(double dx) : x(dx) { }
    virtual void Message() const {
        cout << "ErrorKrl: " << str << endl;
    }
    virtual double setFun() const { return x + 1; }
};

class ErrorDKrl : public ErrorKrl {
public:
    ErrorDKrl(double dx) : ErrorKrl(dx) { }
    void Message() const override {
        cout << "ErrorDKrl: derived from ErrorKrl" << endl;
    }
    double setFun() const override { return x + 2; }
};

// Main function
int main() {
    // Initialization of variables
    double x, y, z, r, k;
    string text;

    // Input variables
    cout << "Enter values for x, y, z: ";
    cin >> x >> y >> z;

    // Open files
    ifstream dat1, dat2, dat3;

    // Processing dat1.dat file
    try {
        dat1.open("dat1.dat");
        if (!dat1.is_open()) throw ErrorNoFile("dat1.dat");

        double dat1_x, dat1_y;
        int count = 0;
        while (dat1 >> dat1_x >> dat1_y && count < 5) { // Process only the first 5 lines for example
            double temp = Rnk(dat1_x, dat1_y);
            cout << fixed << setprecision(5) << "Processing dat1.dat, Rnk: " << temp << endl;
            count++;
        }
    }
    catch (const ErrorNoFile& e) {
        e.Message();
        // Call Algorithm 2
        double i = 1;
        while (i <= 5) {
            double temp = Rnk2(x, y);
            cout << fixed << setprecision(5) << "Algorithm 2, Rnk2: " << temp << endl;
            i++;
        }
    }

    // Processing dat2.dat file
    try {
        dat2.open("dat2.dat");
        if (!dat2.is_open()) throw ErrorNoFile("dat2.dat");

        double dat2_x, dat2_y, dat2_z;
        int count = 0;
        while (dat2 >> dat2_x >> dat2_y >> dat2_z && count < 5) { // Process only the first 5 lines for example
            double temp = func(dat2_x, dat2_y, dat2_z);
            cout << fixed << setprecision(5) << "Processing dat2.dat, func: " << temp << endl;
            count++;
        }
    }
    catch (const ErrorNoFile& e) {
        e.Message();
        // Call Algorithm 3
        double i = 1;
        while (i <= 10) {
            double temp = Rnk(x, y);
            cout << fixed << setprecision(5) << "Algorithm 3, Rnk: " << temp << endl;
            i++;
        }
    }

    // Main calculations
    r = func(x, y, z);
    k = CText(Max(x, y, z), x + y + z, r, text);

    // Calculate Variant(r, k)
    double result = Variant(r, k);

    // Output result
    cout << "The value of fun(x, y, z) is: " << fixed << setprecision(5) << result << endl;

    return 0;
}

// Function definitions
double Variant(double r, double k) {
    return 0.8973 * r + 0.1027 * k;
}

double Qgn(double x, double y) {
    return log(1 + abs(x - y)) * (pow(sin(x), 2) + pow(cos(y), 2));
}

double Qnk(double x, double y) {
    return Qgn(x, y - x) + Qgn(y, x - y);
}

double Rnk(double x, double y) {
    return x * Qnk(x, y) + y * Qnk(y, x);
}

double U(double x) {
    return pow(sin(x), 2) - pow(cos(x), 2);
}

double T(double x) {
    return pow(x, 2) - x + 1;
}

double Max(double x, double y, double z) {
    return max({ x, y, z });
}

double RText(double x, double y, double z, string text) {
    if (text.empty()) {
        return x + y + z;
    }
    else {
        return x * y * z;
    }
}

double CText(double x, double y, double z, double u, string text) {
    return Max(x, y, z) + u + text.length();
}

double func(double x, double y, double z) {
    return Rnk(x, y) + Rnk(y, z) * Rnk(x, y);
}

double Gtext(string action) {
    if (action == "set") {
        return 1;
    }
    else if (action == "get") {
        return 2;
    }
    return 0;
}

double CText(double x, double y, double z, string text) {
    if (text.empty()) {
        return Gtext("set") + Gtext("get") - x * y;
    }
    else {
        return Gtext("set") + Gtext(text) + z;
    }
}

double Rnk2(double x, double y) {
    return x * Qnk(x, y) + y * Qnk(y, x) - 0.03 * Qnk(x, y) + 0.12 * Qnk(x, y) * y;
}

double Qnk2(double x, double y) {
    return 1.1 * Qgn(x, y - x) + 0.9 * Qgn(y, x - y) + Qnk(x, y);
}

double U1(double x) {
    return 2 * pow(sin(x), 2);
}

double U2(double x) {
    return pow(cos(x), 2);
}

double U2(double x, double y) {
    return (U1(x) + y * T(y) - U2(y) * T(x)) / (U1(x) + T(x));
}
