#pragma warning(disable : 4996)
#pragma once

// STL
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>

// Local Includes
#include "../libraries/engine/SwitcherEngine.hpp"

// constexpresions
constexpr size_t BOARD_SIZE{ 5ul };

class base_tester
{
private:	// varriables

public:		// methodes

private:	// methodes
};

// TODO: REPAIR IT, THIS ONE IS TOTALL ABSURD !!!
class switcher_tester : public base_tester
{
public:		// varriables

	SwitcherEngine< BOARD_SIZE, num > eng{ [](bool){ return 1; } };
	typename SwitcherEngine< BOARD_SIZE, num >::two_dimension_storage_type as_it_should_be;

public:		// methodes

	switcher_tester()
	{
		// as_it_should_be = eng.data();
	}

	bool is_win()
	{
		// return eng.data() == as_it_should_be;
		return eng.win();
	}
};
