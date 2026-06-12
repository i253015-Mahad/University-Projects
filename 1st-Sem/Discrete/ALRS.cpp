using namespace std;
#include <iostream>
#include <fstream>

//if there is var after var, clear the stack!!!

//global variables

int var, check = 0, choice, premises, row = 0;
char variable[6] = {"PQRST"};
bool invalid;
string final, expression, premise[5], conclusion;

//function prototypes

string single_variables();
void get_variables ();
string expression_validation (string expression);
string table_columns (string expression);
string shunting_yard (string expression);
int pow(int a, int b);
void truth_table (string expression);
void derivation (string a, string b, string c, string d, string e);
void save_result ();

int main()
{
	string file, txt = ".txt";
	char save;
	//making the main menu
	
	main:
	cout<<"\t\tMain Menu\n";
	cout<<"1. Generate truth table for expression\n";
	cout<<"2. Validate an argument (premisis --> conclusion)\n";
	cout<<"3. Check equivalence of two expressions\n";
	cout<<"4. Reasoning chain / Derive implications\n";
	cout<<"5. View / Load saved results\n";
	cout<<"6. Exit\n";
	
	//asking for user's choice and validating
	
	cout<<"\nEnter selection (1-6): ";
	cin>>choice;
	while (choice <= 0 || choice > 6)
	{
		cout<<"Enter a valid choice: ";
		cin>>choice;
	}
	
	//using switch to do the required tasks
	
	switch (choice)
	{
		case 1:
			    {
			    	cout<<"\n\nTruth Table Generator\n";
			    	
			    	//asking for number of variables and validating
			    	
			    	get_variables ();
			    	
			    	//getting expression and validating
			    	
			    	cout<<"\nEnter the expression: ";
			    	cin.ignore();
					expression = expression_validation(expression);
					
					//writing the column names of truth table
					
					cout<<single_variables();
					cout<<table_columns(expression);
					
					//making table
					truth_table(expression);
					
					//saving result or not
					cout<<"\n\nDo you want to save the result? ('y' for yes or 'n' for no) ";
	                cin>>save;
	                while (save != 'y' && save != 'n')
	                {
	                	cout<<"Enter a correct input (small letter 'y' or 'n': ";
	                	cin>>save;
					}
	                if (save == 'y')
	                {
	                	save_result ();
	                	cout<<"Returning to main menu....\n\n";
		                goto main;
	                }
	                else
	                {
		                cout<<"\nReturning to main menu....\n\n";
		                goto main;
	                }
					
					break;
				}
		case 2:
			    {
			    	cout<<"\n\nArgument Validation\n";
			    	//getting number of variables and validating
			    	
			    	get_variables();
			    	
			    	//getting premises 
			    	
			    	cout<<"Enter total number of premesis: ";
			    	cin>>premises;
			    	cin.ignore();
			    	for (int i = 0; i < premises; i++)
			    	{
			    		cout<<"Enter premise "<<i+1<<": ";
			    		premise[i] = expression_validation(premise[i]);
					}
					
					//getting conclusion
					
					cout<<"Enter conclusion: ";
					conclusion = expression_validation(conclusion);
					
					//combining all strings
					final = premise[0] + "n";
					for (int i = 1; i < premises; i++)
					{
						final += premise[i] + "n";
					}
					final += conclusion;
					
					//writing column names of truth table
					
					cout<<single_variables();
					for (int i = 0; i < premises; i++)
					{
						cout<<table_columns(premise[i]);
					}
					cout<<table_columns(conclusion);
					cout<<"Result";
					
					//making table
					truth_table(final);
					
					//judging conclusion
					cout<<"\n\nFinal Verdict:\n";
					if (invalid == false)
					{
						cout<<"The argument is valid.\n";
						cout<<"No row was found where ALL premises were true AND the conclusion was false.\n";
					}
					else
					{
						cout<<"The argument is invalid.\n";
						cout<<"In row "<<row<<", ALL premises are true AND the conclusion is false.\n";
					}
					
					//saving result or not
					cout<<"\n\nDo you want to save the result? ('y' for yes or 'n' for no) ";
	                cin>>save;
	                while (save != 'y' && save != 'n')
	                {
	                	cout<<"Enter a correct input (small letter 'y' or 'n': ";
	                	cin>>save;
					}
	                if (save == 'y')
	                {
	                	save_result ();
	                	cout<<"Returning to main menu....\n\n";
		                goto main;
	                }
	                else
	                {
		                cout<<"Returning to main menu....\n\n";
		                goto main;
	                }
			    	
			    	break;
				}
		case 3:
			    {
			    	cout<<"\n\nLogical Equivalence Checker\n";
			    	
			    	//getting variables
			    	get_variables();
			    	
			    	//getting expressions
			    	cin.ignore();
			    	for (int i = 0; i < 2; i++)
			    	{
			    		cout<<"Enter expression "<<i+1<<": ";
			    		premise[i] = expression_validation(premise[i]);
					}
					
					//making the table columns
					cout<<single_variables();
					cout<<table_columns(premise[0]);
					cout<<table_columns(premise[1]);
					cout<<"Match";
					
					//combining strings
					final = premise[0] + "n" + premise[1] + "n";
					
					//making table
					truth_table(final);
					
					//judging conclusion
					cout<<"\n\nFinal Verdict:\n";
					if (invalid == false)
					{
						cout<<"Expressions are equivalent.\n";
					}
					else
					{
						cout<<"Expressions are not equivalent.\n";
						cout<<"In row "<<row<<", Both expressions have different output.\n";
					}
					
					//saving result or not
					cout<<"\n\nDo you want to save the result? ('y' for yes or 'n' for no) ";
	                cin>>save;
	                while (save != 'y' && save != 'n')
	                {
	                	cout<<"Enter a correct input (small letter 'y' or 'n': ";
	                	cin>>save;
					}
	                if (save == 'y')
	                {
	                	save_result ();
	                	cout<<"Returning to main menu....\n\n";
		                goto main;
	                }
	                else
	                {
		                cout<<"Returning to main menu....\n\n";
		                goto main;
	                }
					break;
				}
		case 4:
			    {
			    	cout<<"\n\nReasoning Chain Simulator\n";
			    	
			    	//getting premises
			    	var = 5;
			    	cout<<"Enter the number of premise implications (Max 5): ";
			    	cin>>premises;
			    	cin.ignore();
			    	for (int i = 0; i < premises; i++)
			    	{
			    		cout<<"Enter premise "<<i+1<<" (e.g: P>Q): ";
			    		premise[i] = expression_validation(premise[i]);
					}
					
					//outputing starting premises
					cout<<"\nStarting premises:\n";
					for (int i = 0; i < premises; i++)
					{
						cout<<i+1<<". "<<premise[i]<<endl;
					}
					
					//outputing derived implications
					//cout<<"\nFinal Derived Implications:\n";
					derivation(premise[0], premise[1], premise[2], premise[3], premise[4]);
					
					//saving result or not
					cout<<"\n\nDo you want to save the result? ('y' for yes or 'n' for no) ";
	                cin>>save;
	                while (save != 'y' && save != 'n')
	                {
	                	cout<<"Enter a correct input (small letter 'y' or 'n': ";
	                	cin>>save;
					}
	                if (save == 'y')
	                {
	                	save_result ();
	                	cout<<"Returning to main menu....\n\n";
		                goto main;
	                }
	                else
	                {
		                cout<<"Returning to main menu....\n\n";
		                goto main;
	                }
			    	break;
				}
		case 5:
			{
				char any;
				cout<<"Enter the name of file you want to load: ";
				cin>>file;
				ifstream file1(file+txt);
				string s;
				while (getline(file1, s))
				{
					cout<<s<<"\n";
				}
				file1.close();
				cout<<"\nPress any character to return to main menu: ";
				cin>>any;
				cout<<"Returning to main menu........\n";
				goto main;
				break;
			}
		case 6:
			{
				cout<<"\n\nExiting program.....";
				return 0;
			}
	}
	return 0;
}



