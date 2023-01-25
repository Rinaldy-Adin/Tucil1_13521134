# Tugas Kecil 1 IF2211 Strategi Algoritma 2022/2023

Nama: Rinaldy Adin\
Kelas: K2\
NIM: 13521134

## Make It 24

Permainan kartu 24 adalah permainan kartu aritmatika dengan tujuan mencari cara untuk mengubah 4 buah angka random sehingga mendapatkan hasil akhir sejumlah 24. Pengguna akan diberi pilihan untuk memilih kartu sendiri atau mendapat pilihan kartu secara acak. Program akan menampilkan persamaan dengan hasil akhir 24 yang menggunakan angka pada kartu yang dipilih.

## Requirement Program

-   C++ compiler (eg. g++)
-   Makefile (Optional for windows)

## Cara Kompilasi dan Menjalankan Program

1. Pada directory utama, ketik command `make` untuk mengcompile semua file yang ada. ([Pengguna windows perlu install make terlebih dahulu](https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows))

    ```
    make
    ```

    1. Apabila makefile tidak berfungsi compile program dengan command dibawah

    ```
    (powershell)
    g++ .\src\cliui.cpp .\src\evaluate_exp.cpp .\src\generate_exp.cpp .\src\generate_perms.cpp .\src\main.cpp .\src\cliui.h .\src\evaluate_exp.h .\src\generate_exp.h .\src\generate_perms.h -o .\bin\main.exe

    (linux)
    g++ ./src/cliui.cpp ./src/evaluate_exp.cpp ./src/generate_exp.cpp ./src/generate_perms.cpp ./src/main.cpp ./src/cliui.h ./src/evaluate_exp.h ./src/generate_exp.h ./src/generate_perms.h -o ./bin/main.exe
    ```

2. Ketik `.\bin\main.exe` (powershell) untuk menjalankan program.

    ```
    (powershell)
    .\bin\main.exe

    (linux)
    ./bin/main.exe
    ```

## Struktur Program

```
│   makefile
│   README.md
│
├───bin
│       main.exe
│
├───doc
│       Tucil1_K2_13521134_Rinaldy Adin.docx
│       Tucil1_K2_13521134_Rinaldy Adin.pdf
│
├───src
│       cliui.cpp
│       cliui.h
│       evaluate_exp.cpp
│       evaluate_exp.h
│       generate_exp.cpp
│       generate_exp.h
│       generate_perms.cpp
│       generate_perms.h
│       main.cpp
│
└───test
        test1.txt
        test2.txt
        test3.txt
        test4.txt
        test5.txt
        test6.txt
```
