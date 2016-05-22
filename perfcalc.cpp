#include <stdio.h>
#include <stdlib.h>
#include "elotable.h"

int number;
int result;
int opponents[100];
int rating;

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
	if(argc == 2){
		printf("%d\n", getProbability(atoi(argv[1])));
	}
	else {
		scanf("%d\n", &number);
		scanf("%d\n", &result);
		int theor = 0;
		int sommeAdv = 0;
		for(int i = 0 ; i < number ; i ++){
			scanf("%d %d\n", &rating, &(opponents[i]));
			sommeAdv += opponents[i];
			theor += getProbability(rating - opponents[i]);
		}
		printf("Score theorique : %d\n", theor);
		printf("Performance : %d\n", getPerformance((float)sommeAdv/number));
	}
	return 0;
}
