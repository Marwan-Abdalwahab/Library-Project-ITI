#include<iostream>
#include <string>
#include <vector>
#include<iomanip>
#include<conio.h>
#include <fstream>
#include <algorithm>
#include <cstdlib>


using namespace std;

// Base Structure
struct status
{
	bool is_mine;
	bool is_read;
	bool is_fav= false;
};
struct book
{
	string title;
	string author;
	status stat;
	string year_published;
	string genre;
};


// input Validation
int validate_number(int from, int to, string message)
{
	while (true)
	{

	int number;
	cin >> number;
	if (cin.fail() or number<from or number>to)
	{

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << message;
	}
	else
	{
	return number;

	}
	}
}


//Prototypes
void main_menu(vector <book> &books); 
int ask_for_editing(vector <book> &books,vector <int> &indices);
void Display_all_books(vector <book>& books);

//books forming
string convert_to_lower(string word)
{
	string proper;
	for (int i = 0; i < word.size(); i++)
	{
		proper += tolower(word[i]);
	}
	return proper;
}
void table_formating(vector <book>& books)
{
	cout << "+---------------------------------------------+---------------------+--------+-----------------+-----------------+------------------+----------+\n";
	cout << "| " << setw(43) << left << "Title"
		<< " | " << setw(19) << left << "Author"
		<< " | " << setw(6) << left << "Year"
		<< " | " << setw(15) << left << "Genre"
		<< " | " << setw(15) << left << "Reading Status"
		<< " | " << setw(16) << left << "Property Status"
		<< " | " << setw(10) << left << "Favorite" << "\n";
	cout << "+---------------------------------------------+---------------------+--------+-----------------+-----------------+------------------+----------+\n";

	for (int i = 0; i < books.size(); i++)
	{
		cout << left <<"|" << setw(45) << books[i].title
			<< "|" << setw(21) << books[i].author
			<< "|" << setw(8) << books[i].year_published
			<< "|" << setw(17) << books[i].genre
			<< "|" << setw(17) << (books[i].stat.is_read ? "Read" : "Not Read")
			<< "|" << setw(17) << (books[i].stat.is_mine ? "Owned" : "Not Owned")
			<< " | " << setw(10) << (books[i].stat.is_fav ? "Yes" : "No") << endl;


		cout << "+---------------------------------------------+---------------------+--------+-----------------+-----------------+------------------+----------+\n";
	}
}
void table_formating_using_indices(vector <int> &indices, vector <book> &books)
{
	cout << "+-------------------------------------+----------------------+---------------+---------------+----------------------+----------------------+----------+\n";
	cout << "| " << setw(35) << left << "  Title"
		<< " | " << setw(20) << left << "Author"
		<< " | " << setw(13) << left << "Year"
		<< " | " << setw(13) << left << "Genre"
		<< " | " << setw(20) << left << "Reading Status"
		<< " | " << setw(20) << left << "Property Status"
		<< " | " << setw(10) << left << "Favorite" << "\n";
	cout << "+-------------------------------------+----------------------+---------------+---------------+----------------------+----------------------+----------+\n";


	for (int i = 0; i < indices.size(); i++)
	{
		cout << "|" << i + 1 << "- " << setw(33) << left << books[indices[i]].title
			<< " | " << setw(20) << left <<  books[indices[i]].author
			<< " | " << setw(13) << left <<  books[indices[i]].year_published
			<< " | " << setw(13) << left <<  books[indices[i]].genre
			<< " | " << setw(20) << left << (books[indices[i]].stat.is_read ? "Read" : "Not Read")
			<< " | " << setw(20) << left << (books[indices[i]].stat.is_mine ? "Owned" : "Not Owned")
			<< " | " << setw(10) << left << (books[indices[i]].stat.is_fav ? "Yes" : "No") << "\n";
		cout << "+-------------------------------------+----------------------+---------------+---------------+----------------------+----------------------+----------+\n";
	}

}



