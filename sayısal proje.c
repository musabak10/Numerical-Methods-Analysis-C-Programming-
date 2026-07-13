#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define PI 3.14159265358979323846
#define E  2.71828182845904523536
typedef enum {
    NODE_NUMBER,      
    NODE_VARIABLE,    
    NODE_OPERATOR,    
    NODE_FUNCTION     
} NodeType;
typedef struct TreeNode {
    NodeType type;
    double value;               
    char* op_or_func;        
    struct TreeNode* left;      
    struct TreeNode* right;     
} TreeNode;
typedef struct {
    TreeNode** data;
    int top;
    int kapasite;
} NodeStack;

typedef struct {
    char* data;
    int top;
    int kapasite;
} CharStack;
void ozgurlukmatris(double **matris,int n);
void printmatris(double **matris,int n);
double** allocatematris(int n);
void get_minor(double **mat, double **out, int skip_row, int skip_col, int n);
double determinant(double **matris, int n);
void kofaktormatris(double **matris, double **kof, int n);
void adjoint(double **kof, double **adj, int n);
int inverse(double **matris,double **inv,int n);
int is_digit(char c);
int is_alpha(char c);
int operatoronceligi(char op);
TreeNode* create_node(NodeType type, double val,char* name);
void free_tree(TreeNode* root);
TreeNode* create_node(NodeType type, double val,char* name);
void nodestack_init(NodeStack* s, int kapasite);
void charstack_init(CharStack* s, int kapasite);
void nodestack_free(NodeStack* s);
void charstack_free(CharStack* s);
TreeNode* parse_expression(char* expr);
int fonksiyonmu(char* str,int index);
char* implicit_multiplication(char* expr);
double hesapla_fonksiyon(char* ifade_stringi, double x_degeri);
void bisection(char* fonksiyon_stringi, double a, double b, double tolerance);
void regula_falsi(char* fonksiyon_stringi, double a, double b, double tolerance);
double turev_hesapla(char* fonksiyon_stringi, double x);
void newton_raphson(char* fonksiyon_stringi,double a,double tolerance);
void cholesky(double** A, int n);
void gauss_seidel(double** A, double* b, int n, double tolerance, int max_iter);
double sayisalturevmerkezi(char* fonksiyon_stringi, double x,double h);
double sayisalturevileri(char* fonksiyon_stringi, double x,double h);
double sayisalturevgeri(char* fonksiyon_stringi, double x,double h);
void simpson(char* fonksiyon_stringi, double a, double b, int n);
void trapez(char* fonksiyon_stringi, double a, double b, int n);
void newton_enterpolasyon(double* x, double* y, int n, double hedef); 
int main(){
	int i,j,k,choice,exit,matris,n,chol_n,max_iter,gs_n;
	double **nxn;
	double **inv;
	double** A;
	double** A_gs;
    double*  b_gs;
	double a,b,tolerance,ileri,geri,merkezi,hedef,tolerance_gs;
	char* func;
	double* x;
    double* y;
	choice=-1;
	matris=-1;
	exit=0;
	n=-1;
	chol_n=-1;
	func=malloc(sizeof(char)*500);
	while(exit!=1){
		printf("\n-----YONTEMLER-----\n");
		printf("-------------------\n");
		printf("0: CIKIS\n");
		printf("1: BISECTION \n");
		printf("2: REGULA-FALSI \n");
		printf("3: NEWTON RAPHSON \n");
		printf("4: MATRISIN TERSINI ALMA\n");
		printf("5: CHOLESKY\n");
		printf("6: GAUSS SEIDEL\n");
		printf("7: SAYISAL TUREV\n");
		printf("8: SIMPSON YONTEMLERI\n");
		printf("9: TRAPEZ YONTEMI\n");
		printf("10: GREGORY NEWTON ENTERPOLASYONU\n");
		printf("-------------------");
		printf("\nSECIMINIZ:");
		scanf("%d",&choice);
	if(choice==0){
       exit=1;
	}else if(choice==1){
       n=-1;
	   printf("\nFONKSIYONUNUZU GIRINIZ (arcsin(x^3)*e^x gibi)\n");
	   scanf(" %[^\n]",func);
	   printf("\nBISECTION YONTEMI ICIN KOKU BULACAGIMIZ ARALIGI VERINIZ [a,b]\n");
	   printf("\na:");
	   scanf("%lf",&a);
	   printf("\nb:");
	   scanf("%lf",&b);
	   printf("\nHATA PAYINI VERINIZ:");
	   scanf("%lf",&tolerance);
	   bisection(func,a,b,tolerance);
	}else if(choice==2){
       n=-1;
	   printf("\nFONKSIYONUNUZU GIRINIZ (arcsin(x^3)*e^x gibi)\n");
	   scanf(" %[^\n]",func);
	   printf("\nREGULA-FALSI YONTEMI ICIN KOKU BULACAGIMIZ ARALIGI VERINIZ [a,b]\n");
	   printf("\na:");
	   scanf("%lf",&a);
	   printf("\nb:");
	   scanf("%lf",&b);
	   printf("\nHATA PAYINI VERINIZ:");
	   scanf("%lf",&tolerance);
	   regula_falsi(func,a,b,tolerance);       
	}else if(choice==3){
       n=-1;
	   printf("\nFONKSIYONUNUZU GIRINIZ (arcsin(x^3)*e^x gibi)\n");
	   scanf(" %[^\n]",func);
	   printf("\nNEWTON-RAPHSON YONTEMI BASLANGIC DEGERINI VERINIZ:");
	   scanf("%lf",&a);
	   printf("\nHATA PAYINI VERINIZ:");
	   scanf("%lf",&tolerance);
	   newton_raphson(func,a,tolerance);
	}else if(choice==4){
		n=-1;
		while(matris<=0){
			printf("\nKARE MATRISINIZ (NxN) KACA KACLIK OLUCAK:");
		    scanf("%d",&matris);
		}
        nxn=allocatematris(matris);
        inv=allocatematris(matris);
        if(nxn==NULL||inv==NULL){
        	printf("\n!!!Dynamic Memort Allocatiýn Failed!!!!!\n");
		}
		for(i=0;i<matris;i++){
			for(j=0;j<matris;j++){
				printf("\nMATRISINIZIN %d.SATIR %d.SUTUNUNDAKI ELEMANINI GIRINIZ:",i+1,j+1);
				scanf("%lf",(*(nxn+i)+j));
			}
		}
	    printmatris(nxn,matris);
		if(!inverse(nxn,inv,matris)){
			printf("\nDETERMINANT 0 MATRISINIZIN TERSI YOK\n");
		}else{
			printf("\nMATRISNIZIN TERSI:\n");
			printmatris(inv,matris);
		}
		ozgurlukmatris(nxn,matris);
		ozgurlukmatris(inv,matris);
        matris=-1;
    }else if(choice==5){
        n=-1;
		while (chol_n <= 0) {
        printf("\nKARE MATRISINIZ (NxN) KACA KACLIK OLUCAK: ");
        scanf("%d", &chol_n);
        }
    A = allocatematris(chol_n);
    for (i = 0; i < chol_n; i++){
    	for (j = 0; j < chol_n; j++) {
            printf("\n%d.SATIR %d.SUTUN: ", i+1, j+1);
            scanf("%lf", &A[i][j]);
        }
	}
    printf("\nGirilen Matris:\n");
    printmatris(A, chol_n);
    cholesky(A, chol_n);
    ozgurlukmatris(A, chol_n);
	chol_n=-1;
	}else if(choice==6){
    n=-1;
	gs_n = -1;
    while (gs_n <= 0) {
        printf("\nDENKLEM SAYISI (NxN sistem): ");
        scanf("%d", &gs_n);
    }
    b_gs = (double*)malloc(sizeof(double) * gs_n);
	A_gs = allocatematris(gs_n);
    printf("\nKATSAYI MATRISINI GIRINIZ (A):\n");
    for (i = 0; i < gs_n; i++){
        for (j = 0; j < gs_n; j++) {
            printf("%d.denklem %d.katsayi: ", i+1, j+1);
            scanf("%lf", &A_gs[i][j]);
        }
    }
    printf("\nSAG TARAF VEKTORUNU GIRINIZ (B):\n");
    for (i = 0; i < gs_n; i++) {
        printf("b[%d]: ", i+1);
        scanf("%lf", &b_gs[i]);
    }
    printf("\nMAKSIMUM ITERASYON SAYISI: ");
    scanf("%d", &max_iter);
    printf("HATA PAYI: ");
    scanf("%lf", &tolerance_gs);
    printf("\nGirilen Sistem:\n");
    printmatris(A_gs, gs_n);
	gauss_seidel(A_gs, b_gs, gs_n, tolerance_gs, max_iter);
    ozgurlukmatris(A_gs, gs_n);
    free(b_gs);
    }else if(choice==7){
       n=-1;
	   printf("\nFONKSIYONUNUZU GIRINIZ (arcsin(x^3)*e^x gibi)\n");
	   scanf(" %[^\n]",func);
	   printf("\nHANGI DEGERDE TUREV ALMAK ISTIYORSUNUZ:");
	   scanf("%lf",&a);
	   printf("\nH SAYISINI GIRINIZ:");
	   scanf("%lf",&tolerance);
	   ileri=sayisalturevileri(func,a,tolerance);
	   geri=sayisalturevgeri(func,a,tolerance);
	   merkezi=sayisalturevmerkezi(func,a,tolerance); 
	   printf("FONKSIYON:%s\n",func);
	   printf("\nILERI FARK:%f",ileri); 
	   printf("\nGERI FARK:%f",geri);
	   printf("\nMERKEZI FARK:%f",merkezi);     
    }else if(choice==8){
       n=-1;
	   printf("\nFONKSIYONUNUZU GIRINIZ (arcsin(x^3)*e^x gibi)\n");
	   scanf(" %[^\n]",func);
	   printf("\nSIMPSON YONTEMI ICIN INTEGRALI BULACAGIMIZ ARALIGI VERINIZ [a,b]\n");
	   printf("\na:");
	   scanf("%lf",&a);
	   printf("\nb:");
	   scanf("%lf",&b);
	   while(n<=0){
	   	printf("\nARALIK SAYISINI GIRINIZ: ");
        scanf("%d", &n);
	   }
	   simpson(func,a,b,n);
	}else if(choice==9){
       n=-1;
	   printf("\nFONKSIYONUNUZU GIRINIZ (arcsin(x^3)*e^x gibi)\n");
	   scanf(" %[^\n]",func);
	   printf("\nTRAPEZ YONTEMI ICIN INTEGRALI BULACAGIMIZ ARALIGI VERINIZ [a,b]\n");
	   printf("\na:");
	   scanf("%lf",&a);
	   printf("\nb:");
	   scanf("%lf",&b);
	   while(n<=0){
	   	printf("\nARALIK SAYISINI GIRINIZ: ");
        scanf("%d", &n);
	   }
	   trapez(func,a,b,n); 
	}else if(choice==10){
    n=-1;
	printf("\nKAC VERI NOKTASI GIRECEKSINIZ: ");
    scanf("%d", &n);
    x=(double*)malloc(sizeof(double)*n);
    y=(double*)malloc(sizeof(double)*n);
	for (i = 0; i < n; i++) {
        printf("%d. nokta -> x: ",i+1);
        scanf("%lf",&x[i]);
        printf("%d. nokta -> f(x):",i+1);
        scanf("%lf",&y[i]);
    }
    printf("\nENTERPOLASYON YAPILACAK x DEGERI:");
    scanf("%lf",&hedef);
    newton_enterpolasyon(x,y,n,hedef);
	free(x);
	free(y);
	}
}
    free(func);
	return 0;
}
void ozgurlukmatris(double **matris,int n){
	int i;
	for(i=0;i<n;i++){
		free(*(matris+i));
	}
	free(matris);
}
void printmatris(double **matris,int n){
	int i,j;
	printf("\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("[%.4f]",*(*(matris+i)+j));
		}
		printf("\n");
	}
}
double** allocatematris(int n){
	double **m;
	int i;
	m=(double**)malloc(sizeof(double*)*n);
	for(i=0;i<n;i++){
	   *(m+i)=(double*)malloc(sizeof(double)*n);
	}
	return m;
}
void get_minor(double **matris, double **minor, int skip_row, int skip_col, int n){
    int currcol,currrow,i,j;
    for(i=0;i<n-1;i++) {
        if(i<skip_row){
        	currrow=i;
		}else{
		    currrow=i+1;	
		}
        for(j=0;j<n-1;j++) {
            if(j<skip_col){
            	currcol=j;
			}else{
				currcol=j+1;
			} 
        minor[i][j]=matris[currrow][currcol];
        }
    }
}
double determinant(double **matris, int n){
    double **minor;
    double det,sign;
    int j;
	minor=allocatematris(n-1);
	det=0.0;
	if(n==1){
    	return matris[0][0];
	}
    if(n==2){
    	return matris[0][0]*matris[1][1]-matris[0][1]*matris[1][0];
	}
    for(j=0;j<n;j++){
        get_minor(matris, minor,0,j,n);
        if(j%2==0){
        	sign=1.0;
		}else{
			sign=-1.0;
		}
        det+=sign*matris[0][j]*determinant(minor, n - 1);
    }
 
    ozgurlukmatris(minor,n-1);
    return det;
}
void kofaktormatris(double **matris,double **kof,int n){
    double **minor;
    double sign;
    int i,j;
    minor=allocatematris(n-1);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            get_minor(matris,minor,i,j,n);
            if ((i+j)%2==0){
            	sign=1.0;
			}else{
				sign=-1.0;
			}
            kof[i][j]=sign*determinant(minor, n - 1);
        }
    }
 
    ozgurlukmatris(minor,n-1);
}
void adjoint(double **kof, double **adj, int n){
    int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			adj[i][j]=kof[j][i];
		}
    }
}
int inverse(double **matris,double **inv,int n){
	double det;
	double **kof;
	double **adj;
	int i,j;
	det=determinant(matris,n);
	if(det==0){
		return 0;
	}
	kof=allocatematris(n);
	adj=allocatematris(n);
	kofaktormatris(matris,kof,n);
	adjoint(kof,adj,n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			inv[i][j]=adj[i][j]/det;
		}
	}
    ozgurlukmatris(kof,n);
    ozgurlukmatris(adj,n);
    return 1;
}
int is_digit(char c){
    return (c>='0'&&c<='9');
}

