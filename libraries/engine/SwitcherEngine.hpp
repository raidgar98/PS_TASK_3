#pragma once

// STL
#include <algorithm>
#include <random>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <functional>

// Local includes
#include "coordinates.hpp"

using num = int32_t;

// constexpresions
constexpr num empty_value{0};

// defines
#if UNIX == 1

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

#elif UNIX == 0

#define u8(element) u8##element

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

template <size_t SIZE, typename T = num>
class SwitcherEngine
{
public: // aliases
	// Type aliases
	template <typename X, size_t s>
	using storage_type = std::array<X, s>;

	using fill_function = std::function<T(bool)>;				  // if argument is true, function should return empty_value and reset itself if required
	using swap_callback_function = std::function<void(T &, T &)>; // called if swap succed

	using row_storage_type = storage_type<T, SIZE>;
	using row_storage_iterator_type = decltype(((row_storage_type *)(nullptr))->begin());

	using two_dimension_storage_type = storage_type<row_storage_type, SIZE>;
	using two_dimension_storage_iterator_type = decltype(((two_dimension_storage_type *)(nullptr))->begin());

private: // varriables
	// internal aliases
	using panel_arr = two_dimension_storage_type;
	using panel_it = two_dimension_storage_iterator_type;
	using row_arr = row_storage_type;
	using row_it = row_storage_iterator_type;

	fill_function generator;
	swap_callback_function swap_callback;
	panel_arr board;
	coord empty;

public: // methodes
	// [constructor](https://www.youtube.com/watch?v=0V5PLkFuxrY)
	explicit SwitcherEngine( fill_function _generator, swap_callback_function sw_call = [](T &, T &) { return; })
		:swap_callback{sw_call}, generator{ _generator }
	{}

	// getters
	const panel_arr &data() const noexcept { return board; }
	const row_arr &get(const size_t row) const noexcept { return board[row]; }
	const num &get(const size_t row, const size_t col) const noexcept { return get(row)[col]; }
	bool win() const noexcept { return __is_win(); }
	coord null() const noexcept { return empty; }

	// operators
	operator const panel_arr &() const noexcept { return data(); }
	operator bool() const noexcept { return win(); }
	const row_arr &operator[](const size_t row) const noexcept { return get(row); }

	// non-const methodes

	// reset board to ordered state
	void reset() noexcept { __fill(); }

	//shuffles all board
	void shuffle(const size_t entropy = 10ul * SIZE) noexcept { __shuffle(entropy); }

	// swaps two cells
	bool swap(const coord &first, const coord &second) noexcept
	{
		if (!__is_swap_possible(first, second))
			return false;
		__swap(first, second);
		return true;
	}
	// moves null cell relatively to itself (TIP: use consts like: up, down, left, right here)
	bool null_swap(const coord &direction) noexcept
	{
		const coord first = null();
		const coord second = first + direction;
		return swap(first, second);
	}

	//checks
	bool good(const size_t row_1, const size_t col_1, const size_t row_2, const size_t col_2) const noexcept { return good(row_1, col_1, row_2, col_2); }
	bool good(const coord &first_cell, const coord &second_cell) const noexcept { return __is_swap_possible(first_cell, second_cell); }

private: // methodes
	// return empty value
	const T &__empty_value() const
	{
		return v(empty);
	}

	// fills board with proper values
	void __fill() noexcept
	{
		const auto& begin = board.begin()->begin();
		__for_each( [&](row_it &val) { 
			*val = generator(val == begin); 
		});
		empty = { 0, 0 };
	}

	// shuffle values in board
	void __shuffle(const size_t level = 100) noexcept
	{
		std::random_device rng;
		std::uniform_int_distribution<pos> range{0, SIZE - 1};

		for (size_t i = 0; i < level; i++)
			__swap({range(rng), range(rng)}, {range(rng), range(rng)});
	}

