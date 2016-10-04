#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
struct point;
struct polypoint;
struct edge;
struct rectangle;

void Bubble(vector<polypoint>& polypointArr);
void Bubble_hole(vector<polypoint>& polypointArr,int start,int end);

edge edgeini(float x,float y1,float y2);

void edgesort(vector<edge>& edgeArr);
void edgesort_swap(edge& edgeA,edge& edgeB);

void buildedge(vector<polypoint>& polypointArr,vector<edge>& edgeArr);

void getrow(vector<float>& rowArr,vector<polypoint>& polypointArr);
void rowsort(vector<float>& rowArr);
void rowsort_swap(float& rowA,float& rowB);

void input(fstream& fin, vector<polypoint>& polypointArr);
void outputpoint(polypoint output);
void outputedge(edge output);
void outputrectangle(rectangle output);

void buildrectangle(vector<rectangle>& rectangleArr,vector<float>& rowArr,vector<edge>& edgeArr);
void exceptrectangle(vector<rectangle>& rectangleArr,vector<rectangle>& intersection,vector<float>& rowArr);
rectangle inirect(float low_x,float low_y,float up_x,float up_y);

struct point
{
    float x_value;
    float y_value;
};

struct polypoint
{
    float x_value;
    float y_value;
    int hole;
};
struct edge
{
    polypoint node1;
    polypoint node2;
};
struct rectangle
{
    float up_x,up_y,low_x,low_y;
};
void input(fstream& fin,vector<polypoint>& polypointArr)
{
    polypoint temppoint;
    char sign;
    int hole=0;
    while(fin!=NULL)
    {
        fin>>sign;
        if(sign=='#')
        {
            hole++;
            continue;
        }
        fin>>temppoint.x_value;
        fin>>sign;
        fin>>temppoint.y_value;
        fin>>sign;
        temppoint.hole=hole;
        polypointArr.push_back(temppoint);
    }
    polypointArr.pop_back();
    return ;
}
void Bubble(vector<polypoint>& polypointArr)
{
    int start=0;
    int end=0;
    for(int i=0;i<polypointArr.size()-1;i++)
    {
        if(polypointArr[i].hole!=polypointArr[i+1].hole)
        {
            end=i;
            if (polypointArr[start].x_value==polypointArr[end].x_value)
                Bubble_hole(polypointArr,start,end);
            start=i+1;
        }
    }
    if(polypointArr[polypointArr.size()-1].hole==0)
        start=0;
    end=polypointArr.size()-1;
    if (polypointArr[start].x_value==polypointArr[end].x_value)
        Bubble_hole(polypointArr,start,end);

}
void Bubble_hole(vector<polypoint>& polypointArr,int start,int end)
{
    polypoint temppoint;
    temppoint=polypointArr[start];
    for(int i=start;i<end;i++)
    {
        polypointArr[i]=polypointArr[i+1];
    }
    polypointArr[end]=temppoint;

}

edge edgeini(float x,float y1,float y2)
{
    edge temp;
    temp.node1.x_value=x;
    temp.node2.x_value=x;
    temp.node1.y_value=y1;
    temp.node2.y_value=y2;
    return temp;
}

void outputpoint(polypoint output)
{
    cout<<output.x_value<<','<<output.y_value<<' '<<output.hole<<endl;
}
void outputedge(edge output)
{
    cout<<output.node1.x_value<<','<<output.node1.y_value;
    cout<<'-';
    cout<<output.node2.x_value<<','<<output.node2.y_value;
    cout<<endl;
}
void outputrectangle(rectangle output)
{
    cout<<'x'<<output.low_x<<' '<<output.up_x<<'y'<<output.low_y<<' '<<output.up_y<<endl;
}
void buildedge(vector<polypoint>& polypointArr,vector<edge>& edgeArr)
{
    edge tempedge;
    for(int i=0;i<polypointArr.size()-1;i++)
    {
        if(polypointArr[i].y_value>polypointArr[i+1].y_value)
        {
            tempedge.node1=polypointArr[i];
            tempedge.node2=polypointArr[i+1];
        }
        else
        {
            tempedge.node2=polypointArr[i];
            tempedge.node1=polypointArr[i+1];
        }
        edgeArr.push_back(tempedge);
    }
}

