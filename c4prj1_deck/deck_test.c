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
  card_t * c0 = add_empty_card(hand);
  print_hand(hand);
  printf("\n");
  add_card_to(hand, c1);
  print_hand(hand);
  printf("\n");
  add_card_to(hand, *c0);
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

  card_t c3 = {.value = 8, .suit = CLUBS};
  card_t c4 = {.value = 3, .suit = HEARTS};

  card_t c5 = {.value = 11, .suit = CLUBS};
  card_t c6 = {.value = 6, .suit = HEARTS};

  deck_t ** hand_arr = malloc(2*sizeof(*hand_arr));
  deck_t hand1 = {.n_cards = 2, .cards =malloc(2*sizeof(*(hand1.cards)))};
  deck_t hand2 = {.n_cards = 4, .cards =malloc(4*sizeof(*(hand2.cards)))};

  hand1.cards[0] = &c1;
  hand1.cards[1] = &c6;

  hand2.cards[0] = &c2;
  hand2.cards[1] = &c3;
  hand2.cards[2] = &c4;
  hand2.cards[3] = &c5;
  
  hand_arr[0] = &hand1;
  hand_arr[1] = &hand2;
  
  deck_t * hand3 = build_remaining_deck(hand_arr, 2);
  print_hand(hand3);
  printf("\n");
  
  free_deck(hand);
  free_deck(hand3);
  free(deck_0.cards);
  free(hand1.cards);
  free(hand2.cards);
  free(cm);
  free(cm2);
  free(hand_arr);
 
  return EXIT_SUCCESS;
}
