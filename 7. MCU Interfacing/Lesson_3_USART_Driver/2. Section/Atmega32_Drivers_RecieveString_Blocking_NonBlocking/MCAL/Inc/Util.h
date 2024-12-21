/*
 * Util.h
 *
 * Created: 10/12/2024 2:58:18 PM
 *  Author: Dubai Store
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#define F_CPU 8000000UL // Define CPU clock frequency

// Macro to set a bit
#define SET_BIT(REG, BIT) ((REG) |= (1 << (BIT)))

// Macro to reset (clear) a bit
#define RESET_BIT(REG, BIT) ((REG) &= ~(1 << (BIT)))

// Macro to toggle a bit
#define TOGGLE_BIT(REG, BIT) ((REG) ^= (1 << (BIT)))

// Macro to read a bit (returns 0 or 1)
#define READ_BIT(REG, BIT) (((REG) >> (BIT)) & 1)

#endif /* UTIL_H_ */