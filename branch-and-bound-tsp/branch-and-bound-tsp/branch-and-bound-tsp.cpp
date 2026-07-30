#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class Graph;
class Add_mtr;
class Answer;

class Graph
{
public:
	Graph(int& size);
	~Graph();
	void init_Graph();
	int return_Graph(int* i, int* j);
	int return_size_graph();
	int& operator()(int, int);

private:
	int N;
	int** pGraph;
};

class Add_mtr {
public:

	Add_mtr(int& size);
	void init_Add_mtr();
	void change_Add_mtr(int* i, bool num);
	bool return_Add_mtr(int* i);
	~Add_mtr();


private:
	int N;
	bool* pMatr;
};

class Answer
{
public:
	Answer(int& size);
	~Answer();
	void init_Answer(int* i, int j, int* num);
	void init_Answer(int num);
	int return_size_Answer();
	int return_answer();
	int& operator()(int, int);
private:
	int N;
	int answer;
	int** Answer_mtr;
};

class Algorithm
{
public:
	void branches_and_boundaries(Graph& graph, Answer& Answer_mtr, Add_mtr& vertex_str, Add_mtr& vertex_col, Add_mtr& vertex_answer_col, int* N);
	void comparison_min(int* function, int* function_min, int* i_answer, int* j_answer, int* i, int* j);
	void comparison(int* function_str, int* function_col, int* i_answer, int* j_answer, int* i, int* j);
private:
};

void record_file(Answer& Answer_mtr);

istream& operator >> (std::istream& in, Graph& graph)
{
	for (int i = 0; i < graph.return_size_graph(); i++)
		for (int j = 0; j < graph.return_size_graph(); j++)
			in >> graph(i, j);
	return(in);
}

ostream& operator << (ostream& ostr, Graph& graph)
{
	for (int i = 0; i < graph.return_size_graph(); i++)
	{
		for (int j = 0; j < graph.return_size_graph(); j++)
		{
			ostr << graph(i, j) << "\t";
		}
		ostr << "\n";
	}
	return(ostr);
}

int& Graph::operator()(int i, int j)
{
	return (pGraph[i][j]);
}

ostream& operator << (ostream& ostr, Answer& Answer_mtr)
{
	ostr << "Минимальное назанчение равно: " << Answer_mtr.return_answer() << "\n";
	ostr << "\tМножество X" << "\tМножество Y" << "\n";
	for (int i = 0; i < Answer_mtr.return_size_Answer(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			ostr << "\t" << Answer_mtr(i, j) + 1 << "\t";
		}
		ostr << "\n";
	}
	return(ostr);
}

int& Answer::operator()(int i, int j)//перегрузка круглых скобок для матрицы.
{                             // Если m - матрица, то m(i,j) будет
	return (Answer_mtr[i][j]);  //означать i,j-тый элемент матрицы
}

void main()
{
	setlocale(LC_ALL, "RUS");

	const string path = "MyFile.txt";

	fstream fin(path, fstream::in);

	if (!fin.is_open())
	{
		cout << "Файл не открыт." << endl;
	}
	else
	{

		if (!fin.eof())
		{
			int num;
			fin >> num;

			Graph graph(num);

			fin >> graph;

			cout << graph;


			Add_mtr vertex_str(num);
			Add_mtr vertex_col(num);
			Add_mtr vertex_answer_col(num);

			Answer Answer_mtr(num);

			Algorithm algorithm;
			algorithm.branches_and_boundaries(graph, Answer_mtr, vertex_str, vertex_col, vertex_answer_col, &num);
			cout << Answer_mtr;
			record_file(Answer_mtr);
		}
		else
		{
			cout << "Файл пуст " << endl;
		}
	}
	fin.close();
}

Graph::Graph(int& size)
{
	this->N = size;
	init_Graph();
}

void Graph::init_Graph()
{
	if (N != 0)
	{
		pGraph = (int**)new int* [N];
		for (int i = 0; i < N; i++)
		{
			pGraph[i] = (int*)new int[N];
		}
	}
}

Graph::~Graph()
{
	for (int i = 0; i < N; i++) {
		delete[] pGraph[i];
	}
	delete[] pGraph;
}

int Graph::return_size_graph()
{
	return N;
}

int Graph::return_Graph(int* i, int* j)
{
	return pGraph[*i][*j];
}

Add_mtr::Add_mtr(int& size)
{
	this->N = size;
	init_Add_mtr();
}

void Add_mtr::init_Add_mtr()
{
	pMatr = (bool*)new bool* [N];
	for (int i = 0; i < N; i++)
	{
		change_Add_mtr(&i, true);
	}
}

void Add_mtr::change_Add_mtr(int* i, bool num)
{
	pMatr[*i] = num;
}

bool Add_mtr::return_Add_mtr(int* i)
{
	return pMatr[*i];
}

Add_mtr::~Add_mtr()
{
	delete[] pMatr;
}

Answer::Answer(int& size)
{
	answer = 0;

	this->N = size;

	if (N != 0)
	{
		Answer_mtr = (int**)new int* [N];
		for (int i = 0; i < N; i++)
		{
			Answer_mtr[i] = (int*)new int[2];
		}
	}
}

