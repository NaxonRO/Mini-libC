// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	if(size == 0) {
		return NULL;
	}
	/*
		* Luat din manualul de pe linux "man mmap"
		* PROT_READ Paginile trebuies citite
		* PROT_WRITE Paginile trebuiesc scrise
		* MAP_ANON este sinonimul pentru MAP_ANONYMOUS si face ca maparea sa nu fie sustinuta de alt fisier
		* Contentul lui este initializat la 0
		* MAP_SHARED este procesul de mapare care il face vizibil pt alte procese de mapare din aceeasi regiune
		* MAP_PRIVATE este procesul de mapare copy-onwrite, care nu il face vizibil pt alte procese de mapare din acelasi fisier
		* Daca puneam MAP_SHARED imi dadea core-dump la realloc
	*/
	// size_total adaugam un sizeof(size_t) pentru a retine cat de lung este sirul
	size_t size_total = size + sizeof(size_t);
	void *src = mmap(NULL, size_total, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	if(src == MAP_FAILED) {
		return NULL;
	}

	// Salvez lungimea la inceput si returnez cu offset ca sa nu returnez si lungimea
	*((size_t *)src) = size;
	return (void *)((char *)src + sizeof(size_t));
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	if(size == 0 || nmemb == 0) {
		return NULL;
	}
	/*
		* Luat din manualul de pe linux "man mmap"
		* PROT_READ Paginile trebuies citite
		* PROT_WRITE Paginile trebuiesc scrise
		* MAP_ANON este sinonimul pentru MAP_ANONYMOUS si face ca maparea sa nu fie sustinuta de alt fisier
		* Contentul lui este initializat la 0
		* MAP_SHARED este procesul de mapare care il face vizibil pt alte procese de mapare din aceeasi regiune
		* MAP_PRIVATE este procesul de mapare copy-onwrite, care nu il face vizibil pt alte procese de mapare din acelasi fisier
		* Daca puneam MAP_SHARED imi dadea core-dump la realloc
	*/
	// size_total adaugam un sizeof(size_t) pentru a retine cat de lung este sirul
	size_t size_total = nmemb * size + sizeof(size_t);
	void *src = mmap(NULL, size_total, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	if(src == MAP_FAILED) {
		return NULL;
	}

	// Salvez lungimea la inceput si returnez cu offset ca sa nu returnez si lungimea
	*((size_t *)src) = size * nmemb;
	return (void *)((char *)src + sizeof(size_t));
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	// Daca e deja NULL, nu mai trebuie sa eliberam memorie
	if (ptr == NULL) {
        return;
    }

	// Mutam pointerul la inceput pentru a vedea dimensiunea
    void *ptr_vechi = (char *)ptr - sizeof(size_t);
    size_t size = *((size_t *)ptr_vechi);

	// Elibram memoria incluzand si spatiul pt marime
    munmap(ptr_vechi, size + sizeof(size_t));
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	// Daca size este 0, eliberam memoria si returnam null
	if(size == 0) {
		if(ptr != NULL) {
			free(ptr);
		}
		return NULL;
	}

	// Daca ptr este deja null, alocam memoria
	if(ptr == NULL) {
		return malloc(size);
	}

	// Luam dimensiunea veche
	void *ptr_vechi = (char *)ptr - sizeof(size_t);
    size_t size_vechi = *((size_t *)ptr_vechi);

	// Flagul MREMAP_MAYMOVE permite kernel-ului sa realoce maparea la o noua adresa virtuala in caz ca nu mai este spatiu
	// Facem noul size total
	size_t size_total = size + sizeof(size_t);
	// Alocam spatiu nou prin remapare folosind acel flag
	void *nou_ptr = mremap(ptr_vechi, size_vechi + sizeof(size_t), size_total, MREMAP_MAYMOVE);
	if(nou_ptr == MAP_FAILED) {
		return NULL;
	}

	// Returnam noua memorie alocata si punem si seize-ul nou la inceput
    *((size_t *)nou_ptr) = size;
    return (void *)((char *)nou_ptr + sizeof(size_t));
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	// Daca size este 0, eliberam memoria si returnam null
		if(size == 0 || nmemb == 0) {
		if(ptr != NULL) {
			free(ptr);
		}
		return NULL;
	}
	// Daca ptr este deja null, alocam memoria
	if(ptr == NULL) {
		return calloc(nmemb, size);
	}

	// Luam dimensiunea veche
	void *ptr_vechi = (char *)ptr - sizeof(size_t);
    size_t size_vechi = *((size_t *)ptr_vechi);

	/// Flagul MREMAP_MAYMOVE permite kernel-ului sa realoce maparea la o noua adresa virtuala in caz ca nu mai este spatiu
	// Facem noul size total
	size_t size_total = nmemb * size + sizeof(size_t);
	// Alocam spatiu nou prin remapare folosind acel flag
	void *nou_ptr = mremap(ptr_vechi, size_vechi + sizeof(size_t), size_total, MREMAP_MAYMOVE);
	if(nou_ptr == MAP_FAILED) {
		return NULL;
	}

    // Returnam noua memorie alocata si punem si seize-ul nou la inceput
	*((size_t *)nou_ptr) = nmemb * size;
    return (void *)((char *)nou_ptr + sizeof(size_t));
}
