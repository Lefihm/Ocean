#pragma once

#include "Ocean/Types/Integers.hpp"

namespace Ocean {

	/**
	 * @brief A type definition for mouse button codes used in the Ocean Engine.
	 * 
	 * This is a 16-bit unsigned integer type, suitable for representing mouse button codes.
	 */
	using MouseCode = u16;

	namespace Mouse {

		/**
		 * @brief An enumeration of mouse buttons used in the Ocean Engine.
		 * 
		 * Based on GLFW mouse button codes, but can be extended or modified as needed.
		 */
		enum : MouseCode {
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2,

			ButtonCount = 8
		};

	}	// Mouse

}	// Ocean