void get_variables ()
{
	//asking for number of variables and validating
			    	
			    	cout<<"Enter the maximum number of unique propositional variables (Max 5): ";
			    	cin>>var;
			    	while (var <= 0 || var > 5)
			    	{
			    		cout<<"Number should be from 1-5: ";
			    		cin>>var;
					}
					
					//showing the chosen variables
					
					cout<<"Variables Detected: ";
					for (int i = 0; i < var; i++)
					{
						cout<<variable[i];
						if (i != var-1)
						{
							cout<<",";
						}
					}
					cout<<endl;
}



string expression_validation (string expression)
{
	//getting the expression from user
			
					again:
					check = 0;
					getline (cin, expression);
					bool bracket = false, letter = false, negation = false, operation = false, correct = false;
					bool b1 = false, b2 = false, outer = false, b = false;
					int ob = 0, vary = 0;
					
					//validating expression
					
					//for choice 4
					if (choice == 4)
					{
						while (expression[check] != 0)
						{
							if (expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R'
							|| expression[check] == 'S' || expression[check] == 'T')
							{
							 	vary++;
							}
							check++;
						}
						if (vary > 2)
						{
							cout<<"Implication should be between two variables only: ";
							goto again;
						}
					}
					
					//validating outer bracket
					
					//counting external operators
					check = 0;
					while (expression[check] != '\0')
					{
						//skipping the bracket equation
						if (expression[check] == '(')
						{
							while (expression[check] != ')')
							{
								check++;
							}
						}
						if (expression[check] == '&' || expression[check] == '|' || expression[check] == '>'
						|| expression[check] == '=')
						{
							ob++;
						}
						check++;
					}
					
					//checking if outer bracket was used or not
					if (ob > 1)
					{
						check = 0;
						while (expression[check] != '\0')
						{
							if (expression[check] == '(')
							{
								b1 = true;
								check++;
							}
							if (expression[check] == ')' && b1 == true && b2 == false)
							{
								if (b == true)
								{
									outer = true;
								}
								b1 = false;
							}
							if (expression[check] == '(' && b1 == true)
							{
								b2 = true;
								check++;
							}
							if (expression[check] == ')' && b2 == true)
							{
								b = true;
								b2 = false;
							}
							
							check++;
						}
						
						if (outer == false)
						{
							cout<<"Please use outer brackets to reduce confusion: ";
							goto again;
						}
					}
				
					check = 0;
					while (expression[check]  != '\0')
					{
						
						//validating starting of expression
						
						if (expression[0] == '|' || expression[0] == '&' || expression[0] == '>' || expression[0] == '=')
						{
							cout<<"Starting of expression is incorrect.\nEnter again: ";
							goto again;
						}
						
						//validating proper variables used
						
						if (expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R' 
						    || expression[check] == 'S' || expression[check] == 'T')
						    {
						    	for (int i = 0; i < var; i++)
						    	{
						    		if (expression[check] == variable[i])
						    		{
						    			correct = true;
									}
								}
						        if (correct == true)
						        {
						        	correct = false;
								}
								else 
								{
									cout<<"Use only the detected variables.\nEnter again: ";
									goto again;
								}
							}
						
						//validating correct use of brackets
						
						if (expression[check] == '(')
						{
							bracket = true;
						}
						
						if (expression[check] == ')' && bracket == true || outer == true)
						{
							bracket = false;
						}
						else if (expression[check] == ')' && bracket == false)
						{
							cout<<"Cannot use ')' without '(' first.\nEnter Again: ";
							goto again;
						}
						
						//validating proper placement of !
						if (expression[check] == '!')
						{
							negation = true;
						}
						if ((expression[check] == '|' || expression[check] == '&' || expression[check] == '>' || expression[check] == '='
						   || expression[check] == ')') && negation == true)
						   {
						   	 cout<<"You need to enter a variable after '!'.\nEnter again: ";
						   	 negation = false;
						   	 goto again;
						   }
						else if ((expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R' 
						           || expression[check] == 'S' || expression[check] == 'T') && negation == true)
						{
							negation = false;
						}
						
						//validating that two Variables have operation between them
						
						if ((expression[check] == '|' || expression[check] == '&' || expression[check] == '>' || expression[check] == '=')
						 && letter == true)
						 {
						 	letter = false;
						 }
						 else if ((expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R' 
						           || expression[check] == 'S' || expression[check] == 'T' || expression[check] == '(')
								    && letter == true)
						{
							cout<<"There should be an operator between variables or brackets.\nEnter again: ";
							letter = false;
							goto again;
						}
						if (expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R' || expression[check] == 'S' 
						|| expression[check] == 'T')
						{
							letter = true;
						}
						
						//validating variable comes after operation
						
						if ((expression[check] == '|' || expression[check] == '&' || expression[check] == '='
						    || expression[check] == '>' || expression[check] == ')') && operation == true)
						    {
						    	cout<<"There should be a variable after operation.\nEnter again: ";
						    	goto again;
							}
						else if ((expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R' || expression[check] == 'S' 
						         || expression[check] == 'T') && operation == true)
						{
							operation = false;
						}
						if (expression[check] == '|' || expression[check] == '&' || expression[check] == '!' || expression[check] == '='
						    || expression[check] == '>')
						    {
						    	operation = true;
							}
						
						//validating wrong input
						
						if (expression[check] == '|' || expression[check] == '>' || expression[check] == '=' || expression[check] == '&' 
						|| expression[check] == '!' || expression[check] == '(' || expression[check] == ')' || expression[check] == 'P' 
						|| expression[check] == 'Q' || expression[check] == 'R' || expression[check] == 'S' || expression[check] == 'T'
						|| expression[check] == ' ')
						{
							//cout<<"Good ";
						}
						else
						{
							cout<<"wrong input\nEnter again: ";
							goto again;
						}
						check++;
					}
					//checking if brackets were closed
					
					if (bracket == true)
					{
						cout<<"You have to close the brackets.\nEnter again: ";
						goto again;
					}
					return expression;
}