//in/out file stream
void save_books_to_file(vector<book>& books,const string& filename) 
{
	ofstream outFile (filename, ios::out);
	
	if (!(outFile.is_open())) 
	{
		cout << "Error opening file for writing!\n";
		return;
	}

	for (book b : books) {
		outFile << b.title << "|"
			<< b.author << "|"
			<< b.year_published << "|"
			<< b.genre << "|"
			<< b.stat.is_read << "|"
			<< b.stat.is_mine << "|"
			<< b.stat.is_fav<<"\n";
	}
	outFile.close();
}
void load_books_from_file(vector<book>& books, const string& filename) {
	ifstream inFile(filename, ios::in);
	if (!(inFile.is_open())) {
		cout << "No existing file found, starting with empty library.\n";
		return;
	}

	books.clear();


	string line;
	while (getline(inFile, line)) {
		
		size_t pos = 0;
		vector<string> parts;
		while ((pos = line.find('|')) != string::npos)
		{
			parts.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		parts.push_back(line); 

		if (parts.size() == 7) {
			book b;
			b.title = parts[0];
			b.author = parts[1];
			b.year_published = (parts[2]);
			b.genre = parts[3];
			b.stat.is_read = stoi(parts[4]);
			b.stat.is_mine = stoi(parts[5]);
			b.stat.is_fav = stoi(parts[6]);
			books.push_back(b);
		}
	}
	inFile.close();
}


//helping functions
void Display_book_by_index(vector <book>& books, int index)
{
	if (index != -1)
	{
		cout << "===========================\n";
		cout << "Title: " << books[index].title << endl;
		cout << "Author: " << books[index].author << endl;
		cout << "Year Published: " << books[index].year_published << endl;
		cout << "Genre: " << books[index].genre << endl;
		cout << "Reading Status: " << books[index].stat.is_read << endl;
		cout << "Property Status: " << books[index].stat.is_mine << endl;
		cout << "Favourite: " << books[index].stat.is_fav << endl;
		cout << "===========================\n\n";

	}
	else
		cout << "Book Not Found!\n";

} 
int  find_book_by_name(vector <book>& books,string name)
{
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].title == name)
		{
			return i;
		}
	}
	return -1;
}
vector <string> split_each_word(string line)
{
	vector <string> words;
	string delimeter = " ";
	string sword;
	int pos = 0;
	while (pos != string::npos)
	{
		pos = line.find(delimeter);
		sword = line.substr(0, pos);
		if (!sword.empty())
		{
		words.push_back(sword);
		}
		line.erase(0, (pos + delimeter.length()));
	}
	return words;
}
bool word_in_long_string(string sentence, string target_word) 
{
	vector <string> splited_title= split_each_word(sentence);
	for (string s:splited_title)
	{
		if (s == target_word)
		{
			return true;
		}
	}
	return false;
}


//start menu methods
void add_book_method(vector <book>& books)  
{
	book my_book;
	char choice;
	string title,author,genre;
	cout <<"Enter book's Title: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	my_book.title = convert_to_lower(title);
	for (book b : books)
	{
		if (b.title == my_book.title)
		{
			cout << "The book with the title: " << my_book.title << " is already in the library\n";
			return;
		}
	}
	cout <<"Enter book's author's name: ";
	getline(cin,author);
	my_book.author = convert_to_lower(author);

	cout << "Enter book's genre: ";
	getline(cin, genre);
	my_book.genre = convert_to_lower(genre);
	cout << "Enter the book's year of publishment: ";
	getline(cin,my_book.year_published);

	cout << "Do you own the book ?(y/n): ";
	cin>>choice;

	if (choice == 'y'|| choice=='Y')
		my_book.stat.is_mine = true;
	else
		my_book.stat.is_mine = false;

	cout << "Did you read the book ? (y/n): ";
	cin >> choice;

	if (choice == 'y' or choice == 'Y')
		my_book.stat.is_read = true;
	else
		my_book.stat.is_read = false;

	cout << "Do you want to add it to your favourites? (y/n): ";
	cin >> choice;

	if (choice == 'y' or choice == 'Y')
		my_book.stat.is_fav = true;
	else
		my_book.stat.is_fav = false;

	books.push_back(my_book);
	cout << "\nAdded Successfully !\n";

	Display_all_books(books);
}
void search_by_keywords_method(vector <book>&books, string&keyword)  
{
	while (true)
	{
	keyword = convert_to_lower(keyword);
	vector<int> list;
	for (int i = 0; i < books.size(); i++)
	{
		if ((books[i].author == keyword) || (books[i].genre == keyword) || (books[i].year_published == keyword) || word_in_long_string(books[i].title, keyword))
		{
			list.push_back(i);
		}
	}

	if (list.empty())
	{
		cout << "No books found holding the word: "<<keyword<<" in it's properties\n" << "\n";
		return;
	}

	table_formating_using_indices(list, books);
	
	int edit = ask_for_editing(books,list);
	if (edit != 1)
		break;
	system("cls");
	
	}
}
void Display_all_books( vector<book> &books) 
{
	if (books.empty())
	{
		cout << "No books in the library yet.\n";
		return;
	}

	table_formating(books);
}
void Display_favourites(vector <book>& books)
{
	while (true)
	{
	vector <int> favourites;
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].stat.is_fav)
			favourites.push_back(i);
	}
	if (favourites.empty())
	{
		cout << "No boooks found in the favourite list\n";
		return;
	}

	cout << "books in favourite list: \n";

	table_formating_using_indices(favourites, books);

	int edit = ask_for_editing(books, favourites);
	if (edit != 1)
		break;

	system("cls");
    }
}
void update_book_method(vector <book>& books)

