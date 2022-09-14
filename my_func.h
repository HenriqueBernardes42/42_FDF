#include <stdlib.h>
#include <stdio.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 500

#define RED_COLOR		0XFF0000
#define GREEN_COLOR		0X00FF00
#define BLUE_COLOR		0X0000FF
#define PINK_COLOR		0XFF00FF
#define YELLOW_COLOR	0XFFFF00
#define WHITE_COLOR		0XFFFFFF
#define ORANGE_COLOR	0xFF5000

#define MLX_ERROR 1
#define POSITIVE 1
#define NEGATIVE 0

typedef struct coordinates
{
	int x;
	int y;
	int width;
	int height;
	int color;
} _coordinates;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct manage
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	_manage;

typedef struct next
{
	int x;
	int y;
	int last_x;
	int last_y;
	int start_x;
	int start_y;
} _next;

typedef struct create_line
{
	int decision_x;
	int decision_y;
	int fork;
	int p;
	int validate_negative;
} _create_line;

//linked list
typedef struct node
{
	int x;
	int y;
	int position;
	struct node *next;
} _node;

typedef struct head
{
	_node *begin;
	_node *end;
} _head;
///
#include "set_line.c"
#include "linked_lists.c"
