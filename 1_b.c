/**
 * @brief Converte una stringa in intero (data la base).
 *
 * Calcola il numero intero rappresentato dalla stringa in argomento nella base
 * (la base deve essere un numero intero nel range 2..36) in argomento:
 * − saltando gli eventuali spazi bianchi iniziali,
 * − riconoscendo l'eventuale (singolo) carattere del segno,
 * − fermandosi al raggiungimento del primo carattere non cifra nella base data (le cifre per la base 36 sono: 0,..,9,A,..,Z).
 *
 * @param s: Una stringa da convertire.
 * @param b: La base.
 * @param r: L'indirizzo dell'intero dove memorizzare il risultato.
 * @return   Restituisce 0 se 'b' non è nell’intervallo ammesso, oppure se non trova nessuna cifra valida
 *           (e in tal caso il valore all'indirizzo r non è significativo).
 *           Altrimenti restituisce 1, e scrive all'indirizzo r il numero intero rappresentato nella stringa nella base data.
 *           Non si accorge dell'eventuale overflow (restituendo in questo caso un risultato scorretto).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
 
int stoub(char *s, unsigned short b, int*r) {
	int tmp = 0;
	bool flg_segno = false;
 
	if(strlen(s) == 0 || b < 2 || b > 36){
		*r = 0;
		return 0;
	}

	for(int i = 0; i < strlen(s); i++){
		//controllo che non sia uno spazio vuoto
		if (s[i] == ' '){
			continue;
		}
		//controllo se è un segno
		if(s[i] == '-'){
			if(flg_segno == false){
				flg_segno = true;
			}
			continue;
		}

		//inizializzo la potenza
		int potenza = strlen(s)-1-i;

		int carattere;

		// controllo che non sia out of range
		if (b <= 10) {
			if (s[i] < '0' || s[i] >= '0' + b) {
				*r = 0;
				return 0;
			}
		} else {
			if ((s[i] < '0' || (s[i] > '9' && s[i] < 'A') || s[i] >= 'A' + (b - 10))) {
				*r = 0;
				return 0;
			}
		}

		// controllo se è un numero
		if (s[i] >= '0' && s[i] <= '9') {
			carattere = s[i] - '0';
		}
		// controllo se è una lettera
		else if (s[i] >= 'A' && s[i] <= 'Z') {
			carattere = s[i] - 'A' + 10;
		} else {
			*r = 0;
			return 0;
		}

		//calcolo il numero
		tmp = tmp + (carattere * (int) pow(b, potenza));
	}
	if(flg_segno == true){
		tmp = -tmp;
	}
	*r = tmp;

	return 1;
}
 
int main() {
	system("cls");
	int result;
	int value;
 
	// Test case 0: correct
	result = stoub("123", 4, &value);
	printf("Test 0: %d, %d\n", result, value);

	// Test case 1: base out of range
	result = stoub("123", 1, &value);
	printf("Test 1: %d, %d\n", result, value);

	// Test case 2: empty string
	result = stoub("", 10, &value);
	printf("Test 2: %d, %d\n", result, value);

	// Test case 3: string with spaces
	result = stoub(" 123", 10, &value);
	printf("Test 3: %d, %d\n", result, value);

	// Test case 4: string with sign
	result = stoub("-12-3", 4, &value);
	printf("Test 4: %d, %d\n", result, value);

	// Test case 5: string with non-digit character
	result = stoub("12A3", 10, &value);
	printf("Test 5: %d, %d\n", result, value);

	// Test case 6: base 36
	result = stoub("1Z", 36, &value);
	printf("Test 6: %d, %d\n", result, value);
 
	return 0;
}