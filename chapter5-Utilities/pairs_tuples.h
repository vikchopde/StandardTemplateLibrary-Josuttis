
#ifndef STANDARDTEMPLATELIBRARY_JOSUTTIS_PAIRS_TUPLES_H
#define STANDARDTEMPLATELIBRARY_JOSUTTIS_PAIRS_TUPLES_H

#include <iosfwd>
#include <utility>
#include <iostream>
#include <string>
#include <tuple>

using std::cout;
using std::endl;

/* Possible implementation
namespace std
{
    template <typename T1, typename T2>
    struct pair
    {
        T1 first;
        T2 second;
    };
}*/

namespace vik
{
    //// accessing members of pair
    template<typename T1, typename T2>
    class MyPair
    {
    public:
        friend std::ostream& operator<<(std::ostream &out, const MyPair<T1,T2>& p)
        {
            //out << p.pair_.first << " " << p.pair_.second;
            out << std::get<0>(p.pair_) << " " << std::get<1>(p.pair_);

            return out;
        }


        MyPair(T1 first, T2 second)
                : pair_(std::pair<T1,T2>(first, second))
        {
        }

    private:
        std::pair<int, std::string> pair_;
    };


    ////Note: Since c++11 a type with non constant copy constructor wont work with pair

    class A
    {
    public:
        A(A&) //non const copy constructor
        {

        }
    };


    //// Piecewise Construction of pair

    class Foo
    {
    public:
        Foo(std::tuple<int, float>&)
        {
            std::cout << "Foo(std::tuple<int, float>&)" << std::endl;
        }


        ////Invoking this constructor require passing piecewise_construct as first param,
        //// and both first and second param should be tuple.
        template <typename ...Args>
        Foo(Args ...)
        {
            std::cout << "Foo(Args ...)" << std::endl;
        }
    };


    /*
        #include <iostream>
        #include "pairs_tuples.h"
        #include <functional>

        int main()
        {
            std::string str = "hello";
            vik::MyPair<int, std::string> p {42, str};
            std::cout << p << std::endl;

            //std::pair<vik::A,int> p1;    //// Wont Work

            std::tuple<int, float> tp(1,1.0);
            std::pair<int, vik::Foo> p2(1,tp);
            std::pair<int,vik::Foo> p4(std::piecewise_construct,std::make_tuple(1), tp);


            std::tuple<int, float> tp_move(1,1.0);
            std::pair<int, vik::Foo> p2_move(1,tp);
            std::pair<int,vik::Foo> p4_move(std::piecewise_construct,std::make_tuple(1), std::move(tp));

            int i = 0;
            std::pair<int, vik::Foo> p2_ref(std::ref(i),tp);

            p2_ref.first++;
            p2_ref.first++;
            std::cout << p2_ref.first << std::endl;

            return 0;
        }
     */


}


#endif //STANDARDTEMPLATELIBRARY_JOSUTTIS_PAIRS_TUPLES_H
