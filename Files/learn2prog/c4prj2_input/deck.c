#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t *hand) {
    for (size_t i = 0; i < hand->n_cards; i++) {
        print_card(*hand->cards[i]);
        printf(" ");
    }
}

int deck_contains(deck_t *d, card_t c) {
    for (size_t i = 0; i < d->n_cards; i++) {
        if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit) {
            return 1;
        }
    }
    return 0;
}

void shuffle(deck_t *d) {
    card_t c;
    for (size_t i = d->n_cards; i > 0; i--) {
        size_t r = rand() % i;
        c = *d->cards[i - 1];
        *d->cards[i - 1] = *d->cards[r];
        *d->cards[r] = c;
    }
}

void assert_full_deck(deck_t *d) {
    card_t temp;
    for (int i = 0; i <= 51; i++) {
        temp = card_from_num(i);
        assert(deck_contains(d, temp) == 1);
    }
}

void add_card_to(deck_t *deck, card_t c) {
    deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
    deck->cards[deck->n_cards] = malloc(sizeof(**deck->cards));
    *deck->cards[deck->n_cards] = c;
    deck->n_cards++;
}

card_t *add_empty_card(deck_t *deck) {
    card_t c = {0, 0};
    add_card_to(deck, c);
    return deck->cards[deck->n_cards - 1];
}

deck_t *make_deck_exclude(deck_t *excluded_cards) {
    deck_t *deck = malloc(sizeof(*deck));
    deck->cards = NULL;
    deck->n_cards = 0;
    for (unsigned i = 0; i < 52; i++) {
        card_t c = card_from_num(i);
        if (!deck_contains(excluded_cards, c)) {
            add_card_to(deck, c);
        }
    }
    return deck;
}

deck_t *build_remaining_deck(deck_t **hands, size_t n_hands) {
    deck_t *temp_deck = malloc(sizeof(*temp_deck));
    temp_deck->cards = NULL;
    temp_deck->n_cards = 0;
    for (size_t i = 0; i < n_hands; i++) {
        for (size_t j = 0; j < hands[i]->n_cards; j++) {
            add_card_to(temp_deck, *hands[i]->cards[j]);
        }
    }
    
    deck_t *result = make_deck_exclude(temp_deck);
    free_deck(temp_deck);
    return result;
}

void free_deck(deck_t *deck) {
    for (size_t i = 0; i < deck->n_cards; i++) {
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
}
