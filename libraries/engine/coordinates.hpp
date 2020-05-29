#pragma once

#include <iostream>
#include <cassert>

using pos = int32_t;

struct coord {
	// public fields
	pos row, col;

	// defaults -_-
	coord() = default;
	coord(const coord &) = default;
	coord(coord &&) = default;
	coord &operator=(const coord &) = default;
	coord &operator=(coord &&) = default;

	// extended constructors
	coord(const pos _row, const pos _col) : row{_row}, col{_col} {}

	// conversion constructor
	explicit coord(const std::pair<pos, pos> &pair)
		: row{pair.first}, col{pair.second} {}

	// conversion operator
	operator std::pair<pos, pos>() const { return {row, col}; }

	// compare operator
	bool operator==(const coord &val)	const { return (row == val.row) && (col == val.col); }
	bool operator!=(const coord &val)	const { return !(*this == val); }
	bool operator<(const coord &val)	const { return (row != val.row ? row < val.row : col < val.col); }
};

inline const coord up{-1, 0};
inline const coord left{0, -1};
inline const coord down{1, 0};
inline const coord right{0, 1};

inline coord operator+(const coord &val1, const coord &val2) { return {val1.row + val2.row, val1.col + val2.col}; }

inline std::ostream& operator<<( std::ostream& os, const coord& src )
{
	os << "( " << src.row << ", " << src.col << " )";
	return os;
}
