#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// Читання таблиці з файлу
vector<pair<double, double>> readTable(const string& fileName) {
    vector<pair<double, double>> data;
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open file " << fileName << endl;
        return data;
    }
    double x, y;
    while (file >> x >> y) {
        data.emplace_back(x, y);
    }
    file.close();
    return data;
}

// Читання таблиці text-value
map<string, double> readTextTable(const string& fileName) {
    map<string, double> data;
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open file " << fileName << endl;
        return data;
    }
    string text;
    double value;
    while (file >> text >> value) {
        data[text] = value;
    }
    file.close();
    return data;
}

// Інтерполяція значень
double interpolate(double x, const vector<pair<double, double>>& data) {
    for (size_t i = 0; i < data.size() - 1; ++i) {
        if (x >= data[i].first && x <= data[i + 1].first) {
            double t = (x - data[i].first) / (data[i + 1].first - data[i].first);
            return (1 - t) * data[i].second + t * data[i + 1].second;
        }
    }
    return 0;
}

double U(double x, const vector<pair<double, double>>& data) {
    return interpolate(x, data);
}

double T(double x, const vector<pair<double, double>>& data) {
    return interpolate(x, data);
}

double G(const string& text, const map<string, double>& data) {
    if (text.empty()) return 0;
    if (data.find(text) != data.end()) {
        return data.at(text);
    }
    return 0;
}

double Max(double a, double b, double c, double d) {
    return max(max(a, b), max(c, d));
}

// Обчислення R(x, y) за алгоритмом 2
double Rnk2(double x, double y, const vector<pair<double, double>>& uData, const vector<pair<double, double>>& tData) {
    return x * y + U(x, uData) * T(y, tData);
}

// Алгоритм 2
double Qnk1(double x, double y) {
    return x * y;
}

double Qqn1(double x, double y) {
    return x - y;
}

double Qnk1Alg2(double x, double y, double z, const vector<pair<double, double>>& uData, const vector<pair<double, double>>& tData) {
    return (U(x, uData) * U(x, uData) / (T(z, tData) - U(z, uData))) + Qnk1(x, y);
}

double Rnk1Alg2(double x, double y, const vector<pair<double, double>>& uData, const vector<pair<double, double>>& tData) {
    return Qnk1Alg2(x, y, x * y, uData, tData);
}

double Rnk2Alg2(double x, double y, const vector<pair<double, double>>& uData, const vector<pair<double, double>>& tData) {
    return Qnk1(x, y) + Qnk1Alg2(x, y, x * y, uData, tData);
}

// Алгоритм 3
double Qnk2(double x, double y) {
    return x * y * 1.25 + Qnk1(x, y);
}

double Qqn2(double x, double y) {
    return 1.3 * x * y - Qqn1(x, y);
}

double Qnk2Alg3(double x, double y, double z, const vector<pair<double, double>>& uData, const vector<pair<double, double>>& tData) {
    return (U(x, uData) * U(x, uData) * 0.9 / (T(z, tData) - U(z, uData))) + Qnk2(x, y);
}

double Rnk1Alg3(double x, double y, const vector<pair<double, double>>& uData, const vector<pair<double, double>>& tData) {
    return Qnk2Alg3(x, y, x * y, uData, tData);
}

double Rnk2Alg3(double x, double y, const vector<pair<double, double>>& uData, const vector<pair<double, double>>& tData) {
    return Qnk2(x, y) + Qnk2Alg3(x, y, x * y, uData, tData);
}

// Основна функція обчислення
double compute(double x, double y, double z, const string& text,
    const vector<pair<double, double>>& uData,
    const vector<pair<double, double>>& tData,
    const map<string, double>& textData) {

    double r, k;

    if (uData.empty() || x <= 5) {
        r = Rnk2(x, y, uData, tData);
    }
    else {
        r = U(x, uData);
    }

    if (tData.empty() || x <= 10) {
        k = Rnk2(x, y, uData, tData);
    }
    else {
        k = T(x, tData);
    }

    double CText = G(text, textData) + x;

    double variant = r + 1027.0 * k + 8973.0;

    return Max(variant, r + k, z, CText);
}

int main() {
    // Зчитування даних з файлів
    vector<pair<double, double>> uData = readTable("dat1.dat");
    vector<pair<double, double>> tData = readTable("dat2.dat");
    map<string, double> textData = readTextTable("dat3.dat");

    double x, y, z;
    string text;

    // Введення даних
    cin >> x >> y >> z;
    cin.ignore();
    getline(cin, text);

    // Обчислення результату
    double result = compute(x, y, z, text, uData, tData, textData);

    // Виведення результату
    cout << "Result: " << result << endl;

    return 0;
}
