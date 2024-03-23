#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for (size_t i=0;i<hand->n_cards;i++){
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(size_t i=0;i< d->n_cards;i++){
    if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t c;
  for(size_t i = d->n_cards;i>0;i--){
    int r = rand() %i;
    c = *d->cards[i-1];
    *d->cards[i-1] = *d->cards[r];
    *d->cards[r] = c;
  }
}

void assert_full_deck(deck_t * d) {
  card_t temp;
  for(int i =0;i<=51;i++){
    temp = card_from_num(i);
    assert(deck_contains(d,temp)==1);
  }
}
