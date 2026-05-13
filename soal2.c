/** Pemecahan Masalah dengan Pemrograman 2025/2026
 *   Nama (NIM)          : Muhammad Isnan Basya Ramdhani (13224097)
 *   Nama File           : soal2.c
 *   Deskripsi           : Menerima dengan format "R C row1 row2... rowR" di mana R dan C adalah integer dan rowX adalah integer berupa 0 atau 1, menyimpannya dalam dynamic array of Node berukuran R*C, menghitung jumlah kumpulan row yang bernilai 1 sebagai ISLAND dan menghitung jalur terpanjang yang dibentuk oleh beberapa row sebagai LARGEST.
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int x;
    int y;
    int val;
    int visited;
} Node;

int isSafe(Node* G, int r, int c, int rows, int cols){
    int idx = r * cols + c;
    return (r >= 0 && r < rows) && (c >= 0 && c < cols) && (G[idx].val == 1); // Cek kalau r dan c masih di dalam matriks dan val nya bernilai 1
}

void DFS(Node* G, int r, int c, int i, int *area){
    // Array arah bawah, kiri, kanan, atas
    int dirR[] = {-1, 0, 0, 1};
    int dirC[] = {0, -1, 1, 0};

    G[i].visited = 1; // Mark as visited
    (*area)++; // Tambah total area yang dihitung

    for (int k = 0; k < 4; ++k){
        int newY = G[i].y + dirR[k];
        int newX = G[i].x + dirC[k];
        int newIdx = newY * c + newX;
        if ((newY >= 0 && newY < r) && (newX >= 0 && newX < c) && G[newIdx].val == 1 && !G[newIdx].visited){
            DFS(G, r, c, newIdx, area); 
        }
    }
}

void findEVERYTHING(Node* G, int r, int c, int* island, int* largest){ // Cari jumlah pulau dan ukuran terbesar sekaligus
    for (int i = 0; i < r * c; i++){
        G[i].visited = 0; // Reset visited sebelum DFS
    }
    for (int i = 0; i < r * c; i++){
        if (G[i].val == 1 && !G[i].visited){
            int area = 0;
            DFS(G, r, c, i, &area);
            (*island)++; // Tambah jumlah island untuk setiap node awal DFS

            if (area > *largest){
                *largest = area; // Jadikan luas area jadi luas terbesar
            }
        }
    }
}

int main(){
    int R, C;
    int island = 0;
    int largest = 0;
    Node* grid = NULL;
    scanf("%d %d", &R, &C);
    grid = (Node *)realloc(grid, R*C * sizeof(Node));
    for(int i = 0; i < R; i ++){
        int in;
        scanf("%d", &in);
        for(int j = C - 1; j >= 0; j--){ // Ekstrak angka dari integer besar
            int r;
            int jumlah = i * C + j;
            grid[jumlah].x = j;
            grid[jumlah].y = i;
            grid[jumlah].visited = 0;
            r = in % 10;
            grid[jumlah].val = r;
            in /= 10;
        }
    }
    
    findEVERYTHING(grid, R, C, &island, &largest);
    printf("ISLANDS %d\n", island);
    printf("LARGEST %d\n", largest);
    free(grid);
}

/** REFERENSI KODE
 * https://www.geeksforgeeks.org/dsa/find-length-largest-region-boolean-matrix/
 * https://www.geeksforgeeks.org/dsa/find-the-number-of-islands-using-dfs/\
**/