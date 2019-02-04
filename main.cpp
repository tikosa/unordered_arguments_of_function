#include <iostream>
#include <tuple>

struct Param1 {};
struct Param2 {};
struct Param3 {};
struct Param4 {};


template<typename X, typename... Ts>
struct position;

template<typename X>
struct position<X> {
    static const int pos = -1; 
};

template<typename X, typename... Ts> 
struct position<X, X, Ts...> {
    static const int pos = 0;
};

template<typename X, typename T, typename... Ts> 
struct position<X, T, Ts...> {
    static const int pos = position<X, Ts...>::pos != -1 ? position<X, Ts...>::pos + 1 : -1; 
};

template<class... Types>
struct count {
        static const std::size_t value = sizeof...(Types);
};

void logic(Param1 _p1, Param2 _p2, Param3 _p3, Param4 _p4)
{
	std::cout << "Do actual logic\n";
}

// Another implementation of position
// template <typename T, typename U=void, typename... Types>
// constexpr size_t index() {
//     return std::is_same<T, U>::value ? 0 : 1 + index<T, Types...>();
// }

template<typename ...Types>
void f(Types ...args)
{
	static_assert(count<Types...>::value == 4, "The number of arguments should be 4");
	auto _t = std::make_tuple(args...);
	logic(std::get<position<Param1, Types...>::pos>(_t), std::get<position<Param2, Types...>::pos>(_t),
			std::get<position<Param3, Types...>::pos>(_t), std::get<position<Param4, Types...>::pos>(_t));

}


int main()
{
    // std::cout << count<int, int, int>::value << std::endl;
	// f(Param2{}, Param3{}, Param4{}, Param1{});
	// f(Param4{}, Param3{}, Param2{}, Param1{});
	// f(Param1{}, Param3{}, Param4{}, Param2{});
    std::cout << position<int, int>::pos << std::endl;

    return 0;
}
