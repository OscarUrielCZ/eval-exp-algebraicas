/* Data */

typedef char *DataS;

void printDataS(DataS d) {
	printf("%s\n", d);
}

/* Stack */

typedef struct Node {
	DataS d;
	struct Node *next;
} *Stack;

Stack empty() {
	return NULL;
}

int isEmpty(Stack s) {
	return s == NULL;
}

Stack push(DataS a, Stack s) {
	Stack temp = (Stack)malloc(sizeof(struct Node));
	
	temp->d = a;
	temp->next = s;

	return temp;
}

DataS top(Stack s) {
	if(!isEmpty(s))
		return s->d;
	else
		return '\0';
}

Stack pop(Stack s) {
	if(!isEmpty(s))
		return s->next;
	else
		return NULL;
}

void printStack(Stack s) {
	while(!isEmpty(s)) {
		printDataS(top(s));
		s = pop(s);
	}
}