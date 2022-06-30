// BoxesAndPrisoners.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include "bcrypt.h"
#include <vector>

#pragma comment(lib, "Bcrypt")

int genCryptRandom() {
    int randomNumber = 0;
    BCRYPT_ALG_HANDLE Prov;
    int Buffer = 0;
    if (!BCRYPT_SUCCESS(BCryptOpenAlgorithmProvider(&Prov, BCRYPT_RNG_ALGORITHM,NULL, 0))) {
        std::cout << "Error Unbale to Open an Algorithm Provider\n";
    }
    if (!BCRYPT_SUCCESS(BCryptGenRandom(Prov, (PUCHAR)(&Buffer),sizeof(Buffer), 0))) {
        std::cout << "Error Unable to Generate a random number use the Algorithm Provider\n";
    }
    BCryptCloseAlgorithmProvider(Prov, 0);
	return Buffer;
}

int oneToOneHundred(int inputNumber)
{
	return int (std::abs(inputNumber % 100)+1);
}

void fillVectorRandom1to100(std::vector<int> &vector)
{
    for (int i = 100; i >= 1; i--)
    {
        bool valueFilled = false;
        while (!valueFilled) {
            int randomIndex = oneToOneHundred(genCryptRandom()) - 1;
            if (vector[randomIndex] == -1) {
                vector[randomIndex] = i;
                valueFilled = true;
            }
        }
    }
}

bool findBoxLessFifty(std::vector<int> &prisoners, std::vector<int>& boxes)
{
    bool fail = false;
    for (int j : prisoners) {
        if (!fail) {
            int num_searched = 0;
            int search_index = 0;
            search_index = j - 1;
            while (boxes[search_index] != j)
            {
                search_index = boxes[search_index] - 1;
                num_searched++;
            }
            if (num_searched >= 50) {
                fail = true;
            }
        }
    }
    return fail;
}

int main()
{
    int num_fails = 0;
    int num_successes = 0;
    for (int iters = 0; iters < 1000000; iters++) {
        std::vector<int> prisoners(100, -1);
        std::vector<int> boxes(100, -1);
        fillVectorRandom1to100(prisoners);
        fillVectorRandom1to100(boxes);
        bool fail = findBoxLessFifty(prisoners,boxes);
        if (fail)num_fails++;
        else num_successes++;
    }

    std::cout << "our success rate is: " << double((double(num_successes) / double(num_fails + num_successes)) * 100);
}
