#include "pierwszyProgram.h"

int main(int argc, char* argv[])
{
    Wektor wektor{ 10 };
    wektor = menu();
    std::cout << wektor;

    return 0;
}

std::ostream& operator<<(std::ostream& wyjscie, const Wektor& wektor)
{
    wyjscie << "Liczba elementow = " << wektor.currentSize << " ";
    wyjscie << "Zawartosc wektora [ ";
    for (size_t i = 0; i < wektor.currentSize; i++)
    {
        wyjscie << wektor.vector[ i ] << " ";
        if ((i + 1) % 10 == 0)
        {
            wyjscie << std::endl;
        }
    }
    wyjscie << "]" << std::endl;
    return wyjscie;
}

Wektor::Wektor(int maxSize_)
{
    currentSize = 0;
    maxSize = maxSize_;
    vector = new int[ maxSize ];
}

Wektor::Wektor(const Wektor& wektor)
{
    maxSize = wektor.maxSize;
    currentSize = wektor.currentSize;
    vector = new int[ maxSize ];
    std::copy(wektor.vector, wektor.vector + currentSize, vector);
}

Wektor::~Wektor()
{
    delete[] vector;
}

Wektor& Wektor::operator=(const Wektor& wektor)
{
    if (this != &wektor)
    {
        delete[] vector;
        maxSize = wektor.maxSize;
        currentSize = wektor.currentSize;
        vector = new int[ maxSize ];
        std::copy(wektor.vector, wektor.vector + currentSize, vector);
    }
    return *this;
}

void Wektor::moreThenMaxSize(int newSize)
{
    delete[] this->vector;
    this->vector = new int[ newSize ];
    maxSize = newSize;
}

void Wektor::setVector(int vector[], int vecSize)
{
    if (maxSize < vecSize)
    {
        moreThenMaxSize(vecSize);
    }
    std::copy(vector, vector + vecSize, this->vector);
    currentSize = vecSize;
}

void Wektor::readVector(int nrOfIntegers)
{
    if (maxSize < nrOfIntegers)
    {
        moreThenMaxSize(nrOfIntegers);
    }
    char znak;
    for (size_t i = 0; i < nrOfIntegers; ) {
        if (scanf("%d", &vector[ i ]))
        {
            ++i;
        }
        else
        {
            std::cin >> znak;
        }
    }
    currentSize = nrOfIntegers;
}

void Wektor::randVector(int nrOfIntegers, int min, int max)
{
    if (maxSize < nrOfIntegers)
    {
        moreThenMaxSize(nrOfIntegers);
    }
    std::cout << "Losowanie " << nrOfIntegers << " liczb z przedzialu [" << min << "," << max << "]" << std::endl;
    std::cout << "Wylosowane liczby: ";
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    for (size_t i = 0; i < nrOfIntegers; i++)
    {
        vector[ i ] = dist(engine);
        std::cout << vector[ i ] << " ";
    }
    std::cout << std::endl;
    currentSize = nrOfIntegers;
}

void Wektor::insert(int position, int value)
{
    if (position < 0 || position > currentSize)
    {
        std::cout << "Błęd: pozycja spoza zakresu!" << std::endl;
        return;
    }

    if (currentSize >= maxSize)
    {
        int newSize = maxSize + (maxSize * 50 / 100);
        if (newSize == maxSize) newSize++;

        int* newVector = new int[ newSize ];
        std::copy(vector, vector + currentSize, newVector);

        delete[] vector;
        vector = newVector;
        maxSize = newSize;
    }

    for (int i = currentSize; i > position; i--)
    {
        vector[ i ] = vector[ i - 1 ];
    }

    vector[ position ] = value;
    currentSize++;
}

int Wektor::removeFirst(int value)
{
    for (int i = 0; i < currentSize; i++)
    {
        if (vector[ i ] == value)
        {
            for (int j = i; j < currentSize - 1; j++)
            {
                vector[ j ] = vector[ j + 1 ];
            }
            currentSize--;
            return i;
        }
    }
    return -1;
}

int Wektor::removeAll(int value)
{
    int writeIndex = 0;
    int initialSize = currentSize;

    for (int readIndex = 0; readIndex < initialSize; readIndex++)
    {
        if (vector[ readIndex ] != value)
        {
            vector[ writeIndex ] = vector[ readIndex ];
            writeIndex++;
        }
    }

    int removedCount = currentSize - writeIndex;
    currentSize = writeIndex;

    return removedCount;
}

