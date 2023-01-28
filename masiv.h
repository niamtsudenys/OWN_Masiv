#pragma once
#include <iostream>

template <class T>
class masiv
{
private:
    int Capacity;
    int Size;

    void OsvobojdenieResursovVsluchaiIscliuceniya()
    {
        delete[] mas;
    }

protected:
    T* mas;

public:

    // consruktor1 po umolchaniiu
    masiv() : Capacity(0), Size(0)
    {
        try
        {
            mas = new T[1]{};
        }
        catch (std::bad_alloc&)
        {
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }
    }

    // constructor2 vydelyaet dinamicheskuiu pamyaty pod masiv razmerom Capacity
    //  i initsializizuem vse elementy 0
    masiv(int Capacity) : Capacity(Capacity), Size(0)
    {
        try
        {
            mas = new T[Capacity]{};
        }
        catch (std::bad_alloc&)
        {
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }
    }

    // construktor3   // initsializatsia cherez initializer_list
    masiv(const std::initializer_list<T>& list) :
        masiv(list.size()) // vyzyvaem constuctor2 // delegirovanie
    {
        // initsializatsiya nashego masiva znacheniyamy iz spisca
        int index = 0;
        for (auto& element : list)
        {
            mas[index] = element;
            ++index;
        }

        Size = list.size();
    }

    // destruktor // osvobojdaem dinamicheskuiu pamyati
    ~masiv() { delete[] mas; }

