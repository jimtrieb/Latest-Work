
#ifndef __CPU_SINGLE__
#define __CPU_SINGLE__

#include <cstdint>
#include "memory.h"
#include "rv32i_hart.h"


class cpu_single_hart : public rv32i_hart
{
	public:
		/**
		 * contructor used to pass memory class instance to constructor in base class
		 *
		 * @param mem memory class instance
		 *
		 * @note rv32i_hart base class
		 ******************************************************************************/
		cpu_single_hart(memory &mem) : rv32i_hart(mem) {}

		/**
		 * will run until is_halted is true or exec_limit is reached
		 *
		 * @param exec_limit number of instructions to execute
		 *
		 * @note sets register 2 to memory size
		 *****************************************************************************/
		void run(uint64_t exec_limit);


};

#endif