string single_variables ()
{
	//writing the propositional variables
	string svariable;
					
					//cout<<"\n\n\n\t";
					for (int i = 0; i < var; i++)
					{
						//cout<<variable[i]<<"\t";
						svariable += "\t";
						svariable += variable[i];
					}
					svariable += "\t";
	return svariable;
}


string table_columns (string expression)
{					
					//writing the brokendown expression
					
					check = 0;
					bool tab = false, bracket = false, exclaim = false, skip = false, dont = false;
					int z, total = 0;
					string name;
					
					check = 0;
					while (expression[check] != '\0')
					{
						//specification for '!'
						if (expression[check] == '!')
						{
							dont = false;
							z = check + 1;
							while (expression[z] == ' ')
							{
								z++;
							}
							if (expression[z] == '(')
							{
								
							}
							else
							{
							  //cout<<expression[check]<<expression[z]<<"\t";
							  name += (expression[check] + expression[z]);
							  name += "\t";
							  dont = true;
							}
						}
						
						//writing whole negation bracket eq
						if (expression[check] == '!')
						{
							z = check + 1;
							while (expression[z] == ' ')
							{
								z++;
							}
							if (expression[z] == '(')
							{
								while (expression[z] != ')')
								{
									if (expression[z] == ' ')
									{
										
									}
									else
									{
									   //cout<<expression[z];
									   name += expression[z];
								    }
									z++;
								}
								//cout<<expression[z]<<"\t";
								name += expression[z];
								name += "\t";
							}
						}
						
						//Printing ! with expression
						
						if (expression[check] == '!' && exclaim == false && var != 1 )//&& dont == false)
						{
							//cout<<expression[check];
							name += expression[check];
						}
						
						//for whole negation
						
						if (expression[check] == '(')
						{
							z = check - 1;
							while (expression[z] == ' ')
							{
								z--;
							}
							if (expression[z] == '!')
							{
								//cout<<expression[check];
								name += expression[check];
								z = check + 1;
								while (expression[z] != ')')
								{
									if (expression[z] == ' ')
									{
										
									}
									else
									{
										//cout<<expression[z];
										name += expression[z];
									}
									z++;
								}
								//cout<<expression[z]<<"\t";
								name += expression[z];
								name += "\t";
								exclaim = true;
							}
						}
						
					
						
						//specifications for brackets
						
						if (expression[check] == ')')
						{
							bracket = true;
							exclaim = false;
						}
						if ((expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R'
						  || expression[check] == 'S' || expression[check] == 'T') && bracket == true)
						  {
						  	bracket = false;
						  }
						  
						  //specifications for operators
						if ((expression[check] == '|' || expression[check] == '&' || expression[check] == '='
						 || expression[check] == '>') && tab == false && bracket == false && exclaim == false)
						{
							z = check + 1;
							while (expression[z] == ' ')
							{
								z++;
							}
							if (expression[z] == '(')
							{
								skip = true;
							}
							else
							{
						        z = check - 1;
							     while (expression[z] == ' ')
							      {
								     z--;
							      }
							     //cout<<expression[z];
							     name += expression[z];
							}
						}
						if ((expression[check] == '|' || expression[check] == '&' || expression[check] == '='
						 || expression[check] == '>') && bracket == false && exclaim == false && skip == false)
						 {
						 	//cout<<expression[check];
						 	name += expression[check];
						 	tab = true;
						 }
						 if ((expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R'
						  || expression[check] == 'S' || expression[check] == 'T') && tab == true && bracket == false && exclaim == false)
						  {
						  	//cout<<expression[check]<<"\t";
						  	name += expression[check];
						  	name += "\t";
						  	tab = false;
						  }
						  
						if (expression[check] == '(')
						{
							skip = false;
						}
						  check++;
					}
					
					//checking total variables used
					
					check = 0;
					while (expression[check] != '\0')
					{
						if (expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R'
						  || expression[check] == 'S' || expression[check] == 'T')
						  {
						  	total++;
						  }
						  check++;
					}
					
					check = 0;
					while (expression[check] != '\0')
					{
							//specification for double brackets
						if (expression[check] == '(')
						{
							z = check+1;
							while (expression[z] != ')')
							{
								if (expression[z] == '(')
								{
									while (expression[check] != ')')
									{
										//cout<<expression[check];
										name += expression[check];
										check++;
									}
									//cout<<expression[check];
									name += expression[check];
									check++;
									while (expression[check] != ')')
									{
										//cout<<expression[check];
										name += expression[check];
										check++;
									}
									//cout<<expression[check]<<" ----"<<"\t";
									name += expression[check];
									name += " ----\t";
								}
								z++;
							}
						}
						check++;
					}
					
					//writing the whole expression
					
					check = 0;
					if (total > 2)
					{
						while (expression[check] != '\0')
					{
						if (expression[check] != ' ')
						{
							//cout<<expression[check];
							name += expression[check];
						}
						check++;
					}
					//cout<<"\t";
					name += "\t";
					}
	return name;
}