    // vyvod masiva v konsoly
    void print()
    {
        try
        {
            if (Size <= 0)
                throw Size;
        }
        catch (int)
        {
            // std::cerr << std::endl << "Oshibka vyvoda. V masive net elementov.  print()" << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }

        for (int i = 0; i < Size; ++i)
        {
            std::cout << mas[i] << "\t";
        }

        std::cout << std::endl;
    }

    // iterator ukazyvaet na 1 element masiva
    T* begin()
    {
        try
        {
            if (Size <= 0)
                throw Size;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka iteratora. V masive net elementov. begin()" << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }

        return  &mas[0];
    }

    // iterator ukazyvaet na positsiiu posle poslednego elementa masiva
    T* end()
    {
        try
        {
            if (Size <= 0)
                throw Size;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka iteratora. V masive net elementov. end()" << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }

        return  &mas[Size];
    }

    // dobavlyaem element v konets masiva
    void push_back(T value)
    {
        if (Capacity == 0)
        {
            ++Capacity;

            mas[Size++] = value;
        }
        else
        {
            int copySize = Size;

            if (Size >= Capacity)
                resize(Capacity * 2);

            Size = copySize;

            mas[Size++] = value;
        }
    }

    // dobavlyaem element v nachalo masiva
    void push_front(T value)
    {
        if (Capacity == 0)
            push_back(value);
        else
        {
            int copySize = Size;

            if (Size >= Capacity)
                resize(Capacity * 2);

            Size = copySize + 1;

            for (int i = Size - 1; i >= 0; --i)
            {
                mas[i] = mas[i - 1];
            }

            mas[0] = value;
        }
    }

    // vstavlyaem element na positsiiu kuda ukazivaet iterator position
    void insert(int position, T value)
    {
        try
        {
            if (position < 1 || position > Size)
                throw Size;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka vstavky. Nepravilynye argumenty. insert(position, value)" << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }

        T* temp = nullptr;

        if (Capacity < Size + 1)
        {
            ++Capacity;

            temp = mas;

            try
            {
                mas = new T[Capacity];
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }
        }

        for (int i = 0; i <= Size; ++i)
        {
            if (i < position - 1)
                mas[i] = temp[i];
            else if (i == position - 1)
                mas[position - 1] = value;
            else
                mas[i] = temp[i - 1];
        }

        delete[] temp;

        ++Size;
    }

    // vstavlyaem n elementa c positsii kuda ukazivaet iterator position
    void insert(int position, const std::initializer_list<T>& list)
    {
        try
        {
            if (position < 1 || position > Size)
                throw Size;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka vstavky. Nepravilynye argumenty. insert (position, { value, ... , value })" << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }

        T* temp = nullptr;

        if (Capacity < Size + list.size())
        {
            Capacity = Size + list.size();

            temp = mas;

            try
            {
                mas = new T[Capacity];
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }
        }

        Size += list.size();

        for (int i = 0; i < position - 1; ++i)
            mas[i] = temp[i];

        int index = position - 1;
        for (auto& element : list)
        {
            mas[index] = element;
            ++index;
        }

        for (int i = position - 1 + list.size(); i < Size; ++i)
            mas[i] = temp[i - list.size()];

        delete[] temp;
    }

    // dobavlyaem c mesta position iz drugogo vectora elementy 
    void insert(int position, T* begin, T* end)
    {
        try
        {
            if (position < 1 || position > Size)
                throw Size;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka vstavky. Nepravilynye argumenty. insert(position, mas.begin, mas.end)" << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }

        int copySize = Size;

        if (Size >= Capacity)
            resize(Capacity + end - begin);

        Size = copySize;

        T* temp = mas;

        try
        {
            mas = new T[Capacity]{};
        }
        catch (std::bad_alloc&)
        {
            delete[] temp;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        Size += (end - begin);

        for (int i = 0; i < position - 1; ++i)
            mas[i] = temp[i];

        int index = position - 1;
        for (int* i = begin; i < end; ++i)
        {
            mas[index] = *i;
            ++index;
        }

        for (int i = position - 1 + (end - begin); i < Size; ++i)
            mas[i] = temp[i - (end - begin)];

        delete[] temp;
    }

    // dobaclyaem v konets masiva elementy iz spiska
    void insert(const std::initializer_list<T>& list)
    {
        T* temp = nullptr;

        if (Capacity < Size + list.size())
        {
            Capacity = Size + list.size();

            temp = mas;

            try
            {
                mas = new T[Capacity];
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }
        }

        for (int i = 0; i < Size; ++i)
            mas[i] = temp[i];

        int index = Size;

        for (auto& element : list)
        {
            mas[index] = element;
            ++index;
        }

        delete[] temp;

        Size += list.size();
    }

    // ochistka masiva
    void clear()
    {
        if (Size > 0)
            Size = 0;
    }

    // udalyaem posledniy element
    void delete_last()
    {
        try
        {
            if (Size <= 0)
                throw 1;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka delete_last()." << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        if (Size > 0)
        {
            --Size;
            resize();
        }


    }

    // udalyaem pervyi element
    void delete_first()
    {
        try
        {
            if (Size <= 0)
                throw 1;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka delete_first()." << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }
        if (Size > 0)
        {
            T* temp = mas;

            try
            {
                mas = new T[Capacity]{};
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }

            --Size;

            for (int i = 0; i < Size; ++i)
            {
                mas[i] = temp[i + 1];
            }

            delete[] temp;

            resize();
        }
    }

    // udalyaem 1 element c positsii 
    void delete_elem(int position)
    {
        try
        {
            if (position < 1 || position > Size)
                throw 1;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka pri udaleniya elementa: delete_elem(int)." << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }
        if (Size > 0 && (position > 0 && position <= Size))
        {
            T* temp = mas;

            try
            {
                mas = new T[Capacity]{};
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }

            for (int i = 0; i < position - 1; ++i)
            {
                mas[i] = temp[i];
            }

            for (int i = position - 1; i < Size; ++i)
            {
                mas[i] = temp[i + 1];
            }

            delete[] temp;

            --Size;

            resize();
        }
    }

    // udalyaem elementy c positsii ot pos1 do pos2
    void delete_elem(int pos1, int pos2)
    {
        try
        {
            if (pos1 < 1 || pos2 < 1 || pos1 > pos2 || pos1 > Size || pos2 > Size)
                throw 1;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka pri udaleniya elementov: delete_elem(int, int)." << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        if (Size > 0 && (pos2 > 0 && pos2 <= Size) && pos1 <= pos2)
        {
            T* temp = mas;

            try
            {
                mas = new T[Capacity]{};
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }

            for (int i = 0; i < pos1 - 1; ++i)
                mas[i] = temp[i];

            int index = pos1 - 1;

            for (int i = pos2; i < Size; ++i, ++index)
                mas[index] = temp[i];

            delete[] temp;

            Size -= (pos2 + 1 - pos1);

            resize();
        }
    }

    // proveryayem yesli masiv pustoy
    bool empty()
    {
        if (Size)
            return false;
        else
            return true;
    }

    // vozvrachaet razmer masiva
    int size() { return Size; }

    // vozvrachaet maksimal'nyi razmer masiva
    int capacity() { return Capacity; }

    // esli maximalynyi razmer bolyshe chem v 2 raza chem masiv to umenishaem razmer
    void resize()
    {
        if ((Capacity - Size) > Size)
        {
            Capacity = Size;

            T* temp = mas;

            try
            {
                mas = new T[Capacity]{};
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }

            for (int i = 0; i < Size; ++i)
            {
                mas[i] = temp[i];
            }

            delete[] temp;
        }
    }

    // menyaem razmer masiva
    void resize(int Size)
    {
        try
        {
            if (Size < 0)
                throw 1;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka: resize(Size)." << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        if (this->Size >= Size)
            this->Size = Size;
        else
        {
            this->Capacity = Size;

            T* temp = mas;

            try
            {
                mas = new T[Capacity]{};
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }

            for (int i = 0; i < this->Size; ++i)
            {
                mas[i] = temp[i];
            }

            delete[] temp;
            //this->Size = Size;
        }
    }

    // ostavlyaet v masive n pervyh elementov
    // esly razmer masiva menyshe n, to dobavlyaem nedostoiushie elementy so znacheniem value
    void resize(int n, T value)
    {
        try
        {
            if (n < 1)
                throw 1;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka: resize(n, value)." << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        if (Size >= n)
            Size = n;
        else
        {
            Capacity = n;
            T* temp = mas;

            try
            {
                mas = new T[Capacity];
            }
            catch (std::bad_alloc&)
            {
                delete[] temp;
                OsvobojdenieResursovVsluchaiIscliuceniya();
                throw;
            }

            for (int i = 0; i < Capacity; ++i)
            {
                if (i < Size)
                    mas[i] = temp[i];
                else
                    mas[i] = value;
            }

            Size = n;

            delete[] temp;
        }
    }

    // zamenyayem vse elementy masiva opredelennym naborom
    void replacement(int Size, T value)
    {
        try
        {
            if (Size < 0)
                throw 1;
        }
        catch (int)
        {
            std::cerr << std::endl << "Oshibka argumentov: replacement(Size, value)." << std::endl;
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        if (this->Size >= Size)
            this->Size = Size;
        else
            resize(Size);

        for (int i = 0; i < Size; ++i)
        {
            mas[i] = value;
        }

        resize();
    }

    void swap(masiv& other)
    {
        T* temp = mas;
        int tempSize = Size;
        int tempCapacity = Capacity;

        mas = other.mas;
        Size = other.Size;
        Capacity = other.Capacity;

        other.mas = temp;
        other.Size = tempSize;
        other.Capacity = tempCapacity;
    }

    // vozvrashchayem obychnuyu ssilku na element
    T& operator [] (int index)
    {
        try
        {
            if (index < 0 || index >= Size)
                throw index;

            return mas[index];
        }
        catch (int a)
        {
            std::cerr << "Vy vyshli za pridely masiva: " << a << '\n';
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }
    }

    // vozvrashchayem obychnuyu ssilku na element
    T& at(int index)
    {
        try
        {
            if (index < 0 || index >= Size)
                throw index;

            return mas[index];
        }
        catch (int a)
        {
            std::cerr << "Vy vyshli za pridely masiva: " << a << '\n';
            OsvobojdenieResursovVsluchaiIscliuceniya();
        }
    }

    // operator prisvaevaniya // prisvaivaem soderjimoe odnogo konteynera nashemu
    masiv& operator = (const masiv& other)
    {
        if (this != &other)
        {
            if (Capacity != other.Capacity)
            {
                delete[] mas;

                try
                {
                    mas = new T[other.Capacity];
                }
                catch (std::bad_alloc&)
                {
                    OsvobojdenieResursovVsluchaiIscliuceniya();
                    throw;
                }
            }

            for (int i = 0; i < other.Size; ++i)
                mas[i] = other.mas[i];

            Size = other.Size;
            Capacity = other.Capacity;
        }

        return *this;
    }

    // operator prisvaevaniya // prisvaivaem soderjimoe odnogo konteynera nashemu
    masiv& operator = (masiv& other)
    {
        if (this != &other)
        {
            if (Capacity != other.Capacity)
            {
                delete[] mas;

                try
                {
                    mas = new T[other.Capacity];
                }
                catch (std::bad_alloc&)
                {
                    OsvobojdenieResursovVsluchaiIscliuceniya();
                    throw;
                }
            }

            for (int i = 0; i < other.Size; ++i)
                mas[i] = other.mas[i];

            Size = other.Size;
            Capacity = other.Capacity;
        }

        return *this;
    }

    // operator prisvaevaniya // prisvaivaem nashemu masivu - spisok znacheniy
    void operator = (const std::initializer_list<T>& list)
    {
        Capacity = Size = list.size();

        if (mas != nullptr)
            delete[] mas;

        try
        {
            mas = new T[Capacity];
        }
        catch (std::bad_alloc&)
        {
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        int index = 0;

        for (auto& element : list)
        {
            mas[index] = element;
            ++index;
        }
    }

    // operator sravneniya == 
    // masivy ravny, yesli oni soderzhat odinakovyye elementy na tekh zhe pozitsiyakh
    bool operator == (masiv& mas2)
    {
        bool ravenstvo;

        if (Size != mas2.Size) // esly razmery masivov raznye net smysla proverka na ravenstvo
            return false;
        else
        {
            for (int i = 0; i < Size; ++i)
            {
                if (mas[i] != mas2[i])
                {
                    ravenstvo = 0;
                    break;
                }
                else
                {
                    ravenstvo = 1;
                }
            }
        }

        return ravenstvo;
    }

    // operator sravneniya != 
    // masivy ne ravny, yesli hotyaby odna para elementov na tekh zhe pozitsiyakh ne ravny
    bool operator != (masiv& mas2)
    {
        return !(operator == (mas2));
    }

    // operatory >, >=, <, <=  // sravnivaem tolyko po dline masiva

    bool operator > (masiv& mas2)
    {
        return Size > mas2.Size;
    }

    bool operator >= (masiv& mas2)
    {
        return Size >= mas2.Size;
    }

    bool operator < (masiv& mas2)
    {
        return Size < mas2.Size;
    }

    bool operator <= (masiv& mas2)
    {
        return Size <= mas2.Size;
    }

    // operator + // concotenatsia, soderjimoe mas2 dobavlyaetsya v conets mas
    masiv operator + (masiv& mas2)
    {
        masiv <T> sum(Size + mas2.Size);

        sum.Size = Size + mas2.Size;

        for (int i = 0, j = 0; i < sum.Size; ++i)
        {
            if (i < Size)
                sum.mas[i] = mas[i];
            else
            {
                sum.mas[i] = mas2[j];
                ++j;
            }
        }

        return sum;
    }

    // constructor4 copirovaniya
    masiv(masiv& mas2)
    {
        Size = mas2.Size;
        Capacity = mas2.Capacity;

        try
        {
            mas = new T[Capacity];
        }
        catch (std::bad_alloc&)
        {
            OsvobojdenieResursovVsluchaiIscliuceniya();
            throw;
        }

        for (int i = 0; i < Capacity; ++i)
        {
            mas[i] = mas2[i];
        }
    }
};