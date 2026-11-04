#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#define k 1

/*double euclidianDistance(double* a, double* b, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}*/

struct Data {
    int classNo;
    int pixelArray[784];
};

void readDataFromFile(const string& filename, Data* data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line = "";

    int j=0;
    while (getline(file, line)) {
        if ((line.rfind("@", 0) == 0) || (line.rfind("%", 0) == 0) || (line.empty())) {
            continue;
        } else {
            data[j].classNo = line.back() - '0';
            const char* splitBy = ",";
            char* token = strtok(line.data(), splitBy);

            int i = 0;
            while (token != nullptr) {
                if (i == 784) {
                    break;
                }
                data[j].pixelArray[i++] = atoi(token);
                token = strtok(nullptr, splitBy);
            }
        }
        j++;
    }
}
int main() {
    Data* data = new Data[70000];
    readDataFromFile("mnist_784.arff", data);
    for (int i = 0; i < 10; ++i) {
        cout << "Class: " << data[i].classNo << ", Pixels: ";
        for (int j = 0; j < 784; ++j) {
            cout << data[i].pixelArray[j] << " ";
        }
        cout << endl;
    }
    return 0;
}