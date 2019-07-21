#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include "future.h" 

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  // check number of decks in fc, if less than index, add empty decks
  if (index +1 > fc->n_decks) {
    for (size_t i = fc->n_decks; i < index + 1; i++) {
      fc->decks = realloc(fc->decks, (i + 1) * sizeof(*fc->decks));
      fc->decks[i].cards = NULL;
      fc->decks[i].n_cards = 0;
      fc->n_decks++;
    // generate empty decks
    }
  }
    // fc->decks[index].cards[fc->decks.n_cards] = ptr;
  if(0 == fc->decks[index].n_cards) {
    fc->decks[index].cards = malloc(sizeof(*(fc->decks[index].cards)));
  }
  fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards + 1)* sizeof(*(fc->decks[index].cards))); 
  fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
  fc->decks[index].n_cards++;
}


void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  for (size_t i = 0; i < fc->n_decks; i++) {
    // check if we need card ?i: 
    if(fc->decks[i].n_cards > 0) {
      // assign deck->cards[i] to all pointers in fc->decks[i]:
      for(size_t j = 0; j < fc->decks[i].n_cards; j++) {
	// pass by value, should not pass by address!
	fc->decks[i].cards[j]->value = deck->cards[i]->value;
	fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
      }
    }
  }
}

