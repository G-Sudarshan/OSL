/*
Roll No: 33318
Name: Sudarshan Gawale
Subject: OS Lab
Assignment 8: Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, C-Look
            considering the initial head position moving away from the spindle
*/

#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
// #include<GL/gl.h>
// #include<GL/freeglut.h>
using namespace std;

void display_vertice(int x, int y, int num){
	string str=to_string(num);
	int c=x;
 	for(int i=0;i<str.size();i++){
 		glColor3f(1.0,0.0,0.0);
 		glRasterPos2i(c,y);
 		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
 		c+=10;
 	}
 	glFlush();
	glutSwapBuffers();
}
void bres_line_func(int x1, int y1, int x2, int y2){
	float dx,dy,p,x,y;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	int xinc=1,yinc=1;
	if(x2<x1) xinc=-1;
	if(y2<y1) yinc=-1;
	x=x1;
	y=y1;
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	if(dx>dy){
		p=2*dy-dx;
		for(int i=0;i<dx;i++){
			if(p>=0){
				y+=yinc;
				p+=(2*(dy-dx));
			}else{
				p+=(2*dy);
			}
			x+=xinc;
			glVertex2i(x,y);
		}

	}
	else{
		p=2*dx-dy;
		for(int i=0;i<dy;i++){
			if(p>=0){
				x+=xinc;
				p+=(2*(dx-dy));
			}else{
				p+=(2*dx);
			}
			y+=yinc;
			glVertex2i(x,y);
		}
	}
	glFlush();
	glEnd();
	glutSwapBuffers();

}

void fcfs_algo(int n, vector<int>& vec, int p){
	glClear(GL_COLOR_BUFFER_BIT);
    	int ast=0, f1=50;
    	int r=450;
    	cout<<"Average Seek Time: ";
    	display_vertice(f1*2,r,f1);

    	for(int i=0;i<n;i++){
     		ast+=abs(vec[i]-f1);
        	bres_line_func(f1*2,r,vec[i]*2,r-25);
        	r-=25;
        	f1=vec[i];
        	display_vertice(f1*2,r,f1);
    	}
    	cout<<float(ast)/n<<endl;
    	glFlush();
	glutSwapBuffers();
}

void sstf_algo(int n, vector<int>& vec, int p){
	glClear(GL_COLOR_BUFFER_BIT);
    	vector<int>vec1(n);
    	vec1=vec;
    	sort(vec1.begin(), vec1.end());

    	int ast,c1,c2,c=0,f1=abs(p-vec1[0]);
    	for(int i=1;i<n;i++){
        	if(abs(p-vec1[i])<f1){
            		f1=abs(p-vec1[i]);
            		c=i;
        	}
    	}
    	int cnt=0, r=450;
    	display_vertice(p*2,r,p);
    	c1=c-1,c2=c+1;
    	ast=abs(vec1[c]-p);
    	bres_line_func(p*2,r,vec1[c]*2,r-25);
        r-=25;
        display_vertice(vec1[c]*2,r,vec1[c]);
    	while(cnt<=n){
        	if(c1>=0 && c2<n){
            		f1=abs(vec1[c1]-vec1[c]);
            		if(f1>abs(vec1[c2]-vec1[c])){
                		ast+=abs(vec1[c2]-vec1[c]);
                		bres_line_func(vec1[c]*2,r,vec1[c2]*2,r-25);
                		r-=25;
                		display_vertice(vec1[c2]*2,r,vec1[c2]);
                		c=c2;
                		c2++;
            		}else{
                		ast+=f1;
                		bres_line_func(vec1[c]*2,r,vec1[c1]*2,r-25);
                		r-=25;
                		display_vertice(vec1[c1]*2,r,vec1[c1]);
                		c=c1;
                		c1--;
            		}
            		cnt++;
       	}
        	else if(c1<0 && c2<n){
            		ast+=abs(vec1[c]-vec1[c2]);
            		bres_line_func(vec1[c]*2,r,vec1[c2]*2,r-25);
            		r-=25;
            		display_vertice(vec1[c2]*2,r,vec1[c2]);
            		c=c2;
            		c2++;
            		cnt++;
        	}
        	else if(c1>=0 && c2>=n){
            		ast+=abs(vec1[c]-vec1[c1]);
            		bres_line_func(vec1[c]*2,r,vec1[c1]*2,r-25);
            		r-=25;
            		display_vertice(vec1[c1]*2,r,vec1[c1]);
            		c=c1;
            		c1--;
            		cnt++;
        	}
        	else{
            		break;
        	}
    	}
    	cout<<"Average Seek Time: "<<float(ast)/n<<endl;
	glFlush();
	glutSwapBuffers();

}

