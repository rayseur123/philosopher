#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data_test
{
	pthread_mutex_t	mutex;
	int				data;
}	t_data_test;

void	*print_ten_time(void *dat)
{
	t_data_test	*data;

	data = (t_data_test *)dat;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		printf("thread : %ld\ndata : %d\n", pthread_self(), data->data);
		data->data++;
		pthread_mutex_unlock(&data->mutex);
		usleep(1);
	}
	return (NULL);
}

int	main(void)
{
	t_data_test data;
	pthread_t	thread1;
	pthread_t	thread2;

	data.data = 0;
	if (pthread_mutex_init(&data.mutex, NULL)
		|| pthread_create(&thread1, NULL, &print_ten_time, (void *)&data)
		|| pthread_create(&thread2, NULL, &print_ten_time, (void *)&data))
		return (1);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&data.mutex);

	return (0);
}