{
	int choice;
	char ch;
	string name;
	char stat;
	cout << "Enter the book's name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name);
	name = convert_to_lower(name);
	int index = find_book_by_name(books, name);
	if (index != -1)
	{
		Display_book_by_index(books, index);


	cout << "Choose update type: \n\n";
	cout << "[1] Title\n"<<
		    "[2] Author\n"<<
		    "[3] Year Published\n"<<
		    "[4] Genre\n"<<
		    "[5] Reading Status\n"<<
		    "[6] Property Status\n"<<
		    "[7]Favourite Status\n\n";
	choice = validate_number(1, 7, "Please enter an integer from 1-->7: ");
	switch (choice)
	{
	case 1 :
		cout << "Enter the new Title: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin,books[index].title);
		books[index].title = convert_to_lower(books[index].title);
		break;
	
	case 2:
		cout << "Enter the new Author name: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, books[index].author);
		books[index].author = convert_to_lower(books[index].author);

		break;

	case 3:
		cout << "Enter the new Year of publishing: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, books[index].year_published);
		break;

	case 4:
		cout << "Enter the new Genre: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, books[index].genre);
		books[index].genre = convert_to_lower(books[index].genre);

		break;

	
	case 5:
		cout << "Do you own the book ? (y/n): ";
		cin >> ch;

		if (ch == 'y' || ch == 'Y')
			books[index].stat.is_mine = true;
		else
			books[index].stat.is_mine = false;
		break;
	case 6:

		cout << "Did you read the book ? (y/n): ";
		cin >> ch;

		if (ch == 'y' or ch == 'Y')
			books[index].stat.is_read = true;
		else
			books[index].stat.is_read = false;

		break;
	case 7:

		cout << "Do you want to add it to your favourites? (y/n): ";
		cin >> ch;

		if (ch == 'y' or ch == 'Y')
			books[index].stat.is_fav = true;
		else
			books[index].stat.is_fav = false;

		break;

	default:
		cout << "Invalid input !";
		break;
	}
	switch (choice)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			cout << "\nUpdated Successfully\n\n";
			Display_book_by_index(books, index);
			break;

	}
	system("cls");
	cout << "\nTitle: " << books[index].title << endl;
	cout << "Author: " << books[index].author << endl;
	cout << "Year Published: " << books[index].year_published << endl;
	cout << "Genre: " << books[index].genre << endl;
	cout << "Read Status: " << (books[index].stat.is_read ? "Read" : "Not Read") << endl;
	cout << "Property Status: " << (books[index].stat.is_mine ? "Owned" : "Not Owned") << "\n\n";
	}
	else
	{
		cout << "The name of the book you entered isn't in the library\n";
	}

}
void Statistics_method(const vector<book>& books)
{
	short owned_counter = 0;
	short read_counter = 0;

	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].stat.is_mine)
			owned_counter++;
		if (books[i].stat.is_read)
			read_counter++;
	}

	int total = books.size();
	int unread_counter = total - read_counter;      
	int borrowed_counter = total - owned_counter;   

	double read_percent = (read_counter * 100.0) / total;
	double unread_percent = (unread_counter * 100.0) / total;
	double owned_percent = (owned_counter * 100.0) / total;
	double borrowed_percent = (borrowed_counter * 100.0) / total;

	cout << "\n";
	cout << "+------------------------+----------+-------------+" << endl;
	cout << "| Category               | Count    | Percentage  |" << endl;
	cout << "+------------------------+----------+-------------+" << endl;
	cout << "| Read Books             | " << setw(8) << read_counter
		<< " | " << setw(10) << fixed << setprecision(1) << read_percent << "% |" << endl;
	cout << "| Unread Books           | " << setw(8) << unread_counter
		<< " | " << setw(10) << fixed << setprecision(1) << unread_percent << "% |" << endl;
	cout << "+------------------------+----------+-------------+" << endl;
	cout << "| Owned Books            | " << setw(8) << owned_counter
		<< " | " << setw(10) << fixed << setprecision(1) << owned_percent << "% |" << endl;
	cout << "| Borrowed Books         | " << setw(8) << borrowed_counter
		<< " | " << setw(10) << fixed << setprecision(1) << borrowed_percent << "% |" << endl;
	cout << "+------------------------+----------+-------------+" << endl;
	cout << "| TOTAL                  | " << setw(8) << total
		<< " | " << setw(10) << "100.0" << "% |" << endl;
	cout << "+------------------------+----------+-------------+" << endl;
	cout << "\n";
}
void Display_wishlist_method(vector <book>& books) 

