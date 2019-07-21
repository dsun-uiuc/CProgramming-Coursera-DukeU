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

  FILE * f = fopen("C4_testinput.txt","r");
  if (NULL == f) {
    perror("Cannot open file");
    return EXIT_FAILURE;
  }

  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = malloc(sizeof(*fc->decks));
  fc->n_decks = 0;

  size_t n_hands = 0;

  deck_t ** hands = read_input(f, &n_hands, fc);

  for(size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
  }

  future_cards_from_deck(hands[1], fc);

  for(size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
  }
  
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


