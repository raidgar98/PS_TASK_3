#pragma once

// STL
#include <algorithm>
#include <random>
#include <vector>
#include <array>
#include <string>
#include <sstream>

// Local includes
#include "coordinates.hpp"

// Type aliases
template<typename T, size_t s>
using storage_type = std::array<T, s>;
using num = int32_t;

template<size_t s>
using row_storage_type = storage_type<num, s>;
template<size_t s>
using row_storage_iterator_type = decltype(((row_storage_type<s>*)(nullptr))->begin());

template<size_t s>
using two_dimension_storage_type = storage_type<row_storage_type<s>, s>;
template<size_t s>
using two_dimension_storage_iterator_type = decltype(((two_dimension_storage_type<s>*)(nullptr))->begin());

// constexpresions
constexpr num empty_value{ 0 };

// defines
#ifdef UNIX

	constexpr auto u2551 = "\u2551";
	constexpr auto u2554 = "\u2554";
	constexpr auto u2557 = "\u2557";
	constexpr auto u255A = "\u255A";
	constexpr auto u255D = "\u255D";
	constexpr auto u2560 = "\u2560";
	constexpr auto u2550 = "\u2550";
	constexpr auto u2563 = "\u2563";
	constexpr auto u2566 = "\u2566";
	constexpr auto u2569 = "\u2569";
	constexpr auto u256C = "\u256C";

#else

	#define u8( element ) u8##element

	constexpr auto u2551 = u8("║");
	constexpr auto u2554 = u8("╔");
	constexpr auto u2557 = u8("╗");
	constexpr auto u255A = u8("╚");
	constexpr auto u255D = u8("╝");
	constexpr auto u2560 = u8("╠");
	constexpr auto u2550 = u8("═");
	constexpr auto u2563 = u8("╣");
	constexpr auto u2566 = u8("╦");
	constexpr auto u2569 = u8("╩");
	constexpr auto u256C = u8("╬");

#endif

template<size_t SIZE>
class SwitcherEngine
{
private: // varriables

	// internal aliases
	using panel_arr = two_dimension_storage_type<SIZE>;
	using panel_it = two_dimension_storage_iterator_type<SIZE>;
	using row_arr = row_storage_type<SIZE>;
	using row_it = row_storage_iterator_type<SIZE>;

	panel_arr board;
	coord empty;

public: // methodes
	
	// [constructor](https://www.youtube.com/watch?v=0V5PLkFuxrY)
	explicit SwitcherEngine(const size_t entropy = 10ul*SIZE )
	{
		__fill();
		assert( win() );
	}


	// getters
	const panel_arr& data()																				const	noexcept { return board; }
	const row_arr& get( const size_t row )																const	noexcept { return board[row]; }
	const num& get( const size_t row, const size_t col )												const	noexcept { return get( row )[col]; }
	bool win()																							const	noexcept { return __is_win(); }
	coord null()																						const	noexcept {	return empty;			}

	// operators
	operator const panel_arr&()																			const	noexcept {	return data();			}
	operator bool()																						const	noexcept {	return win();			}
	const row_arr& operator[](const size_t row)															const	noexcept {	return get(row);		}

	// non-const methodes

	// reset board to ordered state
	void reset()																								noexcept {	__fill();				}

	//shuffles all board
	void shuffle( const size_t entropy = 10ul * SIZE )															noexcept {	__shuffle(entropy);		}

	// swaps two cells
	bool swap( const coord& first, const coord& second )														noexcept 
	{
		if(!__is_swap_possible(first, second)) return false;
		__swap(first, second);
		return true;
	}
	// moves null cell relatively to itself (TIP: use consts like: up, down, left, right here)
	bool null_swap( const coord& direction )																	noexcept 
	{
		const coord first = null();
		const coord second = first + direction;
		return swap(first, second);
	}

	//checks
	bool good( const size_t row_1, const size_t col_1, const size_t row_2, const size_t col_2 )			const noexcept { return good(row_1, col_1, row_2, col_2); }
	bool good( const coord& first_cell, const coord& second_cell )										const noexcept { return __is_swap_possible( first_cell, second_cell ); }

private: // methodes

	// fills board with proper values 
	void __fill() noexcept
	{
		num val{ 1 };
		for (auto& row : board)
			for (auto& col : row) 
				col = val++;
		board.back().back() = empty_value;
		empty = { SIZE-1, SIZE-1 };
	}

