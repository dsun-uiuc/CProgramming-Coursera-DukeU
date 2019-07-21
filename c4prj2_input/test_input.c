#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
#include "cards.c"
#include "deck.c"
#include "eval.c"
#include "future.c"
#include "input.c"


int main(void) {

  // test empty line
  //char str[] = "As Qh Jd Jc 0d 8c 2d Kc Ah 0h 8c ?1 ?0 ?10 ?5 Kc";
  //char str2[] = "Ks Jh 0d 7c 6d Qc 2h 3c Ad 0h 4d 5c";
  FILE * f = fopen("C4_testinput.txt","r");
  if (NULL == f) {
    perror("Cannot open file");
    return EXIT_FAILURE;
  }

  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = malloc(sizeof(*fc->decks));
  fc->n_decks = 0;

  size_t n_hands = 0;

  //deck_t ** hands = malloc(sizeof(*hands));
  deck_t ** hands = read_input(f, &n_hands, fc);

  //deck_t * hand = hand_from_string(str, fc);
  //deck_t * hand2 = hand_from_string(str2, fc);

  for(size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
  }

  for(size_t i = 0; i < fc->n_decks; i++) {
    printf("\nindex: %zu, # of cards: %zu", i, fc->decks[i].n_cards);
  }

  future_cards_from_deck(hands[1], fc);

  printf("\nCards after draw future decks:\n");
  print_hand(hands[0]);

  printf("\nCards in future decks:\n");
  for(size_t i = 0; i < fc->n_decks; i++) {
    if(fc->decks[i].n_cards > 0) {
      print_hand(&fc->decks[i]);
    }
  }
  printf("\n");

  for(size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);

  for (size_t i = 0; i < fc->n_decks; i++) {
    if(fc->decks[i].n_cards > 0) {
      free(fc->decks[i].cards);
    }
  }

  free(fc->decks);
  free(fc);

  return EXIT_SUCCESS;
}


