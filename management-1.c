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
//상품의 구조체(개체) {상품명, 가격, 남은 상품의 개수}
typedef struct product{
	char name[SIZE];
	int price;
	int remaining; 
	struct product *link;
}product;
//주문의 구조체(관계) {고객이름, 상품명, 주문 수량, 주문 일자}
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
		printf("무엇을 하시길 원하십니까?\n");
		printf("1)상품 2)고객 3)주문 4)종료\n");
		scanf("%d", &cmd1);
		
		switch(cmd1) {
			case 1: //상품
				printf("어떤 작업을 하시길 원하십니까?\n");
				printf("1)상품 추가 2)상품 수정 3)상품 삭제 4)상품 목록 출력 5)상품 검색\n");
				scanf("%d", &cmd2);
				
				switch(cmd2) {
					case 1: //상품 추가
						create_product();
						break;
					
					case 2: //상품 수정 
						change_product();
						break;
						
					case 3: //상품 삭제
						delete_product();
						break;
						
					case 4: //상품 목록 출력 
						show_product();
						break; 
						
					case 5: //상품 검색  
						search_product();
						break; 
				} 
				break;
				
			case 2: //고객 
				printf("어떤 작업을 하시길 원하십니까?\n");
				printf("1)고객 등록 2고객 수정 3)고객 삭제 4)고객 목록 출력 5)고객 검색\n");
				scanf("%d", &cmd2);
				
				switch(cmd2) {
					case 1: //고객 추가
						create_customer();
						break;
					
					case 2: //고객 수정 
						change_customer();
						break;
						
					case 3: //고객 삭제
						delete_customer();
						break;
						
					case 4: //고객 목록 출력 
						show_customer();
						break; 
					
					case 5: //고객 검색
						search_customer();
						break; 
				} 
				break; 
				
			case 3: //주문 
				printf("어떤 작업을 하시길 원하십니까?\n");
				printf("1)주문 생성 2)주문 수정 3)주문 삭제 4)주문 목록 출력 5)주문 상세 내역 출력 6)주문 검색\n");
				scanf("%d", &cmd2);
				
				switch(cmd2) {
					case 1: //주문 추가
						create_order();
						break;
					
					case 2: //주문 수정 
						change_order();
						break;
						
					case 3: //주문 삭제
						delete_order();
						break;
						
					case 4: //주문 목록 출력 
						show_order();
						break; 
						
					case 5: //주문 상세 목록 출력 
						show_detail_order();
						break; 
					
					case 6: //고객 검색
						search_order();
						break; 
				} 
				break; 
				
			case 4:
				printf("안녕히계세요~");
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
    new_product = (product_pointer) malloc(sizeof(product)); //메모리 동적 할당 

    if(new_product == NULL) {
        printf("메모리 할당에 실패하였습니다.\n");
        return;
    }

    // 새 상품의 정보를 사용자로부터 입력
    printf("상품명을 입력하세요: ");
    scanf("%s", new_product->name);
    printf("가격을 입력하세요: ");
    scanf("%d", &new_product->price) ;
    printf("남은 상품 개수를 입력하세요: ");
    scanf("%d", &new_product->remaining);

    new_product->link = NULL;

    if (product_list == NULL) { // 리스트가 비어 있다면, 새 상품이 리스트의 처음으로 설정
        product_list = new_product;
    } 
	else { // 리스트의 마지막 위치로 이동 후 새 상품을 추가 
        p = product_list;
        
		while (p->link != NULL) {
            p = p->link;
        }
        
        p->link = new_product; //마지막에 새로운 product를 추가 
    }
    
    printf("새 상품이 추가되었습니다.\n");
}