string shunting_yard (string expression)
{
	string infix = {"                                                              "};
	int tarteeb = 0;
	char algorithm[20];
	int check = 0;
	int x = 0;
	bool higher = false;
	
	while (expression[check] != '\0')
	{
		if (expression[check] == '(')
		{
			algorithm[x] = expression[check];
			x++;
			
			while (expression[check] != ')')
			{
				if (expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R'
			        || expression[check] == 'S' || expression[check] == 'T')
			        {
			 	       infix[tarteeb] = expression[check];
			 	       tarteeb++;
			        }
			    if (expression[check] == '|' || expression[check] == '&' || expression[check] == '!' || expression[check] == '='
			        || expression[check] == '>')
			        {
			        	algorithm[x] = expression[check];
			        	x++;
					}
				check++;
			}
			
			x--;
			while (algorithm[x] != '(')
			{
				if (algorithm[x] == ' ')
				{
					
				}
				else
				{
					infix[tarteeb] = algorithm[x];
					tarteeb++;
					algorithm[x] = ' ';
				}
				x--;
			}
			algorithm[x] = ' ';
		}
		
		//new
			 	if (expression[check] == 'n')
			 	{
			 		while (x > 0)
			 		{
			 			x--;
			 		infix[tarteeb] = algorithm[x];
			 		tarteeb++;
			 		algorithm[x] = ' ';
					}
					infix[tarteeb] = expression[check];
					tarteeb++;
				}
		
		if (expression[check] == 'P' || expression[check] == 'Q' || expression[check] == 'R'
			 || expression[check] == 'S' || expression[check] == 'T')
			 {
			 	infix[tarteeb] = expression[check];
			 	tarteeb++;
			 }
			 
		if (expression[check] == '|' || expression[check] == '&' || expression[check] == '!' || expression[check] == '='
			|| expression[check] == '>')
			{
				switch (expression[check])
				{
					case '!':
						     {
						     	algorithm[x] = expression[check];
						     	x++;
						     	break;
							 }
					case '&':
						     {
						     	for (int i = 0; i < x; i++)
						     	{
						     		if (algorithm[i] == '!')
						     		{
						     			infix[tarteeb] = algorithm[i];
						     			tarteeb++;
						     			x = i;
						     			algorithm[x] = expression[check];
						     			x++;
						     			higher = true;
									}
								}
								if (higher == false)
								{
									algorithm[x] = expression[check];
									x++;
								}
								else
								{
									higher = false;
								}
								break;
							 }
					case '|':
						     {
						     	for (int i = 0; i < x; i++)
						     	{
						     		if (algorithm[i] == '!' || algorithm[i] == '&')
						     		{
						     			infix[tarteeb] = algorithm[i];
						     			tarteeb++;
						     			x = i;
						     			algorithm[x] = expression[check];
						     			x++;
						     			higher = true;
									}
								}
								if (higher == false)
								{
									algorithm[x] = expression[check];
									x++;
								}
								else
								{
									higher = false;
								}
								break;
							 }
					case '>':
						     {
						     	for (int i = 0; i < x; i++)
						     	{
						     		if (algorithm[i] == '!' || algorithm[i] == '&' || algorithm[i] == '|')
						     		{
						     			infix[tarteeb] = algorithm[i];
						     			tarteeb++;
						     			x = i;
						     			algorithm[x] = expression[check];
						     			x++;
						     			higher = true;
									}
								}
								if (higher == false)
								{
									algorithm[x] = expression[check];
									x++;
								}
								else
								{
									higher = false;
								}
								break;
							 }
					case '=':
						     {
						     	for (int i = 0; i < x; i++)
						     	{
						     		if (algorithm[i] == '!' || algorithm[i] == '&' || algorithm[i] == '|' || algorithm[i] == '>')
						     		{
						     			infix[tarteeb] = algorithm[i];
						     			tarteeb++;
						     			x = i;
						     			algorithm[x] = expression[check];
						     			x++;
						     			higher = true;
									}
								}
								if (higher == false)
								{
									algorithm[x] = expression[check];
									x++;
								}
								else
								{
									higher = false;
								}
								break;
							 }
				}
			}
		check++;
	}
	for (int i = x-1; i >= 0; i--)
	{
		if (algorithm[i] == ' ')
		{
			
		}
		else
		{
			infix[tarteeb] = algorithm[i];
			tarteeb++;
		}
	}
	infix[tarteeb] = 'n';
	tarteeb++;
	return infix;
}


int pow(int a, int b)
{
	int product = 1;
	for (int i = 1; i <= b; i++)
	{
		product *= a;
	}
	return product;
}