int is_alpha(char c){
    return ((c>='a'&&c<='z')||(c>='A'&&c<='Z'));
}

int operatoronceligi(char op){
    int oncelik=0;
    if(op=='+'||op=='-'){
    	oncelik=1;
	}else if(op=='*'||op=='/'){
		oncelik=2;
	}else if(op=='^'||op=='_'){
		oncelik=3;
	}
    return oncelik;
}
TreeNode* create_node(NodeType type, double val, char* name){
    TreeNode* new_node=(TreeNode*)malloc(sizeof(TreeNode));
    if(new_node != NULL){
        new_node->type=type;
        new_node->value=val;
        new_node->op_or_func=(char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(new_node->op_or_func,name);
        new_node->left=NULL;
        new_node->right=NULL;
    }
    return new_node;
}
void free_tree(TreeNode* root){
    if(root!=NULL){
        free_tree(root->left);
        free_tree(root->right);
        free(root->op_or_func);
        free(root);
    }
}
double evaluate_tree(TreeNode* root, double x_value){
    double result,left_val,right_val,taban,arguman;
    char op;
    result=0.0;
    if(root==NULL){
        result=0.0;
    }else if(root->type==NODE_NUMBER){
        result=root->value;
    }else if(root->type==NODE_VARIABLE){
        result=x_value;
    }else if(root->type==NODE_OPERATOR){
        left_val=evaluate_tree(root->left,x_value);
        right_val=evaluate_tree(root->right,x_value);
        op=root->op_or_func[0];
        if(op=='+'){
            result=left_val+right_val;
        }else if(op=='-'){
            result=left_val-right_val;
        }else if(op=='*'){
            result=left_val*right_val;
        }else if(op=='/'){
            if(right_val!=0){
                result=left_val/right_val;
            }else{
                result=0;
            }
        }else if(op=='^'){
            result=pow(left_val,right_val);
        }else if(op=='_'){
            if(left_val>0.0&&left_val!=1.0&&right_val>0.0){
                result=log(right_val)/log(left_val);
            }else{
                result=0.0;
            }
        }
    }else if(root->type==NODE_FUNCTION){
        right_val=evaluate_tree(root->right,x_value);
        if(strcmp(root->op_or_func,"sin")==0){
            result=sin(right_val);
        }else if(strcmp(root->op_or_func,"cos")==0){
            result=cos(right_val);
        }else if(strcmp(root->op_or_func,"log")==0){
            if(root->left==NULL){
                result=log10(right_val);
            }else{
                taban=evaluate_tree(root->left, x_value);
                arguman=right_val;             
            if(taban>0.0&&taban!=1.0&&arguman>0.0){
                result=log(arguman)/log(taban);
            }else{
                result=0.0;
            }
        }
        }else if(strcmp(root->op_or_func,"ln")==0){
            result=log(right_val);
        }else if(strcmp(root->op_or_func,"exp")==0){
            result=exp(right_val);
        }else if(strcmp(root->op_or_func,"arcsin")==0){
            result=asin(right_val);
        }else if(strcmp(root->op_or_func,"arccos")==0){
            result=acos(right_val);
        }else if(strcmp(root->op_or_func,"arctan")==0){
            result=atan(right_val);
        }else if(strcmp(root->op_or_func,"tan")==0){
            result=tan(right_val);
        }else if(strcmp(root->op_or_func,"cot")==0){
            result=1.0/tan(right_val);
        }else if(strcmp(root->op_or_func,"arccot")==0){
            result=atan(1.0/right_val);
        }else if(strcmp(root->op_or_func,"sec")==0){
            result =1.0/cos(right_val);
        }else if(strcmp(root->op_or_func,"csc")==0){
            result=1.0/sin(right_val);
        }else if(strcmp(root->op_or_func,"arcsec")==0){
            if(right_val!=0){
                result=acos(1.0/right_val);
            }else{
                result=0.0;
            }
        }else if(strcmp(root->op_or_func,"arccsc")==0){
            if(right_val!=0){
                result=asin(1.0/right_val);
            }else{
                result=0.0;
            }
        }
    }
    return result;
}
void nodestack_init(NodeStack* s, int kapasite){
    s->data=(TreeNode**)malloc(sizeof(TreeNode*)*kapasite);
    s->top=-1;
    s->kapasite=kapasite;
}

void charstack_init(CharStack* s, int kapasite){
    s->data=(char*)malloc(sizeof(char)*kapasite);
    s->top=-1;
    s->kapasite=kapasite;
}

void nodestack_free(NodeStack* s){
    free(s->data);
    s->data=NULL;
}

void charstack_free(CharStack* s){
    free(s->data);
    s->data=NULL;
}
TreeNode* parse_expression(char* expr){
    NodeStack nodes;
    CharStack ops;
    TreeNode* op_node;
    TreeNode* sonuc;
    TreeNode* child;
    TreeNode* right;      
    TreeNode* left;      
    TreeNode* func_node; 
    int i, ni, len, alpha_i;
    char* num_str;
    char* name;
    char* op_str;
    double val;
    char op, func_char;
    len=strlen(expr);
    nodes.top=-1;
    ops.top=-1;
    i=0;
    op_str=(char*)malloc(sizeof(char)*2);
    num_str=(char*)malloc(sizeof(char)*32);
    name=(char*)malloc(sizeof(char) * 32);
    nodestack_init(&nodes,len+10);   
    charstack_init(&ops,len+10);
	while(i<len){
        if(expr[i]==' '||expr[i]=='\t'||expr[i]=='\n'||expr[i]=='\r'){
            i++;
        }
        else if(is_digit(expr[i])||expr[i]=='.') {
            ni=0;
            while(i<len&&(is_digit(expr[i])||expr[i]=='.')){
                num_str[ni++]=expr[i++];
            }
            num_str[ni]='\0';
            val=atof(num_str);
            nodes.data[++nodes.top]=create_node(NODE_NUMBER,val,"");
        }
        else if (is_alpha(expr[i])){
            alpha_i=0;
            while (i<len&&(is_alpha(expr[i])||is_digit(expr[i]))){
                if(alpha_i<11) {
                    name[alpha_i++]=expr[i];
                }
                i++;
            }
            name[alpha_i]='\0';
            
            if(strcmp(name,"x")==0||strcmp(name,"X")==0){
                nodes.data[++nodes.top]=create_node(NODE_VARIABLE,0,"x");
            }else if(strcmp(name, "pi")==0||strcmp(name, "PI")==0){
                nodes.data[++nodes.top]=create_node(NODE_NUMBER,PI,"");
            }else if(strcmp(name, "e")==0||strcmp(name, "E")==0){
                nodes.data[++nodes.top] = create_node(NODE_NUMBER,E,"");
            } 
			else {
                if(strcmp(name,"sin")==0){
                	ops.data[++ops.top] = 's';
				}else if(strcmp(name,"cos")==0){
					ops.data[++ops.top] = 'c';
				}else if(strcmp(name,"log")==0){
					ops.data[++ops.top] = 'g';
				}else if(strcmp(name,"ln")==0){
					ops.data[++ops.top] = 'l';
				}  else if(strcmp(name,"exp")==0){
					ops.data[++ops.top] = 'e';
				}else if(strcmp(name,"arcsin")==0||strcmp(name,"asin")==0){
					ops.data[++ops.top] = 'i';
				}else if(strcmp(name,"arccos")==0||strcmp(name,"acos")==0){
					ops.data[++ops.top] = 'o';
				}else if(strcmp(name,"arctan")==0||strcmp(name,"atan")==0){
					ops.data[++ops.top] = 'a';
				}else if(strcmp(name,"tan")==0){
					ops.data[++ops.top]='t';
				}else if(strcmp(name,"cot")==0){
					ops.data[++ops.top]='q';
				}else if(strcmp(name,"arccot")==0||strcmp(name,"acot")==0){
					ops.data[++ops.top] = 'u';
				}else if(strcmp(name,"sec")==0){
					ops.data[++ops.top]='S';
				}else if(strcmp(name,"csc")==0){
					ops.data[++ops.top]='C';
				}else if(strcmp(name,"arcsec")==0|| strcmp(name,"asec")==0){
					ops.data[++ops.top]='R';
				}else if(strcmp(name,"arccsc")==0||strcmp(name,"acsc")==0){
					ops.data[++ops.top] = 'K';
				}
			}
        }
        else if(expr[i]=='('){
            ops.data[++ops.top]='(';
            i++;
        }
        else if(expr[i]==')'){
            while(ops.top>=0&&ops.data[ops.top]!='('){
                op=ops.data[ops.top--];
                right=nodes.data[nodes.top--];
                left=nodes.data[nodes.top--];
                op_str[0]=op;
                op_str[1]='\0';
                op_node=create_node(NODE_OPERATOR,0,op_str);
                op_node->left=left;
                op_node->right=right;
                nodes.data[++nodes.top]=op_node;
            }
            if(ops.top>=0&&ops.data[ops.top]=='('){
                ops.top--; 
            }
            
            if(ops.top>= 0&&(ops.data[ops.top]=='s'||ops.data[ops.top]=='c'||ops.data[ops.top]=='t'||ops.data[ops.top]=='q'||ops.data[ops.top]=='g' 
			||ops.data[ops.top]=='l'||ops.data[ops.top]=='e'||ops.data[ops.top]=='i'||ops.data[ops.top]=='o' ||ops.data[ops.top]=='a'||ops.data[ops.top]=='u')){
                func_char=ops.data[ops.top--];
                child=nodes.data[nodes.top--];
                func_node=NULL;
                
                if(func_char=='s'){
                	func_node=create_node(NODE_FUNCTION,0,"sin");
				}else if(func_char=='c'){
                	func_node=create_node(NODE_FUNCTION,0,"cos");
				}else if(func_char=='g'){
                        func_node=create_node(NODE_FUNCTION,0,"log");
                        func_node->right=child;  
                        func_node->left=nodes.data[nodes.top--];
                }else if(func_char=='l'){
                	func_node=create_node(NODE_FUNCTION,0,"ln");
				}else if(func_char=='e'){
                	func_node=create_node(NODE_FUNCTION,0,"exp");
				}else if(func_char=='i'){
                	func_node=create_node(NODE_FUNCTION,0,"arcsin");
				}else if(func_char=='o'){
                	func_node=create_node(NODE_FUNCTION,0,"arccos");
				}else if(func_char=='a'){
                	func_node=create_node(NODE_FUNCTION,0,"arctan");
				}else if(func_char=='t'){
                	func_node=create_node(NODE_FUNCTION,0,"tan");
				}else if(func_char=='q'){
                	func_node=create_node(NODE_FUNCTION,0,"cot");
				}else if(func_char=='u'){
                	func_node=create_node(NODE_FUNCTION,0,"arccot");
				}else if(func_char=='S'){
                	func_node=create_node(NODE_FUNCTION,0,"sec");
				}else if(func_char=='C'){
                	func_node=create_node(NODE_FUNCTION,0,"csc");
				}else if(func_char=='R'){
                	func_node=create_node(NODE_FUNCTION,0,"arcsec");
				}else if(func_char=='K'){
                	func_node=create_node(NODE_FUNCTION,0,"arccsc");
				}
				if(func_char!='g'){          
                    func_node->right=child;
                } 
                nodes.data[++nodes.top]=func_node;
            }
            i++;
        }
        else if(expr[i]==','){
    while(ops.top>=0&&ops.data[ops.top]!='('){
        op=ops.data[ops.top--];
        right=nodes.data[nodes.top--];
        left=nodes.data[nodes.top--];
        op_str[0]=op;
        op_str[1]='\0';
        op_node=create_node(NODE_OPERATOR,0,op_str);
        op_node->left=left;
        op_node->right=right;
        nodes.data[++nodes.top]=op_node;
    }
    i++;
}
		else if(expr[i]=='+'||expr[i]=='-'||expr[i]=='*'||expr[i]=='/'||expr[i]=='^'||expr[i]=='_'){
                if(expr[i]=='-'&&(i==0||expr[i-1]=='('||expr[i-1]==',')){
                    nodes.data[++nodes.top]=create_node(NODE_NUMBER,0.0,"");
                }
			while(ops.top>=0&&ops.data[ops.top]!='(' &&(ops.data[ops.top]=='+'||ops.data[ops.top]=='-'||ops.data[ops.top]=='*'||ops.data[ops.top]=='/'||ops.data[ops.top]=='^'||ops.data[ops.top]=='_')&&
                   operatoronceligi(ops.data[ops.top])>=operatoronceligi(expr[i])){
                op=ops.data[ops.top--];
                right=nodes.data[nodes.top--];
                left=nodes.data[nodes.top--];
                op_str[0]=op;
                op_str[1]='\0'; 
                op_node=create_node(NODE_OPERATOR,0,op_str);
                op_node->left=left;
                op_node->right=right;
                nodes.data[++nodes.top]=op_node;
            }
            ops.data[++ops.top]=expr[i];
            i++;
        }
        else{
            i++; 
        }
    }
    
    while(ops.top>=0){
        op=ops.data[ops.top--];
        right=nodes.data[nodes.top--];
        left=nodes.data[nodes.top--];
        op_str[0]=op;
        op_str[1]='\0';
        op_node=create_node(NODE_OPERATOR,0,op_str);
        op_node->left=left;
        op_node->right=right;
        nodes.data[++nodes.top]=op_node;
    }
    if(nodes.top==0){
    sonuc=nodes.data[0];
    } else {
    sonuc=NULL;
    }
    nodestack_free(&nodes);
    charstack_free(&ops);
    free(num_str);
    free(name);
    free(op_str);
	return sonuc;
}
int fonksiyonmu(char* str,int index){
    if(strncmp(&str[index],"sin",3)==0){
        return 3;
    }else if(strncmp(&str[index],"cos",3)==0){
        return 3;
    }else if(strncmp(&str[index],"tan",3)==0){
        return 3;
    }else if(strncmp(&str[index],"log",3)==0){
        return 3;
    }else if(strncmp(&str[index],"ln",2)==0){
        return 2;
    }else if(strncmp(&str[index],"exp",3)==0){
        return 3;
    }else if(strncmp(&str[index],"arcsin",6)==0){
        return 6;
    }else if(strncmp(&str[index],"arccos",6)==0){
        return 6;
    }else if(strncmp(&str[index],"arctan",6)==0){
        return 6;
    }else if(strncmp(&str[index],"cot",3)==0){
        return 3;
	}else if(strncmp(&str[index],"arccot",6)==0){
        return 6;
	}
    return 0;
}
char* implicit_multiplication(char* expr){
    int i,j,k,len,f_len,sag_uygun,sol_uygun;
    char next,curr;
    char* yeni;
    char* temiz_expr;
    len=strlen(expr);
    temiz_expr=(char*)malloc(sizeof(char)*(len + 1));
    i=0;
    j=0;
    while(expr[i]!='\0'){
        if(expr[i]!=' '&&expr[i]!='\t'&&expr[i]!='\n'&&expr[i]!='\r'){
            temiz_expr[j++]=expr[i];
        }
        i++;
    }
    temiz_expr[j]='\0';
    len=strlen(temiz_expr);
    yeni=(char*)malloc(sizeof(char)*(len*3 + 1));
    i=0;
    j=0;
    while(i<len){
        f_len=fonksiyonmu(temiz_expr, i);  
        if(f_len>0){
            for(k=0;k<f_len;k++){
                yeni[j]=temiz_expr[i];     
                j++;
                i++;
            }
        }else{
            yeni[j]=temiz_expr[i];         
            j++;
            i++;
        }
        if(i<len){
            curr=yeni[j-1];
            next=temiz_expr[i];            
            sol_uygun=0;
            sag_uygun=0;
            if(is_digit(curr)||curr=='x'||curr=='X'||curr==')'||curr=='e'||curr=='i'){
                sol_uygun=1;
            }
            if(curr == '_'){
            	sol_uygun=0;
			}
            if(curr == ','){
            	sol_uygun=0;
			}
            if(next=='x'||next=='X'||next=='('||is_alpha(next)){
                sag_uygun=1;
            }
            if(next == ','){
            	sag_uygun=0;
			}
            if(sol_uygun==1 && sag_uygun==1){
                if(curr!='+'&&curr!='-'&&curr!='*'&&curr!='/'&&curr!='^'&&curr!='_'){
                    yeni[j]='*';
                    j++;
                }
            }
        }
    }
    yeni[j]='\0';
    free(temiz_expr);
    return yeni;
}
double hesapla_fonksiyon(char* ifade_stringi, double x_degeri){
    double sonuc;
    TreeNode* fonksiyon_agaci;
    sonuc=0.0;
    char* yeni_ifade;
    yeni_ifade=implicit_multiplication(ifade_stringi);
	fonksiyon_agaci=parse_expression(yeni_ifade);
    free(yeni_ifade);
    if (fonksiyon_agaci!=NULL) {
        sonuc=evaluate_tree(fonksiyon_agaci,x_degeri);
        free_tree(fonksiyon_agaci);
    } else {
        printf("\nHATA:'%s' IFADESI AGACA DONUSTURULEMEDI!!!\n",ifade_stringi);
        sonuc=0.0;
    }
    return sonuc;
}
void bisection(char* fonksiyon_stringi, double a, double b, double tolerance){
	double fa,fb,c,fc;
	int devam,iterasyon;
	devam=1;
	iterasyon=1;
	fa=hesapla_fonksiyon(fonksiyon_stringi,a);
	fb=hesapla_fonksiyon(fonksiyon_stringi,b);
	if(fa*fb>0){
		printf("\nHATA:BU ARALIKTA KOK OLMAYABILIR\n");
	}else{
		while(fabs(b-a)>tolerance&&devam==1){
			c=(b+a)/2;
			fc=hesapla_fonksiyon(fonksiyon_stringi,c);
			printf("\n%d.ITERASYON: [%f,%f]",iterasyon,a,b);
			printf("\nf(%f)=%f     f(%f)=%f   f(%f) x f(%f) <0",a,fa,b,fb,a,b);
			printf("\nc=%f   f(%f)=%f  HATA DEGERI:%f",c,c,fc,fabs(b-a));
            if(fc==0.0||fabs(fc)<1e-9){
               devam = 0;
            }else if(fa*fc < 0.0){
                b=c;
                fb=fc;
            }else {
                a=c;
                fa=fc;
            }
		    iterasyon++;
		    printf("\n\n\n");
		}
		printf("\nYAKLASIK KOK DEGERI: %f\n",c);
	}
}
void regula_falsi(char* fonksiyon_stringi, double a, double b, double tolerance){
	double fa,fb,c,fc,hata;
	int devam,iterasyon,payda;
	payda=2;
	devam=1;
	iterasyon=1;
	fa=hesapla_fonksiyon(fonksiyon_stringi,a);
	fb=hesapla_fonksiyon(fonksiyon_stringi,b);
	if(fa*fb>0){
		printf("\nHATA:BU ARALIKTA KOK OLMAYABILIR\n");
	}else{
		while(fabs(b-a)/payda>tolerance&&devam==1){
			hata=fabs(b-a)/payda;
			c=(a*fb-b*fa)/(fb-fa);
			fc=hesapla_fonksiyon(fonksiyon_stringi,c);
			printf("\n%d.ITERASYON: [%f,%f] ",iterasyon,a,b);
			printf("\nf(%f)=%f     f(%f)=%f   f(%f) x f(%f) <0",a,fa,b,fb,a,b);
			printf("\nc=%f   f(%f)=%f  HATA DEGERI:%f",c,c,fc,hata);
			payda=payda*2;
            if(fc==0.0||fabs(fc)<1e-9){
               devam = 0;
            }else if(fa*fc<0.0){
                b=c;
                fb=fc;
            }else {
                a=c;
                fa=fc;
            }
		    iterasyon++;
		    printf("\n\n\n");
		}
		printf("\nYAKLASIK KOK DEGERI: %f\n",c);	    	
        }
    }
    double turev_hesapla(char* fonksiyon_stringi, double x){
	double h=1e-6; 
    double fx_arti_h=hesapla_fonksiyon(fonksiyon_stringi,x + h);
    double fx_eksi_h=hesapla_fonksiyon(fonksiyon_stringi,x - h); 
    return (fx_arti_h-fx_eksi_h)/(2*h);
    }
    void newton_raphson(char* fonksiyon_stringi,double a,double tolerance){
    	double c,fa,hata;
    	int iterasyon;
    	iterasyon=1;
    	hata=tolerance+1;
		while(hata>tolerance){
    		fa=hesapla_fonksiyon(fonksiyon_stringi,a);
	        c=a-(fa/turev_hesapla(fonksiyon_stringi,a));
		    hata=fabs(c-a);
		    printf("\n%d.ITERASYON:  X%d=X%d-(F(X%d)/F'(X%d))\n",iterasyon,iterasyon,iterasyon-1,iterasyon-1,iterasyon-1);
		    printf("%f-(%f/%f)=%f",a,fa,turev_hesapla(fonksiyon_stringi,a),c);
			printf("\nX%d=%f        X%d=%f       HATA:%f",iterasyon-1,a,iterasyon,c,hata);
			a=c;
			printf("\n\n");
			iterasyon++;
		}
		printf("\nYAKLASIK KOK DEGERI: %f\n",a);
    }
void cholesky(double** A, int n){
    int i, j, k;
    double toplam, ic, toplam2, ax;
    double** L;
    double** LT;
    double** check;
    double* b_vec;
    double* y;
    double* x_sol;
    L=allocatematris(n);
    LT=allocatematris(n);
    check=allocatematris(n);
    b_vec=(double*)malloc(sizeof(double)*n);
    y=(double*)malloc(sizeof(double)*n);
    x_sol=(double*)malloc(sizeof(double)*n);
    for(i=0;i<n;i++){
        for(j=0;j<=i;j++){
            toplam=0.0;
            if(i==j){
                for(k=0;k<j;k++){
                    toplam+=L[j][k]*L[j][k];
                }
                ic=A[i][i]-toplam;
                if(ic<=0.0){
                    printf("\nHATA: MATRIS POZITIF TANIMLI DEGIL!\n");
                    printf("(%d. KOSEGEN ICIN NEGATIF/SIFIR IC DEGER: %.6f)\n", i+1, ic);
                    ozgurlukmatris(L, n);
                    ozgurlukmatris(LT, n);
                    ozgurlukmatris(check, n);
                    free(b_vec);
                    free(y);
                    free(x_sol);
                    return;
                }
                L[i][j]=sqrt(ic);
            } else {
                for(k=0;k<j;k++){
                    toplam+=L[i][k]*L[j][k];
                }
                L[i][j]=(A[i][j]-toplam)/L[j][j];
            }
        }
        for(j=i+1;j<n;j++){
            L[i][j]=0.0;
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            LT[i][j]=L[j][i];
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            check[i][j]=0.0;
            for (k=0;k<n;k++){
                check[i][j]+=L[i][k]*LT[k][j];
            }
        }
    }
    printf("\n---------- CHOLESKY AYRISTIRMASI ----------\n");
    printf("\nA = L * L^T\n");
    printf("\nL MATRISI:\n");
    printmatris(L, n);
    printf("\nL^T MATRISI:\n");
    printmatris(LT, n);
    printf("\nDOGRULAMA (L * L^T):\n");
    printmatris(check, n);
    printf("\nSAG TARAF VEKTORUNU GIRINIZ (b):\n");
    for(i=0;i<n;i++){
        printf("b[%d]: ",i + 1);
        scanf("%lf",&b_vec[i]);
    }
    for(i=0; i < n; i++){
        toplam=0.0;
        for(j=0;j<i;j++){
            toplam+=L[i][j]*y[j];
        }
        y[i]=(b_vec[i]-toplam)/L[i][i];
    }
    for(i=n-1;i>=0;i--){
        toplam2=0.0;
        for(j=i+1;j<n;j++) {
            toplam2+=LT[i][j]*x_sol[j];
        }
        x_sol[i]=(y[i]-toplam2)/LT[i][i];
    }
    printf("\n---------- COZUM VEKTORU ----------\n");
    for(i=0;i<n;i++){
        printf("x%d = %.10f\n", i + 1, x_sol[i]);
    }
    printf("\nDOGRULAMA (AX = B):\n");
    for(i=0;i<n;i++){
        ax=0.0;
        for(j=0;j<n;j++){
            ax+=A[i][j]*x_sol[j];
        }
        printf("Denklem %d: Ax = %-12.6f  b = %-12.6f  Fark = %.10f\n",i+1,ax,b_vec[i],fabs(ax - b_vec[i]));
    }
    ozgurlukmatris(L,n);
    ozgurlukmatris(LT,n);
    ozgurlukmatris(check,n);
    free(b_vec);
    free(y);
    free(x_sol);
}
void gauss_seidel(double** A, double* b, int n, double tolerance, int max_iter){
    int i, j, iter;
    double toplam, hata, max_hata;
    double* x;
    double* x_eski;
    int yakinsaklik;
    int diagonal_hata;
    double ax;
    ax=0.0;
    x=(double*)malloc(sizeof(double) * n);
    x_eski=(double*)malloc(sizeof(double) * n);
    for(i=0;i<n;i++){
    	x[i]=0.0;
	}
    printf("\n--------- GAUSS-SEIDEL YONTEMI ---------\n");
    diagonal_hata=0;
    for(i=0;i<n;i++) {
        if(A[i][i]==0.0){
        	diagonal_hata=1;
		}
    }
    if(diagonal_hata==1){
        printf("\nHATA: DIAGONAL ELEMAN SIFIR!\n");
        printf("Satirlari yeniden siralayin.\n");
        free(x);
        free(x_eski);
        return;
    }
    printf("\n%-10s", "Iterasyon");
    for(i=0;i<n;i++){
    	printf("  x%-9d", i+1);
	}
    printf("Max Hata\n");
    printf("----------");
    for(i=0;i<n;i++){
    	printf("  -----------");
	}
    printf("-----------\n");
    yakinsaklik=0;
    iter=1;
    while(iter<=max_iter&&yakinsaklik==0){
        for(i=0;i<n;i++){
        	x_eski[i]=x[i];
		}
        for(i=0;i<n;i++){
            toplam=0.0;
            for (j=0;j<n;j++){
                if (j!=i){
                	toplam+=A[i][j]*x[j];
				}
            }
            x[i]=(b[i]-toplam)/A[i][i];
        }
        max_hata=0.0;
        for(i=0;i<n;i++){
            hata=fabs(x[i]-x_eski[i]);
            if (hata>max_hata){
            	max_hata=hata;
			}
        }
        printf("%-10d", iter);
        for(i=0;i<n;i++){
        	printf("  %-11.6f", x[i]);
		}
        printf("  %-11.8f\n", max_hata);
        if(max_hata<tolerance){
            yakinsaklik=1;
            printf("\n%d. ITERASYONDA YAKINSAKLIK SAGLANDI (hata < %.2e)\n",iter,tolerance);
        }
        if(iter==max_iter&&yakinsaklik==0){
        	printf("\nUYARI: MAKSIMUM ITERASYON SAYISINA ULASILDI, YAKINSAKLIK SAGLANAMADI!\n");
		}
        iter++;
    }
    printf("\n---------- SONUCLAR ----------\n");
    for(i=0;i<n;i++){
    	printf("x%d = %.10f\n",i+1,x[i]);
	}
    printf("\nDogrulama (Ax):\n");
    for(i=0;i<n;i++){
        ax=0.0;
		for(j=0;j<n;j++){
        	ax+=A[i][j]*x[j];
		}
        printf("Denklem %d: Ax = %-12.6f  b = %-12.6f  Fark = %.8f\n",
            i+1,ax,b[i],fabs(ax-b[i]));
    }
    free(x);
    free(x_eski);
}
	double sayisalturevmerkezi(char* fonksiyon_stringi, double x,double h){
	double fx_arti_h=hesapla_fonksiyon(fonksiyon_stringi,x+h);
    double fx_eksi_h=hesapla_fonksiyon(fonksiyon_stringi,x-h); 
    return (fx_arti_h-fx_eksi_h)/(2*h);
    }
	double sayisalturevileri(char* fonksiyon_stringi, double x,double h){
    double fx_arti_h=hesapla_fonksiyon(fonksiyon_stringi,x+h);
    double fx=hesapla_fonksiyon(fonksiyon_stringi,x); 
    return (fx_arti_h-fx)/(h);
	}
	double sayisalturevgeri(char* fonksiyon_stringi, double x,double h){
    double fx= hesapla_fonksiyon(fonksiyon_stringi,x);
    double fx_eksi_h=hesapla_fonksiyon(fonksiyon_stringi,x-h); 
    return (fx-fx_eksi_h)/(h);
	}
    void simpson(char* fonksiyon_stringi, double a, double b, int n){
    int i,n13,n38;
    double h13, h38, x, fx,sum13, sum38,result13, result38;
    n13=n;
    n38=n;
    if (n13%2!=0){
    	n13++;
	}
    h13=(b-a)/n13;
    sum13=hesapla_fonksiyon(fonksiyon_stringi,a)+ hesapla_fonksiyon(fonksiyon_stringi,b);
    for (i=1;i<n13;i++) {
        x=a+i*h13;
        fx=hesapla_fonksiyon(fonksiyon_stringi,x);
        if (i%2==0){
        	sum13+=2.0*fx;
		}else{
		    sum13+=4.0*fx;	
		}
    }
    result13=(h13/3.0)*sum13;
    if (n38%3!=0){
    	n38+=(3-n38%3);
	}
    h38=(b-a)/n38;
    sum38=hesapla_fonksiyon(fonksiyon_stringi,a)+hesapla_fonksiyon(fonksiyon_stringi,b);
    for (i=1;i<n38;i++){
        x=a+i*h38;
        fx=hesapla_fonksiyon(fonksiyon_stringi,x);
        if(i% 3==0){
        	sum38+=2.0*fx;   
		}else{
		    sum38+=3.0*fx;  	
		}
    }
    result38=(3.0*h38/8.0)*sum38;
    printf("\n---------- SIMPSON YONTEMLERI ----------\n");
    printf("Fonksiyon : %s\n",fonksiyon_stringi);
    printf("Aralik    : [%f, %f]\n",a,b);
    printf("\n--- Simpson 1/3 Kurali ---\n");
    printf("Kullanilan n (cift olmali) : %d\n",n13);
    printf("Adim buyuklugu h           : %f\n",h13);
    printf("Sonuc                      : %.10f\n",result13);
    printf("\n--- Simpson 3/8 Kurali ---\n");
    printf("Kullanilan n (3'un kati)   : %d\n",n38);
    printf("Adim buyuklugu h           : %f\n",h38);
    printf("Sonuc                      : %.10f\n",result38);
    }
    void trapez(char* fonksiyon_stringi,double a,double b,int n){
    int i;
    double h,x,sum,result;
    h=(b-a)/n;
    sum=hesapla_fonksiyon(fonksiyon_stringi,a)+hesapla_fonksiyon(fonksiyon_stringi,b);
    for(i=1;i<n;i++) {
        x=a+i*h;
        sum+=2.0*hesapla_fonksiyon(fonksiyon_stringi,x);
    }
    result=(h/2.0)*sum;
    printf("\n---------- TRAPEZ YONTEMI ----------\n");
    printf("Fonksiyon        : %s\n", fonksiyon_stringi);
    printf("Aralik           : [%f, %f]\n",a,b);
    printf("Parca sayisi (n) : %d\n",n);
    printf("Adim buyuklugu h : %f\n",h);
    printf("Sonuc            : %.10f\n",result);
}
void newton_enterpolasyon(double* x,double* y,int n,double hedef){
    int i,j;
    double h,s,result,carpim,faktoriyel;
    double** fark;
    fark = (double**)malloc(sizeof(double*) * n);
    for(i=0;i<n;i++){
    	fark[i] = (double*)malloc(sizeof(double) * n);
	}
    for(i=0;i<n;i++){
    	fark[i][0]=y[i];
	}
    for(j=1;j<n;j++) {
        for (i=0;i<n-j;i++) {
            fark[i][j]=fark[i+1][j-1]-fark[i][j-1];
        }
    }
    printf("\nFark Tablosu:\n");
    printf("%-12s %-12s","x","f(x)");
    for(j=1;j<n;j++){
    	printf("  D^%d f     ",j);
	}
    printf("\n");
    for(i=0;i<n;i++){
        printf("%-12.4f %-12.4f",x[i],fark[i][0]);
        for(j=1;j<n-i;j++){
        	printf("%-12.4f ",fark[i][j]);
		}
        printf("\n");
    }
    h=x[1]-x[0];
    s=(hedef-x[0])/h;
    printf("\nh (adim)     : %.4f\n", h);
    printf("Hedef x      : %.4f\n", hedef);
    printf("s = (x-x0)/h : %.4f\n", s);
    result=fark[0][0]; 
    carpim=1.0;
    faktoriyel=1.0;
    for(j=1;j<n;j++){
        carpim*= (s-(j-1));   
        faktoriyel*=j;              
        result+=(carpim/faktoriyel)*fark[0][j];
    }

    printf("\nf(%.4f) = %.10f\n", hedef, result);
    for(i=0;i<n;i++){
    	free(fark[i]);
	}
	free(fark);
}
