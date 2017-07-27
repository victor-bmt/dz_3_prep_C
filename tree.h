struct node;

// Узел
typedef struct node {
	unsigned int key;
	unsigned char height;
	struct node* left;
	struct node* right;
} node;

// Получить высоту поддерева
unsigned char get_height(const node *p);

// Разность между высотой правого и левого поддеревьев
int bfactor(const node* p);

// Установить высоту поддерева для данного узла
void set_height(node* p);

// Правый поворот вокруг p
node* rotate_right(node* p);

// Левый поворот вокруг q
node* rotate_left(node* q);

// Балансировка узла p
node* balance(node* p);

// Вставка узла
node* insert(node *p, unsigned int k);

// Поиск узла с минимальным ключом в поддереве p
node* find_min(node* p);

// Удаление узла с минимальным ключом из поддерева p
node* remove_min(node* p);

// Удаление ключа k из дерева с корнем p
node* remove_node(node* p, unsigned int k);

// Деструктор дерева
void destruct_tree(node* p);

// Поиск ключа в дереве
int find_key(const node* p, unsigned int k);

// Глобальная переменная для передачи ошибки функции main
int error_glob;

// Печать дерева
void print_tree(const node* p);

// Функция для печати дерева на экран
unsigned int goto_next(const unsigned int string_n, const unsigned int pos, const node* p);
