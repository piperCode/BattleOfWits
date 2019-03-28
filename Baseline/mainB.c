#include <getopt.h>

#include "game.h"

// Global seed for the random number generator
int seed = 0;

// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "s:")) != -1) {
    switch (opt) {
    case 's':
      seed = atoi(optarg);
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-s seed] \n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char *argv[]){
  parse_opts(argc, argv);
  printf("Seed : %d\n", seed);
  srand(seed);

  board B;
  init_board(&B);
  
  char mode[20];
  char chaine[20];
  printf("Choose game mode [ (1) round by round (other) all game ]: ");
  fgets(mode, sizeof(mode), stdin);
  printf("%s\n", mode);

  int comptour = 0;

  //////////////////////////////////////////////////PHASE DE JEU/////////////////////////////////////////////////
  while(count_alive(B)>=2){
    ////////INCREMENTATION DES IDEES/////////
    for (int i=0; i<NB_PLAYERS; i++){
      if((B.players[i]).isAlive)
	increase_ideas(&(B.players[i]));
    }
    ////////JOUEURS///////////
    for (int i=0; i<NB_PLAYERS; i++){
      if((B.players[i]).isAlive){
	
	(B.players[i]).isPlaying = 1;
	
	int c = select_card(B.players[i], B).idCard;
	int idAdv = select_player(B);
	
	if(c) {
	  apply_card(id2card(c, B), &(B.players[i]), &(B.players[idAdv-1]));
	  remove_card(id2card(c, B), &(B.players[i]));
	}
	
	refill_cards(&(B.players[i]));
	
	(B.players[i]).isPlaying = 0;
      }
    }
    ///////////INCREMENTATION DES IDEES//////////
    kill_players(&B);
    ///////////////////////////////////////////////////////PHASE AFFICHAGE//////////////////////////////////////////
    display_players(comptour,B);
    comptour++;
    if ( atoi(mode)==1 ){
      printf("press return to continue\n");
      fgets(chaine, sizeof(chaine), stdin);
    }
  }
  ///////////////////////////////////////////////////PHASE RESULTAT////////////////////////////////////////////
  announce_results(comptour,B);
  
  return 0;
}