void change_product() {
	product_pointer p = product_list;
	char target_name[SIZE]; //바꾸려는 상품의 이름 
	char target_attribute[SIZE]; //바꾸려는 속성 
	char new_value[SIZE]; //새로운 값 


	printf("변경할 상품의 이름을 입력하세요: ");
	scanf("%s", target_name);

	printf("변경할 항목을 선택하세요 (상품명, 가격, 남은 개수): ");
	scanf("%s", target_attribute);

	while (p) { //연결 리스트 순회 
    	if (strcmp(p->name, target_name) == 0) { //만약 해당 상품을 찾았다면 
       		if (strcmp(target_attribute, "상품명") == 0) { //만약 고치려는 속성이 상품명이라면 
            	printf("새로운 상품명을 입력하세요: ");
            	scanf("%s", new_value);
            	strcpy(p->name, new_value);
            	printf("상품명이 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "가격") == 0) { //만약 고치려는 속성명이 가격이라면 
            	printf("새로운 가격을 입력하세요: ");
            	scanf("%s", new_value);
            	p->price = atoi(new_value);
            	printf("가격이 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "남은 개수") == 0) { //만약 고치려는 속성명이 개수라면 
            	printf("남은 개수를 입력하세요: ");
            	scanf("%s", new_value);
            	p->remaining = atoi(new_value);
            	printf("남은 개수가 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else {
            	printf("잘못된 입력입니다. 다시 시도하세요.\n");
            	break;
        	}
        	break;
    	} 
		
		else { //다음 노드로 
        	p = p->link;
    	}
	}
	
	if (!p->link) { //전부 순회했는데도 없음 
    	printf("해당 상품을 찾을 수 없습니다.\n");
	}
}

void delete_product() {
    char target_name[SIZE];
    product_pointer p = product_list, temp = NULL, prev = NULL;

    printf("삭제할 상품의 이름은 무엇인가요?\n ");
    scanf("%s", target_name);

    if (p == NULL) {
        printf("아직 연결리스트에 상품이 없습니다.\n");
        return;
    }

    if (strcmp(p->name, target_name) == 0) { // 지우려는 노드가 첫 번째 노드인 경우
        product_list = p->link;
        free(p);
        return;
    }

    prev = p;
    p = p->link;

    while (p != NULL) { //연결 리스트 순회
        if (strcmp(p->name, target_name) == 0) { //지울 상품을 찾음
            temp = p;
            prev->link = p->link;
            free(temp); // 메모리 반환
            return;
        }
        
        else {
        	prev = p;
        	p = p->link;
		}
    }
    printf("상품을 찾을 수 없습니다.\n");
}

void show_product() {
  product_pointer p = product_list;
  while(p != NULL) { //순회 
    printf("상품 이름: %s \n", p->name);
    printf("상품 가격: %d \n", p->price);
    printf("남은 수량: %d \n", p->remaining);

    p = p->link;
  }
}

void search_product() {
	product_pointer p = product_list;
	char target_name[SIZE];
	
	printf("찾고 있는 상품의 이름은 무엇인가요?\n");
	scanf("%s", target_name);
	
	while(p != NULL) {
		if(strcmp(p->name, target_name) == 0) {
			printf("상품 이름: %s \n", p->name);
   			printf("상품 가격: %d \n", p->price);
    		printf("남은 수량: %d \n", p->remaining);
    		
    		return; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	printf("그런 상품은 존재하지 않습니다.\n");
}



void create_customer() {
	customer_pointer new_customer, current_customer;
    new_customer = (customer_pointer) malloc(sizeof(customer)); //메모리 동적 할당 

    if(new_customer == NULL) {
        printf("메모리 할당에 실패하였습니다.\n");
        return;
    }

    // 새 고객의 정보를 사용자로부터 입력
    printf("고객의 이름 입력하세요: ");
    scanf("%s", new_customer->name);
    printf("성별을 입력하세요: ");
    fflush(stdin);
    scanf("%c", &new_customer->gender);
    printf("나이를 입력하세요: ");
    scanf("%d", &new_customer->age);
	printf("등급을 입력하세요: ");
    scanf("%s", new_customer->credit); 

    new_customer->link = NULL;

    if (customer_list == NULL) { // 리스트가 비어 있다면, 새 상품이 리스트의 처음으로 설정
        customer_list = new_customer;
    } 
	else { // 리스트의 마지막 위치로 이동 후 새 상품을 추가 
        current_customer = customer_list;
        
		while (current_customer->link != NULL) {
            current_customer = current_customer->link;
        }
        
        current_customer->link = new_customer; //마지막에 새로운 customer를 추가 
    }
    
    printf("새 고객이 추가되었습니다.\n");
}

void change_customer() {
	customer_pointer p = customer_list;
	char target_name[SIZE]; //바꾸려는 고객의 이름 
	char target_attribute[SIZE]; //바꾸려는 속성 
	char new_value[SIZE]; //새로운 값 


	printf("변경할 고객의 이름을 입력하세요: ");
	scanf("%s", target_name);

	printf("변경할 항목을 선택하세요 (이름, 나이, 등급): ");
	scanf("%s", target_attribute);

	while (p) { //연결 리스트 순회 
    	if (strcmp(p->name, target_name) == 0) { //만약 해당 상품을 찾았다면 
       		if (strcmp(target_attribute, "이름") == 0) { //만약 고치려는 속성이 이름이라면 
            	printf("새로운 이름을 입력하세요: ");
            	scanf("%s", new_value);
            	strcpy(p->name, new_value);
            	printf("이름이 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "나이") == 0) { //만약 고치려는 속성명이 나이 라면 
            	printf("새로운 나이 입력하세요: ");
            	scanf("%s", new_value);
            	p->age = atoi(new_value);
            	printf("나이가 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "등급") == 0) { //만약 고치려는 속성명이 등급이라면 
            	printf("새로운 등급을 입력하세요: ");
            	scanf("%s", new_value);
            	strcpy(p->name, new_value); 
            	printf("등급이 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else {
            	printf("잘못된 입력입니다. 다시 시도하세요.\n");
            	break;
        	}
        	break;
    	} 
		
		else { //다음 노드로 
        	p = p->link;
    	}
	}
	
	if (!p) { //전부 순회했는데도 없음 
    	printf("해당 고객을 찾을 수 없습니다.\n");
	}
}

void delete_customer() {
    char target_name[SIZE];
    customer_pointer p = customer_list, temp = NULL, prev = NULL;

    printf("삭제할 고객의 이름은 무엇인가요?\n ");
    scanf("%s", target_name);

    if (p == NULL) {
        printf("아직 연결리스트에 상품이 없습니다.\n");
        return;
    }

    if (strcmp(p->name, target_name) == 0) { // 지우려는 노드가 첫 번째 노드인 경우
        customer_list = p->link;
        free(p);
        return;
    }

    prev = p;
    p = p->link;

    while (p != NULL) { //연결 리스트 순회
        if (strcmp(p->name, target_name) == 0) { //지울 상품을 찾음
            temp = p;
            prev->link = p->link;
            free(temp); // 메모리 반환
            return;
        }
        
        else {
        	prev = p;
        	p = p->link;
		}
    }
    printf("고객을 찾을 수 없습니다.\n");
}

void show_customer() {
  customer_pointer p = customer_list;
  while(p != NULL) { //순회 
    printf("고객 이름: %s \n", p->name);
    printf("고객 나이: %d \n", p->age);
    printf("고객 성별: %c \n", p->gender);
	printf("고객 등급: %s \n", p->credit);
    p = p->link;
  }
}

void search_customer() {
	customer_pointer p = customer_list;
	char target_name[SIZE];
	
	printf("찾고 있는 고객의 이름은 무엇인가요?\n");
	scanf("%s", target_name);
	
	while(p != NULL) {
		if(strcmp(p->name, target_name) == 0) {
			printf("고객 이름: %s \n", p->name);
    		printf("고객 나이: %d \n", p->age);
    		printf("고객 성별: %c \n", p->gender);
			printf("고객 등급: %s \n", p->credit);
    		
    		return; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	printf("그런 고객은 존재하지 않습니다.\n");
}



void create_order() {
	order_pointer new_order, p;

    if(new_order == NULL) {
        printf("메모리 할당에 실패하였습니다.\n");
        return;
    }

    // 새 상품의 정보를 사용자로부터 입력
    printf("고객명을 입력하세요: ");
    scanf("%s", new_order->customer_name);
    printf("상품명을 입력하세요: ");
    scanf("%s", new_order->product_name) ;
    printf("주문 수량을 입력하세요: ");
    scanf("%d", &new_order->number);
    printf("주문일자를 입력하시오: ");
    scanf("%s", new_order->date);

    new_order->link = NULL;

	if(check_customer(new_order->customer_name) == NULL || check_product(new_order->product_name) == NULL) {
		printf("그런 고객이나 상품은 존재하지 않습니다.\n");
		return; 
	}
	
    if (order_list == NULL) { // 리스트가 비어 있다면, 새 상품이 리스트의 처음으로 설정
        order_list = new_order;
    } else { // 리스트의 마지막 위치로 이동 후 새 상품을 추가 
        p = order_list;
        
        while (p->link != NULL) {
            p = p->link;
        }
        p->link = new_order;
    }
    
    printf("새 상품이 추가되었습니다.\n");
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
	char target_product_name[SIZE], target_customer_name[SIZE]; //바꾸려는 주문의 이름 
	char target_attribute[SIZE]; //바꾸려는 속성 
	char new_value[SIZE]; //새로운 값 


	printf("변경할 주문의 고객 이름을 입력하세요: ");
	scanf("%s", target_customer_name);
	printf("변경할 주문의 상품 이름을 입력하세요: ");
	scanf("%s", target_product_name);

	
	printf("변경할 항목을 선택하세요 (고객 이름, 상품 이름, 주문 수량, 주문 일자): ");
	scanf("%s", target_attribute);

	while (p) { //연결 리스트 순회 
    	if (strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) { //만약 해당 주문을 찾았다면 
       		if (strcmp(target_attribute, "고객 이름") == 0) { //만약 고치려는 속성이 고객 이름이라면 
            	printf("새로운 이름을 입력하세요: ");
            	scanf("%s", new_value);
            	
            	if(check_customer(new_value) == 0) {
            		printf("그런 고객은 없습니다.\n");
					return; 
				}
				
            	strcpy(p->customer_name, new_value);
            	printf("이름이 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "상품 이름") == 0) { //만약 고치려는 속성명이 상품 이름이라면 
            	printf("새로운 상품이름을 입력하세요: ");
            	scanf("%s", new_value);
            	
            	if(check_product(new_value) == 0) {
            		printf("그런 상품은 없습니다.\n");
            		return; 
				}
				
            	strcpy(p->product_name, new_value);         
            	printf("상품이름이 성공적으로 변경되었습니다.\n");
            	return;
        	} 
			
			else if (strcmp(target_attribute, "주문 수량") == 0) { //만약 고치려는 속성명이 주문수량이라면 
            	printf("새로운 주문 수량을 입력하세요: ");
            	scanf("%d", new_value);
            	p->number = atoi(new_value); 
            	printf("주문 수량이 성공적으로 변경되었습니다.\n");
            	return;
        	} 
        	
        	else if(strcmp(target_attribute, "주문 일자") == 0) {
        		printf("새로운 주문 일자를 입력하세요: ");
            	scanf("%s", new_value);
            	strcpy(p->date, new_value);         
            	printf("주문 일자가 성공적으로 변경되었습니다.\n");
            	return;
			}
			
			else {
            	printf("잘못된 입력입니다. 다시 시도하세요.\n");
            	break;
        	}
        	break;
    	} 
		
		else { //다음 노드로 
        	p = p->link;
    	}
	}
	
	if (!p) { //전부 순회했는데도 없음 
    	printf("해당 주문을 찾을 수 없습니다.\n");
	}
}


void delete_order() {
    char target_customer_name[SIZE], target_product_name[SIZE];
    order_pointer p = order_list, temp = NULL, prev = NULL;

    printf("삭제할 주문 고객의 이름은 무엇인가요?\n ");
    scanf("%s", target_customer_name);
    
    printf("삭제할 주문 상품의 이름은 무엇인가요?\n ");
    scanf("%s", target_product_name); 

    if (p == NULL) {
        printf("아직 연결리스트에 주문이 없습니다.\n");
        return;
    }

    if (strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) { // 지우려는 노드가 첫 번째 노드인 경우
        order_list = p->link;
        free(p);
        return;
    }

    prev = p;
    p = p->link;

    while (p != NULL) { //연결 리스트 순회
        if (strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) { //지울 주문을 찾음
            temp = p;
            prev->link = p->link;
            free(temp); // 메모리 반환
            return;
        }
        
        else {
        	prev = p;
        	p = p->link;
		}
    }
    printf("주문을 찾을 수 없습니다.\n");
}


void show_order() {
  order_pointer p = order_list;
  
  while(p != NULL) { //순회 
    printf("주문 고객 이름: %s \n", p->customer_name);
    printf("주문 상품 이름: %d \n", p->product_name);
    printf("주문 수량: %d \n", p->number);
    printf("주문 일자: %s \n", p->date);
	
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
			printf("주문 고객 이름: %s\n", p->customer_name);
			printf("주문 고객 나이: %d \n", customer_temp->age);
    		printf("주문 고객 성별: %c \n", customer_temp->gender);
			printf("주문 고객 등급: %s \n", customer_temp->credit);
			printf("주문 상품 이름: %s\n", p->product_name);
			printf("주문 상품 가격: %d \n", product_temp->price);
    		printf("주문 상품 남은 수량: %d \n", product_temp->remaining);
			printf("주문 수량: %d \n", p->number);
    		printf("주문 일자: %s \n", p->date);
		}
		
		p = p->link;
	}
}

void search_order() {
	order_pointer p = order_list;
 	char target_customer_name[SIZE], target_product_name[SIZE];
	
	printf("찾고 있는 주문의 고객의 이름은 무엇인가요?\n");
	scanf("%s", target_customer_name);
	printf("찾고 있는 주문의 상품 이름은 무엇인가요?\n");
	scanf("%s", target_product_name); 
	
	while(p != NULL) {
		if(strcmp(p->customer_name, target_customer_name) == 0 && strcmp(p->product_name, target_product_name) == 0) {
			printf("주문 고객 이름: %s \n", p->customer_name);
    		printf("주문 상품 이름: %d \n", p->product_name);
    		printf("주문 수량: %d \n", p->number);
    		printf("주문 일자: %s \n", p->date);
    		
    		return; 
		}
		
		else {
			p = p->link;
		}
	} 
	
	printf("그런 주문은 존재하지 않습니다.\n");
}

void write_customer_file() {
	FILE *fp = fopen("customer.txt", "w");

	
	customer_pointer p = customer_list, next;
	
	while(p != NULL) {
		fprintf(fp,"%s %s %c %d\n", p->name, p->credit, p->gender, p->age);

		next = p->link;
        free(p); // 메모리 반환
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
        free(p); // 메모리 반환
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
        free(p); // 메모리 반환
        p = next;
	}
	
	fclose(fp);
}


void read_customer_file() {
    FILE *fp = fopen("customer.txt", "r");
    if (!fp) {
        printf("파일을 여는데 실패하였습니다.\n");
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
        printf("파일을 여는데 실패하였습니다.\n");
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
        printf("파일을 여는데 실패하였습니다.\n");
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
