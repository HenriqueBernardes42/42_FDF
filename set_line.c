void	img_pix_put(t_img *img, int x, int y, int color);

_next draw_line_lower_45(_create_line line, _coordinates position, t_img *img, int limit)
{
	_next next;
	int y;

	y = 0;
	line.p = (2 * line.decision_y) - (2 * line.decision_x);
	while(position.x < limit)
	{
		if(line.p <= 0)
		{
			++position.x;
			line.p = line.p + (2 * line.decision_y);
		}
		else
		{
			++y;
			++position.x;
			line.p = line.p + (2 * line.decision_y) - (2 * line.decision_x);
		}
		if(line.validate_negative == POSITIVE)
			img_pix_put(img, position.x, (WINDOW_HEIGHT - position.y) - y, position.color);
		else
			img_pix_put(img, position.x, (WINDOW_HEIGHT - position.y) + y, position.color);
	}
	if(line.validate_negative == POSITIVE)
		next.y = position.y + y + 1;
	else
		next.y = position.y - y + 1;
	next.x = position.x;
	
	return next;
}

_next draw_line_greater_45(_create_line line, _coordinates position, t_img *img, int limit)
{
	_next next;
	int y;

	y = 0;
	line.p = (2 * line.decision_x) - (2 * line.decision_y);
	while((position.x) < limit)
	{
		if(line.p > 0)
		{
			++y;
			++position.x;
			line.p = line.p + (2 * line.decision_x) - (2 * line.decision_y);
		}
		else
		{
			++y;
			line.p = line.p + (2 * line.decision_x);
		}
		if(line.validate_negative == POSITIVE)
			img_pix_put(img, position.x, (WINDOW_HEIGHT - position.y) - y, position.color);
		else
			img_pix_put(img, position.x, (WINDOW_HEIGHT - position.y) + y, position.color);
	}
	if(line.validate_negative == POSITIVE)
		next.y = position.y + y + 1;
	else
		next.y = position.y - y + 1;
	next.x = position.x;
	
	return next;
}

_next set_line(t_img *img, _coordinates position)
{
	_create_line line;
	_next next;

	line.decision_x = position.width - position.x;
	line.decision_y = position.height - position.y;
	img_pix_put(img, position.width, WINDOW_HEIGHT - position.height, position.color);
	line.validate_negative = POSITIVE;
	if(line.decision_y < 0)
	{
		line.decision_y = line.decision_y * -1;
		line.validate_negative = NEGATIVE;
	}
	line.fork = line.decision_y / line.decision_x;
	if(line.fork >= 1)
	{
		next = draw_line_greater_45(line, position, img, position.width);
	}
	else
	{
		next = draw_line_lower_45(line, position, img, position.width);
	}
	return next;
}

