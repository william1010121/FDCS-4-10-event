
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<filesystem>
#define LL long long
#define f first
#define s second
#define V vector
#define all(v) v.begin(), v.end()
using namespace std;

const int mod = 998244353;


V<V<int>> story_list = { //can put some of the value in it
    {
      -1  //null index
    },
    {
        0, 1, 2, 3, 4 // index 0 is null
    },
    {
        0, 1, 2, 3, 4 //index 0 is null
    }
};


V<V<bool>> story_problem_exist = {
    {
        0 //null index
    },
    {
        0, 0, 0, 0, 0//index 0 is null
    },
    {
        0, 0, 0, 0, 0//index 0 is null
    }
};

/*string replace(string st, V<char> vc={'\n'}, char replace_to) {
	for(auto &i : st) {
		for(auto &j : vc) {
			if( i == j ) i = replace_to;
		}
	}
	return st;
}*/

int story_chapter_first, story_chapter_second; // chapter.f, chapter.s
void read_story(fstream &file) {
	string text;
	while (getline(file, text)) {
		cout << text << '\n';
		char ch;
		do {
			ch = cin.get();
		} while (ch != '\n');
	}
}
string read(fstream &file, bool f = 1) {
	string text, ret;
	while (getline(file, text)) {
		if (f) cout << text << '\n';
		ret += text + "\n";
	}
	return ret;
}

void wait_for(int time) {
	Sleep(time);
}


bool exist(int chapter_first, int chapter_second) { //chapter.f, chapter.s
    return (chapter_first < story_list.size() && chapter_second < story_list[chapter_first].size());
}
struct story {
	fstream file;
	pair<int, int> chapter;
	bool problem_exist;

	//static pair<int, int> get_chapter() {return this->chapter;}
	//V<string> story_txt;
	struct problem {
		string text, ans;
		bool check(string your_ans) {
			return ans == your_ans;
		}

		void input_ans() {
			//int sec = 20;
			string your_ans;
			cout << "input your answer:";
			getline(cin, your_ans);
			while (!check(your_ans)) {
				cout << "WA" ; wait_for(3000); cout << "\ninput your answer:";
				getline(cin, your_ans);
			}
			cout << "AC\n", Sleep(1000);
		}

		void init(pair<int, int> chapter_copy) {
			fstream problem_file, ans_file;
			problem_file.open("p_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			ans_file.open("a_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			read(problem_file, 1);
			ans = read(ans_file, 0);
		}
		//problem(pair<int, int> _chapter): text(""), ans("") {};
	} story_problem;

	map<pair<int, int>, story> to_story;

	struct selection {
		//V<string> choice;
		map<string, pair<int, int>> to_ch;


		//(A)...
		pair<int, int> check(pair<int, int> chapter_copy) {
			string st;
			do {
				cout << "you can only input ONE CAPITAL letter and the choice should on the list.\ninput your choice:";
				getline(cin , st);
			} while (st.size() != 1 || (st[0] >= 65 && st[0] <= 90) || exist(chapter_copy.f+1, int(st[0]-'A')));
			return make_pair(chapter_copy.f + 1, int(st[0] - 64));
		}

		void init(pair<int, int> chapter_copy) {
			cout << "selection_init " << chapter_copy.f << ' ' << chapter_copy.s << '\n';
			fstream selection_file, choice_file;
			selection_file.open("s_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			choice_file.open("c_" + to_string(chapter_copy.f) + "-" + to_string(chapter_copy.s) + ".txt", ios::in);
			read(selection_file);
			read(choice_file);
		}

	} story_selection;
	bool init_txt(pair<int, int> p) {
		file.open(to_string(p.f) + "-" + to_string(p.s) + ".txt", ios::in);
		if (file.is_open()) return true;
		return false;
	}

	void see() {
		string text;
		while (getline(file, text)) {
			char ch;
			cout << text << '\n';
			do {
				ch = cin.get();
			} while (ch != '\n');
		}
	}

	bool run_story() {
		see();
		if (problem_exist) story_problem.input_ans();
		story_selection.init(chapter);
		//story_selection.output();
		story_selection.check(chapter);
		return true;
	}
	story(pair<int, int> _chapter, bool _problem_exist = false): chapter(_chapter), problem_exist(_problem_exist) {
		init_txt(chapter);
		//see();
		story_problem.init(chapter);
		//story_problem.input_ans();
	}
	story(){};

};


int stories_init() {
    /*
        return -1; graph can't initialize
        return 1; story is finish
    */
    if( story_list.size() != story_problem_exist.size() ) {
        return -1;
    }
    for(int i = 0; i < story_list.size(); ++i) {
        if(story_list[i].size() != story_problem_exist[i].size())
            return -1;
    }
    vector<vector<story>> graph;
    for(int i = 0; i < story_list.size(); ++i) {
        graph.push_back(V<story>(0));
        for(int j = 0; j < story_list[i].size(); ++j) {
            graph[i].push_back(story(make_pair(i, j), story_problem_exist[i][j]));
        }
    }

    return 1;
}
int main() {
	//cin.tie(0)->sync_with_stdio(0);
    int stories_init_status = stories_init();
    if(stories_init_status == -1) {
        cout << "init flase\n";
    }
    else if(stories_init_status == 1) {
        cout << "init complete\n";
    }
    else {
        cout << "unbeknow problem\n";
    }

	return 0;
}
