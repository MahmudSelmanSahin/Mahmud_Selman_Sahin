# Fenwick Tree (İkili İndeksli Ağaç) Algoritması

## Algoritmanın ne yaptığı

Fenwick Tree (diğer adıyla Binary Indexed Tree), bir dizi elemanı üzerinde iki temel işlemi verimli bir şekilde gerçekleştiren bir veri yapısıdır:

1. **Güncelleme:** Dizinin belirli bir indeksindeki değeri değiştirme
2. **Aralık Sorgusu:** Belirli bir indeks aralığındaki elemanların toplamını hesaplama

Her iki işlem de O(log n) zaman karmaşıklığında gerçekleştirilir. Bu, özellikle büyük veri kümeleri üzerinde çok sayıda güncelleme ve sorgulama işleminin yapıldığı durumlar için klasik dizilere göre önemli bir performans avantajı sağlar.

## Kategori

Fenwick Tree aşağıdaki kategorilerde yer alan bir algoritmadır:

- **Veri Yapısı:** Özel bir ağaç veri yapısıdır
- **Aralık Sorgusu:** Verimli aralık sorgulamaları sağlar
- **Kümülatif Toplam:** Kümülatif toplamları verimli şekilde hesaplar

## Çözüm Yaklaşımı

Fenwick Tree algoritması bir **"Divide and Conquer"** (Böl ve Yönet) yaklaşımıyla çalışır. Algoritmanın çalışma prensibi, her düğümün belirli bir indeks aralığının toplamını tutmasına dayanır. Bu, indekslerin ikili temsilindeki en düşük anlamlı bitin (LSB - Least Significant Bit) akıllıca kullanılmasıyla gerçekleştirilir.

Her indeks, dizinin belirli bir aralığını temsil eder ve bu aralıklar birbirini tamamlayacak şekilde tasarlanmıştır. Bu sayede herhangi bir [0, i] aralığındaki toplam, en fazla log(n) düğümün değerinin toplanmasıyla hesaplanabilir.

## Ne zaman ve neden kullanıldığı

Fenwick Tree özellikle aşağıdaki durumlarda kullanılır:

1. **Dinamik Dizi Toplamları:** Sık güncellenen bir dizi üzerinde toplam sorguları yapılması gerektiğinde
2. **Kümülatif Frekans Tabloları:** Özellikle sıklık dağılımı hesaplamalarında
3. **Aralık Sorguları:** Verimli aralık toplam sorguları gerektiğinde
4. **Yarışma Programlama:** Özellikle sıralama ve indeks hesaplama problemlerinde

Normal diziye göre avantajı, hem güncelleme hem de sorgulama işlemlerini logaritmik zamanda gerçekleştirebilmesidir. Klasik bir dizide, aralık toplamı O(n) zamanda hesaplanırken, Fenwick Tree bunu O(log n) zamanda yapabilir.

## Karmaşıklık analizi (Zaman ve Uzay)

**Zaman Karmaşıklığı:**
- Oluşturma: O(n log n) veya hazır dizi ile O(n)
- Güncelleme (update): O(log n)
- Toplam Sorgulama (sum/rangeSum): O(log n)
- Tek değer okuma (getVal): O(log n)

**Uzay Karmaşıklığı:**
- O(n) - n elemanlı bir dizi için n+1 boyutunda bir dizi kullanılır

Test programında yaptığımız performans karşılaştırması, Fenwick Tree'nin özellikle büyük dizilerde standart yaklaşıma göre çok daha hızlı olduğunu göstermektedir.

## Algoritmanın adımları

1. **Başlangıç:** n boyutunda bir dizi (BIT) oluşturulur, tüm değerler 0 olarak başlatılır
2. **Güncelleme (update):**
   - İndeksi 1-tabanlı indekse dönüştür (i → i+1)
   - i'den başlayarak indeksleri dolaş: i += (i & -i)
   - Her uğranan indekste, değeri ekle

3. **Toplam Sorgulama (sum):**
   - İndeksi 1-tabanlı indekse dönüştür (i → i+1)
   - i'den başlayarak indeksleri dolaş: i -= (i & -i)
   - Her uğranan indeksteki değeri topla

4. **Aralık Toplamı (rangeSum):**
   - sum(r) - sum(l-1) formülünü kullan

Bu adımlarda, (i & -i) işlemi i'nin ikili temsilindeki en düşük anlamlı biti (LSB) bulmak için kullanılır.

## Kullanım yerlerine ait örnekler

1. **Kümülatif İstatistik:** Finansal zaman serilerinde kümülatif toplamların hızlı hesaplanması
2. **Sıralama İndeksleri:** Ters çiftlerin sayısını hesaplama problemlerinde
3. **Veri Madenciliği:** Büyük veri kümeleri üzerinde dinamik frekans hesaplamaları
4. **Yarışma Programlama:** ICPC, TopCoder, CodeForces gibi platformlardaki problemlerin çözümünde

## Algoritmanın avantaj ve dezavantajları

**Avantajlar:**
- Her iki temel işlemi de O(log n) zamanda gerçekleştirir
- Bellek kullanımı verimlidir (sadece O(n))
- Uygulama karmaşıklığı diğer gelişmiş veri yapılarına (segment ağacı gibi) göre daha azdır
- Ek bellek alanı gerektirmeden güncelleme işlemleri yapılabilir

**Dezavantajlar:**
- Sadece toplama gibi işlevleri verimli şekilde destekler, minimum, maksimum gibi işlevler için uygun değildir
- Segment Tree'ye göre daha az esnek bir yapıdır
- İndis hesaplamasında bit işlemleri kullanılır, bu nedenle anlaşılması daha zor olabilir
- Dinamik boyutlandırma desteklenmez, başlangıçta sabit boyut belirlenmesi gerekir
