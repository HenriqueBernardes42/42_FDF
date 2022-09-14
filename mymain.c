#include "my_func.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	handle_keypress(int keysym, _manage *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int render(_manage *data)
{
	_head *head;
	_next next;
	int start_x;
	int start_y;
	int last_x;
	int last_y;
	int level_x;
	int level_y;
	int collumns_size;
	int size;
	int counter;
	int i;
	int tmp_x;
	int tmp_y;



	if (data->win_ptr == NULL)
		return (1);

	start_x = 50;
	start_y = 300;
	level_x = 30;
	level_y = 5;
	counter = 1;
	i = 0;
	collumns_size = 10;
	head = create_list();
	add_last_list(head,start_x, start_y );
	next = set_line(&data->img , (_coordinates){start_x , start_y, start_x + level_x, start_y + level_y, GREEN_COLOR});
	add_last_list(head,next.x, next.y);
	while(counter < collumns_size)
	{
		next = set_line(&data->img , (_coordinates){next.x , next.y, next.x + level_x, next.y + level_y, GREEN_COLOR });
		add_last_list(head,next.x, next.y);
		++counter;
	}
	last_x = next.x;
	last_y = next.y;
	head->end = head->begin;


	size = 40;
	counter = 0;
	i = 0;

	while(counter < 10)
	{
		next = set_line(&data->img , (_coordinates){head->begin->x , head->begin->y, head->begin->x + level_x, head->begin->y + level_y - 20 , PINK_COLOR });
		head->begin->x = next.x - 2;
		head->begin->y = next.y - 2;
		next = set_line(&data->img , (_coordinates){next.x , next.y, next.x + level_x, next.y + level_y, GREEN_COLOR });
		tmp_x = next.x;
		tmp_y = next.y;
		if(counter == collumns_size - 1)
		{
			next = set_line(&data->img , (_coordinates){last_x , last_y, last_x + level_x, last_y + level_y - 20, ORANGE_COLOR });
			last_x = next.x -2;
			last_y = next.y -2;
		}
		head->begin = head->begin->next;
		++counter;
	}

	head->begin = head->end;
	counter = 0;

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	main(void)
{
	_manage	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

