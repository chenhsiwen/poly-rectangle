#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#define INF 1e5
using namespace std;
void timeofbuild(int num);

struct node
{
    point p;
    node *left;
    node *right;
    node *parent;
};
class twoDtree
{
    public:
        twoDtree();
        void insert(point p);
        void deletion(point p);
        node *search(point p);
        void destroy_tree();
        int numofnode();
        int numinrange(float low_x,float up_x,float low_y,float up_y,vector<struct point>& pointArr);
        point nearestnode(point p);
    private:
        void destroy_tree(node *leaf);
        void subtree(node *leaf,vector<struct point>& pointArr);
        void insert(char dim,point p, node *leaf);
        void deletion(point p, node *leaf);
        node *search_x(point p, node *leaf);
        node *search_y(point p, node *leaf);
        void node_ini(point p,node* leaf);
        int numofnode(node *leaf);
        int numofrange_x(float low_x,float up_x,float low_y,float up_y,node *leaf,vector<struct point>& pointArr);
        int numofrange_y(float low_x,float up_x,float low_y,float up_y,node *leaf,vector<struct point>& pointArr);
        int nearestsquare(point p,float D,vector<struct point>& pointArr);
        float dis(point p1, point p2);
        point mindis(vector<struct point>& pointArr,point p ,float& D);
        point nearestnode(point p,float D);
        node *root;

};
twoDtree::twoDtree()
{
    root=NULL;
}
void twoDtree::destroy_tree()
{
    destroy_tree(root);
}
void twoDtree::destroy_tree(node *leaf)
{
    if(leaf!=NULL)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}
void twoDtree::node_ini(point p,node* leaf)
{
    leaf->p.x_value=p.x_value;
    leaf->p.y_value=p.y_value;
    leaf->left=NULL;
    leaf->right=NULL;
}
void twoDtree::insert(point p)
{
    if(root!=NULL)
        insert('x',p, root);
    else
    {
        root=new node;
        node_ini(p,root);
    }
}
void twoDtree::insert(char dim,point p, node *leaf)
{
    float comp=0,comp2=0;
    if (dim=='x')
    {
        comp=p.x_value;
        comp2=leaf->p.x_value;
        dim='y';
    }

    else if (dim=='y')
    {
        comp=p.y_value;
        comp2=leaf->p.y_value;
        dim='x';
    }

    if(comp<comp2)
    {
        if(leaf->left!=NULL)
            insert(dim,p,leaf->left);
        else
        {
            leaf->left=new node;
            node_ini(p,leaf->left);
            leaf->left->parent=leaf;
        }
    }
    else if(comp>=comp2)
    {
        if(leaf->right!=NULL)
            insert(dim,p,leaf->right);
        else
        {
            leaf->right=new node;
            node_ini(p,leaf->right);
            leaf->right->parent=leaf;
        }
    }
}
void twoDtree::deletion(point p)
{
    deletion(p,root);
}
void twoDtree::deletion(point p, node *leaf)
{
    if(search(p)==NULL)
    {
        cout<<"do";
        return;
    }
    else
    {
        vector<struct point> temp;
        subtree(search(p),temp);
        if(search(p)->parent->left==search(p))
            search(p)->parent->left=NULL;
        else
            search(p)->parent->right=NULL;
        for(int i=1;i<temp.size();i++)
        {
            insert(temp[i]);
        }


        return;
    }



}
void twoDtree::subtree(node *leaf,vector<struct point>& pointArr)
{
    if (leaf != NULL)
    {
        pointArr.push_back(leaf->p);
        subtree(leaf->left,pointArr);
        subtree(leaf->right,pointArr);
    }
    return;

}
node *twoDtree::search(point p)
{
    return search_x(p, root);
}
node *twoDtree::search_x(point p, node *leaf)
{
    if(leaf!=NULL)
    {
        if(p.x_value==leaf->p.x_value)
        {
            if(p.y_value==leaf->p.y_value)
                return leaf;
            else
                return search_y(p, leaf->right);
        }

        if(p.x_value<leaf->p.x_value)
            return search_y(p, leaf->left);
        else
            return search_y(p, leaf->right);
    }
    else
        return NULL;
}
node *twoDtree::search_y(point p, node *leaf)
{
    if(leaf!=NULL)
    {
        if(p.y_value==leaf->p.y_value)
        {
            if(p.x_value==leaf->p.x_value)
                return leaf;
            else
                return search_x(p, leaf->right);
        }
        if(p.y_value<leaf->p.y_value)
            return search_x(p, leaf->left);
        else
            return search_x(p, leaf->right);
    }
    else
        return NULL;
}
 int twoDtree::numofnode()
 {
     return numofnode(root);
 }
 int twoDtree::numofnode(node *leaf)
 {
     int count=0;
     if (leaf != NULL) {
        count = 1 + numofnode(leaf->left) + numofnode(leaf->right);
    }
    return count;

 }
