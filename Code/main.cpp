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
        out<<setw(25)<<s.addr<<setw(15)<<s.usn;
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
        addr=fi.tellg();
        fi>>s[i].usn>>s[i].name;
        cout<<i<<" "<<s[i].usn<<s[i].name<<endl;
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
    cout<<"size:"<<student_list.size();
}
void LinkedList::create_index()
{
    fstream indexFile;int indexCount=1;
    indexFile.open("index.txt",ios::out);
    list<student>::iterator it;
    indexFile<<setw(15)<<"Index"<<setw(25)<<"Relative Byte Address"<<setw(15)<<"USN"<<"\n";
    for(it=student_list.begin();it!=student_list.end();it++){
         indexFile<<setw(12)<<indexCount<<"***";
         indexFile<< *it;
         indexFile<<endl;
         indexCount++;
         }
    indexFile.close();
}
int main()
{
    int icount=-1;
    string i,j;
    fstream fi;
    fi.open("student.txt", ios::in|ios::out);
    while(!fi.eof())
    {
        fi>>i>>j;
        icount++;
    }
    cout<<icount<<endl;
    fi.close();
    student s[icount];
    s[0].getdata(s,icount);
    LinkedList ll;
    ll.insert_list(s,icount);
    ll.create_index();
    return 0;
}