//truth table for output
void truth_table (string expression)
{
	bool logic[5],stack[5], temp1, temp2, con, ex[2];
	string algo;
	int q = 1, r = 1, s = 1, i = 0, temp, preem = 0, truth = 0, rowcount = 0;
		
	for (int count = 1; count <= pow(2,var); count++)
	{
		preem = 0;
		truth = 0;
	   //assigning logic to 'P'
	   if (count <= pow(2,var-1))
	   {
	   	   logic[0] = true;
	   }
	   else
	   {
		   logic[0] = false;
	   }
	
	   //assigning logic to 'Q'
	   if (var > 1)
	   {
	   	    if (q <= pow(2,var-2))
	   	    {
	   	    	logic[1] = true;
			}
			else
			{
				logic[1] = false;
			}
			if (q == 2*pow(2,var-2))
			{
				q = 1;
			}
			else
			{
				q++;
			}
	   }
	   
	   //assigning logic to 'R'
	   if (var > 2)
	   {
	   	    if (r <= pow(2,var-3))
	   	    {
	   	    	logic[2] = true;
			}
			else
			{
				logic[2] = false;
			}
			if (r == 2*pow(2,var-3))
			{
				r = 1;
			}
			else
			{
				r++;
			}
	   }
	   
	   //assigning logic to 'S'
	   if (var > 3)
	   {
	   	    if (s <= pow(2,var-4))
	   	    {
	   	    	logic[3] = true;
			}
			else
			{
				logic[3] = false;
			}
			if (s == 2*pow(2,var-4))
			{
				s = 1;
			}
			else
			{
				s++;
			}
	   }
	   
	   //asssigning logic to 'T'
	   if (var > 4)
	   {
	   	   if (count % 2 == 0)
	   	    {
	   	    	logic[4] = false;
			}
			else
			{
				logic[4] = true;
			}
	   }
	   
	   //printing the table
	   
	   cout<<"\n";
		for(int j = 0; j < var; j++)
		   {
			   cout<<"\t"<<logic[j];
		   }
		   
		// calculating values of expression columns  
		algo = shunting_yard(expression);
		check = 0;
		int f = 0, y = 0;
		while (algo[check] != '\0')
		{
			while (final[f] == ' ' || final[f] == '(' || final[f] == ')')
			{
				f++;
			}
			if (algo[check] == 'P' || algo[check] == 'Q' || algo[check] == 'R' || algo[check] == 'S'
			    || algo[check] == 'T')
			    {
			    	temp = (algo[check] == 'P')? 0 : (algo[check] == 'Q')? 1 : (algo[check] == 'R')? 2 :
			    		    (algo[check] == 'S')? 3 : 4;
			    	stack[i] = logic[temp];
			    	i++;
				}
			else if (algo[check] == '!' || algo[check] == '&' || algo[check] == '|' || algo[check] == '>'
			          || algo[check] == '=')
			          {
			          	  if (algo[check] == '!')
			          	  {
			          		   i--;
			          		   temp1 = stack[i];
			          		   stack[i] = !temp1;
			          		   cout<<"\t "<<stack[i];
								
			          		   if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
			          		   i++;
						  }  
						  else
						  {
						  	  i--;
					          temp2 = stack[i];
					          stack[i] = ' ';
					          i--;
					          temp1 = stack[i];
						  }
						  
						  switch (algo[check])
						  {
						  	case '&': 
						  	    {
						  	  	     stack[i] = temp1 && temp2;
							         cout<<"\t "<<stack[i];
							         
			          		         if (algo[check+1] == 'n')
			          		        {
			          		        	ex[y] = stack[i];
			          		        	//cout<<stack[i];
			          		        	y++;
			          		         	if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
									}
							         i++;
							         break;
							    }
							    
							case '|':
								{
									//cout<<"("<<temp1<<") ("<<temp2<<")";
									stack[i] = temp1 || temp2;
							        cout<<"\t "<<stack[i];
								
			          		        if (algo[check+1] == 'n')
			          		        {
			          		        	ex[y] = stack[i];
			          		        	y++;
			          		        	if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
									}
							        i++;
							        break;
								}
								
							case '>':
								{
									if (temp1 == 1 && temp2 == 0)
									{
										stack[i] = 0;
									}
									else
									{
										stack[i] = 1;
									}
									cout<<"\t "<<stack[i];
								
			          		   if (algo[check+1] == 'n')
			          		    {
			          		    	ex[y] = stack[i];
			          		    	//cout<<stack[i];
			          		        	y++;
			          		   	   if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
								}
									i++;
									break;
								}
								
							case '=':
								{
									if (temp1 == temp2)
									{
										stack[i] = true;
									}
									else
									{
										stack[i] = false;
									}
									cout<<"\t "<<stack[i];
								
			          		    if (algo[check+1] == 'n')
			          		    {
			          		    	ex[y] = stack[i];
			          		        	y++;
			          		    	if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
								}
									i++;
									break;
								}
						  }
					  }
			check++;
		}
		 //last column for choice 2
	   if (choice == 2)
	   {
	   	  if (truth == premises)
	   	  {
	   	  	//cout<<con;
	   	  	   if (con == true)
	   	  	    {
	   	  	   	    cout<<"\tValid";
	   	  	   	    rowcount++;
				}
				else
				{
					cout<<"\tInvalid";
					invalid = true;
					rowcount++;
					row = rowcount;
				}
		  }
		  else
		  {
		  	 cout<<"\tValid";
		  	 rowcount++;
		  }
	   }
	   //cout<<"("<<preem<<") ("<<truth<<")";
	   
	   //last column for choice 3
	   if (choice == 3)
	   {
	   	   if (ex[0] == ex[1])
	   	    {
	   	   	    cout<<"\tYes";
	   	   	    rowcount++;
			}
			else
			{
				cout<<"\tNo";
				rowcount++;
				row = rowcount;
				invalid = true;
			}
	   }
    }
    //cout<<"\n"<<algo;
}

