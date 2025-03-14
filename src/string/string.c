// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	/// Luat din laborator
	char *d;

	for (d = destination; *source != '\0'; source++, d++)
		*d = *source;
	/* Also place NUL byte. */
	*d = *source;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	char *d = destination;
	size_t k = 0;

	// Am adaugat un parametru pentru a retine cat trebuie sa copiem
	for (k = 0; k < len; source++, d++, k++)
		*d = *source;
	/* Also place NUL byte. */
	d++;
	*d = '\0';

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	/// Luat din laborator
	char *d = destination;
    while (*d != '\0') {
        d++;
    }
    while (*source != '\0') {
		*d = *source;
		d++;
		source++;
    }
    *d = '\0';

    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	char *d = destination;
	size_t k = 0;
    while (*d != '\0') {
        d++;
    }

	// Am adaugat un parametru pentru a putea sa retinem cat trebuie sa lipim
    while (k < len && *source != '\0') {
		*d = *source;
		d++;
		k++;
		source++;
	}
    *d = '\0';

    return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	// Verificam pana cand unul dintre ele este null sau au 2 caractere de pe aceeasi poz diferite
	// Returnam suma daca se intampla acest lucru
	while(*str1 != '\0' && *str2 != '\0') {
		if(*str1 != *str2) {
			return (int)(*str1 - *str2);
		}
		str1++;
		str2++;
	}
	// Daca s-au ajuns ambele la null, returnam 0 fiindca sunt sirurile egale
	if(*str1 == '\0' && *str2 == '\0') {
		return 0;
	}
	return (int)(*str1 - *str2);
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	// Fata de strcmp am adaugat un parametru pentru a retine cat trebuie sa verificam
	size_t k = 0;
	while(k < len && *str1 != '\0' && *str2 != '\0') {
		if(*str1 != *str2) {
			return (int)(*str1 - *str2);
		}
		str1++;
		str2++;
		k++;
	}
	if(k == len || (*str1 == '\0' && *str2 == '\0')) {
		return 0;
	}
	return (int)(*str1 - *str2);
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	// Cat timp sirul este diferit de null, verificam de la stanga la dreapta daca este egal cu characterul
	// Daca da, returnam pointerul catre character
	while(*str != '\0') {
		if(c == *str) {
			return (char*)str;
		}
		str++;
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	// La fel ca la strchr, insa mergem mai intai la final si dupa o luam invers
	while(*str != '\0') {
		str++;
	}
	str--;
	while(*str != '\0') {
		if(c == *str) {
			return (char*)str;
		}
		str--;
	}
	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	// Luam din haystack fiecare character, vedem daca se potriveste cu primul din needle
	// Daca da, verificam pana cand needle ajunge la final, ceea ce inseamna ca returnam prima poz
	// Daca nu, trecem la urmatorul character si secventa din haystack
	while(*haystack != '\0') {
		if(*haystack == *needle) {
			const char *a = haystack;
			const char *b = needle;
			while(*a != '\0' && *b != '\0' && *a == *b) {
				a++;
				b++;
			}
			if(*b == '\0') {
				return (char *)haystack;
			}
		}
		haystack++;
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	// Acelasi lucru, numai ca returnam ultima secventa
	const char *ultimul = NULL;
	while(*haystack != '\0') {
		if(*haystack == *needle) {
			const char *a = haystack;
			const char *b = needle;
			while(*a != '\0' && *b != '\0' && *a == *b) {
				a++;
				b++;
			}
			if(*b == '\0') {
				ultimul = haystack;
			}
		}
		haystack++;
	}
	return (char *)ultimul;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	// In aceasta implementare, lipim fiecare octet, asemanator ca la strcpy
	char *a = (char *)destination;
	const char *b = (const char *)source;
	size_t i = 0;
	for(i = 0; i < num; i++) {
		*(a + i) = *(b + i);
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	char *a = (char *)destination;
	const char *b = (const char *)source;
	size_t i = 0;
	// Daca sunt la fel sau num == 0, returnam direct destinatia
	if(a == b || num == 0)
		return destination;
	// Daca destinatia este dupa sursa si se afla si o suprapunere a datelor, copiem de la final spre inceput
	if(a > b && (size_t)(a - b) < num) {
		for(i = num - 1; i > 0; i--) {
			*(a + i) = *(b + i);
		}
	}
	// Daca nu exista suprapunere, copiem datele de la inceput spre final
	for(i = 0; i < num; i++) {
		*(a + i) = *(b + i);
	}
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	const char *a = (const char *)ptr1;
	const char *b = (const char *)ptr2;
	size_t i = 0;
	// Parcurgem fiecare octet si comparam variabilele pana gasim o diferenta
	// Returnam diferenta dintre primul octet diferit
	// Daca toti octetii sunt egali, returnam 0
	for(i = 0; i < num; i++) {
		if(*(a + i) != *(b + i)) {
			return (int)(*(a + i) - *(b + i));
		}
	}
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	char *a = (char *)source;
	size_t i = 0;
	// Umplem memoria cu valoarea specificata, octet cu octet
	// Returnam pointerul de la memorie
	for(i = 0; i < num; i++) {
		*(a + i) = (char)value;
	}
	return source;
}
