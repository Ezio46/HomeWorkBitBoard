#include <iostream>
#include <fstream>
using  namespace std;

int popcnt1(unsigned long long mask)
{
    int cnt = 0;
    while (mask > 0)
    {
        cnt += (int)(mask & 1);
        mask >>= 1;
    }
    return cnt;

}

int popcnt2(unsigned long long mask)
{
    int cnt = 0;
    while (mask > 0)
    {
        cnt ++;
        mask &= mask - 1;
    }
    return cnt;

}

void InitBits(int*& bits)
{
    bits = new int[256];
    for (unsigned long long j = 0; j < 256; j++)
    {
        bits[j] = popcnt2(j);
    }
}

int popcnt3(unsigned long long mask)
{
    int* bits = nullptr;
    InitBits(bits);
    int cnt = 0;
    while (mask > 0)
    {
        cnt += bits[mask & 255];
        mask >>= 8;
    }
    return cnt;

}



unsigned long long BitKing(int cell)
{
    unsigned long long K = 1ULL << cell;

    unsigned long long Ka = K & 0xfefefefefefefefeULL;
    unsigned long long Kh = K & 0x7f7f7f7f7f7f7f7fULL;

    unsigned long long M = (Ka << 7) | (K << 8) | (Kh << 9)
                           |  (Ka >> 1) |            (Kh << 1)
                           |  (Ka >> 9) | (K >> 8) | (Kh >> 7);
    return M;
}

unsigned long long BitKnight(int cell)
{
    unsigned long long K = 1ULL << cell;
    unsigned long long K1 = K & 0xfefefefefefefefeULL; // a
    unsigned long long K2 = K & 0xfcfcfcfcfcfcfcfcULL; // a,b
    unsigned long long K3 = K & 0x3f3f3f3f3f3f3f3fULL; // g,h
    unsigned long long K4 = K & 0x7f7f7f7f7f7f7f7fULL; // h

    unsigned long long M = (K1 << 15) | (K1 >> 17) | (K2 << 6)
            | (K2 >> 10) | (K3 << 10) | (K3 >> 6)
            | (K4 << 17) | (K4 >> 15);

    return M;
}


unsigned long long BitRook(int cell)
{
    unsigned long long K_hor = 0xffULL;
    unsigned long long K_vert = 0x0101010101010101ULL;

    unsigned long long M = (K_hor << ((cell / 8) * 8)) ^ (K_vert << (cell % 8));

    return M;
}


unsigned long long BitBishop(int cell) {

    unsigned long long M;
    unsigned long long K = 1ULL << cell;

    unsigned long long Ka = 0xfefefefefefefefeULL;
    unsigned long long Kh = 0x7f7f7f7f7f7f7f7fULL;

    // Вверх-вправо
    for (int i = 0; i < 7; i++) {
        K <<= 9;
        K &= Ka;
        M |= K;
    }

    // Возвращение слона на начальную позицию
    K = 1ULL << cell;

    // Вверх-влево
    for (int i = 0; i < 7; i++) {
        K <<= 7;
        K &= Kh;
        M |= K;
    }

    K = 1ULL << cell;

    // Вниз-вправо
    for (int i = 0; i < 7; i++) {
        K >>= 7;
        K &= Ka;
        M |= K;
    }

    K = 1ULL << cell;

    // Вниз-влево
    for (int i = 0; i < 7; i++) {
        K >>= 9;
        K &= Kh;
        M |= K;
    }

    return M;
}


unsigned long long BitQueen(int cell)
{
    unsigned long long K = 1ULL << cell;

    unsigned long long M1 = BitBishop(cell);
    unsigned long long M2 = BitRook(cell);

    unsigned long long M = M1 | M2;

    return M;
}

int main() {

    for (int fileIndex = 0; fileIndex < 10; ++fileIndex) {
        string inputFile = "C:/Users/igore/Desktop/0.BITS/5.Bitboard_Queen/test." + to_string(fileIndex) + ".in";
        string outputFile = "C:/Users/igore/Desktop/0.BITS/5.Bitboard_Queen/test." + to_string(fileIndex) + ".out";

        ifstream input(inputFile);
        ifstream output(outputFile);

        int cell;
        input >> cell;

        unsigned long long M = BitQueen(cell);

        unsigned long long M_out;
        int cnt;
        output >> cnt;
        output >> M_out;

        if ((popcnt3(M) == cnt) && (M == M_out))
        {
            cout << cell << " Succes" << endl;
            cout << popcnt3(M) << endl;
            cout << M << endl;
        }
        else
        {
            cout << cell << " Lose" << endl;
            cout << popcnt3(M) << endl;
            cout << M << endl;
        }

        input.close();
    }

    return 0;
}