	// checks basic stuff
	bool __basic_validation(const coord &value) const noexcept
	{
		if (static_cast<size_t>(value.row) >= SIZE)
			return false;
		if (static_cast<size_t>(value.col) >= SIZE)
			return false;
		return true;
	}

	// checks more complex data ex. relative position
	bool __is_swap_possible(const coord &first, const coord &second) const noexcept
	{
		if (!__basic_validation(first))
			return false;
		if (!__basic_validation(second))
			return false;

		// one of theese points have to be empty_value
		if (v(first) != __empty_value() && v(second) != __empty_value())
			return false;

		// coordinates have to neighbours
		if (first + left == second || first + right == second ||
			first + up == second || first + down == second)
			return true;
		else
			return false;
	}

	// extended wrapper for std::iter_swap. Records position of empty element
	void __swap(const coord &_first, const coord &_second) noexcept
	{
		auto first = __goto(_first);
		auto second = __goto(_second);

		if (v(_first) == __empty_value())
			empty = _second;
		else if (v(_second) == __empty_value())
			empty = _first;

		std::iter_swap(first, second);

		swap_callback(*first, *second);
	}

	// scarry name a bit, huh? just translator from <pos, pos> to iterator
	row_it __goto(const coord &xy) noexcept
	{
		panel_it row{board.begin()};
		std::advance(row, xy.row);
		row_it col{row->begin()};
		std::advance(col, xy.col);
		return col;
	}

	// this method checks are all values in proper order
	bool __is_win() const noexcept
	{
		const T _e = generator(true); // reset
		for (size_t i = 0; i < SIZE; i++)
			for (size_t j = 0; j < SIZE; j++)
				if (board[i][j] != generator(false))
				{
					if (i == SIZE - 1 && j == SIZE - 1 && board[i][j] == _e)
						return true;
					return false;
				}
		return true;
	}

	// laaaazy (v)alue getter
	const T &v(const coord &c) const noexcept { return board[c.row][c.col]; }

	void __for_each(std::function<void(row_it &)> fn)
	{
		for (panel_it rw_it = board.begin(); rw_it != board.end(); rw_it++)
			for (row_it c_it = rw_it->begin(); c_it != rw_it->end(); c_it++)
				fn(c_it);
	}
};

// printer for two_dimension_storage_type
template <size_t SIZE, typename T>
std::ostream &operator<<(std::ostream &os, const typename SwitcherEngine<SIZE, T>::two_dimension_storage_type &obj)
{
	// calculates width of biggest number
	const size_t length = std::to_string((SIZE * SIZE) - 1).size() + 2;
	// this lambda prints proper width, row separators
	const auto width = [&os, &length]() {
		for (size_t i = 0; i < length; i++)
			os << u2550;
	};


	// first line of table
	os << std::endl << u2554;
	for (size_t i = 0; i < SIZE - 1; i++)
	{
		width();
		os << u2566;
	}
	width();
	os << u2557 << std::endl;

	// middle (data) of table
	for (size_t i = 0; i < SIZE; i++) // <- each row
	{
		os << u2551; // <- start with something like |

		for (size_t j = 0; j < SIZE; j++) // <- next value + |
			os << obj[i][j] << u2551;

		if (i != SIZE - 1) // <- in the last iteration, don't print, special case
		{
			os << std::endl << u2560;
			for (size_t j = 0; j < SIZE - 1; j++)
			{
				width(); // <- this prints row borders
				os << u256C;
			}
			width();
			os << u2563;
		}

		os << std::endl; // <- endline
	}

	// here is this special case: table footer
	os << u255A;
	for (size_t i = 0; i < SIZE - 1; i++)
	{
		width();
		os << u2569;
	}
	width();
	os << u255D << std::endl;
	;

	return os;
}

// printer for SwitcherEngine
template <size_t SIZE, typename T>
std::ostream &operator<<(std::ostream &os, const SwitcherEngine<SIZE, T> &input)
{
	const typename SwitcherEngine<SIZE, T>::two_dimension_storage_type &obj = input;
	os << obj;
	return os;
}
