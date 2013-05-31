//
// Crypto system calls.
//

#include "types.h"
#include "defs.h"

int
sys_hash(void)
{
  int n;
  char *data;
  char *hash;

  if(argint(2, &n) < 0 || argptr(0, &data, n) < 0 || argptr(1, &hash, 32) < 0)
    return -1;
  return crypto_hash(data, hash, n);
}
