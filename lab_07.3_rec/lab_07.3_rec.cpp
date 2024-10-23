#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

int** make_arr(int rows) {
    return new int* [rows];
}

void make_cols(int** arr, int rows, int cols, int r=0) {
    if (r != rows) {
        arr[r] = new int[cols];
        make_cols(arr, rows, cols, r+1);
    }
}

void fill_arr(int** arr, int rows, int cols, int low, int high, int r = 0, int c = 0) {
    if (r != rows) {
        if (c != cols) {
            arr[r][c] = low + rand() % (high - low + 1);
            fill_arr(arr, rows, cols, low, high, r, c + 1);
        }
        else {
            fill_arr(arr, rows, cols, low, high, r+1);
        }
    }
}

void print_arr(int** arr, int rows, int cols, int r = 0, int c = 0) {
    if (r != rows) {
        if (c != cols) {
            cout << setw(4) << arr[r][c];
            print_arr(arr, rows, cols, r, c + 1);
        }
        else {
            cout << endl;
            print_arr(arr, rows, cols, r+1);
        }
    }
}

int colSpec(int** arr, int rows, int col_index, int i = 0) {
    if (i != rows) {
        if (arr[i][col_index] < 0 && arr[i][col_index] % 2 != 0) {
            return abs(arr[i][col_index]) + colSpec(arr, rows, col_index, i + 1);
        }
        return colSpec(arr, rows, col_index, i + 1);
    }
    return 0;
}

void swapColumns(int** arr, int rows, int col1, int col2, int r = 0) {
    if (r < rows) {
        int temp = arr[r][col1];
        arr[r][col1] = arr[r][col2];
        arr[r][col2] = temp;
        swapColumns(arr, rows, col1, col2, r + 1);
    }
}

void sortBySpecs(int** arr, int rows, int cols, int i = 0, int j = 0) {
    if (i < cols - 1) {
        if (j < cols - i - 1) {
            if (colSpec(arr, rows, j) > colSpec(arr, rows, j + 1)) {
                swapColumns(arr, rows, j, j + 1);
            }
            sortBySpecs(arr, rows, cols, i, j + 1);
        }
        else {
            sortBySpecs(arr, rows, cols, i + 1, 0);
        }
    }
}

int colSum(int** arr, int rows, int col_index, int i = 0) {
    if (i != rows) {
        return arr[i][col_index] + colSum(arr, rows, col_index, i + 1);
    }
    return 0;
}

bool isNegative(int** arr, int rows, int col_index, int i = 0) {
    if (i != rows) {
        return (arr[i][col_index] < 0) || isNegative(arr, rows, col_index, i + 1);
    }
    return false;
}

int sumWithNegative(int** arr, int rows, int cols, int i=0) {
    if (i < cols) {
        int res = colSum(arr, rows, i);
        if (isNegative(arr, rows, i, 0)) {
            return res + sumWithNegative(arr, rows, cols, i + 1);
        }
        else {
            return sumWithNegative(arr, rows, cols, i + 1);
        }
    }
    return 0;
}

int main(){
    srand(time(NULL));
    int k, n, col_index;
    cout << "k = "; cin >> k;
    cout << "n = "; cin >> n;
    cout << "nth col = "; cin >> col_index;

    int** a = make_arr(k);
    make_cols(a, k, n);
    fill_arr(a,k,n,-10,10);
    print_arr(a,k,n);
    cout << col_index << " col specs = " << colSpec(a, k, col_index - 1) << endl << endl;
    sortBySpecs(a, k, n);
    print_arr(a, k, n);
    cout << "sum = " << sumWithNegative(a, k, n) << endl;

    for (int i = 0; i != k; i++) {
        delete[] a[i];
    }
    delete[] a;
}
