#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF 999999999


long int m[20][20];   //Ο πινακας κοστους
int s[20][20];     //Αποθηκευει το μεγιστο σημειο διαχωρισμου k (split point)
int dim[20];    //Το πολυ 19 πινακες θα διαβαζονται (μεχρι 20 διαστασεις αναγνωση απο το αρχειο)
int i, j, n;



void print_optimal_sequence(int i,int j);
void matrix_multiply(void);
int matrix_chain_order(int dim[], int i, int j);




int main (void)
{
	int k;
	FILE *fp;
	
	
	
	fp=fopen("table_dimensions.txt", "r");
	if (fp==NULL)
	{
		printf("Could not open file!\n");
		return 1;
	}
	
	
	fscanf(fp, "%d", &n);   //Διαβασμα του πληθους πινακων
	
	for (k=0 ; k<n+1 ; k++)  //Διαβασμα των διαστασεων των πινακων
	{
		fscanf(fp, "%d", &dim[k]);
	}
	
	fclose(fp);
	
	
	
	for(i=1 ; i<=n ; i++)    //Αρχικοποιηση των πινακων m[][], και s[][]
	{
		for(j=i+1 ; j<=n ; j++)
		{
			m[i][i]=0;
			m[i][j]=INF;
			s[i][j]=0;
		}
	}
	
	
	matrix_multiply();    //Πολλαπλασιασμος πινακων
	
	
	
	printf("\nCost matrix M:\n");     //Εκτυπωση του πινακα κοστους m[][]
	for(i=1 ; i<=n ; i++)
	{
		for(j=i ; j<=n ; j++)
		{
			printf("m[%d][%d]: %ld\n", i, j, m[i][j]);
		}
	}
	printf("\n");
	
	
	
	i=1;
	j=n;
	printf("Optimal multiplication sequence is: ");   //Εκτυπωση της βελτιστης σειρας πολλαπλασιασμου των πινακων
	print_optimal_sequence(i,j);
	printf("\n\nMinimum number of multiplications is : %d\n", matrix_chain_order(dim, 1, n));   //Εκτυπωση του ελαχιστου δυνατου αριθμου πολλαπλασιασμων μεταξυ των πινακων
	
	
	
	getchar();   //(Για να μην κλεινει το παραθυρο του εκτελεσιμου αρχειου)
	
	return 0;
}






void print_optimal_sequence(int i,int j)    //Συναρτηση εκτυπωσης της βελτιστης σειρας πολλαπλασιασμου
{
	if (i == j)
	{
		printf(" A%d ",i);
	}
	else
    {
		printf("( ");
		print_optimal_sequence(i, s[i][j]);
		print_optimal_sequence(s[i][j] + 1, j);
		printf(" )");
    }
}





void matrix_multiply(void)  //Συναρτηση υπολογισμου των πινακων m[][] και s[][]
{
	long int q;
	int k;
	
	for(i=n ; i>0 ; i--)
	{
		for(j=i ; j<=n ; j++)
		{
			if(i==j)
				m[i][j]=0;
			else
			{
				for(k=i ; k<j ; k++)
				{
					q = m[i][k] + m[k+1][j] + dim[i-1]*dim[k]*dim[j];
					if(q<m[i][j])
					{
						m[i][j]=q;
						s[i][j]=k;
					}
				}
			}
		}
	}
}




int matrix_chain_order(int dim[], int i, int j)   //Συναρτηση υπολογισμου του ελαχιστου δυνατου αριθμου πραξεων (για πραξη πολλαπλασιασμου)
{
    if(i == j)
	{
        return 0;
	}
	
    int k;
    int min = INT_MAX;
    int count;
 
    for (k = i; k <j; k++)
    {
        count = matrix_chain_order(dim, i, k) + matrix_chain_order(dim, k+1, j) + dim[i-1]*dim[k]*dim[j];
 
        if (count < min)
		{
            min = count;
		}
    }
 
    
    return min;
}
