#include <iostream>
#include <fstream>
using namespace std;

/*
 * Huffman Coding step 3
 * 
 * Necessary corrections were made for 
 * steps 1.0 and 2.0;
 * Now, correct outputs are displayed; 
 * parameters on dev c++:
 * "HuffmanData.txt output.txt"
 *
 * @author Steve Jun
*/


struct Node{
	string code;
	string ch;
	int prob;
	Node* next;
	Node* left;
	Node* right;
};

void insert(Node* p, Node* newNode){
	while(p->next!=NULL && (newNode->prob)>=(p->next->prob))
		p=p->next;
	newNode->next = p->next;
	p->next = newNode;
}

void printNode(Node* n,ofstream& out){
	
	cout<<"("<<n->ch<<","<<n->prob<<",";
	out<<"("<<n->ch<<","<<n->prob<<",";
	if(n->next==NULL){
		cout<<"NULL"<<",";
		out<<"NULL"<<",";
	}else {
		cout<<n->next->ch<<",";
		out<<n->next->ch<<",";
	}
	if(n->left==NULL){
		cout<<"NULL"<<",";	
		out<<"NULL"<<",";
	}else {
		cout<<n->left->ch<<",";
		out<<n->left->ch<<",";
	}
	if(n->right==NULL){
		cout<<"NULL"<<",";	
		out<<"NULL"<<",";	
	}else {
		cout<<n->right->ch<<",";
		out<<n->right->ch<<",";
	}
	if(n->code==""){
		cout<<"---"<<")"<<endl;
		out<<"---"<<")"<<endl;
	}else {
		cout<<n->code<<")"<<endl;
		out<<n->code<<")"<<endl;	
	}
	
}//used in STEP3.0

void preorderTraversal(Node* n,string code,ofstream& out){
	if(n!=NULL){
		
		if(n->left==NULL && n->right==NULL){
			n->code=code;
			printNode(n,out);
		}
		else {
			printNode(n,out);
			preorderTraversal(n->left,code+'0',out);
			preorderTraversal(n->right,code+'1',out);
		}
	}
}//used in STEP3.0

/*
 * Given a text file that contains characters and the number of times they appear
 * determine what what bit values to assign to each character. The output is 
 * written to another text file and printed to console.
 */
int main(int argc, char* argv[]){

	if (argc < 3) {
		cerr << "usage: " << argv[0] << " <input file> <output file> " << endl;
		return 0;
	}
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile;
	outFile.open(argv[2]);
	
	
	int prob;char ch;
	Node* LH=new Node;
	Node* dummyNode=new Node;
	
	cout<<"**[STEP 1.0]**"<<endl;
	outFile<<"**[STEP 1.0]**"<<endl;
	//step1.0
	LH->next=dummyNode;
	dummyNode->ch="DUMMY";
	
	//step1.1
	while(inFile>>skipws>>ch){
		//step1.2
		Node* newNode = new Node;
		newNode->ch=ch;
		
		inFile>>skipws>>prob;
		newNode->prob=prob;
		
		cout<<ch<<" "<<prob<<endl;
		outFile<<ch<<" "<<prob<<endl;
		//step1.3
		insert(LH,newNode);
	}//step1.4
	inFile.close();
	
	//Node &oldLH=*(Node*)((void*)dummyNode);
	cout<<endl;
	outFile<<endl;
	cout<<"listHead-->";
	outFile<<"listHead-->";
	while(LH->next!=NULL){
		if(LH->next->next==NULL){
			cout<<"("<<LH->next->ch<<","<<LH->next->prob<<","<<"NULL"<<")";
			outFile<<"("<<LH->next->ch<<","<<LH->next->prob<<","<<")";
		}
		else{
			cout<<"("<<LH->next->ch<<","<<LH->next->prob<<","<<LH->next->next->ch<<")";
		outFile<<"("<<LH->next->ch<<","<<LH->next->prob<<","<<LH->next->next->ch<<")";
		}
		LH=LH->next;	
	}
	cout<<endl<<endl<<endl;
	outFile<<endl<<endl<<endl;

	cout<<"**[STEP 2.0]**"<<endl;
	outFile<<"**[STEP 2.0]**"<<endl;
	//step2.0
	Node* walker;
	Node* root;
    walker=dummyNode;
    int c=0;
    
    while(walker->next->next != NULL){
        //step2.1
        Node* NN = new Node;
        
        //step2.2
        NN->ch = walker->next->ch + walker->next->next->ch;
        NN->prob = walker->next->prob + walker->next->next->prob;
        
        NN->left = walker->next;
        NN->right = walker->next->next;
        
        walker = walker->next->next;
        
    	Node* temp = new Node;
    	temp->next = walker;
    	//step2.3
    	insert(temp,NN);
    	
    	++c;
        cout<<"Iteration "<<c<<":"<< endl;
        cout<<"listHead -->";
       	outFile<<"Iteration "<<c<<":"<< endl;
    	outFile<<"listHead -->";
    	while(temp->next->next!=NULL){
			cout<<"("<<temp->next->next->ch<<","<<temp->next->next->prob<<")";
			outFile<<"("<<temp->next->next->ch<<","<<temp->next->next->prob<<")";
			temp=temp->next;	
		}
		cout<<endl;
		outFile<<endl;
		cout<<"("<<NN->ch<<")"<<" was inserted."<<endl;
		outFile<<"("<<NN->ch<<")"<<" was inserted."<<endl;
		
		
		root=temp;
        cout<<endl;
		outFile<<endl;
    }//step2.4
	
	cout<<endl<<"**[STEP 3.0]**"<<endl;
	outFile<<endl<<"**[STEP 3.0]**"<<endl;
/*************************************************
 * [STEP 3.0] STARTS HERE
 * 
**************************************************/
	//step3.0
	//preOrderTraversal will assign a code to leaf nodes
	//and print visited nodes
	preorderTraversal(root,"",outFile);
	cout<<endl;
	outFile<<endl;
	
	Node* newLH=dummyNode;//oldListHead
	LH=newLH;
	while (LH->next!=NULL){
		if(!((LH->next->ch.length())==1)||((LH->next->code).length()<1)){
			if(LH->next->next!=NULL)
				LH->next=LH->next->next;
			else LH->next=NULL;
		}
		else{
			LH=LH->next;
		}
			
	}
	LH=newLH;
	while (LH->next!=NULL){
		cout<<"("<<LH->next->ch<<","<<LH->next->code<<")"<<endl;
		outFile<<"("<<LH->next->ch<<","<<LH->next->code<<")"<<endl;
		LH=LH->next;	
	}
	

	outFile.close();
	cout<<"Assignment Complete!"<<endl;

	system("pause");
    return 0;   
    
}//main
