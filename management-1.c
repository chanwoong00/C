#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#define SIZE 30

typedef struct customer{
	char name[SIZE];
	char gender; //F, M
	int age;
	char credit[SIZE]; //normal, vip, vvip 
	struct customer *link;
}customer;
//��ǰ�� ����ü(��ü) {��ǰ��, ����, ���� ��ǰ�� ����}
typedef struct product{
	char name[SIZE];
	int price;
	int remaining; 
	struct product *link;
}product;
//�ֹ��� ����ü(����) {���̸�, ��ǰ��, �ֹ� ����, �ֹ� ����}
typedef struct order{
	char customer_name[SIZE];
	char product_name[SIZE];
	int number;
	char date[SIZE]; //YYYYMMDD
	struct order *link;
}order;

typedef customer* customer_pointer;
typedef product* product_pointer;
typedef order* order_pointer;

void create_product();
void change_product();
void delete_product();
void show_product();
void search_product();

void create_customer();
void change_customer();
void delete_customer();
void show_customer();
void search_customer();

void create_order();
void change_order();
void delete_order();
void show_order();
void show_detail_order();
void search_order();
customer_pointer check_customer(char name[]);
product_pointer check_product(char name[]);

void read_file();

void write_customer_file();
void write_product_file();
void write_order_file();

void read_customer_file();
void read_product_file();
void read_order_file();

customer_pointer customer_list = NULL;
product_pointer product_list = NULL;
order_pointer order_list = NULL;

void main() {
	int cmd1, cmd2;
	
	read_customer_file();
	read_product_file();
	read_order_file();
	
	show_product();
	show_customer();
	show_order();
	
	while(1) {
		printf("---------------------------------------------------\n");
		printf("������ �Ͻñ� ���Ͻʴϱ�?\n");
		printf("1)��ǰ 2)�� 3)�ֹ� 4)����\n");
		scanf("%d", &cmd1);
		
		switch(cmd1) {
			case 1: //��ǰ
				printf("� �۾��� �Ͻñ� ���Ͻʴϱ�?\n");
				printf("1)��ǰ �߰� 2)��ǰ ���� 3)��ǰ ���� 4)��ǰ ��� ��� 5)��ǰ �˻�\n");
				scanf("%d", &cmd2);
				
				switch(cmd2) {
					case 1: //��ǰ �߰�
						create_product();
						break;
					
					case 2: //��ǰ ���� 
						change_product();
						break;
						
					case 3: //��ǰ ����
						delete_product();
						break;
						
					case 4: //��ǰ ��� ��� 
						show_product();
						break; 
						
					case 5: //��ǰ �˻�  
						search_product();
						break; 
				} 
				break;
				
			case 2: //�� 
				printf("� �۾��� �Ͻñ� ���Ͻʴϱ�?\n");
				printf("1)�� ��� 2�� ���� 3)�� ���� 4)�� ��� ��� 5)�� �˻�\n");
				scanf("%d", &cmd2);
				
				switch(cmd2) {
					case 1: //�� �߰�
						create_customer();
						break;
					
					case 2: //�� ���� 
						change_customer();
						break;
						
					case 3: //�� ����
						delete_customer();
						break;
						
					case 4: //�� ��� ��� 
						show_customer();
						break; 
					
					case 5: //�� �˻�
						search_customer();
						break; 
				} 
				break; 
				
			case 3: //�ֹ� 
				printf("� �۾��� �Ͻñ� ���Ͻʴϱ�?\n");
				printf("1)�ֹ� ���� 2)�ֹ� ���� 3)�ֹ� ���� 4)�ֹ� ��� ��� 5)�ֹ� �� ���� ��� 6)�ֹ� �˻�\n");
				scanf("%d", &cmd2);
				
				switch(cmd2) {
					case 1: //�ֹ� �߰�
						create_order();
						break;
					
					case 2: //�ֹ� ���� 
						change_order();
						break;
						
					case 3: //�ֹ� ����
						delete_order();
						break;
						
					case 4: //�ֹ� ��� ��� 
						show_order();
						break; 
						
					case 5: //�ֹ� �� ��� ��� 
						show_detail_order();
						break; 
					
					case 6: //�� �˻�
						search_order();
						break; 
				} 
				break; 
				
			case 4:
				printf("�ȳ����輼��~");
				write_customer_file();
				write_product_file();
				write_order_file();
				exit(1);
		} 
		
		printf("---------------------------------------------------\n");
	}
}