void scan_algo(int n, vector<int>& vec, int p){
	glClear(GL_COLOR_BUFFER_BIT);
    	cout<<"considering disk size=250"<<endl;
    	vector<int>vec1(n);
    	vec1=vec;
    	sort(vec1.begin(), vec1.end());

    	int c;
    	for(int i=0;i<n;i++){
        	if(vec1[i]>=p){
            		break;
        	}else{
            		c=i;
        	}
    	}

    	int ast=0,f1=p,r=450;
    	display_vertice(f1*2,r,f1);
    	for(int i=c+1;i<n;i++){
        	ast+=abs(vec1[i]-f1);
        	bres_line_func(f1*2,r,vec1[i]*2,r-25);
            	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
    	}

    	ast+=abs(250-f1);
    	bres_line_func(f1*2,r,250*2,r-25);
        r-=25;
    	f1=250;
    	display_vertice(f1*2,r,f1);
    	for(int i=c;i>=0;i--){
        	ast+=abs(vec1[i]-f1);
        	bres_line_func(f1*2,r,vec1[i]*2,r-25);
            	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
    	}
    	cout<<"Average Seek Time: "<<float(ast)/n<<endl;
    	glFlush();
	glutSwapBuffers();
}

void cscan_algo(int n, vector<int>& vec, int p){
   	glClear(GL_COLOR_BUFFER_BIT);
    	cout<<"considering disk size=250"<<endl;
    	vector<int>vec1(n);
    	vec1=vec;
    	sort(vec1.begin(), vec1.end());

    	int c,r=450;
    	for(int i=0;i<n;i++){
      		if(vec1[i]>=p){
         		break;
          	}else{
            		c=i;
       	}
    	}

    	int ast=0,f1=p;
    	display_vertice(f1*2,r,f1);
    	for(int i=c+1;i<n;i++){
        	ast+=abs(vec1[i]-f1);
      		bres_line_func(f1*2,r,vec1[i]*2,r-25);
        	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
    	}

    	ast+=(abs(250-f1)+ 250);
    	bres_line_func(f1*2,r,250*2,r-25);
    	r-=25;
    	display_vertice(250*2,r,250);
    	bres_line_func(250*2,r,0,r-25);
    	r-=25;
    	f1=0;
    	display_vertice(0,r,0);
    	for(int i=0;i<=c;i++){
        	ast+=abs(vec1[i]-f1);
        	bres_line_func(f1*2,r,vec1[i]*2,r-25);
        	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
    	}
    	cout<<"Average Seek Time: "<<float(ast)/n<<endl;
    	glFlush();
    	glutSwapBuffers();

}

void look_algo(int n, vector<int>& vec, int p){
	glClear(GL_COLOR_BUFFER_BIT);
    	cout<<"considering disk size=250"<<endl;
    	vector<int>vec1(n);
    	vec1=vec;
    	sort(vec1.begin(), vec1.end());

    	int c,r=450;
    	for(int i=0;i<n;i++){
        	if(vec1[i]>=p){
            		break;
        	}else{
            		c=i;
        	}
    	}

    	int ast=0,f1=p;
    	display_vertice(f1*2,r,f1);
    	for(int i=c+1;i<n;i++){
       	ast+=abs(vec1[i]-f1);
        	bres_line_func(f1*2,r,vec1[i]*2,r-25);
        	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
    	}

    	for(int i=c;i>=0;i--){
        	ast+=abs(vec1[i]-f1);
        	bres_line_func(f1*2,r,vec1[i]*2,r-25);
        	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
	}
    	cout<<"Average Seek Time: "<<float(ast)/n<<endl;
    	glFlush();
    	glutSwapBuffers();
}

