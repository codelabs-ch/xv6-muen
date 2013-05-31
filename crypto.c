//
// Crypto operations
//

#include <stdint.h>

#include "types.h"
#include "defs.h"
#include "spinlock.h"
#include "crypto.h"
#include "memlayout.h"

#define BUFFER_SIZE 2048

typedef struct message_t message_t;

volatile message_t * const request  = (struct message_t *)P2V(0x70000);
volatile message_t * const response = (struct message_t *)P2V(0x80000);

struct message_t {
  uint16_t size;
  char data[BUFFER_SIZE];
};

static void trigger_event(unsigned long number)
{
  asm volatile("vmcall" : "+a"(number));
}

// Hash given data.
int
crypto_hash(char *data, char *hash, int n)
{
  if(n >= BUFFER_SIZE)
    return -1;

  request->size = n;
  memmove((char*)&request->data, data, n);

  acquire(&crypter_lock);
  trigger_event(1);
  sleep(&crypter_signal, &crypter_lock);
  release(&crypter_lock);

  memmove(hash, (char*)&response->data, 32);
  return response->size;
}
