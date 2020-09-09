#include <cstdlib>
#include<iostream>
#include<fstream>
#include<string.h>
#include <sstream>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>
#include <vector>
#include <unordered_map>
using namespace std;

class manufacturer
{
public:
string id;
string name;
string author;
string category;
string pb1;
string amount;
string buffer,bufferi;
string id_list[100];
string name_list[100];
int address_list[100];
int count;

string compr1(string);
	void read_data();
	void pack();
	void munpack();
	void write_file();
	void create_idx();
	void disp();
	void sort_idx();
	int serch_idx(string);
manufacturer(){count=-1;}
	void serch(string);
	void read_from_file(int);
	void write_to_file();
	void create_index();
	int remove(string);
	void search(string);
        int search_index(string);
	string extract_id();
	string extract_name();
	string decoding(vector<int> op);
	vector<int> encoding(string s1);
	void sort_index();
	void assign_values(string);
	void modify(string);
	string compr(string);
        void display();
};
string manufacturer::extract_name()
{
string id;
int i=0;
id.erase();
while(buffer[i]!='|')
id+=buffer[i++];
i++;
name.erase();
while(buffer[i]!='|')
name+=buffer[i++];
return name;
}
void manufacturer::read_data()
	{
		
		cout<<"Expense ID: ";
		cin>>id;
		cout<<"Project NAME: ";
		cin>>name;
		cout<<"project Head:";
		cin>>author;
		cout<<"department:";
		cin>>category;
	
		cout<<"AMOUNT: ";
		cin>>amount;
	}
			void manufacturer::pack()
	{
		
		buffer.erase();
		buffer+=id+"|"+name+"|"+author+"|"+category+"|"+amount+"$"+"\n";
	}
	void manufacturer::write_to_file()
	{
		int pos;

		fstream file,filei;
		file.open("expense.txt",ios::out|ios::app);
		pos=file.tellp();
		file<<buffer;
		file.close();
		id_list[++count]=id;
		
		address_list[count]=pos;
sort_index();

}

		
		
	string manufacturer::extract_id()
	{
		string id;
		int i=0;
		id.erase();
		while(buffer[i]!='|')
		id+=buffer[i++];
		return id;
	}
	void manufacturer::create_index()
	{
		fstream file;
		int pos;
		string id;
		count=-1;
		file.open("expense.txt",ios::in);
		while(!file.eof())
		{
			pos=file.tellg();
			buffer.erase();
			getline(file,buffer);
			if(buffer[0]!='*')
			{
				if(buffer.empty())break;
				id=extract_id();
				
				
				id_list[++count]=id;
				
			address_list[count]=pos;
		
			
				
			}
		}
		file.close();
		sort_index();
		buffer.erase();
		
	}
	
	void manufacturer::sort_index()
	{
		int i,j,temp_address;
		string temp_id,ind;
		for(int i=0;i<=count;i++)
		{
			for(int j=i+1;j<=count;j++)
			{
				if(id_list[i]>id_list[j])
				{
					temp_id=id_list[i];
					id_list[i]=id_list[j];
					id_list[j]=temp_id;
					temp_address=address_list[i];
					address_list[i]=address_list[j];
					address_list[j]=temp_address;
					}
			}
		}
		std::ofstream ofs;
		ofs.open("index.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		for(i=0;i<=count;i++)
		{      
			cout<<id_list[i]<<"\t"<<address_list[i]<<"\n";
			ind=id_list[i]+"\t"+to_string(address_list[i]);
			vector<int> d = encoding(ind);
			fstream file;
			file.open("index.txt",ios::out|ios::app);
			for (int j = 0; j < d.size(); j++) { 
			        file << d[j] << " "; 
			}
			file << " \n";
			file.close();
		}
	}
	int manufacturer::search_index(string key)
	{
		int low=0,high=count,mid=0,flag=0,pos;
		while(low<=high)
		{
			mid=(low+high)/2;
			if(id_list[mid]==key){flag=1;break;}
			if(id_list[mid]>key)high=mid-1;
				if(id_list[mid]<key)low=mid+1;
			}
			if(flag)
			return mid;
			else
			return -1;
		}
		void manufacturer::munpack()
{
		int i=0;
		id.erase();
		while(buffer[i]!='|')
		id+=buffer[i++];
		name.erase();
		i++;
		while(buffer[i]!='|')
		name+=buffer[i++];
		author.erase();
		i++;
		while(buffer[i]!='|')
		author+=buffer[i++];
		category.erase();
		i++;
		while(buffer[i]!='|')
		category+=buffer[i++];
		amount.erase();
		i++;
		while(buffer[i]!='$')
		amount+=buffer[i++];
}

	
	void manufacturer::search(string key)
	{
		int pos=0,address;
		fstream file;
		buffer.erase();
		pos=search_index(key);
		if(pos==-1)
	    cout<<endl<<"Record not found"<<endl;
	    else if(pos>=0)
	    {
	    	file.open("expense.txt");
	    	address=address_list[pos];
	    	file.seekp(address,ios::beg);
	    	getline(file,buffer);
               	munpack();

	    	cout<<"....... Record list ...........\n"<<buffer;
	    	//cout<<"\n________________________\n";
	    	cout<<"\nExpense ID""\t""Project NAME""\t""Project head""\t\t""department""\t\t""AMOUNT""\n";
	    	cout<<id<<"\t\t"<<name<<"\t\t"<<author<<"\t\t"<<category<<"\t\t"<<amount;
	    	//cout<<"\n________________________\n";
                pack();
                
	    	file.close();
		}
	}
	void manufacturer::assign_values(string key)
{
	int pos=0,address;
		fstream file;
		buffer.erase();
		pos=search_index(key);
		if(pos==-1)
	    cout<<endl<<"Record not found"<<endl;
	    else if(pos>=0)
	    {
	    	file.open("expense.txt");
	    	address=address_list[pos];
	    	file.seekp(address,ios::beg);
	    	getline(file,buffer);
	    	munpack();
	    }
}
void manufacturer::modify(string key)
	{
		int c;
		assign_values(key);
		if(remove(key))
			{
				cout<<"\nWHAT TO MODIFY\n1:Project NAME 2:AMOUNT \n";
				cin>>c;
				switch(c)
					{
						
						case 1:cout<<"Project NAME:\n";
						cin>>name;
						break;
						case 2:cout<<"AMOUNT:\n";
						cin>>amount;
						break;
					
						default:cout<<"wrong choice\n";
					}
				buffer.erase();
				pack();
				write_to_file();
			}
	}

	vector<int> manufacturer::encoding(string s1) 
	{
		unordered_map<string, int> table; 
		for (int i = 0; i <= 255; i++) { 
		        string ch = ""; 
        		ch += char(i); 
        		table[ch] = i; 
 		} 
		    string p = "", c = ""; 
		    p += s1[0]; 
		    int code = 256; 
		    vector<int> output_code; 
		    for (int i = 0; i < s1.length(); i++) { 
		        if (i != s1.length() - 1) 
		            c += s1[i + 1]; 
		        if (table.find(p + c) != table.end()) { 
		            p = p + c; 
		        } 
		        else { 
		            output_code.push_back(table[p]); 
		            table[p + c] = code; 
		            code++; 
		            p = c; 
		        } 
		        c = ""; 
		    }
		    output_code.push_back(table[p]); 
		    return output_code; 
		}   
		string manufacturer::decoding(vector<int> op) 
		{
		    unordered_map<int, string> table; 
		    for (int i = 0; i <= 255; i++) { 
		        string ch = ""; 
		        ch += char(i); 
		        table[i] = ch; 
		    } 
		    int old = op[0], n; 
		    string s = table[old]; 
		    string c = ""; 
		    string d = "";
		    c += s[0]; 
		    d+= s; 
		    int count = 256; 
		    for (int i = 0; i < op.size() - 1; i++) { 
		        n = op[i + 1]; 
		        if (table.find(n) == table.end()) { 
		            s = table[old]; 
		            s = s + c; 
		        } 
		        else { 
		            s = table[n]; 
		        } 
		        d+= s; 
		        c = ""; 
		        c += s[0]; 
		        table[count] = table[old] + c; 
		        count++; 
		        old = n; 
		        return d;
		    } 
		} 

		int manufacturer::remove(string key)
	{
		int pos=0, i,address,flag=0;
		fstream file;
		pos=search_index(key);
		if(pos>=0)
			{        
                                flag=1;
				file.open("expense.txt",ios::out|ios::in);
				address=address_list[pos];
				file.seekp(address,ios::beg);
				file.put('*');
				file.close();
				cout<<"\nrecord deleted:";
				for(i=pos;i<count;i++)
				{
					id_list[i]=id_list[i+1];
					address_list[i]=address_list[i+1];
				}
				count--;
			}
                 if(flag==1) return 1;
                 else 
                     return -1;
 
	}
        void manufacturer::display()
	{
    		
    		ifstream file ;
			file.open("expense.txt",ios::in);
		
    	 	cout<<"PROJECT ID"<<"\t\t"<<"Project NAME"<<"\t\t"<<"Project Head"<<"\t\t"<<"Department"<<"\t\t"<<"AMOUNT"<<"\n";

    	 	cout<<"________________________________________\n";
       				 while(1)
       				 {
       				 	buffer.erase();
            	      			 getline(file,buffer,'\n');
						
						if(file.fail())break;
						
       					 {		
       					 		
            			
            					munpack();

						if(id!="*")
{
            				cout<<setw(10)<<left<<id<<setw(30)<<left<<name<<setw(15)<<left<<author<<setw(25)<<left<<category<<setw(20)<<left<<amount;
            				            					cout<<"\n";
								}
          				 }
}
          			
    					 file.close();
	}
	


	class dealer:public manufacturer
	{
		public:
			int i,nop;
			string cid;
			string CNAME;
			string cnam;
	string did;
	string dname;
	string dparts;
	string address;
	string buffer;
        void display();	
	int bread_data();
	void bpack();
	void xpack();
	void bwrite_to_file();
	void xwrite_to_file();
	void bunpack();
	int bsearch(string);
	int bdelete_from_file(string);
	void bmodify(string);
	void xunpack();
	string key;
	string state2;
	string compr2(string);
		string compr(string);
		string state1;
		void xzunpack();
		string teststate;
	
	};
	void dealer::xzunpack()
	{
		int i=0;
		cid.erase();
		while(buffer[i]!='|')
		cid+=buffer[i++];
		CNAME.erase();
		i++;
		while(buffer[i]!='$')
		CNAME+=buffer[i++];
	
	
	}
void dealer::display()
	{
    		
    		ifstream file ;
			file.open("income.txt",ios::in);
		
    	 	
cout<<" INCOME ID"<<"\t"<<"NAME"<<"\t"<<"SOURCE"<<"\t\t"<<"AMOUNT"<<endl;
    	 	cout<<"________________________________________\n";
       				 while(1)
       				 {
       				 	buffer.erase();
            	      			 getline(file,buffer,'\n');
						
						if(file.fail())break;
						
       					 {		
       					 		
            			
            					bunpack();
					if(did!="*")
{
            				cout<<setw(20)<<left<<did<<setw(10)<<left<<dname<<setw(20)<<left<<address<<setw(30)<<left<<dparts;
            					            					cout<<"\n";
								}
          				 }
}
          			
    					 file.close();
	}

int dealer::bdelete_from_file(string key)
	{
		fstream file;
		int pos, flag=0;
		pos=bsearch(key);
		if(pos>=0)
			{
				file.open("income.txt");
				file.seekp(pos,ios::beg);
				file.put('*');
				flag=1;
				file.close();
			}
		if(flag==1) 
		return 1;
		else
		return 0;
	}
	
		int dealer::bread_data()
	{
		cout<<"     ****Enter Income details***\n";
		//cout<"__________________\n";
		cout<<"INCOME ID: ";
		cin>>did;
		cout<<"NAME: ";
		cin>>dname;
		cout<<"SOURCE";
		cin>>address;
		cout<<"AMOUNT: ";
		cin>>dparts;
	
	}
		void dealer::bpack()
	{
		buffer.erase();
		buffer+=did+"|"+dname+"|"+address+"|"+dparts+"$"+"\n";
	}
		void dealer::bwrite_to_file()
	{
		fstream file;
		file.open("income.txt",ios::out|ios::app);
		file<<buffer;
		file.close();
	}
		
		void dealer::bunpack()
	{
		int ch=1, i=0;
		did.erase();
		while(buffer[i]!='|')
		did+=buffer[i++];
		dname.erase();
		i++;
		while(buffer[i]!='|')
		dname+=buffer[i++];
		address.erase();
		i++;
		while(buffer[i]!='|')
		address+=buffer[i++];
		dparts.erase();
		i++;
		while(buffer[i]!='$')
		dparts+=buffer[i++];
	}

	
	int dealer::bsearch(string key)
{
ifstream file;
int flag=0,pos=0;
file.open("income.txt",ios::in);
while(!file.eof())
{
buffer.erase();
pos=file.tellg();
getline(file,buffer);
bunpack();
if(key==did)
{
cout<<"\nfound the key.the record is..\n"<<buffer;
return pos;
}
}
file.close();
if(flag==0)
{
cout<<"\nnot found...\n";
return-1;
}
}
	void dealer::bmodify(string key)
	{
		int c;
		if(bdelete_from_file(key))
			{
				
				cout<<"\nWHAT TO MODIFY\n 1:NAME 2:SOURCE 3:AMOUNT 4:EXIT\n";
				cin>>c;
				switch(c)
					{
						case 1:cout<<" NAME:\n";
						cin>>dname;
						break;
						case 2:cout<<"SOURCE:\n";
						cin>>address;
						break;
						case 4:cout<<"AMOUNT:\n";
						cin>>dparts;
						break;
                                                
						default:cout<<"wrong choice\n";
					}
				buffer.erase();
				bpack();
				bwrite_to_file();
			}
	}

	
class menu
{ public:
	string id;
string name;
string amount;
string quantity;
string author;
string category;
string publicatn;
	string did;
	string dname;
string address;
	string dparts;
	string dquantity;
	string key;
	int manufactureroperation();
	int dealeroperation();
	int bill();
	string buffer;
	manufacturer s1;
	dealer b1;
	void bxunpack();
	void lunpack();
};
void menu::lunpack()
	{
		int ch=1, i=0;
		id.erase();
		while(buffer[i]!='|')
		id+=buffer[i++];
		name.erase();
		i++;
		while(buffer[i]!='|')
		name+=buffer[i++];
		author.erase();
		i++;
		while(buffer[i]!='|')
		author+=buffer[i++];
		category.erase();
		i++;
		while(buffer[i]!='|')
		category+=buffer[i++];
		amount.erase();
		i++;
		while(buffer[i]!='$')
		amount+=buffer[i++];
	}

void menu::bxunpack()
	{
		int ch=1, i=0;
		did.erase();
		while(buffer[i]!='|')
		did+=buffer[i++];
		dname.erase();
		i++;
		while(buffer[i]!='|')
		dname+=buffer[i++];
		address.erase();
		i++;
		while(buffer[i]!='|')
		address+=buffer[i++];
		dparts.erase();
		i++;
		while(buffer[i]!='$')
		dparts+=buffer[i++];
	}
int menu::bill()
{       int pos,flag=0;
	int it=0,et=0,xp,xq;
	fstream file;
	file.open("income.txt",ios::in);
	while(!file.eof())
	{
		buffer.erase();
		getline(file,buffer);
		bxunpack();
		stringstream ab(dparts);
		ab>>xq;
		if(did!="*")
		it+=xq;
	}
	fstream filex;
	filex.open("expense.txt",ios::in);
	while(!filex.eof())
	{
		buffer.erase();
		getline(filex,buffer);
		lunpack();
		stringstream ab1(amount);
		ab1>>xp;
		if(id!="*")
		et+=xp;
	}
	cout<<"-------------BUDGET BALANCE----------";
	cout<<"\nTotal amount collected : "<<it;
	cout<<"\nTotal amount spent : "<<et;
	cout<<"\nAvailable Reserve : "<<(it-et);
}
int menu:: manufactureroperation()
{ int ch,i,count;
string key;
manufacturer s1;
s1.create_index();
	while(1)
	{
		
		cout<<"\n***EXPENSE DETAILS****\n"<<endl;
		cout<<" 1.ADD EXPENSE INFORMATION\n 2.SEARCH PARTICULAR INFORMATION \n 3.DELETE EXPENSE DETAILS\n 4.MODIFY DETAILS\n 5.DISPLAY EXPENSE DETAILS\n 6.EXIT\n";
		cout<<"\nEnter  your choice: \n";
		cin>>ch;
			switch(ch)
			{
				case 1: cout<<"\n How many record to insert\n";
				cin>>count;
				for(i=0;i<count;i++)
				{
				cout<<"DATA\n";
				        	s1.read_data();
						s1.pack();
						s1.write_to_file();
					}
						break;
					
				case 2:cout<<"ENTER EXPENSE ID.....\n";
				        cin>>key;
			            s1.search(key);
						break;
				case 3: cout<<"ENTER EXPENSE ID....\n";
				        cin>>key;
				       i=s1.remove(key);
                                       if(i==1)
                                       cout<<"RECORD DELETED\n";
                                       else
                                       cout<<"RECORD NOT FOUND\n";
						break;
		        case 4:cout<<"ENTER EXPENSE ID....\n";
				        cin>>key;
				        s1.modify(key);
						break;
                        case 5:s1.display();
                                 break;
				case 6:return 0;
			
			
			}
	}
}

int menu::dealeroperation()
{ int ch,i;
dealer b1;
manufacturer s1;
	while(1)
	{
		
		
		cout<<"\n***INCOME MENU****\n"<<endl;
		cout<<" 1.ADD INCOME DETAILS\n 2.DELETE DETAILS \n 3.SEARCH PATICULAR DETAILS\n 4.MODIFY PARTICULAR INFO.\n 5.DISPLAY DETAILS\n 6.Exit";
		cout<<"\nENTER CHOICE: \n";
		cin>>ch;
			switch(ch)
			{
				case 1: b1.bread_data();
						b1.bpack();
						b1.bwrite_to_file();
						break;
				case 2: cout<<"INCOME ID.....\n";
				    	cin>>key;
			            i=b1.bdelete_from_file(key);
						if(i==1)
						cout<<"RECORD DELETED\n";
						else
						cout<<"RECORD NOT FOUND";
						break;
				case 3: cout<<"ENTER INCOME ID.....\n";
				        cin>>key;
				        b1.bsearch(key);
						break;
				case 4:cout<<"ENTER INCOME ID.....\n";
				       cin>>key;
				       b1.bmodify(key);
						break;
                                case 5:b1.display();
                                       break;
				case 6: return 0;
				default: cout<<"wrong choice\n";
			}
	}
	return 0;
	
}
int main()
{
	int i,choice;
	menu m1;
	while(1)
	{
			cout<<"\n***STATE BUDGET MANAGEMENT****\n"<<endl;
	cout<<" 1.EXPENSE DETAILS\n 2.INCOME DETAILS \n 3.OUTSTANDING RESERVE\n 4.EXIT\n";
	cout <<"Enter your choice\n";
	cin>>choice;
	switch(choice)
	{
			case 1:m1.manufactureroperation();
					break;
			case 2:m1.dealeroperation();
					break;
			case 4:return 0;
			case 3:m1.bill();
				break;
			default:cout<<"wrong choice\n";
	}
	}return 0;
}
