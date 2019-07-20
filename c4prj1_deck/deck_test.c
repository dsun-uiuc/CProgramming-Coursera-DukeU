#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "cards.c"
#include "deck.c"
#include "eval.c"


int main(void) {

  card_t c1 = {.value = 5, .suit = SPADES};
  card_t c2 = {.value = 14, .suit = DIAMONDS};
  
  deck_t deck_0 = {.n_cards = 0, .cards =malloc(2*sizeof(*(deck_0.cards)))};
  deck_0.n_cards = 2;
  deck_0.cards[0] = &c1;
  deck_0.cards[1] = &c2;

  deck_t * hand = make_deck_exclude(&deck_0);
  print_hand(hand);
  printf("\n");
  card_t * c3 = add_empty_card(hand);
  print_hand(hand);
  printf("\n");
  add_card_to(hand, c1);
  print_hand(hand);
  printf("\n");
  add_card_to(hand, *c3);
  print_hand(hand);
  printf("\n");

  unsigned * cm = get_match_counts(&deck_0);
  for(size_t i = 0; i < 2; i++) {
    printf("cm[%zu]: %u\n",i,cm[i]);
  }
  unsigned * cm2 = get_match_counts(hand);
  for(size_t i = 0; i < hand->n_cards; i++) {
    printf("%u ",cm2[i]);
  }
  
  free_deck(hand);
  free(deck_0.cards);
  free(cm);
  free(cm2);
 
  return EXIT_SUCCESS;
}
