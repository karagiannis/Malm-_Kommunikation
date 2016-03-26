/*
 * STM3210C-EVAL_callback.c
 *
 *  Created on: Sep 18, 2012
 *      Author: Atollic AB
 */

#include "stm3210c_eval_i2c_ee.h"


/*
 * Callback used by stm3210c_eval_i2c_ee.c.
 * Refer to stm3210c_eval_i2c_ee.h for more info.
 */
__attribute__((weak)) uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  while (1)
  {
  }
}
