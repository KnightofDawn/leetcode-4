/* �����̫�����ˣ����ֱ߽������������Ū�˿�����Сʱ��AC�������ؼ��ĵ㣺
1. ѭ����ͨ���������Ƿ���ֹ����������ܵ�ȡֵ�ͳ�����ͬ�����Զ�INT_MIN���֣�ֱ�����鲻�У���Ҫ��HashTable��
2. ���INT_MIN��INT_MAX����������ָ������10֮���ٳ�������һ�������������ˣ�ʹ��unsigned int������΢��һ�㣬Ȼ����ѭ�����Լ�����
3. ��Ȼ��unsigned int����Ҫ��INT_MIN������ֵһ��һ����С�Ĵ��� */
struct I2iHashNode {
    int key;
    int value;
    struct I2iHashNode* next;
};

struct I2iHashTable {
    struct I2iHashNode** buckets;
    int bucketSize;
};

struct I2iHashTable* hashmap_create(int size) {
	struct I2iHashTable * table = malloc(sizeof(struct I2iHashTable));
	table->bucketSize = size;
	table->buckets = malloc(sizeof(struct I2iHashTable *) * size);
	memset(table->buckets, 0, sizeof(struct I2iHashTable *) * size);
	return table;
}

struct I2iHashNode* hashmap_get(struct I2iHashTable* table, int key) {
    int hash = key % table->bucketSize;
    while (hash < 0) hash += table->bucketSize;
    struct I2iHashNode* node = table->buckets[hash];
    while(node != NULL && node->key <= key) {
        if(node->key == key) {
        	return node;
		}
        node = node->next;
    }
    return NULL;
}
void hashmap_set(struct I2iHashTable* table, int key, int value) {
    int hash = key % table->bucketSize;
    while (hash < 0) hash += table->bucketSize;
    struct I2iHashNode* node = table->buckets[hash];
    if (node == NULL || node->key > key) {
    	struct I2iHashNode * tmp = malloc(sizeof(struct I2iHashNode));
    	tmp->key = key;
    	tmp->value = value;
    	tmp->next = node; // node != NULL ? node : NULL
    	table->buckets[hash] = tmp;
    	return;
	}
	
	if (node->key == key) {
		node->value = value;
		return;
	}

	while (node->next != NULL && node->next->key < key) {
		node = node->next;
	}
	if (node->next != NULL && node->next->key == key) {
		node->next->value = value;
		return;
	}
	struct I2iHashNode * tmp = malloc(sizeof(struct I2iHashNode));
	tmp->key = key;
	tmp->value = value;
	tmp->next = node->next;
	node->next = tmp;
}
void mymemcpy(char* d, char* s, int l) {
	if (s == d || l <= 0) return;
	int i;
	if (s > d) {
		for (i = 0 ; i < l ; i++) {
			*(d+i) = *(s+i);
		}
	} else {
		for (i = l - 1 ; i >= 0 ; i--) {
			*(d+i) = *(s+i);
		}
	}
}
char* mitoa(unsigned int i, bool neg) {
    char* res = malloc(20);
    int pos = 19;
    res[pos--] = '\0';
    if (i < 0) {
        i = -i;
    }
    if (i == 0) {
        res[pos--] = '0';
    }
    while (i != 0) {
        res[pos--] = i % 10 + '0';
        i /= 10;
    }
    if (neg) {
        res[pos--] = '-';
    }
    return res+pos+1;
}
char* fractionToDecimal(int numerator, int denominator) {
    int size = 10000;
    char* res = malloc(size);
    if (numerator == INT_MIN && denominator == 1) {
        memcpy(res, "-2147483648", 12);
        return res;
    }
    if (numerator == 0) {
        memcpy(res, "0", 2);
        return res;
    }
    int pos = 0, i;
    
    bool neg = numerator < 0 ^ denominator < 0;
    unsigned int d = (denominator > 0 ? denominator : -denominator);
    unsigned int n = (numerator > 0 ? numerator : -numerator);
    unsigned int remain = n % d;
    
    char* integer = mitoa(n / d, neg);
    
    int len = strlen(integer);
    memcpy(res, integer, len);
    pos += len;
    
    if (remain > 0) res[pos++] = '.';
    
    struct I2iHashTable* table = hashmap_create(size);

    while (remain > 0 && pos < size - 2) {
        struct I2iHashNode * node = hashmap_get(table, remain);
        if (node != NULL) {
            int start = node->value;
            mymemcpy(res+start+1, res+start, pos-start);
            res[start] = '(';
            pos++;
            res[pos++] = ')';
            break;
        }
        hashmap_set(table, remain, pos);
        int result = 0, remaintmp = remain;
        for (i = 0 ; i < 9 ; i++) {
        	remaintmp += remain;
        	if (remaintmp >= d) {
        		result++;
        		remaintmp -= d;
			}
		}
        remain = remaintmp;
        res[pos++] = result + '0';
    }
    res[pos++] = '\0';
    return res;
}