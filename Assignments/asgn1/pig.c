#include <stdio.h>
#include <stdlib.h>
#include "names.h"

int main (void) {
	typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;

	const Position pig [7] = {
		SIDE,
		SIDE,
		RAZORBACK,
		TROTTER,
		SNOUTER,
		JOWLER,
		JOWLER,
	};

	int num_players = 2;
	printf ("Number of players (2 to 10)? ");
	int scanf_result = scanf ("%d", &num_players);

	if (scanf_result < 1 || num_players < 2 || num_players > 10) {
		fprintf (stderr, "Invalid number of players. Using 2 instead.\n");
		num_players = 2;
	}

	unsigned seed = 2023;
	printf ("Random-number seed? ");
	int num_assignments = scanf ("%u", &seed);

	if (num_assignments < 1) {
		fprintf (stderr, "Invalid seed. Using 2023 instead.\n");
		seed = 2023;
	}

	srandom (seed);
	
	int player_points [10] = {0};
	int points [7] = {0, 0, 10, 10, 15, 5, 5};
	int current_player;
	int result;
	
	for (current_player = 0; player_points [current_player] < 100; current_player = (current_player + 1) % num_players) {
		printf ("%s\n", player_name [current_player]);
		do {
			result = random () % 7;
			switch (pig [result]) {
				case JOWLER:
					player_points [current_player] += points [result];
					break;
				case RAZORBACK:
					player_points [current_player] += points [result];
					break;
				case TROTTER:
					player_points [current_player] += points [result];
					break;
				case SNOUTER:
					player_points [current_player] += points [result];
					break;
				case SIDE:
					break;
			}
			printf (" rolls %d, has %d\n", points [result], player_points [current_player]);
		} while (pig [result] != SIDE && player_points [current_player] < 100);
		if (player_points [current_player] >= 100) {
			break;
		}
	}

	printf ("%s won!\n", player_name [current_player]);
		
	
}