bool Wektor::isNonDecreasing()
{
    for (int i = 0; i < currentSize - 1; i++)
    {
        if (vector[ i ] > vector[ i + 1 ])
            return false;
    }
    return true;
}

bool Wektor::isNonIncreasing()
{
    for (int i = 0; i < currentSize - 1; i++)
    {
        if (vector[ i ] < vector[ i + 1 ])
            return false;
    }
    return true;
}

bool Wektor::isConstant()
{
    if (currentSize == 0) return true;
    for (int i = 1; i < currentSize; i++)
    {
        if (vector[ i ] != vector[ 0 ])
            return false;
    }
    return true;
}

int Wektor::getMin()
{
    if (currentSize == 0)
    {
        std::cout << "Błąd: wektor jest pusty!" << std::endl;
        return 0;
    }
    int minVal = vector[ 0 ];
    for (int i = 0; i < currentSize; i++)
    {
        if (vector[ i ] < minVal)
            minVal = vector[ i ];
    }
    return minVal;
}

int Wektor::getMax()
{
    if (currentSize == 0)
    {
        std::cout << "Błąd: wektor jest pusty!" << std::endl;
        return 0;
    }
    int maxVal = vector[ 0 ];
    for (int i = 0; i < currentSize; i++)
    {
        if (vector[ i ] > maxVal)
            maxVal = vector[ i ];
    }
    return maxVal;
}

int Wektor::hornerPolynomial(int x)
{
    if (currentSize == 0)
        return 0;

    int result = vector[ currentSize - 1 ];
    for (int i = currentSize - 2; i >= 0; i--)
    {
        result = result * x + vector[ i ];
    }
    return result;
}

void Wektor::removeDuplicatesOn3()
{
    for (int i = 0; i < currentSize; i++)
    {
        for (int j = i + 1; j < currentSize; j++)
        {
            if (vector[ i ] == vector[ j ])
            {
                for (int k = j; k < currentSize - 1; k++)
                {
                    vector[ k ] = vector[ k + 1 ];
                }
                currentSize--;
                j--;
            }
        }
    }
}