{
	while (true)
	{
	vector<int> wishlist;
		for (int i = 0; i < books.size(); i++)
		{
			if ((!books[i].stat.is_read) and (!books[i].stat.is_mine))
				wishlist.push_back(i);
		}

		if (wishlist.empty())
		{
			cout << "No books found in the wishlist " << "\n";
			return;
		}


		cout << "\nBooks in wishlist:\n";


		table_formating_using_indices(wishlist,books);

		int edit = ask_for_editing(books,wishlist);
		if (edit != 1)
			break;
		system("cls");
	}
	
}  
void Display_categorized_books_method(vector <book> &books, string target_genre) 
{
	while (true)
	{

	vector<int> category_indices;
	target_genre = convert_to_lower(target_genre);
	for (int i = 0; i < books.size();i++)
	{
		if (books[i].genre == target_genre)
		{
			category_indices.push_back(i);
		}
	}

	if (category_indices.empty())
	{
		cout << "No books found with genre: " << target_genre << "\n";
		return;
	}


	cout << "\nBooks with genre [" << target_genre << "]:\n";


	table_formating_using_indices(category_indices, books);

		int edit = ask_for_editing(books,category_indices);
		if (edit != 1)
			break;
		system("cls");
	}
	

}
void exiting(vector <book>& books) 
{
	save_books_to_file(books, "lib.txt");
	exit(0);
}


