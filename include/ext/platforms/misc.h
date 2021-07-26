#pragma once

#ifndef FLAG_ON
#define FLAG_ON(_F, _SF) ((_F) & (_SF))
#endif

#ifndef BOOLEAN_FLAG_ON
#define BOOLEAN_FLAG_ON(F, SF) ((bool)(((F) & (SF)) != 0))
#endif

#ifndef SET_FLAG
#define SET_FLAG(_F, _SF) ((_F) |= (_SF))
#endif

#ifndef CLEAR_FLAG
#define CLEAR_FLAG(_F, _SF) ((_F) &= ~(_SF))
#endif

#ifndef ROUND_TO_SIZE
#define ROUND_TO_SIZE(_length, _alignment)                                     \
  ((((size_t)(_length)) + ((_alignment)-1)) & ~((size_t)(_alignment)-1))
#endif