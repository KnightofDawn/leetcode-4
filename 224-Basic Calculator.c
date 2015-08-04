/* ��������ʱ��û�п���ֻ��+-���ֲ�����������ֱ�Ӿ�д����Basic Calculator II�Ĵ��룬
�������һ����������ȴ���˼�����󣬲�֪��ԭ�򣬶�����ֱ����Basic Calculator II���ύ�ǿ��Թ��ģ�
����Basic Calculator II�Ĳ�������û�и��ǵ��ɣ�ɾ���˳��Ĵ�����ܹ� */
void pushNum(int* stack, int* top, int num) {
    if (*top > 1 && stack[*top-1] == '+' || stack[*top-1] == '-') {
        char c = stack[--(*top)];
        int n = stack[--(*top)];
        stack[(*top)++] = c == '+' ? n + num : n - num;
    } else {
    	stack[(*top)++] = num;
	}
}
int calculate(char* s) {
    int size = 10000, top = 0, num = 0;
    bool hasNum = false;
    int stack[size];
    char op;
    
    while (*s != '\0') {
        if (!isdigit(*s) && *s != ' ') {
            if (hasNum) {
            	// if we use num != 0 instand of hasNum, when the input is 0, it will be confused
                pushNum(stack, &top, num);
            	num = 0;
            	hasNum = false;
            }
            if (*s == ')') {
                int n = stack[top-1];
                top = top-2;
                pushNum(stack, &top, n);
            } else {
                stack[top++] = *s;
            }
        } else if (isdigit(*s)) {
            num = num * 10 + *s - '0';
            hasNum = true;
        }
        s++;
    }
    if (hasNum) {
        pushNum(stack, &top, num);
    }
    return stack[0];
}