#include <iostream>
#include <cstring>
#include <fstream>
#include <list>
#include <cstdlib>
#include<iomanip>

using namespace std;

class student
{
    private:string name,usn;
            long int addr;
    public:
        void getdata(student[], int);
    friend class LinkedList;
    friend fstream& operator<<(fstream& out, student s)
    {
        out<<s.usn<<setw(25)<<s.addr;
        return out;
    }

};
void student::getdata(student s[], int icount)
{
    fstream fi;
    int i=0;
    fi.open("student.txt",ios::in|ios::out);
    while(i<icount)
    {
        s[i].addr=fi.tellp();
        fi>>s[i].usn>>s[i].name;
        //cout<<i<<" "<<s[i].usn<<s[i].name<<endl;
        i++;
    }
    cout<<"\n\n";
}
class LinkedList
{
    private:list<student> student_list;
    public:
        void insert_list(student[],int icount);
        void create_index();
};
void LinkedList::insert_list(student s[], int icount)
{
    list<student>::iterator it;

    for(int i=0;i<icount;i++) student_list.push_back(s[i]);
    //cout<<"size:"<<student_list.size();
}
void LinkedList::create_index()
{
    fstream indexFile;int indexCount=1;
    indexFile.open("index.txt",ios::out);
    list<student>::iterator it;
    //indexFile<<setw(15)<<"Index"<<setw(25)<<"Relative Byte Address"<<setw(15)<<"USN"<<"\n";
    for(it=student_list.begin();it!=student_list.end();it++){
         indexFile<< *it;
        // indexFile<<setw(12)<<indexCount;
         indexFile<<endl;
         indexCount++;
         }
    indexFile.close();
}
class indexList
{
    private:string usn;
            long int raddr;
    public:
            indexList(string temp)
            {
                usn=temp;
            }
            void searchIndex(indexList ind, int indexCount);

};
void indexList::searchIndex(indexList ind, int indexCount)
            {
                indexList temp("\0");
                fstream indexFile,studentFile;
                int flag=0;
                indexFile.open("index.txt",ios::in);
                while((indexCount)>0)
                {
                    indexFile>>temp.usn>>temp.raddr;
                    indexCount--;
                    //cout<<temp.usn<<"  "<<ind.usn<<"\n";
                    if(ind.usn==temp.usn)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag)
                {
                    studentFile.open("student.txt", ios::in);
                    string studentStr;
                    studentFile.seekg(temp.raddr+1,ios::beg);
                    getline(studentFile, studentStr);
                    cout<<"\nRecord is \n"<<studentStr;
                }
                else
                    cout<<"\nRecord not found!";
                indexFile.close();
                studentFile.close();
            }
int main()
{
    int icount=-1, ch;
    string i,j;
    fstream fi;
    fi.open("student.txt", ios::in|ios::out);
    while(!fi.eof())
    {
        fi>>i>>j;
        icount++;
    }
    //cout<<icount<<endl;
    fi.close();
    student s[icount];
    s[0].getdata(s,icount);
    LinkedList ll;
    ll.insert_list(s,icount);
    ll.create_index();
    system("clear");
    while(1)
    {
        cout<<"\nEnter the USN:";
        cin>>i;
        indexList indexed(i);
        indexed.searchIndex(indexed, icount);
        cout<<"\nWant to continue?Press 1 to continue, 0 to exit:";
        cin>>ch;
        if(ch!=1)
        {
            cout<<"\nBye!";
            return 0;
        }
    }
    return 0;
}
