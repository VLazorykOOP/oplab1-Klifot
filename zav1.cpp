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

    return Max(r, k, z, CText);
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