void create_product() {
	product_pointer new_product, p;
    new_product = (product_pointer) malloc(sizeof(product)); //�޸� ���� �Ҵ� 

    if(new_product == NULL) {
        printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.\n");
        return;
    }

    // �� ��ǰ�� ������ ����ڷκ��� �Է�
    printf("��ǰ���� �Է��ϼ���: ");
    scanf("%s", new_product->name);
    printf("������ �Է��ϼ���: ");
    scanf("%d", &new_product->price) ;
    printf("���� ��ǰ ������ �Է��ϼ���: ");
    scanf("%d", &new_product->remaining);

    new_product->link = NULL;

    if (product_list == NULL) { // ����Ʈ�� ��� �ִٸ�, �� ��ǰ�� ����Ʈ�� ó������ ����
        product_list = new_product;
    } 
	else { // ����Ʈ�� ������ ��ġ�� �̵� �� �� ��ǰ�� �߰� 
        p = product_list;
        
		while (p->link != NULL) {
            p = p->link;
        }
        
        p->link = new_product; //�������� ���ο� product�� �߰� 
    }
    
    printf("�� ��ǰ�� �߰��Ǿ����ϴ�.\n");
}

void change_product() {
	product_pointer p = product_list;
	char target_name[SIZE]; //�ٲٷ��� ��ǰ�� �̸� 
	char target_attribute[SIZE]; //�ٲٷ��� �Ӽ� 
	char new_value[SIZE]; //���ο� �� 


	printf("������ ��ǰ�� �̸��� �Է��ϼ���: ");
	scanf("%s", target_name);

	printf("������ �׸��� �����ϼ��� (��ǰ��, ����, ���� ����): ");
	scanf("%s", target_attribute);

	while (p) { //���� ����Ʈ ��ȸ 
    	if (strcmp(p->name, target_name) == 0) { //���� �ش� ��ǰ�� ã�Ҵٸ� 
       		if (strcmp(target_attribute, "��ǰ��") == 0) { //���� ��ġ���� �Ӽ��� ��ǰ���̶�� 
            	printf("���ο� ��ǰ���� �Է��ϼ���: ");
            	scanf("%s", new_value);
            	strcpy(p->name, new_value);
            	printf("��ǰ���� ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "����") == 0) { //���� ��ġ���� �Ӽ����� �����̶�� 
            	printf("���ο� ������ �Է��ϼ���: ");
            	scanf("%s", new_value);
            	p->price = atoi(new_value);
            	printf("������ ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "���� ����") == 0) { //���� ��ġ���� �Ӽ����� ������� 
            	printf("���� ������ �Է��ϼ���: ");
            	scanf("%s", new_value);
            	p->remaining = atoi(new_value);
            	printf("���� ������ ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else {
            	printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            	break;
        	}
        	break;
    	} 
		
		else { //���� ���� 
        	p = p->link;
    	}
	}
	
	if (!p->link) { //���� ��ȸ�ߴµ��� ���� 
    	printf("�ش� ��ǰ�� ã�� �� �����ϴ�.\n");
	}
}

void delete_product() {
    char target_name[SIZE];
    product_pointer p = product_list, temp = NULL, prev = NULL;

    printf("������ ��ǰ�� �̸��� �����ΰ���?\n ");
    scanf("%s", target_name);

    if (p == NULL) {
        printf("���� ���Ḯ��Ʈ�� ��ǰ�� �����ϴ�.\n");
        return;
    }

    if (strcmp(p->name, target_name) == 0) { // ������� ��尡 ù ��° ����� ���
        product_list = p->link;
        free(p);
        return;
    }

    prev = p;
    p = p->link;

    while (p != NULL) { //���� ����Ʈ ��ȸ
        if (strcmp(p->name, target_name) == 0) { //���� ��ǰ�� ã��
            temp = p;
            prev->link = p->link;
            free(temp); // �޸� ��ȯ
            return;
        }
        
        else {
        	prev = p;
        	p = p->link;
		}
    }
    printf("��ǰ�� ã�� �� �����ϴ�.\n");
}

void show_product() {
  product_pointer p = product_list;
  while(p != NULL) { //��ȸ 
    printf("��ǰ �̸�: %s \n", p->name);
    printf("��ǰ ����: %d \n", p->price);
    printf("���� ����: %d \n", p->remaining);

    p = p->link;
  }
}

void search_product() {
	product_pointer p = product_list;
	char target_name[SIZE];
	
	printf("ã�� �ִ� ��ǰ�� �̸��� �����ΰ���?\n");
	scanf("%s", target_name);
	
	while(p != NULL) {
		if(strcmp(p->name, target_name) == 0) {
			printf("��ǰ �̸�: %s \n", p->name);
   			printf("��ǰ ����: %d \n", p->price);
    		printf("���� ����: %d \n", p->remaining);
    		
    		return; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	printf("�׷� ��ǰ�� �������� �ʽ��ϴ�.\n");
}



void create_customer() {
	customer_pointer new_customer, current_customer;
    new_customer = (customer_pointer) malloc(sizeof(customer)); //�޸� ���� �Ҵ� 

    if(new_customer == NULL) {
        printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.\n");
        return;
    }

    // �� ���� ������ ����ڷκ��� �Է�
    printf("���� �̸� �Է��ϼ���: ");
    scanf("%s", new_customer->name);
    printf("������ �Է��ϼ���: ");
    fflush(stdin);
    scanf("%c", &new_customer->gender);
    printf("���̸� �Է��ϼ���: ");
    scanf("%d", &new_customer->age);
	printf("����� �Է��ϼ���: ");
    scanf("%s", new_customer->credit); 

    new_customer->link = NULL;

    if (customer_list == NULL) { // ����Ʈ�� ��� �ִٸ�, �� ��ǰ�� ����Ʈ�� ó������ ����
        customer_list = new_customer;
    } 
	else { // ����Ʈ�� ������ ��ġ�� �̵� �� �� ��ǰ�� �߰� 
        current_customer = customer_list;
        
		while (current_customer->link != NULL) {
            current_customer = current_customer->link;
        }
        
        current_customer->link = new_customer; //�������� ���ο� customer�� �߰� 
    }
    
    printf("�� ���� �߰��Ǿ����ϴ�.\n");
}

void change_customer() {
	customer_pointer p = customer_list;
	char target_name[SIZE]; //�ٲٷ��� ���� �̸� 
	char target_attribute[SIZE]; //�ٲٷ��� �Ӽ� 
	char new_value[SIZE]; //���ο� �� 


	printf("������ ���� �̸��� �Է��ϼ���: ");
	scanf("%s", target_name);

	printf("������ �׸��� �����ϼ��� (�̸�, ����, ���): ");
	scanf("%s", target_attribute);

	while (p) { //���� ����Ʈ ��ȸ 
    	if (strcmp(p->name, target_name) == 0) { //���� �ش� ��ǰ�� ã�Ҵٸ� 
       		if (strcmp(target_attribute, "�̸�") == 0) { //���� ��ġ���� �Ӽ��� �̸��̶�� 
            	printf("���ο� �̸��� �Է��ϼ���: ");
            	scanf("%s", new_value);
            	strcpy(p->name, new_value);
            	printf("�̸��� ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "����") == 0) { //���� ��ġ���� �Ӽ����� ���� ��� 
            	printf("���ο� ���� �Է��ϼ���: ");
            	scanf("%s", new_value);
            	p->age = atoi(new_value);
            	printf("���̰� ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "���") == 0) { //���� ��ġ���� �Ӽ����� ����̶�� 
            	printf("���ο� ����� �Է��ϼ���: ");
            	scanf("%s", new_value);
            	strcpy(p->name, new_value); 
            	printf("����� ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else {
            	printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            	break;
        	}
        	break;
    	} 
		
		else { //���� ���� 
        	p = p->link;
    	}
	}
	
	if (!p) { //���� ��ȸ�ߴµ��� ���� 
    	printf("�ش� ���� ã�� �� �����ϴ�.\n");
	}
}

void delete_customer() {
    char target_name[SIZE];
    customer_pointer p = customer_list, temp = NULL, prev = NULL;

    printf("������ ���� �̸��� �����ΰ���?\n ");
    scanf("%s", target_name);

    if (p == NULL) {
        printf("���� ���Ḯ��Ʈ�� ��ǰ�� �����ϴ�.\n");
        return;
    }

    if (strcmp(p->name, target_name) == 0) { // ������� ��尡 ù ��° ����� ���
        customer_list = p->link;
        free(p);
        return;
    }

    prev = p;
    p = p->link;

    while (p != NULL) { //���� ����Ʈ ��ȸ
        if (strcmp(p->name, target_name) == 0) { //���� ��ǰ�� ã��
            temp = p;
            prev->link = p->link;
            free(temp); // �޸� ��ȯ
            return;
        }
        
        else {
        	prev = p;
        	p = p->link;
		}
    }
    printf("���� ã�� �� �����ϴ�.\n");
}

void show_customer() {
  customer_pointer p = customer_list;
  while(p != NULL) { //��ȸ 
    printf("�� �̸�: %s \n", p->name);
    printf("�� ����: %d \n", p->age);
    printf("�� ����: %c \n", p->gender);
	printf("�� ���: %s \n", p->credit);
    p = p->link;
  }
}

void search_customer() {
	customer_pointer p = customer_list;
	char target_name[SIZE];
	
	printf("ã�� �ִ� ���� �̸��� �����ΰ���?\n");
	scanf("%s", target_name);
	
	while(p != NULL) {
		if(strcmp(p->name, target_name) == 0) {
			printf("�� �̸�: %s \n", p->name);
    		printf("�� ����: %d \n", p->age);
    		printf("�� ����: %c \n", p->gender);
			printf("�� ���: %s \n", p->credit);
    		
    		return; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	printf("�׷� ���� �������� �ʽ��ϴ�.\n");
}



void create_order() {
	order_pointer new_order, p;

    if(new_order == NULL) {
        printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.\n");
        return;
    }

    // �� ��ǰ�� ������ ����ڷκ��� �Է�
    printf("������ �Է��ϼ���: ");
    scanf("%s", new_order->customer_name);
    printf("��ǰ���� �Է��ϼ���: ");
    scanf("%s", new_order->product_name) ;
    printf("�ֹ� ������ �Է��ϼ���: ");
    scanf("%d", &new_order->number);
    printf("�ֹ����ڸ� �Է��Ͻÿ�: ");
    scanf("%s", new_order->date);

    new_order->link = NULL;

	if(check_customer(new_order->customer_name) == NULL || check_product(new_order->product_name) == NULL) {
		printf("�׷� ���̳� ��ǰ�� �������� �ʽ��ϴ�.\n");
		return; 
	}
	
    if (order_list == NULL) { // ����Ʈ�� ��� �ִٸ�, �� ��ǰ�� ����Ʈ�� ó������ ����
        order_list = new_order;
    } else { // ����Ʈ�� ������ ��ġ�� �̵� �� �� ��ǰ�� �߰� 
        p = order_list;
        
        while (p->link != NULL) {
            p = p->link;
        }
        p->link = new_order;
    }
    
    printf("�� ��ǰ�� �߰��Ǿ����ϴ�.\n");
}

customer_pointer check_customer(char name[]) {
	customer_pointer p = customer_list;
	
	while(p != NULL) {
		if(strcmp(p->name, name) == 0) {
    		return p; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	return NULL;
}

product_pointer check_product(char name[]) {
	product_pointer p = product_list;
	
	while(p != NULL) {
		if(strcmp(p->name, name) == 0) {
    		return p; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	return NULL;
}

void change_order() {
	order_pointer p = order_list;
	char target_product_name[SIZE], target_customer_name[SIZE]; //�ٲٷ��� �ֹ��� �̸� 
	char target_attribute[SIZE]; //�ٲٷ��� �Ӽ� 
	char new_value[SIZE]; //���ο� �� 


	printf("������ �ֹ��� �� �̸��� �Է��ϼ���: ");
	scanf("%s", target_customer_name);
	printf("������ �ֹ��� ��ǰ �̸��� �Է��ϼ���: ");
	scanf("%s", target_product_name);

	
	printf("������ �׸��� �����ϼ��� (�� �̸�, ��ǰ �̸�, �ֹ� ����, �ֹ� ����): ");
	scanf("%s", target_attribute);

	while (p) { //���� ����Ʈ ��ȸ 
    	if (strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) { //���� �ش� �ֹ��� ã�Ҵٸ� 
       		if (strcmp(target_attribute, "�� �̸�") == 0) { //���� ��ġ���� �Ӽ��� �� �̸��̶�� 
            	printf("���ο� �̸��� �Է��ϼ���: ");
            	scanf("%s", new_value);
            	
            	if(check_customer(new_value) == 0) {
            		printf("�׷� ���� �����ϴ�.\n");
					return; 
				}
				
            	strcpy(p->customer_name, new_value);
            	printf("�̸��� ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "��ǰ �̸�") == 0) { //���� ��ġ���� �Ӽ����� ��ǰ �̸��̶�� 
            	printf("���ο� ��ǰ�̸��� �Է��ϼ���: ");
            	scanf("%s", new_value);
            	
            	if(check_product(new_value) == 0) {
            		printf("�׷� ��ǰ�� �����ϴ�.\n");
            		return; 
				}
				
            	strcpy(p->product_name, new_value);         
            	printf("��ǰ�̸��� ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "�ֹ� ����") == 0) { //���� ��ġ���� �Ӽ����� �ֹ������̶�� 
            	printf("���ο� �ֹ� ������ �Է��ϼ���: ");
            	scanf("%d", new_value);
            	p->number = atoi(new_value); 
            	printf("�ֹ� ������ ���������� ����Ǿ����ϴ�.\n");
            	return;
        	} 
        	
        	else if(strcmp(target_attribute, "�ֹ� ����") == 0) {
        		printf("���ο� �ֹ� ���ڸ� �Է��ϼ���: ");
            	scanf("%s", new_value);
            	strcpy(p->date, new_value);         
            	printf("�ֹ� ���ڰ� ���������� ����Ǿ����ϴ�.\n");
            	return;
			}
			
			else {
            	printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            	break;
        	}
        	break;
    	} 
		
		else { //���� ���� 
        	p = p->link;
    	}
	}
	
	if (!p) { //���� ��ȸ�ߴµ��� ���� 
    	printf("�ش� �ֹ��� ã�� �� �����ϴ�.\n");
	}
}


void delete_order() {
    char target_customer_name[SIZE], target_product_name[SIZE];
    order_pointer p = order_list, temp = NULL, prev = NULL;

    printf("������ �ֹ� ���� �̸��� �����ΰ���?\n ");
    scanf("%s", target_customer_name);
    
    printf("������ �ֹ� ��ǰ�� �̸��� �����ΰ���?\n ");
    scanf("%s", target_product_name); 

    if (p == NULL) {
        printf("���� ���Ḯ��Ʈ�� �ֹ��� �����ϴ�.\n");
        return;
    }

    if (strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) { // ������� ��尡 ù ��° ����� ���
        order_list = p->link;
        free(p);
        return;
    }

    prev = p;
    p = p->link;

    while (p != NULL) { //���� ����Ʈ ��ȸ
        if (strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) { //���� �ֹ��� ã��
            temp = p;
            prev->link = p->link;
            free(temp); // �޸� ��ȯ
            return;
        }
        
        else {
        	prev = p;
        	p = p->link;
		}
    }
    printf("�ֹ��� ã�� �� �����ϴ�.\n");
}


void show_order() {
  order_pointer p = order_list;
  
  while(p != NULL) { //��ȸ 
    printf("�ֹ� �� �̸�: %s \n", p->customer_name);
    printf("�ֹ� ��ǰ �̸�: %d \n", p->product_name);
    printf("�ֹ� ����: %d \n", p->number);
    printf("�ֹ� ����: %s \n", p->date);
	
    p = p->link;
  }
}

void show_detail_order() {
	order_pointer p = order_list;
	product_pointer product_temp = NULL;
	customer_pointer customer_temp = NULL;
	
	
	while(p != NULL) {
		product_temp = check_product(p->product_name);
		customer_temp = check_customer(p->customer_name);
		
		if(product_temp != NULL && customer_temp != NULL) {
			printf("�ֹ� �� �̸�: %s\n", p->customer_name);
			printf("�ֹ� �� ����: %d \n", customer_temp->age);
    		printf("�ֹ� �� ����: %c \n", customer_temp->gender);
			printf("�ֹ� �� ���: %s \n", customer_temp->credit);
			printf("�ֹ� ��ǰ �̸�: %s\n", p->product_name);
			printf("�ֹ� ��ǰ ����: %d \n", product_temp->price);
    		printf("�ֹ� ��ǰ ���� ����: %d \n", product_temp->remaining);
			printf("�ֹ� ����: %d \n", p->number);
    		printf("�ֹ� ����: %s \n", p->date);
		}
		
		p = p->link;
	}
}

void search_order() {
	order_pointer p = order_list;
 	char target_customer_name[SIZE], target_product_name[SIZE];
	
	printf("ã�� �ִ� �ֹ��� ���� �̸��� �����ΰ���?\n");
	scanf("%s", target_customer_name);
	printf("ã�� �ִ� �ֹ��� ��ǰ �̸��� �����ΰ���?\n");
	scanf("%s", target_product_name); 
	
	while(p != NULL) {
		if(strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) {
			printf("�ֹ� �� �̸�: %s \n", p->customer_name);
    		printf("�ֹ� ��ǰ �̸�: %d \n", p->product_name);
    		printf("�ֹ� ����: %d \n", p->number);
    		printf("�ֹ� ����: %s \n", p->date);
    		
    		return; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	printf("�׷� �ֹ��� �������� �ʽ��ϴ�.\n");
}

void write_customer_file() {
	FILE *fp = fopen("customer.txt", "w");

	
	customer_pointer p = customer_list, next;
	
	while(p != NULL) {
		fprintf(fp,"%s %s %c %d\n", p->name, p->credit, p->gender, p->age);

		next = p->link;
        free(p); // �޸� ��ȯ
        p = next;
	}
	
	fclose(fp);
}

void write_product_file() {
	FILE *fp = fopen("product.txt", "w");

	
	product_pointer p = product_list, next;
	
	while(p != NULL) {
		fprintf(fp,"%s %d %d", p->name, p->price, p->remaining);
		
		next = p->link;
        free(p); // �޸� ��ȯ
        p = next;
	}
	
	fclose(fp);
}

void write_order_file() {
	FILE *fp = fopen("order.txt", "w");

	
	order_pointer p = order_list, next;
	
	while(p != NULL) {
		fprintf(fp,"%s %s %d %s", p->customer_name, p->product_name, p->number, p->date);
		
		next = p->link;
        free(p); // �޸� ��ȯ
        p = next;
	}
	
	fclose(fp);
}


void read_customer_file() {
    FILE *fp = fopen("customer.txt", "r");
    if (!fp) {
        printf("������ ���µ� �����Ͽ����ϴ�.\n");
        return;
    }

    customer_pointer last = NULL;

    while(!feof(fp)) {
        customer_pointer new_customer = (customer_pointer)malloc(sizeof(customer));
        int result = fscanf(fp, "%s %s %c %d", new_customer->name, new_customer->credit, &(new_customer->gender), &(new_customer->age));
        
        if (result == EOF) {
            free(new_customer);
            break;
        }

        new_customer->link = NULL;

        if (customer_list == NULL) {
            customer_list = new_customer;
        } 
		
		else {
            last->link = new_customer; 
        }
        last = new_customer;
    }

    fclose(fp);
}

void read_product_file() {
    FILE *fp = fopen("product.txt", "r");
    if (!fp) {
        printf("������ ���µ� �����Ͽ����ϴ�.\n");
        return;
    }

    product_pointer last = NULL;

    while(!feof(fp)) {
        product_pointer new_product = (product_pointer)malloc(sizeof(product));
        int result = fscanf(fp, "%s %s %d", new_product->name, &(new_product->price), &(new_product->remaining));
       
        if (result == EOF) {
            free(new_product);
            break;
        }

        new_product->link = NULL;

        if (product_list == NULL) {
            product_list = new_product;
        } 
		
		else {
            last->link = new_product; 
        }
        last = new_product;
    }

    fclose(fp);
}

void read_order_file() {
    FILE *fp = fopen("order.txt", "r");
    if (!fp) {
        printf("������ ���µ� �����Ͽ����ϴ�.\n");
        return;
    }

    order_pointer last = NULL;

    while(!feof(fp)) {
        order_pointer new_order = (order_pointer)malloc(sizeof(order));
        int result = fscanf(fp, "%s %s %d %s", new_order->customer_name, new_order->product_name, &(new_order->number), new_order->date);
       		

        if (result == EOF) {
            free(new_order);
            break;
        }

        new_order->link = NULL;

        if (order_list == NULL) {
            order_list = new_order;
        } 
		
		else {
            last->link = new_order; 
        }
        last = new_order;
    }

    fclose(fp);
}
