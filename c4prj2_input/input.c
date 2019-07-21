#include <stdio.h>
#include <stdlib.h>
#include "input.h"

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** deck_ts = NULL;// an array of deck_t, each deck_t for a hand (a line in file)
  n_hands = 0;
  // read each line, get the hand, add it to the deck_ts
  size_t sz = 0;
  size_t row = 0;
  char * line = NULL;
  char * ptNl = NULL;
  //deck_t * hand = alloc(sizeof(*hand));
  while( getline(&line, &sz, f) >=0) {

  /* ptNl = strchr(line, '\n');
    if (ptNl != NULL) {
      *ptNl = '\0';
    }
  */
    hand = hand_from_string(line, fc);
    n_hands++;
    // reallocate memory for new hand
    deck_ts = realloc(deck_ts, (row + 1) * sizeof(*deck_ts));
    deck_ts[row] = hand;
    row++;
    hand = NULL;
  }
  return deck_ts;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  // input: a line of string with card value and suit, possibly future cards
  // output: a pointer to a hand of card
  char * ptNl = NULL; // pointer to a newline

  ptNl = strchr(str, '\n');
  if (NULL != ptNl) {
    *ptNl = '\0';
  }

  // remove leading white spaces
  size_t i = 0;
  while(str[i] == ' ') {
    i++;
  }

  // start to read card value/suit pairs, attention: ?10 ?11
  char value = '\0'; 
  
}
