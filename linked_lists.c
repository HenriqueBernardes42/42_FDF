_head *create_list()
{	
	_head *head;
	
	head = calloc(1 , sizeof(_head));
	head->begin = NULL;
	head->end = NULL;
	return head;
}

_node *create_node(int x, int y)
{
	_node *node;

	node = malloc(1 * sizeof(node));
	node->x = x;
	node->y = y;
	node->next = NULL;
	return node;
}

void *add_last_list(_head *head, int x, int y)
{
	_node *node;
	node = create_node(x,y);
	if(head->begin == NULL)
	{
		head->begin = node;
		head->end = node;
		head->end->position = 1;
	}
	else
	{
		head->end->next = node;
		head->end = head->end->next;
	}
}