/*
 * Category.hpp
 *
 *  Created on: 5 dic 2021
 *      Author: joe
 */

#ifndef INCLUDE_BOOK_CATEGORY_HPP_
#define INCLUDE_BOOK_CATEGORY_HPP_

// Entity/scene node category,used to dispatch commands
// No emplear aquí enum class type, cada category tiene
// que tener un valor asociado
namespace Category {
	enum Type {
		None			=0,
		Scene			= 1 << 0,
		PlayerAircraft	= 1 << 1,
		AlliedAircraft	= 1 << 2,
		EnemyAircraft	= 1 << 3
	};
}

#endif /* INCLUDE_BOOK_CATEGORY_HPP_ */
