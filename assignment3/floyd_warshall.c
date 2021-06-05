/* This is a code for COMP 201 assignment 3.
 * In this code, Floyd-Warshall algorithm is implemented
 * to find the shortest paths between any two cities
 * in a given graph of cities.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int INF = 1e7;  

/* Array of vertices. 
 * Each element of the str array contains a city name and 
 * its index in str becomes the city's numeric id.
 */
typedef struct vertices 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of cities in the array
	int city_count;
	// This attribute is the array of city names
	char (* str)[30];
} 
vertices;

/* Array of edges. 
 * Each element of the edge array contains the ids of two cities 
 * connected directy by a road and the length of the road.
 */
typedef struct edges 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of roads in the array
	int edge_count;
	// This attribute is the array of road information
	int (* edge)[3];
} 
edges;

vertices cities;

edges roads;

/* A two-dimensional array that shows 
 * the length of the shortest path connecting 
 * any two cities.
 */
int **city_graph;

/* A two-dimensional array that shows the direction 
 * to the shortest path between any two cities.
 */
int **shortest_paths;

/* A function that implements Floyd-Warshall algorithm. 
 * This algorithm finds the shortest path between 
 * any two vertices in a given graph.
 */
void floydWarshall()  
{  
	for (int k = 0; k < cities.city_count; k++) 
	{  
		for (int i = 0; i < cities.city_count; i++) 
		{  
			for (int j = 0; j < cities.city_count; j++) 
			{  

				// We cannot cross a road that doesn't exist  
				if ((city_graph[i][k] == INF) || (city_graph[k][j] == INF))  
				{
					continue;
				}  

				if (city_graph[i][j] > (city_graph[i][k] + city_graph[k][j])) 
				{  
					city_graph[i][j] = city_graph[i][k] + city_graph[k][j];  
					shortest_paths[i][j] = shortest_paths[i][k];  
				}  
			}  
		}  
	}  
} 

/* A function that initializes the values in 
 * city_graph and shortest_paths arrays.
 */
void initialise()  
{  
	for (int i = 0; i < cities.city_count; i++) 
	{  
		for (int j = 0; j < cities.city_count; j++) 
		{    

			// No edge between node i and j  
			if (city_graph[i][j] == INF)  
			{
				shortest_paths[i][j] = -1;
			}  
			else
			{
				shortest_paths[i][j] = j;
			}  
		}  
	}  
}

/* A function that inserts the name of a new city 
 * to the cities array.
 */
int lookup_string(char str[30]);
int insert_to_cities(char str[30]) 
{
	// Write your code here

	
       
 	// Check if the city name already exists in the array 

        for(int i=0; i<cities.city_count;i++){
		if(strcmp(str,cities.str[i])==0) return i;  // If it does, return the array index of the city 
	}
        cities.city_count=cities.city_count+1;
	cities.size=cities.size+cities.city_count*sizeof(char[30]);

	if(sizeof(cities.str)<=cities.city_count*sizeof(char[30])){
	    cities.str = realloc(cities.str,cities.size); 
	}
        strcpy(cities.str[cities.city_count-1],str);
         

        
	// If the city name doesn't exist, it is inserted to the cities array, and
	// return the array index of the city

	// If the dynamically allocated size of cities array is not large enough, 
	// the size of cities array is enlarged and the city name is inserted 
	// to the newly added region

	// Return the array index of the city.
	return (cities.city_count-1);
}

/* A function that looks up if a city name
 * is already in the cities array. 
 */
int lookup_string(char str[30]) 
{
	for(int i = 0; i < cities.city_count; i++) {
		if(strncmp(str, cities.str[i], 30) == 0)
			return i;
	}
	printf("city %s is not found\n", str);
	return -1;
}

void printPath(int u, int v)  
{  
	// Write your code here 
	int z=0;
        if(shortest_paths[u][v]>=0){ 
		printf("%s  %s",cities.str[u],cities.str[shortest_paths[u][v]] );
        	z=shortest_paths[u][v];   
	    	    while(z!=v){     //checks whether there are any different roads
		            z=shortest_paths[z][v]; 
        	            printf(" %s ",cities.str[z]);	
                    }
		printf("\n%d",city_graph[u][v] ); //prints the length

	}else{
        	printf("--NO PATH--"); 
	}
} 

