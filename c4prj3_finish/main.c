#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if (argc < 2) {
    perror("Not enough command line arguments");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1],"r");
  if (NULL == f) {
    perror("Cannot open file");
    return EXIT_FAILURE;
  }

  // read hands
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = malloc(sizeof(*fc->decks));
  fc->n_decks = 0;

  size_t n_hands = 0;
  deck_t ** hands = read_input(f, &n_hands, fc);
  deck_t * deck_remain = build_remaining_deck(hands, n_hands);
  unsigned * win_count = malloc((n_hands + 1) * sizeof(*win_count));

  for (size_t i = 0; i < n_hands + 1; i++) {
    win_count[i] = 0;
  }
  unsigned num_trials = (3 == argc) ? atoi(argv[2]) : 10000;

  size_t round = 0;
  while(round < num_trials) {
    shuffle(deck_remain);
    future_cards_from_deck(deck_remain, fc);
    deck_t * temp_win = hands[0];
    //    print_hand(hands[0]);
    // printf(" ");
    //print_hand(hands[1]);
    // printf("\n");
    size_t win_hand = 0;
    size_t n_tie = 0;
    for(size_t i = 1; i < n_hands; i++) {
      int result = compare_hands(hands[i], temp_win);
      
      // printf("Compare result: %d\n",result);
      if (1 == result) {
	temp_win = hands[i];
	win_hand = i;
	n_tie = 0;
      }
      else if(0 == result) {
	n_tie++;
      }
    }
    if (n_hands - 1 == n_tie) {
      win_count[n_hands]++; // tie
    }
    else {
      win_count[win_hand]++;
    }
    round++;
  } 

  // print result


  for(size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, win_count[i], num_trials, 100.0*win_count[i]/(float)num_trials);
  }
  printf("And there were %u ties\n", win_count[n_hands]);

  free(win_count);
  free_deck(deck_remain);
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

  fclose(f);
  return EXIT_SUCCESS;
}