//update menu
void update_book_by_index(vector <book> &books,int index) 
{
	int choice;
	char ch;
	cout << "\nChoose update type: \n";
	cout << "[1] Title\n"<<
		    "[2] Author\n"<<
		    "[3] Year Published\n"<<
		    "[4] Genre\n"<<
		    "[5]Reading Status\n"<<
		    "[6]Property Status\n"<<
		    "[7]Favourites Status\n\n";
	choice = validate_number(1, 7, "Please enter an integer from 1-->7: ");
	switch (choice)
	{
	case 1:
		cout << "Enter the new Title: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, books[index].title);
		books[index].title = convert_to_lower(books[index].title);
		break;

	case 2:
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the new Author name: ";
		getline(cin, books[index].author);
		books[index].genre = convert_to_lower(books[index].author);

		break;

	case 3:
		cout << "Enter the new Year of publishing: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, books[index].year_published);
		break;

	case 4:
		cout << "Enter the new Genre: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, books[index].genre);
		books[index].genre = convert_to_lower(books[index].genre);
		break;

	case 5:
		cout << "Do you own the book ?(y/n): ";
		cin >> ch;

		if (ch == 'y' || ch == 'Y')
			books[index].stat.is_mine = true;
		else
			books[index].stat.is_mine = false;
		break;
	case 6:

		cout << "Did you read the book ? (y/n): ";
		cin >> ch;

		if (ch == 'y' or ch == 'Y')
			books[index].stat.is_read = true;
		else
			books[index].stat.is_read = false;
		break;
	case 7:

		cout << "Do you want to add it to your favourites? (y/n): ";
		cin >> ch;

		if (ch == 'y' or ch == 'Y')
			books[index].stat.is_fav = true;
		else
			books[index].stat.is_fav = false;
		break;

	default:
		cout << "Invalid input !";
		break;
	}
	switch (choice)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		cout << "\nUpdated Successfully\n";
	}
	
} 
void delete_book_by_index(vector <book>& books, int index) 
{

		books.erase(books.begin() + index);
		cout << "\nDeleted Successfuly!\n";
	
} 
void add_book_to_favourites(vector <book> &books, int index)
{
	books[index].stat.is_fav = true;
}
int ask_for_editing(vector <book> &books,vector <int> &indices) 
{
	cout << "Do want to edit the books in the list ? (y/n)\n";
	char ch;
	cin >> ch;
	if (ch == 'y' or ch == 'Y')
	{
		int index,method;
		cout << "Enter the index of the book you want to change: ";
		string message = "Please enter an integer between within the indices: ";
		index = validate_number(1, indices.size(),message);
		int real_index = indices[index - 1];
		cout << "\n[1]Delete\n[2]Update specifications\n[3] Add to favourites\n";
		cout << "\nChoose the method you want to apply: ";
		method = validate_number(1, 3, "Please enter a number from 1-->3: ");
		 
		switch (method)
		{
		case 1:
			delete_book_by_index(books, real_index);
			indices.erase(indices.begin() + (index - 1));

			for (int i = 0; i < indices.size(); i++) {
				if (indices[i] > real_index) {
					indices[i]--;
				}
			}
			break;
		case 2:
			update_book_by_index(books, real_index);
			break;
		case 3:
			add_book_to_favourites(books, real_index);
			break;
		default:
			cout << "Invalid input!\n";
			
		}
	}
	else
	{
		return -1;
	}

	return 1;
}





void main_menu(vector <book> &books)	
{
	while (true)
	{
		int choice;
		string Genre;
		string name_to_search;
		system("cls");
		cout << "===========================\n";
		cout << "     Library Main Menu\n";
		cout << "===========================\n\n";
	  cout  << "[1] Add Book\n"
			<< "[2] Find a Book by keyword\n"
			<< "[3] Display all books in my library\n"
			<< "[4] Display Favourites\n"
		    << "[5] Update Book\n"
			<< "[6] Display Statistics\n"
			<< "[7] Display Wishlist\n"
			<< "[8] Display Categorized books\n"
			<< "[9] Exit and save files\n";
	  cout << "===========================";

		cout << "\nEnter your choice: ";
		choice = validate_number(1, 9, "Please enter a number from 1-->9: ");
		switch (choice)
		{

		case 1:
			system("cls");
			add_book_method(books);
			cout << "Press any key to go back to main menu... ";
			_getch();
			break;


		case 2:
			system("cls");
			cout << "Enter a keyword of the book you want to find: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name_to_search);
			search_by_keywords_method(books, name_to_search);
			cout << "Press any key to go back to main menu... ";
			_getch();
			break;

		case 3:
			system("cls");
			Display_all_books(books);
			cout << "Press any key to go back...";
			_getch();
			break;
		case 4:
			system("cls");
			Display_favourites(books);
			cout << "Press any key to go back... ";
			_getch();
			break;
		case 5:
			system("cls");
			update_book_method(books);
			cout << "Press any key to go back... ";
			_getch();
			break;

		case 6:
			system("cls");
			Statistics_method(books);
			cout << "Press any key to go back... ";
			_getch();
			break;
		case 7:
			system("cls");
			Display_wishlist_method(books);
			cout << "Press any key to go back... ";
			_getch();
			break;
		case 8:
			system("cls");
			cout << "Which Genre are you looking for: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, Genre);
			Display_categorized_books_method(books, Genre);
			cout << "Press any key to go back... ";
			_getch();
			break;
		case 9:
			exiting(books);
			break;

		default:
			cout << "invalid input\n";
			cout << "Press any key to go back to main menu... ";
			_getch();
			break;

		}
		
	}

}

int main()
{
	vector <book> books;
	load_books_from_file(books, "lib.txt");
  
	main_menu(books);

}