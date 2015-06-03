#include <iostream>
#include <type_traits>

/* use type traits to check type descriptor */
template <class T>
struct type_desc {
    friend std::ostream& operator << (std::ostream& out, const type_desc<T>&) {
        if (std::is_same<void, T>::value) {
            out << "void";
        } else if (std::is_same<int, T>::value) {
            out << "int";
        } else if (std::is_same<double, T>::value) {
            out << "double";
        } else if (std::is_same<long, T>::value) {
            out << "long";
        } else if (std::is_pointer<T>::value) {
            out << type_desc<typename std::remove_pointer<T>::type>();
            out << "*";
        } else if (std::is_reference<T>::value) {
            out << type_desc<typename std::remove_reference<T>::type>();
            out << "&";
        } else if (std::is_array<T>::value) {
            out << type_desc<typename std::remove_extent<T>::type>();
            out << "[]";
        } else if (std::is_const<T>::value) {
            out << "const ";
            out << type_desc<typename std::remove_const<T>::type>();
        }
        return out;
    }
};

/* use partial specialization to check type descriptor */
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

template <class T, class Arg>
struct type_desc<T(*)(Arg)> {
    friend std::ostream& operator << (std::ostream& out, const type_desc<T(*)(Arg)>&) {
        out << type_desc<T>();
        out << "(*)";
        out << "(" << type_desc<Arg>() << ")";
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
    std::cout << type_desc<char* (*)(char*)>() << std::endl;
    return 0;
}