	// shuffle values in board
	void __shuffle(const size_t level = 100) noexcept
	{
		std::random_device rng;
		std::uniform_int_distribution<pos> range{ 0, SIZE - 1 };

		for (size_t i = 0; i < level; i++)
			__swap({ range(rng), range(rng) }, { range(rng), range(rng) });
	}

	// checks basic stuff
	bool __basic_validation(const coord& value) const noexcept
	{
		if(static_cast<size_t>(value.row) >= SIZE) return false;
		if(static_cast<size_t>(value.col) >= SIZE) return false;
		return true;
	}

	// checks more complex data ex. relative position
	bool __is_swap_possible(const coord& first, const coord& second) const noexcept
	{
		if(!__basic_validation(first)) return false;
		if(!__basic_validation(second)) return false;

		// one of theese points have to be empty_value
		if (v(first) != empty_value && v(second) != empty_value)
			return false;

		// coordinates have to neighbours
		if (first + left == second || first + right == second ||
				first + up == second || first + down == second)
			return true;
		else
			return false;
	}

	// extended wrapper for std::iter_swap. Records position of empty element
	void __swap(const coord& _first, const coord& _second) noexcept
	{
		auto first = __goto(_first);
		auto second = __goto(_second);

		if( v(_first) == empty_value ) empty = _second;
		else if( v(_second) == empty_value ) empty = _first;

		std::iter_swap(first,second);
	}

	// scarry name a bit, huh? just translator from <pos, pos> to iterator
	row_it __goto(const coord& xy) noexcept
	{
		panel_it row{ board.begin() };
		std::advance(row, xy.row );
		row_it col{ row->begin() };
		std::advance(col, xy.col );
		return col;
	}

	// this method checks are all values in proper order
	bool __is_win() const noexcept
	{
		num val{ 1 };
		for( size_t i = 0; i < SIZE; i++ )
			for( size_t j = 0; j < SIZE; j++, val++ )
				if( board[i][j] != val )
				{
					if( i == SIZE -1 && j == SIZE - 1 && board[i][j] == empty_value) return true;
					return false;
				}
		return true;
	}

	// laaaazy (v)alue getter
	num v(const coord& c) const noexcept { return board[c.row][c.col]; }

};


// printer for two_dimension_storage_type
template<size_t SIZE>
std::ostream& operator<<(std::ostream& os, const two_dimension_storage_type<SIZE>& obj )
{
	// calculates width of biggest number
	const size_t length = std::to_string( ( SIZE * SIZE ) - 1 ).size() + 2;
	// this lambda prints proper width, row separators
	const auto width = [&os, &length]() 
	{ 
		for( size_t i = 0; i < length; i++)
			os << u2550; 
	};

	// this lambda format numbers
	const auto format = [length](const num val){
		if(val == 0) return std::string(length, ' ');
		std::string ret = std::to_string(val) + " ";
		while(ret.size() != length - 1)
			ret = "0" + ret;
		return " " + ret;
	};

	// first line of table
	os << std::endl << u2554;
	for( size_t i = 0; i < SIZE - 1; i++)
	{
		width();
		os << u2566;
	}
	width();
	os << u2557 << std::endl;

	// middle (data) of table
	for( size_t i = 0; i < SIZE; i++ ) // <- each row
	{
		os << u2551; // <- start with something like |

		for( size_t j = 0; j < SIZE; j++)	// <- next value + |
			os << format(obj[i][j]) << u2551;

		if(i != SIZE - 1)		// <- in the last iteration, don't print, special case
		{
			os << std::endl << u2560;
			for( size_t j = 0; j < SIZE - 1; j++)
			{
				width();		// <- this prints row borders
				os << u256C;
			}
			width();
			os << u2563;
		}

		os << std::endl;	// <- endline
	}

	// here is this special case: table footer
	os << u255A;
	for( size_t i = 0; i < SIZE - 1; i++)
	{
		width();
		os << u2569;
	}
	width();
	os << u255D << std::endl;;

	return os;
}

// printer for SwitcherEngine
template<size_t SIZE>
std::ostream& operator<<( std::ostream& os, const SwitcherEngine<SIZE>& input )
{
	const two_dimension_storage_type<SIZE>& obj = input;
	os << obj;
	return os;
}