int main(int argc, char *argv[])
{
	// Write your code here
        FILE* textFile;
	char *n =malloc(100*sizeof(char));
	if(argc==2) {
	   strcpy(n,argv[1]);	//taking command line input
	}
      
		
	// Allocate memory regions dynamically to cities array 
	// and roads array.
	
	roads.edge = malloc(sizeof(int[3]));
	roads.size=sizeof(int[3]);
        cities.str=malloc(sizeof(char[30]));	
        cities.size=sizeof(char[30]);
	// Read and parse the input file. Insert the city names to cities array.
	textFile=fopen(n,"r");
	char *theLine=malloc(1000*sizeof(char));
	char *token=malloc(100*sizeof(char));
	while(1){
	      fgets(theLine,1000,textFile);
	      if(feof(textFile)) {fclose(textFile); break;}
	      token=strtok(theLine," ");
	      while(token !=NULL){
		if(isalpha(token[0]))	{               //reading input.txt
							//initilizing city ids
	           insert_to_cities(token); 
		}
			
	        token=strtok(NULL," ");	      

	      }	      
	}
        free(token);


	// The index of the city name in the cities array becomes the city id. 
	// Insert city ids and road lengths to roads array.
	FILE *inputFile=fopen(n,"r");
	int counter=0;
	char *tokenizer=malloc(100*sizeof(char));
	while(1){
             fgets(theLine,1000,inputFile);
	     if(feof(inputFile)) {fclose(inputFile); break;}
	     tokenizer=strtok(theLine," ");
	     if(isalpha(tokenizer[0])) { //allocate memory if there is a city in the new line
		    roads.edge_count++;
		    roads.size=roads.size+roads.edge_count*sizeof(int[3]);
	     	if(sizeof(roads.edge)<=roads.edge_count*sizeof(int[3])){
	    	    roads.edge=realloc(roads.edge,roads.size); 
		}
	     } 
	     while(tokenizer !=NULL){
	     	    if(isalpha(tokenizer[0])){ //takes the city names
			for(int i=0;i<cities.city_count;i++){
			  if(strcmp(cities.str[i],tokenizer)==0){	 
       		             roads.edge[roads.edge_count-1][counter]=i;
			  }	  
        		}
	 		counter++;		
		    }
		    if(isdigit(tokenizer[0])){    //takes the length
		         roads.edge[roads.edge_count-1][counter]=atoi(tokenizer);
		       counter=0;	    
		    }
		    			    
		    	
		    tokenizer=strtok(NULL," ");
	     }
	
           
	}
	free(tokenizer);
        free(n);        
        free(theLine);
	// Allocate memory regions dynamically to city_graph, 
	// distance, and shortest_paths arrays.
        city_graph = malloc(cities.city_count*sizeof(int*));
        shortest_paths = malloc(roads.edge_count*sizeof(int*));
	for(int j=0;j<cities.city_count;j++){                      
	   	city_graph[j]=malloc(cities.city_count*sizeof(int));   //memory allocation
	}
	for(int j=0;j<roads.edge_count;j++){  
                shortest_paths[j]=malloc(roads.edge_count*sizeof(int));  //memory allocation
        }
        
	
         
	// Initialize the values in city_graph array with road lengths, 
	// such that the value in city_graph[i][j] is the road length 
	// between cities i and j if these cities are directly connected 
	// by a road 
	// For cities m and n that are not connected directly by a road, 
	// the value in city_graph[m][n] will be INF, 
        // which is a large value like 10M, 
	// that is assumed to be infinite. 
	
	for(int k=0;k<cities.city_count;k++){
           for(int l=0;l<cities.city_count;l++){
                city_graph[k][l]=INF;            //initializing the whole array before putting road inputs
           }
        }
        
	
    	for(int c=0;c<cities.city_count;c++){
	     
           for(int d=0;d<cities.city_count;d++){
	 	                  
	        for(int e=0;e<roads.edge_count;e++){
 			
		        if(roads.edge[e][0]==c && roads.edge[e][1]==d ){
                               	city_graph[c][d]= roads.edge[e][2];      //Initialize city_graph according to
				city_graph[d][c]= roads.edge[e][2];      //the road inputs
                          			
			}
		}	

	     }

	}

	free(roads.edge);
      	initialise();
	floydWarshall();
	int g=1; //used for to take first and second city correctly
        
	while(1) {
		// prompt user to enter two city names
		char* name=malloc(50*sizeof(char));
                printf("\n\nEnter two city name OR write EXIT to leave program\n ");
		scanf("%[^\n]%*c",name);
		char *firstCity=malloc(50*sizeof(char));
	        char *secondCity=malloc(50*sizeof(char));
	        char *p=malloc(50*sizeof(char));
		
	        p = strtok(name, " ");
		if(strcmp(p,"EXIT")==0){ //to leave program
		   free(firstCity);
                   free(secondCity);
                   free(name);
		   break;	
		}

		while(p != NULL) {
		   
		    if(g==1){
		       strcpy(firstCity,p); 
	               g++;	       
		    }else{
		       strcpy(secondCity,p);
	               break;	       
		    }	    
    		    p = strtok(NULL, " ");
		}
		
		g=1;
		
		if(strcmp(firstCity,secondCity)!=0){
	        	if(lookup_string(firstCity)>=0 && lookup_string(secondCity)>=0){
				// print the shortest path between the two cities
				// print the length of the path
			        printPath(lookup_string(firstCity),lookup_string(secondCity));
			}

		}else{
		  printf("\nPlease enter two different city names!\n");
		}
		free(firstCity);
		free(secondCity);
		free(name);
		
  
    	
	}
    	free(cities.str);
        free(city_graph);
	free(shortest_paths);
	
	return 0;	
}
