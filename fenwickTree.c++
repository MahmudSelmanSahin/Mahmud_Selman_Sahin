#include <iostream>
#include <vector>
using namespace std;

// Fenwick Ağacı (İkili İndeksli Ağaç) Sınıfı
class FenwickTree {
private:
    vector<int> bit; // ağaç dizisi
    int n; // dizinin boyutu

public:
    // n boyutlu bir Fenwick ağacı oluşturuyoruz
    FenwickTree(int size) {
        n = size + 1;
        bit.resize(n, 0); // 1'den başlayan indeks için n+1 boyutunda
    }
    
    // i. indekse val değerini ekleme
    void update(int i, int val) {
        i++; // 1-indeksli yapıya dönüştür
        
        // İlgili tüm üst düğümleri güncelle
        while (i < n) {
            bit[i] += val;
            i += i & -i; // LSB kullanarak sonraki üst düğüme geç
        }
    }
    
    // 0'dan i'ye kadar olan toplam
    int sum(int i) {
        i++; // 1-indeksli yapıya dönüştür
        
        int result = 0;
        while (i > 0) {
            result += bit[i];
            i -= i & -i; // LSB kullanarak bir önceki düğüme geç
        }
        return result;
    }
    
    // [l, r] aralığındaki toplamı bul
    int rangeSum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

int main() {
    // 10 elemanlı bir dizi üzerinde işlem yapacak bir Fenwick ağacı 
    FenwickTree ft(10);
   
    cout << "Dizi oluşturuluyor..." << endl;
    ft.update(0, 3);  // 0. indekse 3 ekle
    ft.update(1, 2);     
    ft.update(2, 5);     
    ft.update(3, 1);     
    ft.update(4, 7);     
    ft.update(5, 4);  
    
    // Toplam değerleri kontrol edelim
    cout << "Toplam [0-2]: " << ft.rangeSum(0, 2) << endl;  // 3 + 2 + 5 = 10 
    cout << "Toplam [1-5]: " << ft.rangeSum(1, 5) << endl;  // 2 + 5 + 1 + 7 + 4 = 19 
    cout << "Toplam [0-5]: " << ft.sum(5) << endl;         // 3 + 2 + 5 + 1 + 7 + 4 = 22 
    
    // Değer güncelleme
    cout << "\nDizi güncelleniyor..." << endl;
    ft.update(3, 8);  // 3. indekse 8 daha ekle  1 + 8 = 9
    
    // Güncellenmiş toplamları kontrol et
    cout << "Güncellenmiş toplam [0-5]: " << ft.sum(5) << endl;  // 3 + 2 + 5 + 9 + 7 + 4 = 30 
    cout << "Güncellenmiş toplam [3-5]: " << ft.rangeSum(3, 5) << endl;  // 9 + 7 + 4 = 20 
    
    return 0;
}
