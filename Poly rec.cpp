#include "rectangle.h"
#include "2Dtree.h"

using namespace std;

int main()
{

    fstream  finpoly("..\\input\\polygon3.txt",ios::in);
    fstream  fin2Dtree("..\\input\\input100K.txt",ios::in);
    ofstream  fout("..\\output\\inner-3-1.txt",ios::out);
    if (!finpoly||!fin2Dtree||!fout)
        cout << "Error opening input file" << endl;
    else
    {
        //init mytree
        vector<struct point> pointArr;
        vector<struct point> deleteArr;
        struct point temp;
        int num=0;
        while(fin2Dtree!=NULL)
        {
            fin2Dtree>>temp.x_value;
            fin2Dtree>>temp.y_value;
            pointArr.push_back(temp);
            num++;
        }
        class twoDtree mytree;
        for(int i=0;i<num-1;i++)
        {
            mytree.insert(pointArr[i]);
        }
        pointArr.clear();
        //init poly
        vector<polypoint> polypointArr;
        vector<edge>edgeArr;
        vector<float>rowArr;
        vector<rectangle>rectangleArr;
        vector<rectangle>intersection;
        input(finpoly,polypointArr);
        Bubble(polypointArr);
        buildedge(polypointArr,edgeArr);

        //forouter
/*
        edge tempedge;
        tempedge=edgeini(0,1,0);
        edgeArr.push_back(tempedge);
        tempedge=edgeini(1,1,0);
        edgeArr.push_back(tempedge);
        rowArr.push_back(1);
        rowArr.push_back(0);
*/
        //forouter
        edgesort(edgeArr);

        getrow(rowArr,polypointArr);


        int numofnode=0;
        buildrectangle(rectangleArr,rowArr,edgeArr);
        exceptrectangle(rectangleArr,intersection,rowArr);
        //calculat node
        for(int i=0;i<rectangleArr.size();i++)
        {

          //  cout<<'x'<<rectangleArr[i].low_x<<','<<rectangleArr[i].up_x<<'y'<<rectangleArr[i].low_y<<','<<rectangleArr[i].up_y<<endl;
            numofnode+=mytree.numinrange(rectangleArr[i].low_x,rectangleArr[i].up_x,rectangleArr[i].low_y,rectangleArr[i].up_y,pointArr);
        }

        for(int i=0;i<intersection.size();i++)
        {
           // cout<<'x'<<intersection[i].low_x<<','<<intersection[i].up_x<<'y'<<intersection[i].low_y<<','<<intersection[i].up_y<<endl;
            numofnode-=mytree.numinrange(intersection[i].low_x,intersection[i].up_x,intersection[i].low_y,intersection[i].up_y,deleteArr);
        }
        for(int i=0;i<deleteArr.size();i++)
        {
            for(int j=0;j<pointArr.size();j++)
            {
                if(pointArr[j].x_value==deleteArr[i].x_value&&pointArr[j].y_value==deleteArr[i].y_value)
                {
                    pointArr.erase(pointArr.begin()+j);
                    break;
                }
            }
        }

        for(int i=0;i<pointArr.size();i++)
        {
            fout<<pointArr[i].x_value<<','<<pointArr[i].y_value<<endl;
        }
        fout<<pointArr.size();




    }

}
