#define BOOST_TEST_MODULE sneaky_pointer_tests

// Internal
#include "../libraries/submodules/sneaky_pointer/sneaky_pointer.hpp"

// Boost
#include <boost/test/included/unit_test.hpp>

template<typename T>
void print_ptr( const T& ptr )
{
	static_assert( sizeof(T*) == sizeof(T) );
	union{
		uint64_t out;
		T in;
	} conv;

	conv.in = ptr;

	std::bitset< sizeof(T) * 8 > bs{ conv.out };
	std::cout << bs.to_string() << std::endl;
};

template<typename T>
bool ret_true(const T&) { return true; }

BOOST_AUTO_TEST_SUITE( sneaky_pointer_test_cases )

BOOST_AUTO_TEST_CASE( basic_test_01 )
{
	sneaky_pointer<int, 4> ptr;

	BOOST_REQUIRE_EQUAL( ptr.get_pointer(), nullptr );
	BOOST_REQUIRE_EXCEPTION( ptr.set_flag(0, true), std::invalid_argument, ret_true );
	BOOST_REQUIRE_EXCEPTION( ptr.set_flag(1, true), std::invalid_argument, ret_true );
	BOOST_REQUIRE_EXCEPTION( ptr.set_flag(5, true), std::invalid_argument, ret_true );

	int * raw = new int(4);
	ptr.set_pointer( raw );

	BOOST_REQUIRE_EQUAL( raw, ptr.get_pointer() );

	raw = nullptr;
	ptr.set_pointer( nullptr );

	BOOST_REQUIRE_EQUAL( ptr.get_pointer(), nullptr );

	ptr.set_pointer( new int(5) );
	std::vector<bool> vec{ { 0, 0, 0, 0, 0 } };
	for(int i = 1; i <= 4; i++)
		ptr.set_flag(i, false);

	for(int i = 1; i <= 4; i++)
	{
		ptr.set_flag(i, true);
		vec[i] = true;
		for(int i = 1; i <= 4; i++)
			BOOST_REQUIRE_EQUAL( vec[i], ptr.get_flag(i) );
	}

	for(int i = 1; i <= 4; i++)
	{
		ptr.set_flag(i, false);
		vec[i] = false;
		for(int i = 1; i <= 4; i++)
			BOOST_REQUIRE_EQUAL( vec[i], ptr.get_flag(i) );
	}
}

BOOST_AUTO_TEST_SUITE_END()
