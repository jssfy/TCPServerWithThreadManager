//
//  main.cpp
//  HelloCPP
//
//  Created by mstr on 10/23/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#include <iostream>
#include <atomic>         // std::atomic_flag
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <sstream>        // std::stringstream
#include <vector>

#include "TCPServer.h"

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_number(int x) {
    while (lock_stream.test_and_set()) {}
    stream << "thread #" << x << '\n';
    lock_stream.clear();
}

template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    std::cout << N << ',' << M << std::endl;
    return strcmp(p1, p2);
}

template <int N>
void printNumber()
{
    std::cout << "N in template is: " << N << std::endl;
    
}

template<typename I, typename T>
I jssfy_find(I begin, I end, T value)
{
    auto itr = begin;
    while(itr!= end)
    {
        if(*itr == value)
        {
            return itr;
        }
        ++itr;
    }
    return itr;
}

template <typename T> class Blob
{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // constructors
    Blob();
    Blob(std::initializer_list<T> il);
    // number of elements in the Blob
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const T &t) {data->push_back(t);}
    // move version; see § 13.6.3 (p. 548)
    void push_back(T &&t) { data->push_back(std::move(t)); } void pop_back();
    // element access
    T& back();
    T& operator[](size_type i); // defined in § 14.5 (p. 566)
private:
    std::shared_ptr<std::vector<T>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

void test(const int &i)
{
    
}

int main (int argc, char* argv[])
{
    
    TcpServer ts(8888); //atoi(argv[1]));
    ts.recv_msg();
    
    return 0;
}



