#include "caltrain.h"
#include <stdio.h>


void
station_init(struct station *station)
{
	station->availableSeats = 0;
    station->waitingPass = 0;
    station->boarded = 0;
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->trainarrived, NULL);
    pthread_cond_init(&station->passboarded, NULL);
}

void
station_load_train(struct station *station, int count)
{
    pthread_mutex_lock(&station->mutex);

    if (count > 0 && station->waitingPass > 0){
        station->availableSeats = count;
        pthread_cond_broadcast(&station->trainarrived);
        pthread_cond_wait(&station->passboarded,&station->mutex);
    }
    station->availableSeats = 0;
    pthread_mutex_unlock(&station->mutex);
}

void
station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->mutex);
    station->waitingPass ++;
    while (station->availableSeats == 0) {
        pthread_cond_wait(&station->trainarrived, &station->mutex);
    }
    station->availableSeats --;
    station->waitingPass --;
    station->boarded ++;
    pthread_mutex_unlock(&station->mutex);
}

void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->mutex);
    station->boarded --;

    if ((station->availableSeats == 0 || station->waitingPass == 0) && station->boarded == 0) {
        pthread_cond_signal(&station->passboarded);
    }
    pthread_mutex_unlock(&station->mutex);
}
