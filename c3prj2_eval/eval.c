#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const *cp1 = vp1;
  const card_t * const *cp2 = vp2;
  // const card_t * cp1 = *c1;
  //const card_t * cp2 = *c2;
  int result = 0;
  //int v1 = (**cp1).value;
  //int v2 = (**cp2).value;
  if ((*cp1)->value == (*cp2)->value)
    result = (int)(*cp2)->suit - (int)(*cp1)->suit;
  else
    result = (int)(*cp2)->value - (int)(*cp1)->value;
  //return ((**cp2).value == (**cp1).value) ? ((**cp2).suit - (**cp1).suit) : ((**cp2).value - (**cp1).value);
  return result;
}

suit_t flush_suit(deck_t * hand) {
  size_t ns =0, nh = 0, nd = 0, nc = 0;
  for (size_t i = 0; i < hand-> n_cards; i++) {
    switch ((*(hand->cards + i))->suit) {
    case SPADES: ns++; break;
    case HEARTS: nh++; break;
    case DIAMONDS: nd++; break;
    case CLUBS: nc++; break;
    default: break;
    }
  }
  if (ns >= 5) return SPADES;
  else if (nh >= 5) return HEARTS;
  else if (nd >= 5) return DIAMONDS;
  else if (nc >= 5) return CLUBS;
  else return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned temp = arr[0];
  for (size_t i = 1; i < n; i++) {
    if (temp < arr[i]) {
      temp = arr[i];
    }
  }
  return temp;
}

size_t get_match_index(unsigned * match_counts, size_t n, unsigned n_of_akind){
  size_t i = 0;
  while(match_counts[i] != n_of_akind && i < n) i++;
  if (i == n) {
    printf("Error! could not find index for n_of_akind\n");
    assert(0);
  }
  return i;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  ssize_t i = 0;
  for ( ; i < hand->n_cards; i++) {
    if (match_counts[i] > 1 && (*(hand->cards + i))->value != (*(hand->cards + match_idx))->value) {
      return i;
    }
  }
  return -1;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int found = 0;
  if (fs == NUM_SUITS) {
    //regular straight
    size_t flag = 0; // found flag: 0: nothing, 1: found next number
    // 2: find second number, ..., 4: found all
    size_t id = index;
    for (size_t i = id; i + 3 - flag < hand->n_cards; i++) {
      if((*(hand->cards + id))->value - (*(hand->cards + i))->value == 1) {
	flag++;
	if (flag == 4) {
	  found = 1;
	  break;
	}
	id = i; // update compared number
      }
    }
    //check Ace-low straight
    if (found == 0 && (*(hand->cards + index))->value == VALUE_ACE) {
      flag = 0;
      unsigned target = 2; // need to find 2, 3, 4, 5
      for (size_t i = hand->n_cards - 1; i > index + 3 - flag; i--) {
	if((*(hand->cards + i))->value == target) {
	  flag++;
	  if (flag == 4) {
	    found = -1;
	    break;
	  }
	  target++; // update target
	}
      }
    }
  }
  else { //flush straight
    if ((*(hand->cards + index))->suit == fs) {
      size_t flag = 0; // flag
      size_t id = index;
      for (size_t i = id; i + 3 - flag < hand->n_cards; i++) {
	if ((*(hand->cards + i))->suit != fs) continue;
	if((*(hand->cards + id))->value - (*(hand->cards + i))->value == 1) {
	  flag++;
	  if (flag == 4) {
	    found = 1;
	    break;
	  }
	  id = i; // update compared number
	}
      }
      //check Ace-low straight
      if (found == 0 && (*(hand->cards + index))->value == VALUE_ACE) {
	flag = 0;
	unsigned target = 2; // need to find 2, 3, 4, 5
	for (size_t i = hand->n_cards - 1; i > index + 3 - flag; i--) {
	  if ((*(hand->cards + i))->suit != fs) continue;
	  if((*(hand->cards + i))->value == target) {
	    flag++;
	    if (flag == 4) {
	      found = -1;
	      break;
	    }
	    target++; // update target
	  }
	}
      }
    }
  }
  return found;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  // printf("idx = %lu, n = %u \n", idx, n);
  if (n == 0) n = 1;
  hand_eval_t ans = {.ranking = what, .cards = {NULL}};
  //ans.ranking = what;
  for (size_t i = 0; i < n; i++) {
    ans.cards[i] = *(hand->cards + idx + i);
  }
  size_t id_c = 0; // starting index for the rest cards
  for (size_t i = n; i < 5; i++) {
    // printf("i = %lu, ",i);
    for (size_t j = id_c; j < hand->n_cards; j++) {
      //  printf("j = %lu, ", j);
      if (idx <= j && j <= idx + n - 1)
	continue;
      ans.cards[i] = *(hand->cards + j);
      // printf("Card: ");
      // print_card(*ans.cards[i]);
      // printf("Here \n");
      id_c = j + 1;
      break;
    }
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(card_t*), card_ptr_comp);
  qsort(hand2->cards, hand1->n_cards, sizeof(card_t*), card_ptr_comp);

  hand_eval_t h1 = evaluate_hand(hand1);
  hand_eval_t h2 = evaluate_hand(hand2);

  int result = 0;
  if (h1.ranking < h2.ranking) {//h1 win
    result = 1;
  }
  else if (h1.ranking > h2.ranking) {//h2 win
    result = -1;
  }
  else {// tie, compare value
    for (size_t i = 0; i < 5; i++) {
      if (h1.cards[i]->value > h2.cards[i]->value) {
	result = 1;
	break;
      }
      else if (h1.cards[i]->value < h2.cards[i]->value) {
	result = -1;
	break;
      }
    }
  }
  return result;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
