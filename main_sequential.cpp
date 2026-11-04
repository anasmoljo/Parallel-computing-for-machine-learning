#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

#define k 1
#define number_of_pixels 784
#define train_size 60000
#define test_size 10000

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

    string line;

    int j=0;
    while (getline(file, line)) {
        if ((line.rfind('@', 0) == 0) || (line.rfind('%', 0) == 0) || (line.empty())) {
            continue;
        }

        data[j].classNo = line.back() - '0';
        const char* splitBy = ",";
        char* token = strtok(line.data(), splitBy);

        int i = 0;
        while (token != nullptr) {
            if (i == number_of_pixels) {
                break;
            }
            data[j].pixelArray[i++] = atoi(token);
            token = strtok(nullptr, splitBy);
        }
        j++;
    }
}

double euclidianDistance(int* a, int* b, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        int diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

Data* getNeighbours(Data* training_set, Data test_instance) {
    vector<pair<Data, double>> neighbourDistances;

    for (int i = 0; i < train_size; i++) {
        neighbourDistances.push_back(make_pair(training_set[i], euclidianDistance(test_instance.pixelArray, training_set[i].pixelArray, number_of_pixels)));
    }

    sort(neighbourDistances.begin(), neighbourDistances.end(), [](const pair<Data, double>& a, const pair<Data, double>& b) {
        return a.second < b.second;
    });

    Data* neighbours = new Data[k];
    for (int i = 0; i < k; i++) {
        neighbours[i] = neighbourDistances[i].first;
        cout << "Distance: " << neighbourDistances[i].second << endl;
    }

    return neighbours;
}

int main() {
    Data* data = new Data[70000];
    readDataFromFile("mnist_784.arff", data);

    Data* training_set = new Data[train_size];
    Data* test_set = new Data[test_size];

    copy_n(data, train_size, training_set);
    copy_n(&data[train_size], test_size, test_set);

    for (int i = 0; i < 10; ++i) {
        cout << "Class: " << data[i].classNo << ", Pixels: ";
        for (int j = 0; j < 784; ++j) {
            cout << data[i].pixelArray[j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < 3; i++) {
        Data* neighbours = getNeighbours(training_set, test_set[i]);
        for (int j = 0; j < k; ++j) {
            cout << "Class: " << neighbours[j].classNo << "is neighbourd to" << test_set[i].classNo;
            cout << endl;
        }
    }

    delete[] data;

    return 0;
}