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

  FILE * f2 = fopen("Deck.txt","r");
  
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = malloc(sizeof(*fc->decks));
  fc->n_decks = 0;

  size_t n_hands = 0;
  size_t m_hands = 0;

  deck_t ** hands = read_input(f, &n_hands, fc);
  deck_t ** decks = read_input(f2,&m_hands,fc);

  printf("n_hands: %zu, ",n_hands);
  printf("m_hands: %zu\n",m_hands);
  
  for(size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
  }
  printf("Hands in deck:\n");
  for(size_t i = 0; i < m_hands; i++) {
    print_hand(decks[i]);
    printf("\n");
  }
  
  future_cards_from_deck(decks[0], fc);
  
  
  printf("After draw from deck1:\n");
  for(size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
    printf("Sorted\n");
    qsort(hands[i]->cards, hands[i]->n_cards, sizeof(card_t*), card_ptr_comp);
    print_hand(hands[i]);
    printf("\n");
  }
  
  future_cards_from_deck(decks[1], fc);
  
  printf("After draw from deck2:\n");
  for(size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
    printf("Sorted\n");
    qsort(hands[i]->cards, hands[i]->n_cards, sizeof(card_t*), card_ptr_comp);
    print_hand(hands[i]);
    printf("\n");
  }

  printf("\nCards in future decks:\n");
  for(size_t i = 0; i < fc->n_decks; i++) {
    if(fc->decks[i].n_cards > 0) {
      printf("\ni = %zu\n", i);
      print_hand(&fc->decks[i]);
    }
  }
  printf("\n");

  for(size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);

  for(size_t i = 0; i < m_hands; i++) {
    free_deck(decks[i]);
  }
  free(decks);
  
  for (size_t i = 0; i < fc->n_decks; i++) {
    if(fc->decks[i].n_cards > 0) {
      free(fc->decks[i].cards);
    }
  }

  free(fc->decks);
  free(fc);

  fclose(f);
  fclose(f2);
  return EXIT_SUCCESS;
}