//derivation for output
void derivation (string a, string b, string c, string d, string e)
{
	check = 0;
	string stack[30][3];
	int count = 0;
	
	//inputting a in stack
	while (a[check] != '\0')
	{
		if (a[check] == 'P' || a[check] == 'Q' || a[check] == 'R' || a[check] == 'S' || a[check] == 'T')
		{
			stack[0][count] = a[check];
			stack[0][count+1] = "\0";
			count++;
		}
		else if (a[check] == '&' || a[check] == '|' || a[check] == '>' || a[check] == '=')
		{
			stack[0][count] = a[check];
			stack[0][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting b in stack
	check = 0;
	count = 0;
	while (b[check] != '\0')
	{
		if (b[check] == 'P' || b[check] == 'Q' || b[check] == 'R' || b[check] == 'S' || b[check] == 'T')
		{
			stack[1][count] = b[check];
			stack[1][count+1] = "\0";
			count++;
		}
		else if (b[check] == '&' || b[check] == '|' || b[check] == '>' || b[check] == '=')
		{
			stack[1][count] = b[check];
			stack[1][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting c in stack
	check = 0;
	count = 0;
	while (c[check] != '\0')
	{
		if (c[check] == 'P' || c[check] == 'Q' || c[check] == 'R' || c[check] == 'S' || c[check] == 'T')
		{
			stack[2][count] = c[check];
			stack[2][count+1] = "\0";
			count++;
		}
		else if (c[check] == '&' || c[check] == '|' || c[check] == '>' || c[check] == '=')
		{
			stack[2][count] = c[check];
			stack[2][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting d in stack
	check = 0;
	count = 0;
	while (d[check] != '\0')
	{
		if (d[check] == 'P' || d[check] == 'Q' || d[check] == 'R' || d[check] == 'S' || d[check] == 'T')
		{
			stack[3][count] = d[check];
			stack[3][count+1] = "\0";
			count++;
		}
		else if (d[check] == '&' || d[check] == '|' || d[check] == '>' || d[check] == '=')
		{
			stack[3][count] = d[check];
			stack[3][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting e in stack
	check = 0;
	count = 0;
	while (e[check] != '\0')
	{
		if (e[check] == 'P' || e[check] == 'Q' || e[check] == 'R' || e[check] == 'S' || e[check] == 'T')
		{
			stack[4][count] = e[check];
			stack[4][count+1] = "\0";
			count++;
		}
		else if (e[check] == '&' || e[check] == '|' || e[check] == '>' || e[check] == '=')
		{
			stack[4][count] = e[check];
			stack[4][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//writing steps
	cout<<"\n\n";
	int counting = 1;
	for (int i = 0; i < premises+counting; i++)
	{
		for (int j = 0; j < premises; j++)
		{
			//checking for hypothetical syllogism
			if ((stack[i][2] == stack[j][0]) && (stack[i][1] == stack[j][1]))
			{
				stack[premises+counting][0] = stack[i][0];
				stack[premises+counting][1] = stack[i][1];
				stack[premises+counting][2] = stack[j][2];
				cout<<"Step "<<counting<<":\n";
				cout<<"As "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[i][2]<<" AND "<<stack[j][0]<<" "<<stack[j][1]<<" "<<stack[j][2];
				cout<<" is present, We can infer "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[j][2]<<" using hypothetical syllogism\n";
				counting++;
			}
			//checking for modus ponen
			if ((stack[i][0] == stack[j][0]) && stack[j][1] == "\0")
			{
				if (stack[i][1] != "\0")
				{
					stack[premises+counting][0] = stack[i][2];
					cout<<"Step "<<counting<<":\n";
					cout<<"As "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[i][2]<<" AND "<<stack[j][0];
					cout<<" is present, We can infer "<<stack[i][2]<<" using modus ponen\n";
					counting++;
				}
			}
		}
	}
	
	//finding derived output
	cout<<"\n\nFinal Derived Implications:\n";
	counting = 1;
	for (int i = 0; i < premises+counting; i++)
	{
		for (int j = 0; j < premises; j++)
		{
			//checking for hypothetical syllogism
			if ((stack[i][2] == stack[j][0]) && (stack[i][1] == stack[j][1]))
			{
				stack[premises+counting][0] = stack[i][0];
				stack[premises+counting][1] = stack[i][1];
				stack[premises+counting][2] = stack[j][2];
				cout<<counting<<". "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[j][2]<<" (Hypothetical Syllogism)"<<endl;
				counting++;
			}
			
			//checking for modus ponen
			if ((stack[i][0] == stack[j][0]) && stack[j][1] == "\0")
			{
				if (stack[i][1] != "\0")
				{
					stack[premises+counting][0] = stack[i][2];
					cout<<counting<<". "<<stack[i][2]<<" (Modus Ponen)"<<endl;
					counting++;
				}
			}
		}
	}
}

//truth table for storing
void truth_table (string expression, ofstream &out)
{
	bool logic[5],stack[5], temp1, temp2, con, ex[2];
	string algo;
	int q = 1, r = 1, s = 1, i = 0, temp, preem = 0, truth = 0, rowcount = 0;
		
	for (int count = 1; count <= pow(2,var); count++)
	{
		preem = 0;
		truth = 0;
	   //assigning logic to 'P'
	   if (count <= pow(2,var-1))
	   {
	   	   logic[0] = true;
	   }
	   else
	   {
		   logic[0] = false;
	   }
	
	   //assigning logic to 'Q'
	   if (var > 1)
	   {
	   	    if (q <= pow(2,var-2))
	   	    {
	   	    	logic[1] = true;
			}
			else
			{
				logic[1] = false;
			}
			if (q == 2*pow(2,var-2))
			{
				q = 1;
			}
			else
			{
				q++;
			}
	   }
	   
	   //assigning logic to 'R'
	   if (var > 2)
	   {
	   	    if (r <= pow(2,var-3))
	   	    {
	   	    	logic[2] = true;
			}
			else
			{
				logic[2] = false;
			}
			if (r == 2*pow(2,var-3))
			{
				r = 1;
			}
			else
			{
				r++;
			}
	   }
	   
	   //assigning logic to 'S'
	   if (var > 3)
	   {
	   	    if (s <= pow(2,var-4))
	   	    {
	   	    	logic[3] = true;
			}
			else
			{
				logic[3] = false;
			}
			if (s == 2*pow(2,var-4))
			{
				s = 1;
			}
			else
			{
				s++;
			}
	   }
	   
	   //asssigning logic to 'T'
	   if (var > 4)
	   {
	   	   if (count % 2 == 0)
	   	    {
	   	    	logic[4] = false;
			}
			else
			{
				logic[4] = true;
			}
	   }
	   
	   //printing the table
	   
	   out<<"\n";
		for(int j = 0; j < var; j++)
		   {
			   out<<"\t"<<logic[j];
		   }
		   
		// calculating values of expression columns  
		algo = shunting_yard(expression);
		check = 0;
		int f = 0, y = 0;
		while (algo[check] != '\0')
		{
			while (final[f] == ' ' || final[f] == '(' || final[f] == ')')
			{
				f++;
			}
			if (algo[check] == 'P' || algo[check] == 'Q' || algo[check] == 'R' || algo[check] == 'S'
			    || algo[check] == 'T')
			    {
			    	temp = (algo[check] == 'P')? 0 : (algo[check] == 'Q')? 1 : (algo[check] == 'R')? 2 :
			    		    (algo[check] == 'S')? 3 : 4;
			    	stack[i] = logic[temp];
			    	i++;
				}
			else if (algo[check] == '!' || algo[check] == '&' || algo[check] == '|' || algo[check] == '>'
			          || algo[check] == '=')
			          {
			          	  if (algo[check] == '!')
			          	  {
			          		   i--;
			          		   temp1 = stack[i];
			          		   stack[i] = !temp1;
			          		   out<<"\t "<<stack[i];
								
			          		   if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
			          		   i++;
						  }  
						  else
						  {
						  	  i--;
					          temp2 = stack[i];
					          stack[i] = ' ';
					          i--;
					          temp1 = stack[i];
						  }
						  
						  switch (algo[check])
						  {
						  	case '&': 
						  	    {
						  	  	     stack[i] = temp1 && temp2;
							         out<<"\t "<<stack[i];
							         
			          		         if (algo[check+1] == 'n')
			          		        {
			          		        	ex[y] = stack[i];
			          		        	//cout<<stack[i];
			          		        	y++;
			          		         	if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
									}
							         i++;
							         break;
							    }
							    
							case '|':
								{
									//cout<<"("<<temp1<<") ("<<temp2<<")";
									stack[i] = temp1 || temp2;
							        out<<"\t "<<stack[i];
								
			          		        if (algo[check+1] == 'n')
			          		        {
			          		        	ex[y] = stack[i];
			          		        	y++;
			          		        	if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
									}
							        i++;
							        break;
								}
								
							case '>':
								{
									if (temp1 == 1 && temp2 == 0)
									{
										stack[i] = 0;
									}
									else
									{
										stack[i] = 1;
									}
									out<<"\t "<<stack[i];
								
			          		   if (algo[check+1] == 'n')
			          		    {
			          		    	ex[y] = stack[i];
			          		    	//cout<<stack[i];
			          		        	y++;
			          		   	   if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
								}
									i++;
									break;
								}
								
							case '=':
								{
									if (temp1 == temp2)
									{
										stack[i] = true;
									}
									else
									{
										stack[i] = false;
									}
									out<<"\t "<<stack[i];
								
			          		    if (algo[check+1] == 'n')
			          		    {
			          		    	ex[y] = stack[i];
			          		        	y++;
			          		    	if (preem < premises)
			          		   {
			          		   	    if (stack[i] == true)
			          		   	    {
			          		   	    	truth++;
									}
									preem++;
							   }
							   else
							   {
							   	con = stack[i];
							   }
								}
									i++;
									break;
								}
						  }
					  }
			check++;
		}
		 //last column for choice 2
	   if (choice == 2)
	   {
	   	  if (truth == premises)
	   	  {
	   	  	   if (con == true)
	   	  	    {
	   	  	   	    out<<"\tValid";
	   	  	   	    rowcount++;
				}
				else
				{
					out<<"\tInvalid";
					invalid = true;
					rowcount++;
					row = rowcount;
				}
		  }
		  else
		  {
		  	 out<<"\tValid";
		  	 rowcount++;
		  }
	   }
	   //cout<<"("<<preem<<") ("<<truth<<")";
	   
	   //last column for choice 3
	   if (choice == 3)
	   {
	   	   if (ex[0] == ex[1])
	   	    {
	   	   	    out<<"\tYes";
	   	   	    rowcount++;
			}
			else
			{
				out<<"\tNo";
				rowcount++;
				row = rowcount;
				invalid = true;
			}
	   }
    }
    //cout<<"\n"<<algo;
}
//derivation for storing
void derivation (string a, string b, string c, string d, string e, ofstream &out)
{
	check = 0;
	string stack[30][3];
	int count = 0;
	
	//inputting a in stack
	while (a[check] != '\0')
	{
		if (a[check] == 'P' || a[check] == 'Q' || a[check] == 'R' || a[check] == 'S' || a[check] == 'T')
		{
			stack[0][count] = a[check];
			stack[0][count+1] = "\0";
			count++;
		}
		else if (a[check] == '&' || a[check] == '|' || a[check] == '>' || a[check] == '=')
		{
			stack[0][count] = a[check];
			stack[0][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting b in stack
	check = 0;
	count = 0;
	while (b[check] != '\0')
	{
		if (b[check] == 'P' || b[check] == 'Q' || b[check] == 'R' || b[check] == 'S' || b[check] == 'T')
		{
			stack[1][count] = b[check];
			stack[1][count+1] = "\0";
			count++;
		}
		else if (b[check] == '&' || b[check] == '|' || b[check] == '>' || b[check] == '=')
		{
			stack[1][count] = b[check];
			stack[1][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting c in stack
	check = 0;
	count = 0;
	while (c[check] != '\0')
	{
		if (c[check] == 'P' || c[check] == 'Q' || c[check] == 'R' || c[check] == 'S' || c[check] == 'T')
		{
			stack[2][count] = c[check];
			stack[2][count+1] = "\0";
			count++;
		}
		else if (c[check] == '&' || c[check] == '|' || c[check] == '>' || c[check] == '=')
		{
			stack[2][count] = c[check];
			stack[2][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting d in stack
	check = 0;
	count = 0;
	while (d[check] != '\0')
	{
		if (d[check] == 'P' || d[check] == 'Q' || d[check] == 'R' || d[check] == 'S' || d[check] == 'T')
		{
			stack[3][count] = d[check];
			stack[3][count+1] = "\0";
			count++;
		}
		else if (d[check] == '&' || d[check] == '|' || d[check] == '>' || d[check] == '=')
		{
			stack[3][count] = d[check];
			stack[3][count+1] = "\0";
			count++;
		}
		check++;
	}
	
	//inputting e in stack
	check = 0;
	count = 0;
	while (e[check] != '\0')
	{
		if (e[check] == 'P' || e[check] == 'Q' || e[check] == 'R' || e[check] == 'S' || e[check] == 'T')
		{
			stack[4][count] = e[check];
			stack[4][count+1] = "\0";
			count++;
		}
		else if (e[check] == '&' || e[check] == '|' || e[check] == '>' || e[check] == '=')
		{
			stack[4][count] = e[check];
			stack[4][count+1] = "\0";
			count++;
		}
		check++;
	}
	
		//writing steps
	out<<"\n\n";
	int counting = 1;
	for (int i = 0; i < premises+counting; i++)
	{
		for (int j = 0; j < premises; j++)
		{
			//checking for hypothetical syllogism
			if ((stack[i][2] == stack[j][0]) && (stack[i][1] == stack[j][1]))
			{
				stack[premises+counting][0] = stack[i][0];
				stack[premises+counting][1] = stack[i][1];
				stack[premises+counting][2] = stack[j][2];
				out<<"Step "<<counting<<":\n";
				out<<"As "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[i][2]<<" AND "<<stack[j][0]<<" "<<stack[j][1]<<" "<<stack[j][2];
				out<<" is present, We can infer "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[j][2]<<" using hypothetical syllogism\n";
				counting++;
			}
			//checking for modus ponen
			if ((stack[i][0] == stack[j][0]) && stack[j][1] == "\0")
			{
				if (stack[i][1] != "\0")
				{
					stack[premises+counting][0] = stack[i][2];
					out<<"Step "<<counting<<":\n";
					out<<"As "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[i][2]<<" AND "<<stack[j][0];
					out<<" is present, We can infer "<<stack[i][2]<<" using modus ponen\n";
					counting++;
				}
			}
		}
	}
	
	//finding derived output
	out<<"\n\nFinal Derived Implications:\n";
	counting = 1;
	for (int i = 0; i < premises+counting; i++)
	{
		for (int j = 0; j < premises; j++)
		{
			//checking for hypothetical syllogism
			if ((stack[i][2] == stack[j][0]) && (stack[i][1] == stack[j][1]))
			{
				stack[premises+counting][0] = stack[i][0];
				stack[premises+counting][1] = stack[i][1];
				stack[premises+counting][2] = stack[j][2];
				out<<counting<<". "<<stack[i][0]<<" "<<stack[i][1]<<" "<<stack[j][2]<<" (Hypothetical Syllogism)"<<endl;
				counting++;
			}
			
			//checking for modus ponen
			if ((stack[i][0] == stack[j][0]) && stack[j][1] == "\0")
			{
				if (stack[i][1] != "\0")
				{
					stack[premises+counting][0] = stack[i][2];
					out<<counting<<". "<<stack[i][2]<<" (Modus Ponen)"<<endl;
					counting++;
				}
			}
		}
	}
}

void save_result ()
{
	string file, txt = ".txt", s;
	
	cout<<"Enter a file name: ";
	cin>>file;
	ofstream file1(file+txt);
	switch (choice)
	{
		case 1:
			{
				file1<<single_variables();
				file1<<table_columns(expression)<<"\n";
				truth_table(expression, file1);
				file1.close();
				break;
			}
		case 2:
			{
				file1<<single_variables();
				for (int i = 0; i < premises; i++)
					{
						file1<<table_columns(premise[i]);
					}
					file1<<table_columns(conclusion);
					file1<<"Result\n";
				truth_table(final, file1);
				file1<<"\n\nFinal Verdict:\n";
				if (invalid == false)
					{
						file1<<"The argument is valid.\n";
						file1<<"No row was found where ALL premises were true AND the conclusion was false.\n";
					}
					else
					{
						file1<<"The argument is invalid.\n";
						file1<<"In row "<<row<<", ALL premises are true AND the conclusion is false.\n";
					}
				break;
			}
		case 3:
			{
				file1<<single_variables();
				file1<<table_columns(premise[0])<<table_columns(premise[1]);
				file1<<"Match\n";
				truth_table(final, file1);
				file1<<"\n\nFinal Verdict:\n";
				if (invalid == false)
				{
					file1<<"Expressions are equivalent.\n";
				}
				else
				{
					file1<<"Expressions are not equivalent.\n";
					file1<<"In row "<<row<<", Both expressions have different output.\n";
				}
				break;
			}
		case 4:
			{
				file1<<"\nStarting premises:\n";
				for (int i = 0; i < premises; i++)
				{
					file1<<i+1<<". "<<premise[i]<<endl;
				}
				file1<<"\nFinal Derived Implications:\n";
				derivation (premise[0], premise[1], premise[2], premise[3], premise[4], file1);
				break;
			}
	}
	cout<<"Data saved in "<<file+txt<<endl;
}