Answer::~Answer()
{
	for (int i = 0; i < N; i++) {
		delete[] Answer_mtr[i];
	}
	delete[] Answer_mtr;
}

void Answer::init_Answer(int* i, int j, int* num)
{
	Answer_mtr[*i][j] = *num;
}

void Answer::init_Answer(int num)
{
	answer += num;
}

int Answer::return_size_Answer()
{
	return N;
}

int Answer::return_answer() {
	return answer;
}

void Algorithm::branches_and_boundaries(Graph& graph, Answer& Answer_mtr, Add_mtr& vertex_str, Add_mtr& vertex_col, Add_mtr& vertex_answer_col, int* N)
{
	int Str_min = 0;
	int Col_min = 0;
	int i_answer = INT_MIN;
	int j_answer = INT_MIN;
	for (int i_vertex = 0; i_vertex < *N; i_vertex++) {
		if (i_vertex != *N - 1) {
			vertex_str.change_Add_mtr(&i_vertex, false);
			int function_str_min = INT_MAX;
			int function_col_min = INT_MAX;
			int i_answer_str = 0;
			int j_answer_str = 0;
			int i_answer_col = 0;
			int j_answer_col = 0;
			for (int j_vertex = 0; j_vertex < *N; j_vertex++)
			{
				int function_str = 0;
				int function_col = 0;
				vertex_col.change_Add_mtr(&j_vertex, false);
				for (int i = 0; i < *N; i++)
				{
					int str_Min = INT_MAX;
					int col_Min = INT_MAX;
					bool check_1 = false;
					bool check_2 = false;
					for (int j = 0; j < *N; j++)
					{
						if ((vertex_str.return_Add_mtr(&i) && vertex_col.return_Add_mtr(&j)) && vertex_answer_col.return_Add_mtr(&j))
						{
							if (graph.return_Graph(&i, &j) < str_Min) {
								str_Min = graph.return_Graph(&i, &j);
								check_1 = true;
							}
						}
						if ((vertex_str.return_Add_mtr(&j) && vertex_col.return_Add_mtr(&i)) && vertex_answer_col.return_Add_mtr(&j)) {
							if (graph.return_Graph(&j, &i) < col_Min) {
								col_Min = graph.return_Graph(&j, &i);
								check_2 = true;
							}
						}
					}
					if (check_1) {
						Str_min += str_Min;
					}
					if (check_2) {
						Col_min += col_Min;
					}
				}

				if (vertex_answer_col.return_Add_mtr(&j_vertex))
				{
					function_str = graph.return_Graph(&i_vertex, &j_vertex) + Str_min;
					function_col = graph.return_Graph(&i_vertex, &j_vertex) + Col_min;
					comparison_min(&function_str, &function_str_min, &i_answer_str, &j_answer_str, &i_vertex, &j_vertex);
					comparison_min(&function_col, &function_col_min, &i_answer_col, &j_answer_col, &i_vertex, &j_vertex);
				}
				Str_min = 0;
				Col_min = 0;
				if (vertex_answer_col.return_Add_mtr(&j_vertex))
				{
					comparison(&function_str_min, &function_col_min, &i_answer, &j_answer, &i_answer_col, &j_answer_col);
					comparison(&function_col_min, &function_str_min, &i_answer, &j_answer, &i_answer_str, &j_answer_str);
				}
				vertex_col.change_Add_mtr(&j_vertex, true);
			}
			vertex_answer_col.change_Add_mtr(&j_answer, false);
			Answer_mtr.init_Answer(graph.return_Graph(&i_answer, &j_answer));
			Answer_mtr.init_Answer(&i_vertex, 0, &i_answer);
			int j_j = j_answer + *N;
			Answer_mtr.init_Answer(&i_vertex, 1, &j_j);
		}
		else
		{
			for (int i = 0; i < *N; i++) {
				for (int j = 0; j < *N; j++) {
					if (vertex_str.return_Add_mtr(&i) && vertex_answer_col.return_Add_mtr(&j)) {
						Answer_mtr.init_Answer(graph.return_Graph(&i, &j));
						Answer_mtr.init_Answer(&i, 0, &i);
						int j_j = j + *N;
						Answer_mtr.init_Answer(&i, 1, &j_j);
					}
				}
			}
		}
	}

}

void Algorithm::comparison_min(int* function, int* function_min, int* i_answer, int* j_answer, int* i, int* j)
{
	if (*function < *function_min)
	{
		*function_min = *function;
		*i_answer = *i;
		*j_answer = *j;
	}
}

void Algorithm::comparison(int* function_str, int* function_col, int* i_answer, int* j_answer, int* i, int* j)
{
	if (*function_str <= *function_col)
	{
		*i_answer = *i;
		*j_answer = *j;
	}
}

void record_file(Answer& Answer_mtr)
{
	const string ans = "MyAnswer.txt";

	ofstream fout(ans, ios::out);

	if (!fout.is_open())
	{
		cout << "Файл не открыт." << endl;
	}
	else
	{
		fout << Answer_mtr;

		cout << "Ответ записан в файл MyAnswer.txt\n";
		cout << "Путь: C:\\Users\\Bernkastel\\Desktop\\Спидозные козявки\\КодОсапрррррРРРРрРрРРР\\бляя\\осапр\\осапр\\MyAnswer.txt \n";
	}
	fout.close();
}
