/*
	±àÂë £º GB18030
	Encoding : GB18030	
*/

int get_pre_number (void);

void Sudo (void) {
	int Pre_Number = get_pre_number();
}

int get_pre_number (void) {
	int a;

	system("cls");
	printf("\n\n      Pre-finished Number: ");
	scanf("%d", &a);

	return a;
}