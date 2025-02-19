# README

## Deskripsi
Kode ini digunakan untuk memodifikasi registry Windows agar dapat menjalankan sebuah file executable (EXE) dengan hak administrator melalui eksploitasi mekanisme "fodhelper.exe". Selain itu, program ini juga dapat menghentikan proses EXE yang sedang berjalan sebelum menjalankannya kembali.

## Cara Kerja
1. Program menerima path dari executable yang akan dijalankan melalui argumen `--exe-path`.
2. Program menambahkan entri registry di `HKEY_CURRENT_USER\Software\Classes\ms-settings\Shell\Open\command` dengan path executable yang diberikan.
3. Program menambahkan nilai kosong ke `DelegateExecute` dalam registry.
4. Program mencari dan menghentikan proses executable jika sedang berjalan.
5. Program menjalankan `fodhelper.exe` dari `C:\Windows\System32\` untuk menjalankan executable dengan hak administrator.

## Cara Menggunakan
### Kompilasi
Gunakan MinGW atau Microsoft Visual Studio untuk mengompilasi kode ini:

#### Dengan MinGW:
```sh
x86_64-w64-mingw32-g++ -O2 PrivEscalate.c -o PrivEscalate.exe -I/usr/share/mingw-w64/include/ -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -fpermissive -lurlmon
```

### Eksekusi
Jalankan program dengan perintah berikut:
```sh
PrivEscalate.exe --exe-path "C:\Path\To\Your\Executable.exe"
```

Gantilah `C:\Path\To\Your\Executable.exe` dengan path yang sesuai.

## Disclaimer
Kode ini hanya untuk tujuan edukasi dan pengujian keamanan sistem pribadi. Penyalahgunaan kode ini untuk tindakan yang tidak sah adalah ilegal dan tidak dianjurkan. Gunakan dengan penuh tanggung jawab.

