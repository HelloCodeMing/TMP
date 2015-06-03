#include <iostream>
#include <type_traits>

template <class T>
struct type_desc {
    friend std::ostream& operator << (std::ostream& out, const type_desc<T>&) = delete;
};

template <class T>
struct type_desc<const T> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<const T>&) {
        out << "const ";
        out << type_desc<T>();
        return out;
    }
};

template <class T>
struct type_desc<T*> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<T*>&) {
        out << type_desc<T>();
        out << "*";
        return out;
    }
};

template <class T>
struct type_desc<T&> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<T&>&) {
        out << type_desc<T>();
        out << "&";
        return out;
    }
};

template <>
struct type_desc<int> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<int>&) {
        out << "int";
        return out;
    }
};

template <>
struct type_desc<double> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<double>&) {
        out << "double";
        return out;
    }
};

template <>
struct type_desc<char> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<char>&) {
        out << "char";
        return out;
    }
};

template <>
struct type_desc<long> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<long>&) {
        out << "long";
        return out;
    }
};

int main()
{
    std::cout << type_desc<int>() << std::endl;
    std::cout << type_desc<double>() << std::endl;
    std::cout << type_desc<long>() << std::endl;
    std::cout << type_desc<char>() << std::endl;

    std::cout << type_desc<int*>() << std::endl;
    std::cout << type_desc<double*>() << std::endl;
    
    std::cout << type_desc<int&>() << std::endl;
    std::cout << type_desc<char&>() << std::endl;

    std::cout << type_desc<const int>() << std::endl;
    std::cout << type_desc<const int&>() << std::endl;
    std::cout << type_desc<const int*>() << std::endl;
    return 0;
}