float twoDtree::dis(point p1,point p2)
{
    return sqrt(pow(p1.x_value-p2.x_value,2)+pow(p1.y_value-p2.y_value,2));
}
point twoDtree::mindis(vector<struct point>& pointArr, point p ,float& D)
{
    float min_d=INF;
    point temp;
    for(int i=0;i<pointArr.size();i++)
    {
        if(min_d>dis(p,pointArr[i]))
        {
            temp.x_value=pointArr[i].x_value;
            temp.y_value=pointArr[i].y_value;
            min_d=dis(p,pointArr[i]);
        }

    }
    pointArr.clear();
    return temp;
}
int twoDtree::numinrange(float low_x,float up_x,float low_y,float up_y,vector<struct point>& pointArr)
{
    numofrange_x(low_x,up_x,low_y,up_y,root,pointArr);
}
int twoDtree::numofrange_x(float low_x,float up_x,float low_y,float up_y, node* leaf ,vector<struct point>& pointArr)
{
    int count=0;
    if (leaf!=NULL)
    {
        if(low_x>leaf->p.x_value)
            count=numofrange_y(low_x,up_x,low_y,up_y,leaf->right,pointArr);
        else if(up_x<leaf->p.x_value)
            count=numofrange_y(low_x,up_x,low_y,up_y,leaf->left,pointArr);
        else if(up_x>=leaf->p.x_value>=low_x)
        {
            if(up_y>=leaf->p.y_value>=low_y)
            {
                count++;
                pointArr.push_back(leaf->p);
            }
            count+=(numofrange_y(low_x,up_x,low_y,up_y,leaf->left,pointArr)+numofrange_y(low_x,up_x,low_y,up_y,leaf->right,pointArr));
        }
    }
    return count;

}
int twoDtree::numofrange_y(float low_x,float up_x,float low_y,float up_y, node* leaf,vector<struct point>& pointArr)
{
    int count=0;
    if (leaf!=NULL)
    {
        if(low_y>leaf->p.y_value)
            count=numofrange_x(low_x,up_x,low_y,up_y,leaf->right,pointArr);
        else if(up_y<leaf->p.y_value)
            count=numofrange_x(low_x,up_x,low_y,up_y,leaf->left,pointArr);
        else if(up_y>=leaf->p.y_value>=low_y)
        {
            if(up_x>=leaf->p.x_value>=low_x)
            {
                count++;
                pointArr.push_back(leaf->p);
            }
            count+=(numofrange_x(low_x,up_x,low_y,up_y,leaf->left,pointArr)+numofrange_x(low_x,up_x,low_y,up_y,leaf->right,pointArr));
        }
    }
    return count;
}
point twoDtree::nearestnode(point p,float D)
{
    vector<struct point> tempArr;
    if(0<nearestsquare(p,D,tempArr)<10)
    {
        nearestsquare(p,D,tempArr);
        return mindis(tempArr,p,D);
    }
    if(nearestsquare(p,D,tempArr)>10&nearestsquare(p,D/2,tempArr)==0)
    {
        nearestsquare(p,D,tempArr);
        return mindis(tempArr,p,D);
    }
    if(nearestsquare(p,D,tempArr)>10&nearestsquare(p,D/2,tempArr)>0)
        return nearestnode(p,D/2);
    if(nearestsquare(p,D,tempArr)==0)
        return nearestnode(p,2*D);
}
point twoDtree::nearestnode(point p)
{
    return nearestnode(p,1/sqrt(numofnode()));

}
int twoDtree::nearestsquare(point p,float D,vector<struct point>& pointArr)
{
    return numinrange(p.x_value-D,p.x_value+D,p.y_value-D,p.y_value+D,pointArr);
}
void timeofbuild(int num)
{
    cin>>num;
    struct point temp;
    vector<struct point> pointArr;
    for (int i=0;i<num;i++)
    {
        int tmp=rand()%1000000;
        temp.x_value=tmp*0.000001;
        tmp=rand()%1000000;
        temp.y_value=tmp*0.000001;
        pointArr.push_back(temp);
    }
    time_t Start = clock();
    class twoDtree mytree;
    for(int i=0;i<pointArr.size();i++)
    {
        mytree.insert(pointArr[i]);
    }
    cout<<mytree.numofnode();
    time_t End = clock();
    cout<<" cost: "<<End-Start<<" ms"<<endl;
}
