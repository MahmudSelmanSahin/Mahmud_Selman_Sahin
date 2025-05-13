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
    
    // Varolan bir diziyi kullanarak Fenwick ağacı oluşturur
    FenwickTree(vector<int>& arr) {
        n = arr.size() + 1;
        bit.resize(n, 0);
        
        // Diziyi ağaca dönüştür
        for (int i = 0; i < arr.size(); i++) {
            update(i, arr[i]);
        }
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
    
    // i. indeksteki değeri doğrudan güncelle
    void setValue(int i, int val) {
        int currVal = getVal(i);
        update(i, val - currVal); // Mevcut değeri çıkar, yeni değeri ekle
    }
    
    // i. indeksin gerçek değerini al (tekil değer, toplam değil)
    int getVal(int i) {
        return rangeSum(i, i);
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
    
    // Fenwick ağacının içeriğini yazdırma
    void printTree() {
        cout << "Fenwick Ağacı içeriği:\n";
        cout << "İndeks -> Değer\n";
        for (int i = 0; i < n-1; i++) {
            cout << i << " -> " << getVal(i) << endl;
        }
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
    
    // Tek değerli güncelleme
    cout << "\nSetValue ile doğrudan değer atama:" << endl;
    ft.setValue(2, 10);  // 2. indeksi 5'ten 10'a değiştir
    cout << "2. indeksin yeni değeri: " << ft.getVal(2) << endl;
    cout << "Toplam [0-5]: " << ft.sum(5) << endl;  // 3 + 2 + 10 + 9 + 7 + 4 = 35
    
    // Ağaç içeriğini yazdır
    cout << "\nAğaç içeriği:" << endl;
    ft.printTree();
    
    // Hazır diziden Fenwick ağacı oluşturma
    cout << "\nYeni dizi ile Fenwick ağacı oluşturma:" << endl;
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    FenwickTree ft2(arr);
    cout << "Yeni ağaç toplam [0-5]: " << ft2.sum(5) << endl;  // 1 + 3 + 5 + 7 + 9 + 11 = 36
    
    return 0;
}
