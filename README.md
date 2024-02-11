# Tugas Kecil 1 Strategi Algoritma 

## Daftar Isi 
- [Tugas kecil1 Strategi Algoritma] (#tugas-kecil1-straregi-algoritma)
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

* pemain memasukkan input dari keyboard atau file 
* melakukan pencarian kombinasi token pada matriks dengan maksimal token sebanyak buffer yang telah ditentukan 
* pada setiap kombinasi token akan dicari kombinasi yang sesuai dengan sequence
* Jika pada kombinasi token ditemukan kombinasi yang sama persis dengan sequence maka player akan mendapatkan reward sebanyak point yang merepresentasikan sequence tersebut

## Struktur Program 

```
| makefile
| README.md
|___
|   bin
| 
|___
|   doc
|
|
|___
|   src
|      |-- main.cpp
|___
|   test
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
## *windows*
jalankan perintah 
```
g++ -std=c++20 -o bin/app src/main.cpp && bin\app
```

## *WSL*
jalankan perintah 
```
g++ -std=c++20 -o ./bin/app ./src/main.cpp && ./bin/app
```
