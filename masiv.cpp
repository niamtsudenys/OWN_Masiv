#include "masiv.h"

template<class T>
void masiv<T>::OsvobojdenieResursovVsluchaiIscliuceniya()
{
    delete[] mas;
}

template<class T>
masiv<T>::masiv() : Capacity(0), Size(0)
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

template<class T>
masiv<T>::masiv(int Capacity) : Capacity(Capacity), Size(0)
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

template<class T>
masiv<T>::masiv(const std::initializer_list<T>& list) :
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

template<class T>
masiv<T>::masiv(masiv& mas2)
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

template<class T>
masiv<T>::~masiv() { delete[] mas; }

template<class T>
void masiv<T>::print()
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

template<class T>
T* masiv<T>::begin()
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

template<class T>
T* masiv<T>::end()
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

template<class T>
void masiv<T>::push_back(T value)
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

template<class T>
void masiv<T>::push_front(T value)
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

template<class T>
void masiv<T>::insert(int position, T value)
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

template<class T>
void masiv<T>::insert(int position, const std::initializer_list<T>& list)
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

template<class T>
void masiv<T>::insert(int position, T* begin, T* end)
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

template<class T>
void masiv<T>::insert(const std::initializer_list<T>& list)
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

template<class T>
void masiv<T>::clear()
{
    if (Size > 0)
        Size = 0;
}

template<class T>
void masiv<T>::delete_last()
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

template<class T>
void masiv<T>::delete_first()
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

template<class T>
void masiv<T>::delete_elem(int position)
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

template<class T>
void masiv<T>::delete_elem(int pos1, int pos2)
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

template<class T>
bool masiv<T>::empty()
    {
        if (Size)
            return false;
        else
            return true;
    }

template<class T>
int masiv<T>::size() { return Size; }

template<class T>
int masiv<T>::capacity() { return Capacity; }

template<class T>
void masiv<T>::resize()
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

template<class T>
void masiv<T>::resize(int Size)
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

template<class T>
void masiv<T>::resize(int n, T value)
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

template<class T>
void masiv<T>::replacement(int Size, T value)
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

template<class T>
void masiv<T>::swap(masiv<T>& other)
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

template<class T>
T& masiv<T>::operator [] (int index)
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

template<class T>
T& masiv<T>::at(int index)
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

template<class T>
masiv<T>& masiv<T>::operator = (masiv<T>& other)
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

template<class T>
masiv<T>& masiv<T>::operator = (const masiv<T>& other)
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

template<class T>
void masiv<T>::operator = (const std::initializer_list<T>& list)
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

template<class T>
bool masiv<T>::operator == (masiv<T>& mas2)
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

template<class T>
bool masiv<T>::operator != (masiv<T>& mas2)
{
    return !(operator == (mas2));
}

template<class T>
bool masiv<T>::operator > (masiv<T>& mas2)
{
    return Size > mas2.Size;
}

template<class T>
bool masiv<T>::operator >= (masiv<T>& mas2)
{
    return Size >= mas2.Size;
}

template<class T>
bool masiv<T>::operator < (masiv<T>& mas2)
{
    return Size < mas2.Size;
}

template<class T>
bool masiv<T>::operator <= (masiv<T>& mas2)
{
    return Size <= mas2.Size;
}

template<class T>
masiv<T> masiv<T>::operator + (masiv<T>& mas2)
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