void Wektor::removeDuplicatesOn2()
{
    if (currentSize <= 1) return;

    int newSize = 1;

    for (int i = 1; i < currentSize; i++)
    {
        bool isDuplicate = false;

        for (int j = 0; j < newSize; j++)
        {
            if (vector[ i ] == vector[ j ])
            {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate)
        {
            vector[ newSize ] = vector[ i ];
            newSize++;
        }
    }

    currentSize = newSize;
}

void Wektor::longestNonDecreasingSubarray()
{
    if (currentSize == 0)
    {
        std::cout << "Wektor jest pusty!" << std::endl;
        return;
    }

    int maxStart = 0, maxEnd = 0, maxLength = 1;
    int currentStart = 0, currentLength = 1;

    for (int i = 1; i < currentSize; i++)
    {
        if (vector[ i ] >= vector[ i - 1 ])
        {
            currentLength++;
        }
        else
        {
            if (currentLength > maxLength)
            {
                maxLength = currentLength;
                maxStart = currentStart;
                maxEnd = i - 1;
            }
            currentStart = i;
            currentLength = 1;
        }
    }

    if (currentLength >= maxLength)
    {
        maxLength = currentLength;
        maxStart = currentStart;
        maxEnd = currentSize - 1;
    }

    std::cout << "Najdłuższa podtablica niemalejąca (długość " << maxLength << "): [ ";
    for (int i = maxStart; i <= maxEnd; i++)
    {
        std::cout << vector[ i ] << " ";
    }
    std::cout << "]" << std::endl;
}

Wektor menu()
{
    int predefArr[] = { 2, -6, 2, 1 };
    size_t rozmiar = 0;
    for (int e : predefArr) ++rozmiar;

    int vectorSize;
    int nrOfIntegers;
    std::cout << "Podaj rozmiar wektora: ";
    std::cin >> vectorSize;
    std::cout << "Podaj liczbe elementow: ";
    std::cin >> nrOfIntegers;
    Wektor wektor{ vectorSize };
    int min;
    int max;

    int choice = 0;
    while (true)
    {
        std::cout << "\n=== MENU ===" << std::endl;
        std::cout << "1. Czytanie z klawiatury" << std::endl;
        std::cout << "2. Losowanie liczb" << std::endl;
        std::cout << "3. Tablica predefiniowana" << std::endl;
        std::cout << "4. Wstawić element (insert)" << std::endl;
        std::cout << "5. Usunąć pierwsze wystąpienie (removeFirst)" << std::endl;
        std::cout << "6. Usunąć wszystkie wystąpienia (removeAll)" << std::endl;
        std::cout << "7. Znaleźć min i max" << std::endl;
        std::cout << "8. Sprawdzić porządek (niemalejące/nierosnące/stałe)" << std::endl;
        std::cout << "9. Obliczyć wielomian Hornera" << std::endl;
        std::cout << "10. Usunąć duplikaty O(n³)" << std::endl;
        std::cout << "11. Usunąć duplikaty O(n²)" << std::endl;
        std::cout << "12. Znaleźć najdłuższą podtablicę niemalejącą" << std::endl;
        std::cout << "0. Koniec" << std::endl;
        std::cout << "Wybór: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Czytanie " << nrOfIntegers << " liczb integer." << std::endl;
            wektor.readVector(nrOfIntegers);
            std::cout << wektor;
            break;
        case 2:
            std::cout << "Losowanie " << nrOfIntegers << " liczb integer." << std::endl;
            std::cout << "Podaj minimum: ";
            std::cin >> min;
            std::cout << "Podaj maksimum: ";
            std::cin >> max;
            if (max < min) max = min;
            wektor.randVector(nrOfIntegers, min, max);
            std::cout << wektor;
            break;
        case 3:
            wektor.setVector(predefArr, rozmiar);
            std::cout << wektor;
            break;
        case 4: {
            int pos, val;
            std::cout << "Pozycja: ";
            std::cin >> pos;
            std::cout << "Wartość: ";
            std::cin >> val;
            wektor.insert(pos, val);
            std::cout << wektor;
            break;
        }
        case 5: {
            int val;
            std::cout << "Wartość do usunięcia: ";
            std::cin >> val;
            int pos = wektor.removeFirst(val);
            if (pos >= 0)
                std::cout << "Usunięto na pozycji: " << pos << std::endl;
            else
                std::cout << "Nie znaleziono!" << std::endl;
            std::cout << wektor;
            break;
        }
        case 6: {
            int val;
            std::cout << "Wartość do usunięcia: ";
            std::cin >> val;
            int count = wektor.removeAll(val);
            std::cout << "Usunięto: " << count << " elementów" << std::endl;
            std::cout << wektor;
            break;
        }
        case 7: {
            std::cout << "Min: " << wektor.getMin() << std::endl;
            std::cout << "Max: " << wektor.getMax() << std::endl;
            break;
        }
        case 8: {
            std::cout << "Niemalejące: " << (wektor.isNonDecreasing() ? "TAK" : "NIE") << std::endl;
            std::cout << "Nierosnące: " << (wektor.isNonIncreasing() ? "TAK" : "NIE") << std::endl;
            std::cout << "Stałe: " << (wektor.isConstant() ? "TAK" : "NIE") << std::endl;
            break;
        }
        case 9: {
            int x;
            std::cout << "Wartość x: ";
            std::cin >> x;
            int result = wektor.hornerPolynomial(x);
            std::cout << "Wynik: " << result << std::endl;
            break;
        }
        case 10: {
            Wektor kopiaD = wektor;
            std::cout << "Przed usunięciem duplikatów:" << std::endl;
            std::cout << kopiaD;
            kopiaD.removeDuplicatesOn3();
            std::cout << "Po usunięciu duplikatów O(n³):" << std::endl;
            std::cout << kopiaD;
            break;
        }
        case 11: {
            Wektor kopiaD = wektor;
            std::cout << "Przed usunięciem duplikatów:" << std::endl;
            std::cout << kopiaD;
            kopiaD.removeDuplicatesOn2();
            std::cout << "Po usunięciu duplikatów O(n²):" << std::endl;
            std::cout << kopiaD;
            break;
        }
        case 12: {
            wektor.longestNonDecreasingSubarray();
            break;
        }
        case 0:
            return wektor;
        default:
            std::cout << "Nieznany wybór!" << std::endl;
        }
    }

    return wektor;
}