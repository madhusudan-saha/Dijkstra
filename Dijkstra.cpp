#include<iostream.h>
#include<stdlib.h>
#include<string.h>


class edge
{
	char name2[10];
	int weight;
	friend class graph;
};

class vertex
{
	char name1[10];
	int m,n,p;
	int label;
	vertex *link1[50];
	edge *link2[50];
	friend class graph;
public:
	vertex()
	{
		label=999;
		m=n=p=0;
	}
};

class graph
{
	vertex *vertices[50];
	edge *edges[50];
	int v;
	int e;
	char source[10],target[10];
public:
	void getvertices();
	void getedges();
	void getconnections();
	void compute();
	void displabels();
	void shortestdist();
	void shortestpath();
};

void graph :: getvertices()
{
	cout<<"Enter the number of vertices:\t";
	cin>>v;
	cout<<"Enter the names of vertices:"<<endl;

	for(int i=0;i<v;i++)
	{
		vertices[i]=new vertex;
		cin>>vertices[i]->name1;
		if(i!=v-1)
			cout<<"Next:"<<endl;
	}

}

void graph :: getedges()
{
	cout<<"Enter the number of edges:\t";
	cin>>e;
	cout<<"Enter the names of edges and their weights:"<<endl;
	cout<<"Example:\ne1\nWeight"<<endl;

	for(int i=0;i<e;i++)
	{
		edges[i]=new edge;
		cin>>edges[i]->name2;
		cin>>edges[i]->weight;
		if(i!=e-1)
			cout<<"Next:"<<endl;
	}
}

void graph :: getconnections()
{
	int i,j,k,l;
	char temp1[10],temp2[10],temp3[10];

	cout<<"Enter the connections..."<<endl;
	cout<<"Example:\nv1\ne1\nv2"<<endl;

	for(i=0;i<e;i++)
	{
		cin>>temp1;
		cin>>temp2;
		cin>>temp3;

		for(j=0;j<v;j++)
		{
			if(strcmp(vertices[j]->name1,temp1)==0)
				break;
		}

		for(k=0;k<e;k++)
		{
			if(strcmp(edges[k]->name2,temp2)==0)
				break;
		}

		for(l=0;l<v;l++)
		{
			if(strcmp(vertices[l]->name1,temp3)==0)
				break;
		}

		vertices[j]->link1[vertices[j]->m]=vertices[l];
		vertices[l]->link1[vertices[l]->m]=vertices[j];
		vertices[j]->link2[vertices[j]->n]=edges[k];
		vertices[l]->link2[vertices[l]->n]=edges[k];

		vertices[j]->m++;
		vertices[l]->m++;
		vertices[j]->n++;
		vertices[l]->n++;

		if(i!=e-1)
			cout<<"Next:"<<endl;
	}

}

void graph :: compute()
{
	int i;

	cout<<"Enter source:"<<endl;
	cin>>source;

	for(i=0;i<v;i++)
	{
		if(strcmp(vertices[i]->name1,source)==0)
		{
			vertices[i]->label=0;
			break;
		}
	}

	for(i=0;i<v;i++)
	{
		for(int h=0;h<vertices[i]->n;h++)
		{
			if(vertices[i]->link1[h]->label>vertices[i]->link2[h]->weight+vertices[i]->label)
			{
				vertices[i]->link1[h]->label=vertices[i]->link2[h]->weight+vertices[i]->label;

			}
		}
	}
}

void graph :: displabels()
{
	cout<<"The labels of the vertices are:"<<endl;
	for(int i=0;i<v;i++)
	{
		cout<<vertices[i]->name1<<"-"<<vertices[i]->label<<endl;
	}
}

void graph :: shortestdist()
{
	cout<<"Enter target:"<<endl;
	cin>>target;

	for(int i=0;i<v;i++)
	{
		if(strcmp(vertices[i]->name1,target)==0)
		{
			cout<<"The shortest distance is:\n"<<vertices[i]->label<<endl;
			break;
		}
	}
}

void graph :: shortestpath()
{
	int i,j=0,k,h,flag1,flag2=1;
	char temp[10];
	int index[50];

	cout<<"Enter target:"<<endl;
	cin>>target;

	for(i=0;i<v;i++)
	{
		if(strcmp(vertices[i]->name1,target)==0)
		{
			break;
		}
	}

	index[j]=i;

	while(1)
	{

	while(strcmp(vertices[i]->name1,source)!=0)
	{
		flag1=0;

	if(flag2==2)
	for(h=vertices[i]->p;h<vertices[i]->m;h++)
	{
		vertices[i]->p=h+1;
		if(vertices[i]->label==vertices[i]->link2[h]->weight+vertices[i]->link1[h]->label)
		{

			strcpy(temp,vertices[i]->link1[h]->name1);
			flag1=1;
			flag2=0;
			break;
		}
	}

	else if(flag2==1)
	for(h=vertices[i]->p;h<vertices[i]->m;h++)
	{
		if(vertices[i]->label==vertices[i]->link2[h]->weight+vertices[i]->link1[h]->label)
		{
			vertices[i]->p=h+1;
			strcpy(temp,vertices[i]->link1[h]->name1);
			flag1=1;
			break;
		}
	}

	else if(flag2==0)
	for(h=0;h<vertices[i]->m;h++)
	{
		if(vertices[i]->label==vertices[i]->link2[h]->weight+vertices[i]->link1[h]->label)
		{
			strcpy(temp,vertices[i]->link1[h]->name1);
			flag1=1;
			break;
		}
	}

	if(flag1==1)
	for(k=0;k<v;k++)
	{
		if(strcmp(vertices[k]->name1,temp)==0)
		{
			j++;
			index[j]=k;
			i=k;
			break;
		}
	}
	else
		break;
	}

	if(flag1==1)
	{
	for(k=j;k>0;k--)
	{
		cout<<vertices[index[k]]->name1<<"-";
	}
	cout<<target<<endl;
	}

	if(strcmp(vertices[index[j]]->name1,source)==0)
		j--;

	while(vertices[index[j]]->p>=vertices[index[j]]->m && j!=0)
	{
		j--;
	}

	flag2=2;
	if(strcmp(vertices[index[j]]->name1,target)==0 && vertices[index[j]]->p>=vertices[index[j]]->m)
		break;
	i=index[j];

	}
}

int main()
{
	int ch=4;
	graph g;

	do
	{

	switch(ch)
	{
	case 1:
		g.displabels();
		break;
	case 2:
		g.shortestdist();
		break;
	case 3:
		g.shortestpath();
		break;
	case 4:
		g.getvertices();
		g.getedges();
		g.getconnections();
		g.compute();
		break;
	case 5:
		exit(0);
	default:
		cout<<"INVALID INPUT!!!"<<endl;
		break;
	}

	cout<<"\n******MENU********"<<endl
		<<"1. Display labels of vertices."<<endl
		<<"2. Display shortest distance."<<endl
		<<"3. Display shortest path."<<endl
		<<"4. Select another graph."<<endl
		<<"5. Exit"<<endl;
	cout<<"Enter your choice:"<<endl;
	cin>>ch;

	}while(ch!=5);
	return 0;
}
