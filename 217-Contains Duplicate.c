typedef enum BRColor { 
    RED = 0, 
    BLACK = 1 
} BRColor;

typedef struct BRNode {
    int value;
    struct BRNode * p;
    struct BRNode * left;
    struct BRNode * right;
    BRColor color;
} BRNode;

typedef struct BRTree {
	struct BRNode * root;
} BRTree;

void LeftRotate(BRTree * T, BRNode * x) {
	if (x->right == NULL) {
		return;
	}
    BRNode * y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NULL) {
        T->root = y;
    } else {
        if( x == x->p->left) {
            x->p->left = y;
        } else {
            x->p->right = y;
        }
    }
    y->left = x;
    x->p = y;
}

void RightRotate(BRTree * T, BRNode * x) {
	if (x->left == NULL) {
		return;
	}
    BRNode * y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->p = x;
    } 
    y->p = x->p;
    if (x->p == NULL) {
        T->root = y;
    } else {
        if (x == x->p->left) {
            x->p->left = y;
        } else {
            x->p->right = y;
        }
    }
    y->right = x;
    x->p = y;
}

void insertFixup(BRTree * T, BRNode * z) {
	if (z->p == NULL) {
		z->color = BLACK;
		return;
	}
	if (z->p->p == NULL) {
		return;
	}
    BRNode * y;
    //��Ϊ����Ľ���Ǻ�ɫ�ģ�����ֻ����Υ������3,�����縸���Ҳ�Ǻ�ɫ�ģ�Ҫ������
    while(z->p != NULL && z->p->color == RED) {
    	//���Ҫ����Ľ��z���丸����������
        if(z->p == z->p->p->left) {
        	// y����Ϊz���常���
            y = z->p->p->right; 
            if(y != NULL && y->color == RED) {
            	//case 1: ���y����ɫΪ��ɫ����ô��y��z�ĸ���ͬʱ��Ϊ��ɫ��Ȼ���z��
            	//�游��Ϊ��ɫ��������z���游������Υ������3,��z���Ƴ�z���游���
                z->p->color = BLACK; 
                y->color = BLACK; 
                z->p->p->color = RED; 
                z = z->p->p; 
            } else { 
                if(z == z->p->right) {
                    z = z->p;
                    LeftRotate(T, z);
                }
                //case 3: ���y����ɫΪ��ɫ������z��z�ĸ�ĸ�����㣬��ô��z��
                //���׵���ɫ��Ϊ�ڣ���z���游����ɫ��Ϊ�죬Ȼ����תz���游
                z->p->color = BLACK;
                z->p->p->color = RED;
                RightRotate(T, z->p->p);
            }
        } else {
        	//��ǰһ������Գƣ�Ҫ����Ľ��z���丸����������,ע����ȥ
            y = z->p->p->left;
            if(y != NULL && y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if(z == z->p->left) {
                    z = z->p;
                    RightRotate(T,z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                LeftRotate(T, z->p->p);
            }
        }
    }
    T->root->color = BLACK;
}

bool insert(BRTree * T, int val) { 
    if(T == NULL) { 
        T = malloc(sizeof(BRTree));
        T->root = NULL;
    }
    BRNode * y = NULL;
    BRNode * x = T->root;
    while(x != NULL) { 
        y = x;
        if(val < x->value) {
            x = x->left;
        } else if (val > x->value) {
            x = x->right;
        } else {
            return true;
        }
    }
    x = malloc(sizeof(BRNode));
    x->left = x->right = NULL;
    x->color = RED;
    x->value = val;
    x->p = y;
    if (y == NULL) {
    	T->root = x;
	} else {
		if(val < y->value) {
			y->left = x;
		} else {
			y->right = x;
		}
	}
    insertFixup(T, x);
    return false;
}

bool containsDuplicate(int* nums, int numsSize) {
	int i;
    BRTree * tree = malloc(sizeof(BRTree));
	tree->root = NULL;
    for (i = 0; i < numsSize; i++)
    {
        if (insert(tree, nums[i]))
			return true;
    }
    return false;
}