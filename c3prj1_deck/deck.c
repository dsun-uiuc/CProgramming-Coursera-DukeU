#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  //this should print out the contents of a hand.
  //It should print each card and a space after each card.
  //Do not put a newline after the hand
  for (size_t i = 0; i < hand -> n_cards; i++) {
    print_card(**(hand -> cards + i));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  //This function should check if a deck contains a particular card or not.
  //If the deck does contain the card, this function should return 1. Otherwise, return 0.
  for (size_t i = 0; i < d -> n_cards; i++) {
    if(((*(d -> cards + i)) -> value == c.value) && ((*(d -> cards + i))-> suit == c.suit)) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  //This function takes in a deck and shuffles it, randomly permuting the order of the cards.
  card_t * pt = NULL; // used for swap pointers
  size_t id = 0;
  for (size_t i = 0; i < d -> n_cards; i++) {
    id = random() % (d -> n_cards - i);
    pt = *(d -> cards + i);
    *(d -> cards + i) = *(d -> cards + i + id);
    *(d -> cards + i + id) = pt;
  }
}

void assert_full_deck(deck_t * d) {
  //This function should check that the passed in deck contains every valid card exactly once.
  //If the deck has any problems, this function should fail an assert.
  for (size_t i = 0; i < 52; i++) {
    if(! deck_contains(d, card_from_num(i))) {
      printf("Missing card: ");
      print_card(card_from_num(i));
      printf("\n");
      assert(0);
      }
  }
    
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  // generate deck
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  // loop through each card
  for(size_t i = 0; i < 52; i++) {
    card_t c = card_from_num(i);
    if(deck_contains(excluded_cards, c)) {
      continue;
    }
    // if should be added
    add_card_to(deck, c);
  }

}

void add_card_to(deck_t * deck, card_t c) {
  card_t * c2 = malloc(sizeof(*c2));
  c2.value = c.value;
  c2.suit = c.suit;
  
  deck->cards = realloc(deck->cards, (deck->n_cards + 1)*sizeof(*deck->cards));
  deck->cards[deck->n_cards] = c2;
  deck->n_cards++;
  
}

card_t * add_empty_card(deck_t * deck) {
  card_t * c0 = malloc(sizeof(*c0));
  c0.value = 0;
  c0.suit = 0;

  deck->cards = realloc(deck->cards, (deck->n_cards + 1)*sizeof(*deck->cards));
  deck->cards[deck->n_cards] = c0;
  deck->n_cards++;
  return c0;
}

void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {

}
