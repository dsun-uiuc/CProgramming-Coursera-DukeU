#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert((2 <= c.value && c.value <= VALUE_ACE) && (SPADES <= c.suit && c.suit <= CLUBS)); 

}

const char * ranking_to_string(hand_ranking_t r) {
  const char * rk = NULL;
  switch(r) {
  case STRAIGHT_FLUSH:
    rk = "STRAIGHT_FLUSH";
    break;
  case FOUR_OF_A_KIND:
    rk = "FOUR_OF_A_KIND";
    break;
  case FULL_HOUSE:
    rk= "FULL_HOUSE";
    break;
  case FLUSH:
    rk = "FLUSH";
    break;
  case STRAIGHT:
    rk =  "STRAIGHT";
    break;
  case THREE_OF_A_KIND:
    rk = "THREE_OF_A_KIND";
    break;
  case TWO_PAIR:
    rk = "TWO_PAIR";
    break;
  case PAIR:
    rk = "PAIR";
    break;
  case NOTHING:
    rk = "NOTHING";
    break;
  default:
    // assert(0);
    break;
  }
  return rk;
}

char value_letter(card_t c) {
  char x = '\0';
  switch(c.value) {
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    x = '0' + c.value % 10;
    break;
  case VALUE_JACK:
    x = 'J';
    break;
  case VALUE_QUEEN:
    x = 'Q';
    break;
  case VALUE_KING:
    x = 'K';
    break;
  case VALUE_ACE:
    x = 'A';
    break;
  default:
    //printf("\nInvalid card value!\n");
    // assert(0);
    break;
  }
  return x;
}


char suit_letter(card_t c) {
  char x = '\0';
  switch(c.suit) {
  case SPADES:
    x = 's';
    break;
  case HEARTS:
    x = 'h';
    break;
  case DIAMONDS:
    x = 'd';
    break;
  case CLUBS:
    x = 'c';
    break;
  default:
    // printf("\nInvalid suit!\n");
    //assert(0);
    break;
  }
  return x;
  
}

void print_card(card_t c) {
  
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  unsigned val;
  switch(value_let) {
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    val = value_let - '0';
    break;
  case '0':
    val = 10;
    break;
  case 'J':
    val = VALUE_JACK;
    break;
  case 'Q':
    val = VALUE_QUEEN;
    break;
  case 'K':
    val = VALUE_KING;
    break;
  case 'A':
    val = VALUE_ACE;
    break;
  default:
    //assert(0);
    break;
  }   
  temp.value = val;

  // convert suit_let to enum suit_t
  switch(suit_let) {
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
    // assert(0);
    break;

  }
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  assert(0<= c && c <= 51);
  switch(c / 13) {
  case 0:
    temp.suit = SPADES;
    break;
  case 1:
    temp.suit = HEARTS;
    break;
  case 2:
    temp.suit = DIAMONDS;
    break;
  case 3:
    temp.suit = CLUBS;
    break;
  default:
    break;
  }
  temp.value = c % 13 + 2;
  
  return temp;
}
