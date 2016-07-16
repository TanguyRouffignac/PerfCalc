#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "elotable.h"

int number;
int result;
int opponents[100];
int ratings[100];

int getTheoricalScore(int value){
	int score = 0;
	for (int i = 0 ; i < number ; i ++)
		score += getProbability(value - opponents[i]);
	return score;
}

int getPerformance(int average){
	int attempt = average;
	int first;
	int second;
	if(result == 0){
		for(int i = 0 ; i < number ; i ++)
			if(opponents[i] < attempt)
				attempt = opponents[i];
		return attempt - 736;
	}
	if(result == 100 * number){
		for(int i = 0 ; i < number ; i ++)
			if(opponents[i] > attempt)
				attempt = opponents[i];
		return attempt + 736;
	}
	if(getTheoricalScore(average) >= result){
		if(getTheoricalScore(average) == result){
			return average;
		} else {
			while(getTheoricalScore(attempt) > result)
				attempt --;
			first = attempt;
			while(getTheoricalScore(attempt) >= result)
				attempt --;
			second = attempt;
			if (first != second)
				return((first + second - 1) / 2);
			else {
				if((result - getTheoricalScore(second)) < (getTheoricalScore(first) - result))
					return second;
				else
					return first;
			}
		}
	} else {
		while(getTheoricalScore(attempt) < result)
			attempt ++;
		first = attempt;
		while(getTheoricalScore(attempt) <= result)
			attempt ++;
		second = attempt;
		if (first != second)
			return((first + second - 1) / 2);
		else {
			if((result - getTheoricalScore(first)) > (getTheoricalScore(second) - result))
				return second;
			else
				return first;
		}
	}
}

int main(int argc, char * argv []){
	srand((unsigned int)time(NULL));
	if(argc == 2){
		printf("%d\n", getProbability(atoi(argv[1])));
	}
	else {
		scanf("%d\n", &number);
		scanf("%d\n", &result);
		int theor = 0;
		int sommeAdv = 0;
		for(int i = 0 ; i < number ; i ++){
			scanf("%d %d\n", &(ratings[i]), &(opponents[i]));
			sommeAdv += opponents[i];
			theor += getProbability(ratings[i] - opponents[i]);
		}
	if (theor % 100 >= 10)
		printf("Score théorique	: %d.%d\n", theor / 100, theor % 100);
	else
		printf("Score théorique : %d.0%d\n", theor / 100, theor % 100);
		printf("Performance : %d\n", getPerformance((float)sommeAdv/number));
	}
	int win = 0;
	int draw = 0;
	int loss = 0;
	for (int i = 0 ; i < 1000000 ; i ++){
		int score = 0;
		for (int j = 0 ; j < number ; j ++){
			int r = rand() % 200;
			int proba = getProbability(opponents[j] - ratings[j]);
			if (proba < 50){
				if(r > proba){
					if(r < 3 * proba){
						score += 1;
					} else {
						score += 2;
					}
				}
			} else {
				proba = 100 - proba;
				if(r < proba){
					score += 2;
				} else {
					if(r < 3 * proba)
						score += 1;
				}
			}
		}
		if (score > number)
			win ++;
		if (score == number)
			draw ++;
		if (score < number)
			loss ++;
	}
	int total = 3 * win + 2 * draw + loss;
	int th = total / 10000;
	if (total % 10000 >= 5000)
		th ++;
	if (th % 100 >= 10)
		printf("Pts de match théoriques (3/2/1) : %d.%d\n", th / 100, th % 100);
	else
		printf("Pts de match théoriques (3/2/1) : %d.0%d\n", th / 100, th % 100);
	return 0;
}
