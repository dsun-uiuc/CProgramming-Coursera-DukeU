#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** deck_ts = malloc(sizeof(*deck_ts));// an array of deck_t, each deck_t for a hand (a line in file)
  *n_hands = 0;
  // read each line, get the hand, add it to the deck_ts
  size_t sz = 0;
  char * line = NULL;
  deck_t * deck_temp = NULL;
  
  while( getline(&line, &sz, f) >= 0) {
    deck_temp = hand_from_string(line, fc);
    if (NULL != deck_temp) {
      deck_ts = realloc(deck_ts, (*n_hands + 1) * sizeof(*deck_ts));
      deck_ts[*n_hands] = deck_temp;
      (*n_hands)++;
      deck_temp = NULL;
    }
  }
  free(line);
  return deck_ts;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  // input: a line of string with card value and suit, possibly future cards
  // output: a pointer to a hand of card
  char * ptNl = NULL; // pointer to a newline
  ptNl = strchr(str, '\n');

  if (ptNl == str) {
    // perror("Empty line");
    return NULL;
  }
  
  if (NULL != ptNl) {
    *ptNl = '\0';
  }

  // remove leading white spaces
  size_t i = 0;
  while(str[i] == ' ') {
    i++;
  }

  deck_t * hand = malloc(sizeof(*hand));
  hand->n_cards = 0;
  hand->cards = malloc(sizeof(*(hand->cards)));

  card_t card = {.value = 0, .suit = 0};
  card_t * ptEm = NULL; // pointer to an empty card
  size_t index = 0; 
  // start to read card value/suit pairs, attention: ?10 ?11
  // need to assert if same future cards in the same hand: ?1 ?1
  size_t id_arr[52] = {0};
  while(i + 1 < strlen(str)) {
    char value = str[i];
    switch (value) {
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
    case 'J':
    case 'Q':
    case 'K':
    case 'A':
      if(str[i+1] == ' ') {
	perror("Invalid card: space after value");
	return EXIT_SUCCESS;
      }
      char suit = str[i+1];
      i += 3;
      card = card_from_letters(value, suit);
      add_card_to(hand, card);
      break;

    case '?':
    default:
      if(isdigit(str[i+2])) {
	char id[3] = {str[i+1],str[i+2],'\0'};
	index = atoi(id);
	i += 4;
      }
      else {
	index = atoi(&str[i+1]);
	i += 3;
      }
      
      id_arr[index]++;
      
      if(index > 51) {
	fprintf(stderr,"Index of future cards > 51, index: %zu\n", index);
	free_deck(hand);
	exit(EXIT_FAILURE);
      }
      
      if(id_arr[index] > 1) {
	fprintf(stderr,"Same future cards in a hand, index: %zu\n", index);
	free_deck(hand);
	exit(EXIT_FAILURE);
      }
      
      ptEm = add_empty_card(hand);
      add_future_card(fc, index, ptEm);
      break;
    }
  }

  if(hand->n_cards < 5) {
    free_deck(hand);
    perror("Hand has less than 5 cards");
    exit(EXIT_FAILURE);

  if(hand->n_cards > 52) {
    free_deck(hand);
    perror("Hand has more than 52 cards");
    exit(EXIT_FAILURE);
    }
  }
  
  return hand; 
}
