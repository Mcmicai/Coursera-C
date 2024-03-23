#include "future.h"

#include <stdio.h>
#include <stdlib.h>

void add_future_card(future_cards_t* fc, size_t index, card_t* ptr) {
  if (fc == NULL) {
    fc = malloc(sizeof(*fc));
    fc->decks = NULL;
    fc->n_decks = 0;
  }

  if (index >= fc->n_decks) {
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));
    size_t size = fc->n_decks;
    fc->n_decks = index + 1;
    for (size_t i = size; i < fc->n_decks; i++) {
      fc->decks[i].cards = NULL;
      fc->decks[i].n_cards = 0;
    }
  }

  size_t new_n_cards = fc->decks[index].n_cards + 1;
  fc->decks[index].cards =
      realloc(fc->decks[index].cards, new_n_cards * sizeof(card_t*));
  fc->decks[index].n_cards++;
  fc->decks[index].cards[new_n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t* deck, future_cards_t* fc) {
  if (fc == NULL) {
    fprintf(stderr, "No future cards.");
  }
  if (fc->n_decks > deck->n_cards) {
    fprintf(stderr, "Not enough cards in deck.");
  }

  for (size_t i = 0; i < fc->n_decks; i++) {
    if (fc->decks[i].n_cards == 0) continue;
    for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
      (*(fc->decks[i].cards[j])).value = (*(deck->cards[i])).value;
      (*(fc->decks[i].cards[j])).suit = (*(deck->cards[i])).suit;
    }
  }
}