void clook_algo(int n, vector<int>& vec, int p){
	glClear(GL_COLOR_BUFFER_BIT);
    	cout<<"considering disk size=250"<<endl;
    	vector<int>vec1(n);
    	vec1=vec;
    	sort(vec1.begin(), vec1.end());

    	int c,r=450;
    	for(int i=0;i<n;i++){
        	if(vec1[i]>=p){
          	  	break;
        	}else{
            		c=i;
        	}
    	}

    	int ast=0,f1=p;
    	display_vertice(f1*2,r,f1);
    	for(int i=c+1;i<n;i++){
        	ast+=abs(vec1[i]-f1);
        	bres_line_func(f1*2,r,vec1[i]*2,r-25);
        	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
    	}

    	for(int i=0;i<=c;i++){
        	ast+=abs(vec1[i]-f1);
        	bres_line_func(f1*2,r,vec1[i]*2,r-25);
        	r-=25;
        	f1=vec1[i];
        	display_vertice(f1*2,r,f1);
    	}
    	cout<<"Average Seek Time: "<<float(ast)/n<<endl;
    	glFlush();
    	glutSwapBuffers();
}


void render_func(){
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,500.0,0.0,500.0);
	int n,p;
    	cout<<"No. of Tracks: ";
    	cin>>n;
    	vector<int>vec(n);
    	cout<<"Enter Requests:"<<endl;
    	for(int i=0;i<n;i++){
       	 cin>>vec[i];
   	 }
	cout<<"Initial Head Position: ";
    	cin>>p;

    	int ch;
    	while(true){
        	cout<<"\n< Operations >"<<endl;
        	cout<<"1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit"<<endl;
        	cout<<"Enter Choice: ";
        	cin>>ch;
        	if(ch==7){
         	   cout<<"Thank You!"<<endl;
          	  break;
        	}else{
          	  switch(ch){
             	  	case 1:
           	       	fcfs_algo(n, vec, p);
           	         	break;
                  	case 2:
                    		sstf_algo(n, vec, p);
                    		break;
                	case 3:
                    		scan_algo(n, vec, p);
                    		break;
                	case 4:
                    		cscan_algo(n, vec, p);
                    		break;
                	case 5:
                    		look_algo(n, vec, p);
                    		break;
                	case 6:
                    		clook_algo(n, vec, p);
                    		break;
                	default:
                    		cout<<"Invalid Op.No! Enter correct Op.No."<<endl;

            		}
        	}
    	}
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Disk Sheduling Algorithm");
	glutDisplayFunc(render_func);
	glutMainLoop();
	return 0;
}

/*______________________________________________________________________________
OutPut:

No. of Tracks: 7
Enter Requests:
82 170 43 140 24 16 190
Initial Head Position: 50

< Operations >
1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit
Enter Choice: 1
Average Seek Time: 91.7143

< Operations >
1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit
Enter Choice: 2
Average Seek Time: 29.7143

< Operations >
1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit
Enter Choice: 3
considering disk size=200, so end position=199
Average Seek Time: 47.4286

< Operations >
1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit
Enter Choice: 4
considering disk size=200, so end position=199
Average Seek Time: 55.8571

< Operations >
1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit
Enter Choice: 5
considering disk size=200, so end position=199
Average Seek Time: 44.8571

< Operations >
1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit
Enter Choice: 6
considering disk size=200, so end position=199
Average Seek Time: 48.7143

< Operations >
1.FCFS    2.SSTF      3.SCAN      4.CSCAN     5.LOOK      6.CLOOK        7.Exit
Enter Choice: 7
Thank You!

Process returned 0 (0x0)   execution time : 42.483 s
Press any key to continue.
______________________________________________________________________________*/
