#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;

// Fenwick Tree testleri için fenwickTree.c++ header olarak dahil edilsin
#include "fenwickTree.c++"

// Doğrudan toplam hesaplama (referans için)
int directSum(vector<int>& arr, int left, int right) {
    int sum = 0;
    for (int i = left; i <= right; i++) {
        sum += arr[i];
    }
    return sum;
}

// Test 1: Temel işlevsellik testi
void testBasicFunctionality() {
    cout << "\n=== Test 1: Temel İşlevsellik Testi ===\n";
    
    // Fenwick ağacını oluştur
    FenwickTree ft(10);
    
    // Bir test dizisi de oluştur (karşılaştırma için)
    vector<int> testArray(10, 0);
    
    // Değerleri ekle ve karşılaştır
    ft.update(0, 3);  testArray[0] += 3;
    ft.update(1, 2);  testArray[1] += 2;
    ft.update(2, 5);  testArray[2] += 5;
    ft.update(3, 1);  testArray[3] += 1;
    ft.update(4, 7);  testArray[4] += 7;
    ft.update(5, 4);  testArray[5] += 4;
    
    // Test: Toplam sorgulama
    cout << "- Toplam sorgulama testi: ";
    bool sumTestPassed = true;
    
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            int expected = directSum(testArray, i, j);
            int result = ft.rangeSum(i, j);
            
            if (expected != result) {
                sumTestPassed = false;
                cout << "HATA! [" << i << ", " << j << "] aralığında: "
                     << "Beklenen: " << expected << ", Alınan: " << result << endl;
            }
        }
    }
    
    if (sumTestPassed) {
        cout << "BAŞARILI!\n";
    }
    
    // Test: GetVal ve SetValue
    cout << "- GetVal ve SetValue testi: ";
    bool getSetTestPassed = true;
    
    for (int i = 0; i < 10; i++) {
        int val = ft.getVal(i);
        if (val != testArray[i]) {
            getSetTestPassed = false;
            cout << "HATA! getVal(" << i << "): "
                 << "Beklenen: " << testArray[i] << ", Alınan: " << val << endl;
        }
        
        // Değeri değiştir
        ft.setValue(i, i * 2);
        testArray[i] = i * 2;
        
        val = ft.getVal(i);
        if (val != testArray[i]) {
            getSetTestPassed = false;
            cout << "HATA! setValue(" << i << ", " << i*2 << ") sonrası: "
                 << "Beklenen: " << testArray[i] << ", Alınan: " << val << endl;
        }
    }
    
    if (getSetTestPassed) {
        cout << "BAŞARILI!\n";
    }
}

// Test 2: Rastgele veri testi
void testRandomData() {
    cout << "\n=== Test 2: Rastgele Veri Testi ===\n";
    const int SIZE = 1000;
    const int TEST_COUNT = 1000;
    const int MAX_VAL = 100;
    
    // Rastgele sayı üreteci
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distVal(0, MAX_VAL);
    uniform_int_distribution<> distIndex(0, SIZE-1);
    
    // Fenwick ağacını oluştur
    FenwickTree ft(SIZE);
    
    // Referans dizi
    vector<int> reference(SIZE, 0);
    
    // Rastgele değerler ekle
    for (int i = 0; i < SIZE; i++) {
        int val = distVal(gen);
        ft.update(i, val);
        reference[i] = val;
    }
    
    // Rastgele aralıklarda toplam sorgula
    cout << "- Rastgele aralık toplamı testi: ";
    bool randomTestPassed = true;
    
    for (int t = 0; t < TEST_COUNT; t++) {
        int left = distIndex(gen);
        int right = distIndex(gen);
        if (left > right) swap(left, right);
        
        int expected = directSum(reference, left, right);
        int result = ft.rangeSum(left, right);
        
        if (expected != result) {
            randomTestPassed = false;
            cout << "HATA! [" << left << ", " << right << "] aralığında: "
                 << "Beklenen: " << expected << ", Alınan: " << result << endl;
            break;
        }
    }
    
    if (randomTestPassed) {
        cout << "BAŞARILI!\n";
    }
}

// Test 3: Performans testi
void testPerformance() {
    cout << "\n=== Test 3: Performans Testi ===\n";
    const int SIZE = 100000;
    const int OPERATIONS = 10000;
    
    // Rastgele sayı üreteci
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distVal(0, 100);
    uniform_int_distribution<> distIndex(0, SIZE-1);
    
    // Vektör ve Fenwick ağacı oluştur
    vector<int> arr(SIZE, 0);
    FenwickTree ft(SIZE);
    
    // Rastgele değerler ekle
    for (int i = 0; i < SIZE; i++) {
        int val = distVal(gen);
        arr[i] = val;
        ft.update(i, val);
    }
    
    cout << "- Fenwick Tree ile toplam hesaplama zamanı: ";
    auto start1 = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < OPERATIONS; i++) {
        int left = distIndex(gen);
        int right = distIndex(gen);
        if (left > right) swap(left, right);
        
        ft.rangeSum(left, right);
    }
    
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
    
    cout << duration1.count() << " mikrosaniye\n";
    
    cout << "- Doğrudan toplam hesaplama zamanı: ";
    auto start2 = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < OPERATIONS; i++) {
        int left = distIndex(gen);
        int right = distIndex(gen);
        if (left > right) swap(left, right);
        
        directSum(arr, left, right);
    }
    
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
    
    cout << duration2.count() << " mikrosaniye\n";
    
    cout << "- Hızlanma oranı: " << (double)duration2.count() / duration1.count() << "x\n";
}

int main() {
    cout << "=== Fenwick Tree (İkili İndeksli Ağaç) Test Programı ===\n";
    
    // Test 1: Temel işlevsellik
    testBasicFunctionality();
    
    // Test 2: Rastgele veri
    testRandomData();
    
    // Test 3: Performans
    testPerformance();
    
    cout << "\nTüm testler tamamlandı!\n";
    
    return 0;
} 