void edgesort(vector<edge>& edgeArr)
{
    for(int i=edgeArr.size()-2;i>=0;i--)
    {
        for(int k=i;k<edgeArr.size()-1;k++)
        {
            if(edgeArr[k].node1.x_value>edgeArr[k+1].node1.x_value)
                edgesort_swap(edgeArr[k],edgeArr[k+1]);
        }
    }
}
void edgesort_swap(edge& edgeA,edge& edgeB)
{
    edge temp;
    temp=edgeA;
    edgeA=edgeB;
    edgeB=temp;
    return;
}
void getrow(vector<float>& rowArr,vector<polypoint>& polypointArr)
{

    rowArr.push_back(polypointArr[0].y_value);
    for(int i=1;i<polypointArr.size();i++)
    {
        bool safe=0;
        for(int j=0;j<rowArr.size();j++)
        {
            if(polypointArr[i].y_value==rowArr[j])
                safe=1;
        }
        if(safe==0)
        {
            rowArr.push_back(polypointArr[i].y_value);
        }
    }
    rowsort(rowArr);
}
void rowsort(vector<float>& rowArr)
{

    for(int i=rowArr.size()-2;i>=0;i--)
    {
        for(int k=i;k<rowArr.size()-1;k++)
        {
            if(rowArr[k]<rowArr[k+1])
                rowsort_swap(rowArr[k],rowArr[k+1]);
        }
    }
}
void rowsort_swap(float& rowA,float& rowB)
{
    float temp;
    temp=rowA;
    rowA=rowB;
    rowB=temp;
    return;
}

void buildrectangle(vector<rectangle>& rectangleArr,vector<float>& rowArr,vector<edge>& edgeArr)
{
    rectangle temprect;
    for(int i=0;i<rowArr.size()-1;i++)
    {
        temprect.up_y=rowArr[i];
        temprect.low_y=rowArr[i+1];
        int count=0;
        for(int j=0;j<edgeArr.size();j++)
        {
            if(rowArr[i]<=edgeArr[j].node1.y_value&&rowArr[i+1]>=edgeArr[j].node2.y_value)
            {
                if(count==0)
                {
                    temprect.low_x=edgeArr[j].node1.x_value;
                    count++;
                }
                else if (count==1)
                {
                    temprect.up_x=edgeArr[j].node1.x_value;
                    rectangleArr.push_back(temprect);
                    count=0;
                }
            }

        }
    }
    return;
}

void exceptrectangle(vector<rectangle>& rectangleArr,vector<rectangle>& intersection,vector<float>& rowArr)
{
    rectangle temprect;
    for(int i=0;i<rowArr.size()-1;i++)
    {
        float upsum=0;
        float downsum=0;
        for(int k=0;k<rectangleArr.size();k++)
        {
            if(rowArr[i]==rectangleArr[k].low_y)
                downsum+=(rectangleArr[k].up_x-rectangleArr[k].low_x);
            if(rowArr[i]==rectangleArr[k].up_y)
                upsum+=(rectangleArr[k].up_x-rectangleArr[k].low_x);
        }
        for(int k=0;k<rectangleArr.size();k++)
        {
            if(downsum>upsum)
            {
                 if(rowArr[i]==rectangleArr[k].up_y)
                 {
                      temprect=inirect(rectangleArr[k].low_x,rectangleArr[k].up_y,rectangleArr[k].up_x,rectangleArr[k].up_y);
                      intersection.push_back(temprect);
                 }

            }
            else
            {
                 if(rowArr[i]==rectangleArr[k].low_y)
                 {
                      temprect=inirect(rectangleArr[k].low_x,rectangleArr[k].low_y,rectangleArr[k].up_x,rectangleArr[k].low_y);
                      intersection.push_back(temprect);
                 }

            }
        }

    }
    return;
}
rectangle inirect(float low_x,float low_y,float up_x,float up_y)
{
    rectangle temp;
    temp.low_x=low_x;
    temp.low_y=low_y;
    temp.up_x=up_x;
    temp.up_y=up_y;
    return temp;
}
