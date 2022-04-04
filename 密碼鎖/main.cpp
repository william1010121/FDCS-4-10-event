#include<bits/stdc++.h>
#include<windows.h>

using namespace std;


const int time_punishment = 3 * 1000; //time_set ms
const int accept_password[4] = {0, 9, 2, 4};
constexpr WORD seleted_color = 0x0C;
constexpr WORD unseleted_color = 0x0F;
int now_control = 0; // 0 ~ 4


void one_line_output(string st, bool special_font = false, int position = -1, int color = -1) {
    cout << "\r";
    SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE) , unseleted_color);

    if( special_font ) {
        for(int i = 0; i <st.size(); i++) {
            if(i == position) {
                HANDLE h0ut = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h0ut, seleted_color);
                cout << st[i];
                SetConsoleTextAttribute(h0ut, unseleted_color);
            }
            else
                cout <<st[i];

        }
    }
    else {
        cout << st;
    }
    cout << "                              ";
    return;
}

void wait_for(int time) { //counted by ms
    int sec = time/1000;
    while( sec ) {
        one_line_output("you need to wait for " + to_string(sec--) + " seconds");
        Sleep(1000);
    }
}
void gotoxy (int x,  int y) {
    COORD pos = {x, y};
    HANDLE h0ut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h0ut, pos);
}

int  mouse_click() {
    int ans = 0;
    if(
       (GetAsyncKeyState( VK_UP ) & 1) ||
       (GetAsyncKeyState( int('W') ) & 1) ||
        (GetAsyncKeyState( int('w') ) & 1)
    ) ans += 1;

    if(
       (GetAsyncKeyState( VK_DOWN ) & 1) ||
       (GetAsyncKeyState( int('S') ) & 1) ||
        (GetAsyncKeyState( int('s') ) & 1)
    ) ans -= 1;
    return ans;
}

int now_row() {
    if( GetAsyncKeyState( 0x0d ) ) {
        return -1;
    }
    if(
        (GetAsyncKeyState( int('D') ) & 1) ||
        (GetAsyncKeyState( int('d') ) & 1) ||
        (GetAsyncKeyState( VK_RIGHT ) & 1)
    ) {
        if(now_control != 3) ++now_control;
        return 1;
    }

    if(
        (GetAsyncKeyState( int('A') ) & 1) ||
        (GetAsyncKeyState( int('a') ) & 1) ||
        (GetAsyncKeyState( VK_LEFT ) & 1)
    ) {
        if(now_control != 0) --now_control;
        return 1;
    }

    return 0;
}

bool run_guess_password() {

    int your_password[4] = {0, 0, 0, 0};

    gotoxy(0, 0);
    cout << "-----------------\n";
    gotoxy(0, 1);
    cout << "|   |   |   |   |\n";
    gotoxy(0, 3);
    cout << "|   |   |   |   |\n";
    gotoxy(0, 4);
    cout << "-----------------\n";


    gotoxy(0, 6);
    cout << "your can use left click to +1, right click to -1\n";
    cout << "(A) (a) move left and (D) (d) to move right\n";
    cout << "push enter to end it";
    /*
    int left_click_cnt = 0;
    int right_click_cnt = 0;
    while( true ) {
        Sleep(30);
        if( GetAsyncKeyState(VK_LBUTTON) & 1) one_line_output("left clicked " + to_string(++left_click_cnt));
        else if(GetAsyncKeyState(VK_RBUTTON) & 1) one_line_output("right clicked " + to_string(++right_click_cnt));
        else if(GetAsyncKeyState(int('E'))) break;
    }
    */

    while(true) {
        Sleep(30);
        int get_status = now_row(); //test if it need to change the now_control

        if(get_status == -1) {
            break; // if user put enter
        }
        else if(get_status == 1) {
        	continue;
		}

        gotoxy(0, 2);
        int change_value = mouse_click();
        if(change_value == 1 && your_password[now_control] != 9) ++your_password[now_control];
        if(change_value == -1 && your_password[now_control] != 0) --your_password[now_control];
        string st = "| ";
        for (auto &i : your_password) st += (to_string(i) + " | ");


        //3 + 4n
        one_line_output(st, true, 2 + (4*now_control), 12);
    }

    bool pass = true;
    for(int i = 0; i < 4; i++) {
        pass &= (your_password[i] == accept_password[i]);
    }
    return pass;
}


int main () {
    while(run_guess_password() != true) {
        system("cls");
        cout << "guess false" << '\n';
        gotoxy(0, 2);
        wait_for(time_punishment);
        system("cls");
    }
    system("cls");
    cout << "accept guess " ;
    system("pause");
}
