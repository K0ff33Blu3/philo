/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:51:08 by miricci           #+#    #+#             */
/*   Updated: 2025/05/23 15:43:48 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// mutex è un tool di pthread che permette di "bloccare" un pezzo di codice dall'essere eseguito da piu threads contemporaneamente
// funziona come una flag che segnala se il codice è eseguito da un thread in quel momento o meno
// va dichiarata copme tipo pthread_mutex_t
// va dichiarata con pthread_mutex_init(puntatore al mutex, array di attributi al mutex)
// alla fine del suo utilizzo va pulita la memoria con pthread_mutex_destroy
pthread_mutex_t mutex;

// La differenza sostanziale tra processi e threads è che più threads possono fare parte dello stesso processo, e in quanto tali condividono lo spazio di memoria 
void    *routine(void *)
{
	int	x = 0;
	int	i = -1;
	int	*x_malloc = malloc(sizeof(int));
	if (!x_malloc)
		return (NULL);
	printf("Hello form thread\n");
	while (++i < 1000000)
	{
		pthread_mutex_lock(&mutex);
        	x++;
		pthread_mutex_unlock(&mutex);
	}
	*x_malloc = x;
	return ((void *) x_malloc);
}

// se si creano thread in cicli è fondamentale non mettere pthread_create e pthread_join nello stesso ciclo
// in questo modo non si avranno mai thread che eseguono contemporaneamente e non ha piu senso usa i threads
int	main(int ac, char **av)
{
	pthread_t t[5];
	int	i;
	int	*x;

	i = 0;
	pthread_mutex_init(&mutex, NULL);    
	while (i < 5)
	{
		// pthread_create è la funzione della libreria pthread.h che crea il thread
		if (pthread_create(&t[i], NULL, &routine, NULL))     // se va a buon fine returna 0
			return (perror("Failed to create thread"), 1);
		printf("Thread %d just started\n", i);
		i++;
	}
    	i = 0;
    	while (i < 5)
	{
		// pthread_join aspetta che termini il thread specificato (tipo wait nei processi)
		// prende come argomento il thread che deve aspettare e una variabile dove mettere il valore di ritorno della funzione della routine del thread
		// le funzioni di routine sono sempre di tipo void *, per cui la variabile che contiene il return dovrà essere sempre un puntatore
		if (pthread_join(t[i], (void **) &x))
			return (4);
		printf("Thread %d just finished\n", i);
		printf("x: %d\n", *x);
		free(x);
		i++;
    	}
	pthread_mutex_destroy(&mutex);
	return (0);
}