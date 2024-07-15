// 22CS10030 Harshit Jain
// Assignment 0 Question 1

#include<stdio.h>
#include<string.h>

typedef struct{
    float x;
    float y;
    float z;        
} point;

typedef struct{
    int v1;
    int v2;
    int v3;
} triangle;

point surface_normal(point p1, point p2, point p3){
    point u,v,n;

    // u=p2-p1 
    u.x = p2.x-p1.x;
    u.y = p2.y-p1.y;
    u.z = p2.z-p1.z;
    
    // v=p3-p1
    v.x = p3.x-p1.x;
    v.y = p3.y-p1.y;
    v.z = p3.z-p1.z;

    n.x = u.y*v.z - u.z*v.y;
    n.y = u.z*v.x - u.x*v.z;
    n.z = u.x*v.y - u.y*v.x;

    return n;
}

int main(){
    char inputfile[100], outputfile[100];

    printf("Enter the file name to be read: ");
    scanf("%s",inputfile);
    printf("Enter the output file name: ");
    scanf("%s",outputfile);

    FILE *fptr;
    fptr = fopen(inputfile,"r");
    
    if(fptr==NULL){
        printf("\nInput File Not Found\n");
        return 0;
    }

    char str[1000];
    point pt[10000];
    triangle tri[10000];
    
    int pt_num,tri_num;
    while(fscanf(fptr,"%s",str) != EOF){
        if(strcmp(str,"Points")==0){
            fscanf(fptr,"%d",&pt_num);
        }
        else if(strcmp(str,"Triangles")==0){
            fscanf(fptr,"%d",&tri_num);
            break;
        }
    }

    int i;
    for(i=1;i<=pt_num;i++){
        fscanf(fptr,"%f",&(pt[i].x));
        fscanf(fptr,"%f",&(pt[i].y));
        fscanf(fptr,"%f",&(pt[i].z));
    }

    for(i=1;i<=tri_num;i++){
        fscanf(fptr,"%d",&(tri[i].v1));
        fscanf(fptr,"%d",&(tri[i].v2));
        fscanf(fptr,"%d",&(tri[i].v2));
    }

    fclose(fptr);

    printf("\n");
    printf("Number of points in the file: %d\n",pt_num);
    printf("Number of triangles in the file: %d\n\n",tri_num);
    printf("Computing the surface normals...\n\n");

    fptr = fopen(outputfile,"w");
    if(fptr==NULL){
        printf("\nOutput File Creation Failed\n");
        return 0;
    }
    fprintf(fptr, "List of surface normals:\n");

    point n;
    for(i=1;i<=tri_num;i++){
        n = surface_normal(pt[tri[i].v1],pt[tri[i].v2],pt[tri[i].v3]);
        fprintf(fptr,"%f %f %f\n",n.x,n.y,n.z);
    }

    fclose(fptr);

    printf("Surface normals have been computed and written to the file %s\n\n",outputfile);
    printf("Reading output file...\n\n");

    fptr = fopen(outputfile,"r");
    if(fptr==NULL){
        printf("\nOutput File Not Found\n");
        return 0;
    }

    char line[1001];
    while(fscanf(fptr," %[^\n]",line) != EOF){
        printf("%s\n",line);
    }

    fclose(fptr);
}
