# Tugas Kecil 1 Strategi Algoritma 

## Daftar Isi 
- [Tugas kecil1 Strategi Algoritma](#tugas-kecil1-straregi-algoritma)
    - [Daftar isi](#daftar-isi)
    - [Breach Protocol Cyberpunk 2077](#breach-protocol-cyberpunk-2077)
    - [Deskripsi Permasalahan](#deskripsi-permasalahan)
    - [Algoritma yang digunakan](#algoritma-yang-digunakan)
    - [Struktur Program](#struktur-program)
    - [Menjalankan Program](#menjalankan-program)

## Breach Protocol Cyberpunk 2077
Made by Indraswara Galih Jayanegara, 13522119, for STIMA *course*

## Deskripsi Permasalahan 
Brach Protocol adalah minigame yang ada di dalam game Cyberpunk 2077 dengan tujuan untuk mencari kombinasi yang paling optimal dari sebuah board game yang merepresentasikan matriks atau array dua dimensi.  

Projek ini membuat suatu algoritma dengan pendekatan *brute force* untuk menyelesaikan Breach Protocol

## Algoritma yang digunakan

- Misalkan ada sequence yang dibentuk dari token unik dan setiap sequence memiliki reward random. 
contoh sequence 
{{AB, CD, EF}, 20}
{{87, G5, J8}, 30} 
{{B8, AB, CD, EF}, 50}
- Pada Matriks game akan ditelusuri semua jalurnya dengan maksimal token yang diambil dari matriks sebanyak buffer yang telah ditentukan yang ada.
- Setiap token yang diambil dari matriks akan langsung di-compare dengan sequence yang memiliki reward. Jika kombinasi dari token ada yang sama dengan Sequence maka total prize akan bertambah sebanyak nilai dari reward sequence tersebut. 
- Setiap kombinasi yang memiliki total reward yang sama, tetapi memiliki langkah yang lebih sedikit, maka kombinasi yang diambil adalah kombinasi yang memiliki langkah yang lebih sedikit sehingga solusinya menjadi lebih optimal

## Struktur Program 

```
| makefile
| README.md
|___
|   bin
|   | app (wsl)
|   | app.exe (windows)
|___
|   doc
|   |--Tucil1_13522119_K1_Indraswara Galih Jayanegara.docx
|   |--Tucil1_13522119_K1_Indraswara Galih Jayanegara.pdf
|   |--Tucil1-2024
|___
|   src
|      |-- main.cpp
|___
|   test
|   |-- data.txt
|   |-- data2.txt
|   |-- data3.txt
|   |-- data4.txt
|   |-- data5.txt
|   |-- data6.txt
|   |-- data7.txt
|   |-- result.txt
|   |-- result2.txt
|   |-- result3.txt
|   |-- result4.txt
|   |-- result5.txt
|   |-- result6.txt
|   |-- result7.txt
|   |-- resultk1.txt
|   |-- resultk2.txt
|   |-- resultk3.txt
|   |-- resultk4.txt
|   |-- resultk5.txt
|   |-- resultk6.txt

```


# Menjalankan Program 
Pastikan pada *wsl* dan *windows* sudah terinstall make
Jika cara dibagian ini tidak berjalan pergi ke section
[Alternatif Menjalankan Program](#alternatif-menjalankan-program)
### Instalasi pada windows 
- install chocolatey pada windows: https://community.chocolatey.org/
- jalankan perintah 
```
choco install make 
```
### Instalasi pada wsl 
- install make pada wsl: https://linuxhint.com/install-make-ubuntu/

## *compile & running*
Untuk menjalankan program, pada *root directory*, jalankan makefile (pada *windows* dan *wsl*)
```
make runs
```
program akan berjalan, mulai dari compile *main.cpp*, lalu menjalankan *app.exe* (pada *windows*) atau *app* (pada *wsl*);


## *compile* 
Untuk compile program saja jalankan perintah 
```
make all
```
Program akan melakukan compiling *main.cpp* menjadi *app.exe* (pada windows) atau *app* (pada wsl) di folder bin

## *run*
Untuk menjalankan program yang sudah di-compile lakukan perintah 
```
make run
```

# Alternatif Menjalankan Program
alternatif menjalankan program pada *root directory*

## *Compile & Run*

### *windows*
jalankan perintah 
```
g++ -std=c++20 -o bin/app src/main.cpp && bin\app
```

### *WSL*
jalankan perintah 
```
g++ -std=c++20 -o ./bin/app ./src/main.cpp && ./bin/app
```

## *Run*
### *Windows*
```
bin\app
```
### *WSL*
```
./bin/app
```
