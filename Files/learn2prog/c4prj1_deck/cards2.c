#include "cards.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.suit <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char* ranking_to_string(hand_ranking_t r) {
  switch (r) {
    case STRAIGHT_FLUSH:
      return "STRAIGHT_FLUSH";
    case FOUR_OF_A_KIND:
      return "FOUR_OF_A_KIND";
    case FULL_HOUSE:
      return "FULL_HOUSE";
    case FLUSH:
      return "FLUSH";
    case STRAIGHT:
      return "STRAIGHT";
    case THREE_OF_A_KIND:
      return "THREE_OF_A_KIND";
    case TWO_PAIR:
      return "TWO_PAIR";
    case PAIR:
      return "PAIR";
    case NOTHING:
      return "NOTHING";
    default:
        return "";
  }
}

char value_letter(card_t c) {
  if (c.value < 10)
    return '0' + c.value;
  else if (c.value == 10)
    return '0';
  else if (c.value == 11)
    return 'J';
  else if (c.value == 12)
    return 'Q';
  else if (c.value == 13)
    return 'K';
  else if (c.value == 14)
    return 'A';
  else
    return 'x';
}

char suit_letter(card_t c) {
  switch (c.suit) {
    case SPADES:
      return 's';
    case HEARTS:
      return 'h';
    case DIAMONDS:
      return 'd';
    case CLUBS:
      return 'c';
    default:
      return 'x';
  }
}

void print_card(card_t c) { printf("%c%c", value_letter(c), suit_letter(c)); }

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if (value_let >= '2' && value_let <= '9')
    temp.value = value_let - '0';
  else if (value_let == '0')
    temp.value = 10;
  else if (value_let == 'J')
    temp.value = 11;
  else if (value_let == 'Q')
    temp.value = 12;
  else if (value_let == 'K')
    temp.value = 13;
  else if (value_let == 'A')
    temp.value = 14;
  else
    temp.value = 100;

switch (suit_let) {
    case 's':
      temp.suit = SPADES;
      break;
    case 'h':
      temp.suit = HEARTS;
      break;
    case 'd':
      temp.suit = DIAMONDS;
      break;
    case 'c':
      temp.suit = CLUBS;
      break;
    default:
    temp.suit = 100;
      break;
  }
  assert_card_valid(temp);

  return temp;
}

card_t card_from_num(unsigned c) {
  assert(c >= 0 && c < 52);
  card_t temp;
  temp.value = c % 13 + 2;
  temp.suit = c / 13;
  return temp;
}