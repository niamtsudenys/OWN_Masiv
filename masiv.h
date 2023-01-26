#pragma once
#include <iostream>

template <class T>
class masiv
{
private:
    int Capacity;
    int Size;

    void OsvobojdenieResursovVsluchaiIscliuceniya();

protected:
    T* mas;

public:

    // consruktor1 po umolchaniiu
    masiv();

    // constructor2 vydelyaet dinamicheskuiu pamyaty pod masiv razmerom Capacity
    //  i initsializizuem vse elementy 0
    masiv(int Capacity);

    // construktor3   // initsializatsia cherez initializer_list
    masiv(const std::initializer_list<T>& list);

    // constructor4 copirovaniya
    masiv(masiv<T>& mas2);

    // destruktor // osvobojdaem dinamicheskuiu pamyati
    ~masiv();

    // vyvod masiva v konsoly
    void print();

    // iterator ukazyvaet na 1 element masiva
    T* begin();

    // iterator ukazyvaet na positsiiu posle poslednego elementa masiva
    T* end();

    // dobavlyaem element v konets masiva
    void push_back(T value);

    // dobavlyaem element v nachalo masiva
    void push_front(T value);

    // vstavlyaem element na positsiiu kuda ukazivaet iterator position
    void insert(int position, T value);

    // vstavlyaem n elementa c positsii kuda ukazivaet iterator position
    void insert(int position, const std::initializer_list<T>& list);

    // dobavlyaem c mesta position iz drugogo vectora elementy 
    void insert(int position, T* begin, T* end);

    // dobaclyaem v konets masiva elementy iz spiska
    void insert(const std::initializer_list<T>& list);

    // ochistka masiva
    void clear();

    // udalyaem posledniy element
    void delete_last();

    // udalyaem pervyi element
    void delete_first();

    // udalyaem 1 element c positsii 
    void delete_elem(int position);

    // udalyaem elementy c positsii ot pos1 do pos2
    void delete_elem(int pos1, int pos2);

    // proveryayem yesli masiv pustoy
    bool empty();

    // vozvrachaet razmer masiva
    int size();

    // vozvrachaet maksimal'nyi razmer masiva
    int capacity();

    // esli maximalynyi razmer bolyshe chem v 2 raza chem masiv to umenishaem razmer
    void resize();

    // menyaem razmer masiva
    void resize(int Size);

    // ostavlyaet v masive n pervyh elementov
    // esly razmer masiva menyshe n, to dobavlyaem nedostoiushie elementy so znacheniem value
    void resize(int n, T value);

    // zamenyayem vse elementy masiva opredelennym naborom
    void replacement(int Size, T value);

    void swap(masiv<T>& other);

    // vozvrashchayem obychnuyu ssilku na element
    T& operator [] (int index);

    // vozvrashchayem obychnuyu ssilku na element
    T& at(int index);

    // operator prisvaevaniya // prisvaivaem soderjimoe odnogo konteynera nashemu
    masiv<T>& operator = (masiv<T> &other);

    masiv<T>& operator = (const masiv<T> &other);

    // operator prisvaevaniya // prisvaivaem nashemu masivu - spisok znacheniy
    void operator = (const std::initializer_list<T>& list);

    // operator sravneniya == 
    // masivy ravny, yesli oni soderzhat odinakovyye elementy na tekh zhe pozitsiyakh
    bool operator == (masiv<T>& mas2);

    // operator sravneniya != 
    // masivy ne ravny, yesli hotyaby odna para elementov na tekh zhe pozitsiyakh ne ravny
    bool operator != (masiv<T>& mas2);

    // operatory >, >=, <, <=  // sravnivaem tolyko po dline masiva
    bool operator > (masiv<T>& mas2);
    bool operator >= (masiv<T>& mas2);
    bool operator < (masiv<T>& mas2);
    bool operator <= (masiv<T>& mas2);

    // operator + // concotenatsia, soderjimoe mas2 dobavlyaetsya v conets mas
    masiv<T> operator + (masiv<T>& mas2);
};

