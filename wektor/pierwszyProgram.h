#pragma once
#include <iostream>
#include <random>

class Wektor
{
    int maxSize; // maksymalna dlugosc wektora
    int* vector; // referencja do wektora
    int currentSize; // aktualna dlugosc wektora
public:
    Wektor(int maxSize_);
    // TODO Trzeba zaimplementowac. Patrz cwiczenie 2a.
    Wektor(const Wektor& wektor);
    ~Wektor();
    // TODO Trzeba zaimplementowac. Patrz cwiczenie 2a.
    Wektor& operator=(const Wektor& wektor);

    void moreThenMaxSize(int newSize);

    void setVector(int vector[], int rozmiar);
    void readVector(int nrOfIntegers);
    void randVector(int nrOfIntegers, int min, int max);

    void insert(int position, int value);
    int removeFirst(int value);
    int removeAll(int value);
    int getMin();
    int getMax();

    bool isNonDecreasing();
    bool isNonIncreasing();
    bool isConstant();

    int hornerPolynomial(int x);

    void removeDuplicatesOn3();
    void removeDuplicatesOn2();

    void longestNonDecreasingSubarray();

    friend std::ostream& operator<<(std::ostream&, const Wektor&);
};

Wektor menu();