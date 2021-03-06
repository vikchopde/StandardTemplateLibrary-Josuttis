
#ifndef STANDARDTEMPLATELIBRARY_JOSUTTIS_TUPLE_H
#define STANDARDTEMPLATELIBRARY_JOSUTTIS_TUPLE_H


#include <tuple>
#include <string>
#include <vector>

//Print Tuple using Variadic templates and metaprogramming

namespace print
{

    template <int IDX, int MAX, typename ...Args>
    struct PRINT_TUPLE
    {
        static void PrintTuple(std::ostream &out, std::tuple<Args...> &tp)
        {
            out << std::get<IDX>(tp) << endl;
            PRINT_TUPLE < IDX + 1, MAX, Args...>::PrintTuple(out, tp);
        }
    };

    //// Note : Learned something heavy here.
    //// Partial specialization of function templates is not allowed.
    //// but struct is allowed so wrapping the printtuple under a struct. :)

    template <int MAX, typename ...Args>
    struct PRINT_TUPLE<MAX, MAX, Args...>
    {
        static void PrintTuple(std::ostream &out, std::tuple<Args...> &tp)
        {
        }
    };

    template <typename ...Args>
    std::ostream& operator << (std::ostream& out, std::tuple<Args...>& tp)
    {
        PRINT_TUPLE<0, sizeof...(Args), Args...>::PrintTuple(out,tp);
    }

    void do_print()
    {
        std::string first  = "vik";
        std::string second = "chop";
        std::tuple<int, std::string, std::string> person_print {10, first, second};
        std::cout << person_print << std::endl;
    }
}
void TupleExamples()
{
    std::string first  = "vik";
    std::string second = "chop";
    //Constructor
    std::tuple<int, std::string, std::string> person {10, first, second};

    //Make tuple
    std::tuple<int, std::string, std::string> person2  = std::make_tuple(10, first, second);

    //Make tuple
    auto person_auto  = std::make_tuple(10, first, second);

    //Acesss Element
    std::cout << std::get<0>(person_auto) << std::endl;
    std::cout << std::get<1>(person_auto) << std::endl;
    std::cout << std::get<2>(person_auto) << std::endl;

    //out_of_range compile error
    //std::cout << std::get<4>(person_auto) << std::endl;

    std::get<1>(person_auto) = std::get<2>(person_auto);

    //Acesss Element
    std::cout << std::get<0>(person_auto) << std::endl;
    std::cout << std::get<1>(person_auto) << std::endl;
    std::cout << std::get<2>(person_auto) << std::endl;

    //tie interface for tuple

    int new_i = 0;
    std::string new_first , new_second;

    //by ref
    std::tie(new_i, new_first, new_second) = person_auto;
    //same as
    std::make_tuple(std::ref(new_i), std::ref(new_first), std::ref(new_second)) = person_auto;
    new_i++;


    ////Note : tuple constructor is explicit
    //foo(42) //wont work
    //foo(std::make_tuple(42))  //It worked :)

    ////Note : tuple constructor is explicit
    ////Error :     error: converting to ‘std::tuple<int, int>’ from initializer list would use explicit constructor
    //std::vector<std::tuple<int,int>> v {{1,1}};

    //Work around , explictly cast it to tuple.
    std::vector<std::tuple<int,int>> v {std::make_tuple(1,1)};

    //tuple size
    using type = std::tuple<int,int>;
    std::tuple_size<type>::value;   //// size = 3

    //tuple element type
    //std::tuple_element<1, type>::type;  //// type = std::string

}








#endif //STANDARDTEMPLATELIBRARY_JOSUTTIS_TUPLE_H
