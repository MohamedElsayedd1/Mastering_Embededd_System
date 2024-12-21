/*
 * Util.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_


#define SET_BIT(REG, BIT) 			        ((REG) |= (1 << (BIT)))
#define CLEAR_BIT(REG, BIT) 		        ((REG) &= ~(1 << (BIT)))
#define TOGGLE_BIT(REG, BIT) 		        ((REG) ^= (1 << (BIT)))

#define READ_BIT(REG, BIT) 		            ((REG >> BIT) & 0X01)

#endif /* INC_UTIL_H_ */
